#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>
#include <cstdlib>

using namespace std;

class Seat {
private:
    string seatNumber;
    int price;
    bool isBooked;

public:
    Seat(string number, int seatPrice) : seatNumber(number), price(seatPrice), isBooked(false) {}

    string getSeatNumber() const {
        return seatNumber;
    }

    string getIsBookedAsString() const {
        return isBooked ? "true" : "false";
    }

    int getPrice() const {
        return price;
    }

    bool getIsBooked() const {
        return isBooked;
    }

    void bookSeat() {
        isBooked = true;
    }

    void freeSeat() {
        isBooked = false;
    }
};

class Ticket {
private:
    string flightNumber;
    string date;
    string seatNumber;
    string passengerName;
    int ticketId;

public:
    Ticket(const string& flight, const string& ticketDate, const string& seat, const string& passenger, int id)
            : flightNumber(flight), date(ticketDate), seatNumber(seat), passengerName(passenger), ticketId(id) {}

    string getFlight() const {
        return flightNumber;
    }

    string getDate() const {
        return date;
    }

    string getSeatNum() const {
        return seatNumber;
    }

    string getPassengerName() const {
        return passengerName;
    }

    int getID() const {
        return ticketId;
    }

    void displayTicketInfo() const {
        cout << "Ticket Information:\n";
        cout << "Flight Number: " << flightNumber << "\n";
        cout << "Date: " << date << "\n";
        cout << "Seat Number: " << seatNumber << "\n";
        cout << "Passenger Name: " << passengerName << "\n";
        cout << "Ticket ID: " << ticketId << "\n";
    }
};

class Airplane {
private:
    int seatsPerRow;
    string flightNumber;
    string date;
    vector<Seat> seats;
    vector<Ticket> tickets;

public:
    Airplane(int seatsPerRow, const string& flightNumber, const string& flightDate, const vector<tuple<int, int, int>>& seatPriceRanges)
            : seatsPerRow(seatsPerRow), flightNumber(flightNumber), date(flightDate) {
        createSeats(seatPriceRanges);
    }

    string getFlight() const {
        return flightNumber;
    }

    string getDate() const {
        return date;
    }

    vector<Seat> getSeats() const {
        return seats;
    }

    vector<Ticket> getTickets() const {
        return tickets;
    }

    bool bookSeat(const string& seatNumber, const string& passengerName, int& ticketId) {
        for (auto& seat : seats) {
            if (seat.getSeatNumber() == seatNumber && !seat.getIsBooked()) {
                seat.bookSeat();
                ticketId = rand() % 10000 + 1;  // Generate a random ticket ID
                Ticket ticket(flightNumber, date, seatNumber, passengerName, ticketId);
                tickets.push_back(ticket);
                return true;
            }
        }
        return false;
    }

private:
    void createSeats(const vector<tuple<int, int, int>>& seatPriceRanges) {
        for (const auto& range : seatPriceRanges) {
            int start = get<0>(range);
            int end = get<1>(range);
            int price = get<2>(range);

            for (int row = start; row <= end; ++row) {
                for (int seatInRow = start; seatInRow <= end; ++seatInRow) {
                    char seatLetter = 'A' + (seatInRow - 1) % seatsPerRow;
                    string seatNumber = to_string(row) + seatLetter;
                    Seat seat(seatNumber, price);
                    seats.push_back(seat);
                }
            }
        }
    }
};

class ConfigReader {
public:
    static vector<Airplane> readConfig(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            exit(EXIT_FAILURE);
        }

        vector<Airplane> airplanes;

        string line;
        while (getline(file, line)) {
            istringstream iss(line);

            string date, flightNumber;
            int row;
            iss >> date >> flightNumber >> row;

            char delimiter;
            int start, end, price;
            vector<tuple<int, int, int>> seatPriceRanges;
            while (iss >> start >> delimiter >> end >> price) {
                seatPriceRanges.emplace_back(start, end, price);

                if (iss.peek() == '$') {
                    iss.ignore();
                }
            }
            airplanes.emplace_back(row, flightNumber, date, seatPriceRanges);
        }

        return airplanes;
    }
};

class Processes {
private:
    vector<Airplane> airplanes;

public:
    void initialize() {
        string filename = "config.txt";

        airplanes = ConfigReader::readConfig(filename);
    }

    void processCommands() {
        while (true) {
            string command;
            cout << "Enter command: ";
            getline(cin, command);

            istringstream iss(command);
            string cmd;
            iss >> cmd;

            if (cmd == "exit") {
                cout << "Exiting...\n";
                break;
            } else if (cmd == "check") {
                checkAvailability(iss);
            } else if (cmd == "book") {
                bookTicket(iss);
            } else {
                cout << "Invalid command. Try again.\n";
            }
        }
    }

private:
    void checkAvailability(istringstream& iss) {
        string flightDate, flightNumber;
        iss >> flightDate >> flightNumber;

        bool flightFound = false;

        for (const auto& airplane : airplanes) {
            if (airplane.getDate() == flightDate && airplane.getFlight() == flightNumber) {
                flightFound = true;

                cout << "Available seats for Flight " << flightNumber << " on " << flightDate << ":\n";

                vector<Seat> seats = airplane.getSeats();
                vector<Ticket> tickets = airplane.getTickets();

                for (const auto& seat : seats) {
                    bool seatBooked = false;

                    for (const auto& ticket : tickets) {
                        if (ticket.getSeatNum() == seat.getSeatNumber()) {
                            seatBooked = true;
                            break;
                        }
                    }

                    if (!seatBooked) {
                        cout << seat.getSeatNumber() << " $" << seat.getPrice() << "\n";
                    }
                }
                break;
            }
        }

        if (!flightFound) {
            cout << "Flight not found.\n";
        }
    }


    void bookTicket(istringstream& iss) {
        string flightDate, flightNumber, seatNumber, passengerName;
        iss >> flightDate >> flightNumber >> seatNumber >> passengerName;

        bool flightFound = false;
        int ticketId;

        for (auto& airplane : airplanes) {
            if (airplane.getDate() == flightDate && airplane.getFlight() == flightNumber) {
                flightFound = true;

                if (airplane.bookSeat(seatNumber, passengerName, ticketId)) {
                    cout << "Confirmed with ID " << ticketId << "\n";
                } else {
                    cout << "Seat " << seatNumber << " is already booked.\n";
                }
                break;
            }
        }

        if (!flightFound) {
            cout << "Flight not found.\n";
        }
    }
};

int main() {
    Processes processes;
    processes.initialize();
    processes.processCommands();

    return 0;
}

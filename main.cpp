#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>

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

class Airplane {
private:
    int seatsPerRow;
    string flightNumber;
    string date;
    vector<Seat> seats;

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

int main() {
    vector<Airplane> airplanes = ConfigReader::readConfig("config.txt");

    for (const auto& airplane : airplanes) {
        cout << "Airplane Information:\n";
        cout << "Flight Number: " << airplane.getFlight() << "\n";
        cout << "Date: " << airplane.getDate() << "\n";

        vector<Seat> seats = airplane.getSeats();

        cout << "Seat Information:\n";
        for (const auto& seat : seats) {
            cout << "Seat Number: " << seat.getSeatNumber() << " | Price: $" << seat.getPrice() << " | Booked:" << seat.getIsBookedAsString() << "\n";
        }
        cout << "\n";
    }

    return 0;
}
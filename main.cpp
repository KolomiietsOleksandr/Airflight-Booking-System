#include <iostream>
#include <string>

using namespace std;

class Seat {
private:
    string seatNumber;
    int price;
    bool isOccupied;

public:
    Seat(string number, double seatPrice) : seatNumber(number), price(seatPrice), isOccupied(false) {}

    string getSeatNumber() const {
        return seatNumber;
    }

    double getPrice() const {
        return price;
    }

    bool getIsOccupied() const {
        return isOccupied;
    }

    void occupySeat() {
        isOccupied = true;
    }

    void freeSeat() {
        isOccupied = false;
    }
};

class Airplane {
private:
    int totalSeats;
    string flightNumber;
    string date;
    vector<Seat> seats;

public:
    Airplane(int seatsCount, const string& flight, const string& flightDate)
            : totalSeats(seatsCount), flightNumber(flight), date(flightDate) {}

    int getTotal() const {
        return totalSeats;
    }

    string getFlight() const {
        return flightNumber;
    }

    string getDate() const {
        return date;
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
    Ticket(const string& flight, const string& ticketDate, string& seat, const string& passenger, int id)
            : flightNumber(flight), date(ticketDate), seatNumber(seat), passengerName(passenger), ticketId(id) {}

    string getFlight() const{
        return flightNumber;
    }

    string getDate() const{
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



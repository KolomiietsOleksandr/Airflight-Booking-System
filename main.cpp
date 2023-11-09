#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

class Seat {
private:
    std::string seatNumber;
    int price;
    bool isAvailable;

public:
    Seat(std::string  number, int price, bool available)
            : seatNumber(std::move(number)), price(price), isAvailable(available) {}

    const std::string& getSeatNumber() const {
        return seatNumber;
    }

    int getSeatPrice() const {
        return price;
    }

    bool isSeatAvailable() const {
        return isAvailable;
    }

    bool bookSeat() {
        return isAvailable = false;
    }
};

class AirFlight {
private:
    std::string date;
    std::string flightNumber;
    int totalSeats;
    std::vector<Seat> availableSeats;

public:
    AirFlight(std::string  date, std::string  flightNumber, int seats, const std::vector<Seat>& available)
            : date(std::move(date)), flightNumber(std::move(flightNumber)), totalSeats(seats), availableSeats(available) {}

    const std::string& getDate() const {
        return date;
    }

    const std::string& getFlightNumber() const {
        return flightNumber;
    }

    std::vector<Seat> getAvailableSeats() const {
        std::vector<Seat> result;
        std::copy_if(availableSeats.begin(), availableSeats.end(), std::back_inserter(result),
                     [](const Seat& seat) { return seat.isSeatAvailable(); });
        return result;
    }
};

class Ticket {
    int id;
    std::string date;
    std::string flightNumber;
    std::string passengerName;
    Seat seat;

public:
    Ticket(const std::string& date, const std::string& flightNumber, const std::string& passengerName, Seat seat, const int id)
            : date(date), flightNumber(flightNumber), passengerName(passengerName), seat(std::move(seat)), id(id) {}

    int getID() const {
        return id;
    }
};


class Passenger{
    std::string name;
    std::vector<Ticket> tickets;

public:
    Passenger(const std::string& name): name(name){}

    void addTicket(const Ticket& ticket) {
        tickets.push_back(ticket);
    }

    std::string getName() const {
        return name;
    }
};

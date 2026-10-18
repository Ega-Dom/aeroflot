#include "AEROFLOT.h"

#include <iostream>

#include "Exceptions.h"
#include "Input.h"

AEROFLOT::AEROFLOT() : destination("unknown"), flightNumber(1), planeType("unknown") {
    std::cout << "[AEROFLOT] default constructor called" << std::endl;
}

AEROFLOT::AEROFLOT(const std::string& dest, int number, const std::string& type)
    : destination(), flightNumber(1), planeType() {
    setDestination(dest);
    setFlightNumber(number);
    setPlaneType(type);
    std::cout << "[AEROFLOT] parameterized constructor called (flight "
              << flightNumber << ")" << std::endl;
}

AEROFLOT::AEROFLOT(const AEROFLOT& other)
    : destination(other.destination),
      flightNumber(other.flightNumber),
      planeType(other.planeType) {
    std::cout << "[AEROFLOT] copy constructor called (flight "
              << flightNumber << ")" << std::endl;
}

AEROFLOT::~AEROFLOT() {
    std::cout << "[AEROFLOT] destructor called (flight "
              << flightNumber << ")" << std::endl;
}

AEROFLOT& AEROFLOT::operator=(const AEROFLOT& other) {
    if (this != &other) {
        destination = other.destination;
        flightNumber = other.flightNumber;
        planeType = other.planeType;
    }
    std::cout << "[AEROFLOT] copy assignment operator called" << std::endl;
    return *this;
}

bool AEROFLOT::operator==(const AEROFLOT& other) const {
    return destination == other.destination &&
           flightNumber == other.flightNumber &&
           planeType == other.planeType;
}

bool AEROFLOT::operator!=(const AEROFLOT& other) const {
    return !(*this == other);
}

bool AEROFLOT::operator<(const AEROFLOT& other) const {
    return flightNumber < other.flightNumber;
}

const std::string& AEROFLOT::getDestination() const { return destination; }

int AEROFLOT::getFlightNumber() const { return flightNumber; }

const std::string& AEROFLOT::getPlaneType() const { return planeType; }

void AEROFLOT::setDestination(const std::string& value) {
    destination = checkNotEmpty(value, "destination");
}

void AEROFLOT::setFlightNumber(int value) {
    if (value <= 0) {
        throw InvalidInputException("Flight number must be a positive integer");
    }
    flightNumber = value;
}

void AEROFLOT::setPlaneType(const std::string& value) {
    planeType = checkNotEmpty(value, "plane type");
}

void AEROFLOT::edit() {
    while (true) {
        std::cout << "Edit flight: 1 - destination, 2 - flight number, "
                     "3 - plane type, 0 - finish" << std::endl;
        int choice = readInt("Field number: ");
        if (choice == 0) {
            return;
        } else if (choice == 1) {
            setDestination(readField("New destination: ", "destination"));
        } else if (choice == 2) {
            while (true) {
                try {
                    setFlightNumber(readInt("New flight number: "));
                    break;
                } catch (const InvalidInputException& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }
        } else if (choice == 3) {
            setPlaneType(readField("New plane type: ", "plane type"));
        } else {
            std::cout << "Unknown field number" << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight) {
    os << "[AEROFLOT] destination: " << flight.getDestination()
       << "; flight number: " << flight.getFlightNumber()
       << "; plane type: " << flight.getPlaneType();
    return os;
}

std::istream& operator>>(std::istream& is, AEROFLOT& flight) {
    std::string dest = readFieldFrom(is, "Destination: ", "destination");
    int number = 0;
    while (true) {
        number = readIntFrom(is, "Flight number: ");
        if (number > 0) {
            break;
        }
        std::cout << "Error: Flight number must be a positive integer" << std::endl;
    }
    std::string type = readFieldFrom(is, "Plane type: ", "plane type");
    flight.setDestination(dest);
    flight.setFlightNumber(number);
    flight.setPlaneType(type);
    return is;
}

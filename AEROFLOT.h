#ifndef AEROFLOT_H
#define AEROFLOT_H

#include <iosfwd>
#include <string>

// One flight record: destination, flight number and plane type.
class AEROFLOT {
private:
    std::string destination;   // name of the destination
    int flightNumber;          // flight number (positive integer)
    std::string planeType;     // type of the plane

public:
    AEROFLOT();
    AEROFLOT(const std::string& destination, int flightNumber,
             const std::string& planeType);
    AEROFLOT(const AEROFLOT& other);
    ~AEROFLOT();

    AEROFLOT& operator=(const AEROFLOT& other);
    bool operator==(const AEROFLOT& other) const;
    bool operator!=(const AEROFLOT& other) const;
    // Records are ordered by flight number.
    bool operator<(const AEROFLOT& other) const;

    // get-functions
    const std::string& getDestination() const;
    int getFlightNumber() const;
    const std::string& getPlaneType() const;

    // set-functions (throw InvalidInputException for wrong values)
    void setDestination(const std::string& value);
    void setFlightNumber(int value);
    void setPlaneType(const std::string& value);

    // Interactive editing of any field of the record.
    void edit();
};

// Insertion: prints the record on the screen.
std::ostream& operator<<(std::ostream& os, const AEROFLOT& flight);

// Extraction: asks the user for all fields (prompts are shown on the screen,
// wrong values are asked again). The object changes only if all fields are read.
std::istream& operator>>(std::istream& is, AEROFLOT& flight);

#endif

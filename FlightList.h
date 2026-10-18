#ifndef FLIGHTLIST_H
#define FLIGHTLIST_H

#include <iosfwd>
#include <string>

#include "AEROFLOT.h"

// Container of AEROFLOT records: dynamic array of pointers (no STL containers).
// The list owns the objects: it deletes them in removeAt, clear and destructor.
class FlightList {
private:
    AEROFLOT** items;   // dynamic array of pointers to records
    int count;          // number of records
    int capacity;       // size of the allocated array

    void grow();                          // doubles the capacity
    void checkIndex(int index, int maxValid, const std::string& operation) const;

public:
    FlightList();
    explicit FlightList(int initialCapacity);
    FlightList(const FlightList& other);
    ~FlightList();

    FlightList& operator=(const FlightList& other);
    // Access to a record by index (0..count-1), throws IndexOutOfRangeException.
    AEROFLOT& operator[](int index);
    const AEROFLOT& operator[](int index) const;
    // Adds a copy of the record to the end of the list.
    FlightList& operator+=(const AEROFLOT& flight);

    int size() const;
    bool isEmpty() const;

    // The list takes ownership of 'item'. NullPointerException for a null pointer.
    void add(AEROFLOT* item);                       // to the end
    void insertAt(int index, AEROFLOT* item);       // to any position 0..count
    void insertSorted(AEROFLOT* item);              // keeps ascending order
    void removeAt(int index);
    void clear();

    bool isSorted() const;
    void sort();   // ascending order of flight numbers (stable insertion sort)

    // Prints flight numbers and plane types of flights to the destination.
    // Returns the number of flights found.
    int printByDestination(std::ostream& os, const std::string& destination) const;
};

// Prints all records with numbers (1, 2, ...).
std::ostream& operator<<(std::ostream& os, const FlightList& list);

#endif

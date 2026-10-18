#include "FlightList.h"

#include <iostream>

#include "Exceptions.h"

namespace {

// ASCII case-insensitive comparison of two strings.
bool sameText(const std::string& a, const std::string& b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (std::string::size_type i = 0; i < a.size(); ++i) {
        char x = a[i];
        char y = b[i];
        if (x >= 'A' && x <= 'Z') x = static_cast<char>(x - 'A' + 'a');
        if (y >= 'A' && y <= 'Z') y = static_cast<char>(y - 'A' + 'a');
        if (x != y) {
            return false;
        }
    }
    return true;
}

}  // namespace

FlightList::FlightList() : items(new AEROFLOT*[4]), count(0), capacity(4) {
    std::cout << "[FlightList] default constructor called" << std::endl;
}

FlightList::FlightList(int initialCapacity) : items(0), count(0), capacity(0) {
    if (initialCapacity <= 0) {
        throw InvalidInputException("Capacity of the list must be positive");
    }
    items = new AEROFLOT*[initialCapacity];
    capacity = initialCapacity;
    std::cout << "[FlightList] parameterized constructor called (capacity "
              << capacity << ")" << std::endl;
}

FlightList::FlightList(const FlightList& other)
    : items(new AEROFLOT*[other.capacity]), count(0), capacity(other.capacity) {
    try {
        for (int i = 0; i < other.count; ++i) {
            items[i] = new AEROFLOT(*other.items[i]);
            ++count;
        }
    } catch (...) {
        for (int i = 0; i < count; ++i) {
            delete items[i];
        }
        delete[] items;
        throw;
    }
    std::cout << "[FlightList] copy constructor called (" << count
              << " records)" << std::endl;
}

FlightList::~FlightList() {
    clear();
    delete[] items;
    std::cout << "[FlightList] destructor called" << std::endl;
}

FlightList& FlightList::operator=(const FlightList& other) {
    if (this != &other) {
        // A temporary copy is made first: if copying fails, *this is unchanged.
        FlightList temp(other);
        AEROFLOT** tmpItems = items;
        items = temp.items;
        temp.items = tmpItems;
        int tmpCount = count;
        count = temp.count;
        temp.count = tmpCount;
        int tmpCap = capacity;
        capacity = temp.capacity;
        temp.capacity = tmpCap;
    }
    std::cout << "[FlightList] copy assignment operator called" << std::endl;
    return *this;
}

void FlightList::checkIndex(int index, int maxValid, const std::string& operation) const {
    if (count == 0 && maxValid == count) {
        throw EmptyListException(operation);
    }
    if (index < 0 || index >= maxValid) {
        throw IndexOutOfRangeException(index, maxValid);
    }
}

AEROFLOT& FlightList::operator[](int index) {
    checkIndex(index, count, "access a record");
    return *items[index];
}

const AEROFLOT& FlightList::operator[](int index) const {
    checkIndex(index, count, "access a record");
    return *items[index];
}

FlightList& FlightList::operator+=(const AEROFLOT& flight) {
    AEROFLOT* copy = new AEROFLOT(flight);
    try {
        add(copy);
    } catch (...) {
        delete copy;
        throw;
    }
    return *this;
}

int FlightList::size() const { return count; }

bool FlightList::isEmpty() const { return count == 0; }

void FlightList::grow() {
    int newCapacity = capacity * 2;
    AEROFLOT** bigger = new AEROFLOT*[newCapacity];
    for (int i = 0; i < count; ++i) {
        bigger[i] = items[i];
    }
    delete[] items;
    items = bigger;
    capacity = newCapacity;
}

void FlightList::add(AEROFLOT* item) {
    insertAt(count, item);
}

void FlightList::insertAt(int index, AEROFLOT* item) {
    if (item == 0) {
        throw NullPointerException("FlightList::insertAt");
    }
    if (index < 0 || index > count) {
        throw IndexOutOfRangeException(index, count + 1);
    }
    if (count == capacity) {
        grow();
    }
    for (int i = count; i > index; --i) {
        items[i] = items[i - 1];
    }
    items[index] = item;
    ++count;
}

void FlightList::insertSorted(AEROFLOT* item) {
    if (item == 0) {
        throw NullPointerException("FlightList::insertSorted");
    }
    int pos = count;
    // Insert after all records with a smaller or equal flight number.
    while (pos > 0 && *item < *items[pos - 1]) {
        --pos;
    }
    insertAt(pos, item);
}

void FlightList::removeAt(int index) {
    checkIndex(index, count, "delete a record");
    delete items[index];
    for (int i = index; i < count - 1; ++i) {
        items[i] = items[i + 1];
    }
    --count;
}

void FlightList::clear() {
    for (int i = 0; i < count; ++i) {
        delete items[i];
    }
    count = 0;
}

bool FlightList::isSorted() const {
    for (int i = 1; i < count; ++i) {
        if (*items[i] < *items[i - 1]) {
            return false;
        }
    }
    return true;
}

void FlightList::sort() {
    for (int i = 1; i < count; ++i) {
        AEROFLOT* current = items[i];
        int j = i - 1;
        while (j >= 0 && *current < *items[j]) {
            items[j + 1] = items[j];
            --j;
        }
        items[j + 1] = current;
    }
}

int FlightList::printByDestination(std::ostream& os, const std::string& destination) const {
    int found = 0;
    for (int i = 0; i < count; ++i) {
        if (sameText(items[i]->getDestination(), destination)) {
            os << "Flight number: " << items[i]->getFlightNumber()
               << "; plane type: " << items[i]->getPlaneType() << std::endl;
            ++found;
        }
    }
    return found;
}

std::ostream& operator<<(std::ostream& os, const FlightList& list) {
    for (int i = 0; i < list.size(); ++i) {
        os << (i + 1) << ". " << list[i] << "\n";
    }
    return os;
}

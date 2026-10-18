#include <iostream>
#include <new>
#include <string>

#include "AEROFLOT.h"
#include "Exceptions.h"
#include "FlightList.h"
#include "Input.h"
#include "TextProcessor.h"

namespace {

void printMenu() {
    std::cout << "\n===== AEROFLOT: flights =====\n"
              << "1 - Add flight (the list stays ordered by flight number)\n"
              << "2 - Insert flight at the chosen position\n"
              << "3 - Delete flight\n"
              << "4 - Edit flight\n"
              << "5 - Sort flights by flight number\n"
              << "6 - Show all flights\n"
              << "7 - Find flights by destination\n"
              << "8 - Copy the list (copy constructors demo)\n"
              << "9 - Print words starting with a vowel from a text file\n"
              << "10 - Compare two flights and copy one (operators ==, !=, <, =)\n"
              << "0 - Exit\n";
}

// Asks for a record number 1..maxValid and returns the index 0..maxValid-1.
int readIndex(const std::string& prompt, int maxValid) {
    int number = readInt(prompt);
    int index = number - 1;
    if (index < 0 || index >= maxValid) {
        throw IndexOutOfRangeException(index, maxValid);
    }
    return index;
}

void addFlight(FlightList& list) {
    AEROFLOT* flight = new AEROFLOT();
    try {
        std::cin >> *flight;
        list.insertSorted(flight);
    } catch (...) {
        delete flight;   // the list did not take the object
        throw;
    }
    std::cout << "Flight added, total flights: " << list.size() << std::endl;
}

// Reads the fields one by one and creates the record with the parameterized constructor.
AEROFLOT* readFlightByFields() {
    std::string destination = readField("Destination: ", "destination");
    while (true) {
        int number = readInt("Flight number: ");
        std::string planeType = readField("Plane type: ", "plane type");
        try {
            return new AEROFLOT(destination, number, planeType);
        } catch (const InvalidInputException& e) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << "Enter the flight number and the plane type again" << std::endl;
        }
    }
}

void insertFlight(FlightList& list) {
    int position = readIndex("Position for the new flight (1.."
                             + std::to_string(list.size() + 1) + "): ",
                             list.size() + 1);
    AEROFLOT* flight = readFlightByFields();
    try {
        list.insertAt(position, flight);
    } catch (...) {
        delete flight;
        throw;
    }
    std::cout << "Flight inserted at position " << (position + 1) << std::endl;
    if (!list.isSorted()) {
        std::cout << "Note: the order of flight numbers is broken, "
                     "use item 5 to sort the list" << std::endl;
    }
}

void deleteFlight(FlightList& list) {
    if (list.isEmpty()) {
        throw EmptyListException("delete a record");
    }
    int index = readIndex("Number of the flight to delete (1.."
                          + std::to_string(list.size()) + "): ", list.size());
    list.removeAt(index);
    std::cout << "Flight deleted, total flights: " << list.size() << std::endl;
}

void editFlight(FlightList& list) {
    if (list.isEmpty()) {
        throw EmptyListException("edit a record");
    }
    int index = readIndex("Number of the flight to edit (1.."
                          + std::to_string(list.size()) + "): ", list.size());
    list[index].edit();
    if (!list.isSorted()) {
        list.sort();
        std::cout << "The list was sorted again by flight number" << std::endl;
    }
}

void sortFlights(FlightList& list) {
    if (list.isEmpty()) {
        throw EmptyListException("sort");
    }
    list.sort();
    std::cout << "Flights are sorted by flight number" << std::endl;
}

void showFlights(const FlightList& list) {
    if (list.isEmpty()) {
        std::cout << "The list of flights is empty" << std::endl;
        return;
    }
    std::cout << list;
}

void findByDestination(const FlightList& list) {
    if (list.isEmpty()) {
        throw EmptyListException("search");
    }
    std::string destination = readField("Destination: ", "destination");
    int found = list.printByDestination(std::cout, destination);
    if (found == 0) {
        std::cout << "There are no flights to '" << destination << "'" << std::endl;
    }
}

void copyList(const FlightList& list) {
    FlightList copy(list);   // copy constructor of the list and of every record
    std::cout << "Copy of the list:\n" << copy;
    std::cout << "The copy is destroyed at the end of this operation" << std::endl;
}

void compareFlights(const FlightList& list) {
    if (list.isEmpty()) {
        throw EmptyListException("compare records");
    }
    int first = readIndex("First flight number (1.." + std::to_string(list.size())
                          + "): ", list.size());
    int second = readIndex("Second flight number (1.." + std::to_string(list.size())
                           + "): ", list.size());
    std::cout << "Flights are " << (list[first] == list[second] ? "equal" : "different")
              << " (== / !=)" << std::endl;
    if (list[first] < list[second]) {
        std::cout << "Flight " << (first + 1) << " has a smaller flight number "
                     "than flight " << (second + 1) << " (<)" << std::endl;
    } else {
        std::cout << "Flight " << (first + 1) << " does not have a smaller flight "
                     "number than flight " << (second + 1) << " (<)" << std::endl;
    }
    AEROFLOT temp;
    temp = list[first];   // copy assignment operator
    std::cout << "Temporary copy: " << temp << std::endl;
}

void vowelWords() {
    std::string fileName = readField("Text file name: ", "file name");
    int count = 0;
    std::string words = extractVowelWordsFromFile(fileName, count);
    if (count == 0) {
        std::cout << "There are no words starting with a vowel in the file" << std::endl;
        return;
    }
    std::cout << "Words starting with a vowel:\n" << words;
    std::cout << "Total: " << count << std::endl;
}

}  // namespace

int main() {
    FlightList list;
    while (true) {
        try {
            printMenu();
            int choice = readInt("Your choice: ");
            switch (choice) {
                case 1: addFlight(list); break;
                case 2: insertFlight(list); break;
                case 3: deleteFlight(list); break;
                case 4: editFlight(list); break;
                case 5: sortFlights(list); break;
                case 6: showFlights(list); break;
                case 7: findByDestination(list); break;
                case 8: copyList(list); break;
                case 9: vowelWords(); break;
                case 10: compareFlights(list); break;
                case 0:
                    std::cout << "Goodbye!" << std::endl;
                    return 0;
                default:
                    std::cout << "Error: there is no menu item " << choice << std::endl;
            }
        } catch (const InputStreamException& e) {
            std::cout << "\nError: " << e.what() << std::endl;
            return 1;
        } catch (const AppException& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (const std::bad_alloc&) {
            std::cout << "Error: not enough memory" << std::endl;
            return 2;
        }
    }
}

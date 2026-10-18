#include "Input.h"

#include <iostream>

#include "Exceptions.h"

std::string trim(const std::string& s) {
    const std::string spaces = " \t\r\n";
    std::string::size_type first = s.find_first_not_of(spaces);
    if (first == std::string::npos) {
        return "";
    }
    std::string::size_type last = s.find_last_not_of(spaces);
    return s.substr(first, last - first + 1);
}

std::string checkNotEmpty(const std::string& value, const std::string& fieldName) {
    std::string result = trim(value);
    if (result.empty()) {
        throw InvalidInputException("Field '" + fieldName + "' must not be empty");
    }
    return result;
}

bool tryParseInt(const std::string& s, int& out) {
    if (s.empty() || s.size() > 9) {
        return false;
    }
    std::string::size_type i = 0;
    bool negative = false;
    if (s[0] == '-' || s[0] == '+') {
        negative = (s[0] == '-');
        i = 1;
    }
    if (i == s.size()) {
        return false;
    }
    int value = 0;
    for (; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
        value = value * 10 + (s[i] - '0');
    }
    out = negative ? -value : value;
    return true;
}

std::string readLineFrom(std::istream& is, const std::string& prompt) {
    std::cout << prompt << std::flush;
    std::string line;
    if (!std::getline(is, line)) {
        throw InputStreamException();
    }
    return line;
}

std::string readFieldFrom(std::istream& is, const std::string& prompt,
                          const std::string& fieldName) {
    while (true) {
        std::string line = readLineFrom(is, prompt);
        try {
            return checkNotEmpty(line, fieldName);
        } catch (const InvalidInputException& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

int readIntFrom(std::istream& is, const std::string& prompt) {
    while (true) {
        std::string line = trim(readLineFrom(is, prompt));
        int value = 0;
        if (tryParseInt(line, value)) {
            return value;
        }
        std::cout << "Error: '" << line << "' is not a valid integer number" << std::endl;
    }
}

std::string readLine(const std::string& prompt) {
    return readLineFrom(std::cin, prompt);
}

std::string readField(const std::string& prompt, const std::string& fieldName) {
    return readFieldFrom(std::cin, prompt, fieldName);
}

int readInt(const std::string& prompt) {
    return readIntFrom(std::cin, prompt);
}

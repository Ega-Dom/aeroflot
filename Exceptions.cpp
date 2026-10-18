#include "Exceptions.h"

#include <sstream>

AppException::AppException(const std::string& msg) : message(msg) {}

AppException::~AppException() noexcept {}

const char* AppException::what() const noexcept {
    return message.c_str();
}

InvalidInputException::InvalidInputException(const std::string& msg)
    : AppException(msg) {}

InputStreamException::InputStreamException()
    : AppException("Input stream was closed, the program cannot read more data") {}

IndexOutOfRangeException::IndexOutOfRangeException(int index, int maxValid)
    : AppException("") {
    std::ostringstream oss;
    oss << "Invalid record number " << (index + 1)
        << ". Valid numbers are 1.." << maxValid;
    message = oss.str();
}

EmptyListException::EmptyListException(const std::string& operation)
    : AppException("Cannot " + operation + ": the list of flights is empty") {}

NullPointerException::NullPointerException(const std::string& where)
    : AppException("Null pointer passed to " + where) {}

FileException::FileException(const std::string& msg)
    : AppException(msg) {}

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

// Base class for all exceptions of the program.
class AppException : public std::exception {
protected:
    std::string message;

public:
    explicit AppException(const std::string& msg);
    virtual ~AppException() noexcept;
    virtual const char* what() const noexcept;
};

// Wrong value entered by the user (empty string, not a number, ...).
class InvalidInputException : public AppException {
public:
    explicit InvalidInputException(const std::string& msg);
};

// The standard input stream was closed (Ctrl+D / Ctrl+Z or end of redirected file).
class InputStreamException : public AppException {
public:
    InputStreamException();
};

// Record number is outside of the valid range 1..maxValid.
class IndexOutOfRangeException : public AppException {
public:
    IndexOutOfRangeException(int index, int maxValid);
};

// An operation requires at least one record, but the list is empty.
class EmptyListException : public AppException {
public:
    explicit EmptyListException(const std::string& operation);
};

// A null pointer was passed where an object is required.
class NullPointerException : public AppException {
public:
    explicit NullPointerException(const std::string& where);
};

// The text file cannot be opened or read.
class FileException : public AppException {
public:
    explicit FileException(const std::string& msg);
};

#endif

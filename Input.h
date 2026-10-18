#ifndef INPUT_H
#define INPUT_H

#include <iosfwd>
#include <string>

// Removes leading and trailing spaces/tabs/CR/LF.
std::string trim(const std::string& s);

// Returns the trimmed value or throws InvalidInputException if it is empty.
std::string checkNotEmpty(const std::string& value, const std::string& fieldName);

// Converts a string to int without exceptions. Returns false if it is not a number.
bool tryParseInt(const std::string& s, int& out);

// Input from an arbitrary stream (the prompt is always shown on the screen).
// The functions repeat the question until the value is correct and throw
// InputStreamException when the stream is closed.
std::string readLineFrom(std::istream& is, const std::string& prompt);
std::string readFieldFrom(std::istream& is, const std::string& prompt,
                          const std::string& fieldName);
int readIntFrom(std::istream& is, const std::string& prompt);

// The same functions for the keyboard (std::cin).
std::string readLine(const std::string& prompt);
std::string readField(const std::string& prompt, const std::string& fieldName);
int readInt(const std::string& prompt);

#endif

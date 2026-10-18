#include "TextProcessor.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Exceptions.h"

namespace {

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

}  // namespace

bool isVowel(char c) {
    switch (c) {
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return true;
        default:
            return false;
    }
}

std::string stripPunctuation(const std::string& word) {
    std::string::size_type first = 0;
    while (first < word.size() && !isLetter(word[first]) && !isDigit(word[first])) {
        ++first;
    }
    std::string::size_type last = word.size();
    while (last > first && !isLetter(word[last - 1]) && !isDigit(word[last - 1])) {
        --last;
    }
    return word.substr(first, last - first);
}

std::string extractVowelWords(std::istream& in, int& count) {
    count = 0;
    std::ostringstream result;
    std::string line;
    bool firstLine = true;
    while (std::getline(in, line)) {
        // Skip the UTF-8 byte order mark at the beginning of the file.
        if (firstLine && line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
            line = line.substr(3);
        }
        firstLine = false;

        std::istringstream words(line);   // string stream: splits a line into words
        std::string word;
        bool lineHasWords = false;
        while (words >> word) {
            word = stripPunctuation(word);
            if (!word.empty() && isVowel(word[0])) {
                if (lineHasWords) {
                    result << ' ';
                }
                result << word;
                lineHasWords = true;
                ++count;
            }
        }
        if (lineHasWords) {
            result << '\n';
        }
    }
    return result.str();
}

std::string extractVowelWordsFromFile(const std::string& fileName, int& count) {
    std::ifstream file(fileName.c_str());   // file stream
    if (!file.is_open()) {
        throw FileException("Cannot open file '" + fileName + "' for reading");
    }
    std::string text = extractVowelWords(file, count);
    if (file.bad()) {
        throw FileException("Error while reading file '" + fileName + "'");
    }
    return text;
}

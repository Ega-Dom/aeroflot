#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <iosfwd>
#include <string>

// True for the English vowels a, e, i, o, u (any case).
bool isVowel(char c);

// Removes punctuation around a word: "(apple)," -> "apple".
// Apostrophes and hyphens inside the word are kept.
std::string stripPunctuation(const std::string& word);

// Reads English text from the stream line by line (every line is split into
// words with a string stream) and returns the words that start with a vowel.
// Words from one source line are placed on one output line, separated by spaces.
// 'count' receives the number of words found.
std::string extractVowelWords(std::istream& in, int& count);

// Opens the text file with a file stream and processes it with extractVowelWords.
// Throws FileException if the file cannot be opened or read.
std::string extractVowelWordsFromFile(const std::string& fileName, int& count);

#endif

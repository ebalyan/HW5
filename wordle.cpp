#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
std::string& word,
size_t pos,
size_t blanks,
std::string& floating,
const std::set<std::string>& dict,
std::set<std::string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    std::string word = in;
    size_t blanks = 0;
    for (size_t i = 0; i < word.size(); i++) {
        if (word[i] == '-') {
            blanks++;
        }
}
    if (floating.size() > blanks) {
        return results;
    }
    std::string remaining = floating;
    wordleHelper(word, 0, blanks, remaining, dict, results);
    return results;
}


// Define any helper functions here
void wordleHelper(
    std::string& word,
    size_t pos,
    size_t blanks,
    std::string& floating,
    const std::set<std::string>& dict,
    std::set<std::string>& results)
{
    if (pos == word.size()) {
        if (floating.empty() && dict.find(word) != dict.end()) {
            results.insert(word);
        }
        return;
    }

    if (word[pos] != '-') {
        wordleHelper(word, pos + 1, blanks, floating, dict, results);
        return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        size_t idx = floating.find(c);

        if (idx == std::string::npos && blanks <= floating.size()) {
            continue;
        }

        word[pos] = c;
        if (idx != std::string::npos) {
            floating.erase(idx, 1);
            wordleHelper(word, pos + 1, blanks - 1, floating, dict, results);
            floating.insert(idx, 1, c);   // undo (backtrack)
        }
        else {
            wordleHelper(word, pos + 1, blanks - 1, floating, dict, results);
        }
        word[pos] = '-';   // undo (backtrack)
    }
}

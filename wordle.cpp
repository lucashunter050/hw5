// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
//size_t charCount(std::string, char);
//std::set<std::string> setIntersection(std::set<std::string>& s1, std::set<std::string>& s2);

//void removeInvalidWords(std::set<std::string>);

void wordleHelper(
    std::string in, 
    const std::string& floating, 
    unsigned unknowns, 
    unsigned numFloatings,
    std::set<string>& validWords,
    const std::set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> validWords;    

    unsigned unknown = 0;
    for (const char& letter: in)
    {
        if (letter == '-')
        {
            ++unknown;
        }
    }

    wordleHelper(in, floating, unknown, floating.size(), validWords, dict);
    return validWords;

}

void wordleHelper(
    std::string in, 
    const std::string& floating, 
    unsigned unknowns,
    unsigned numFloatings,
    std::set<std::string>& validWords,
    const std::set<std::string>& dict)
{
    // base case - we have a leaf of the recursive tree structure
    if (!unknowns)
    {
        // push into a set if the word is english and return that set
        if (!numFloatings)
        {
            if (dict.find(in) != dict.end())
            {
                validWords.insert(in);
            }
        }

        // return the set
        // return validWords;
        return;
    }

    // recursive step
    
    size_t pos = 0;
    while ((pos < in.size()) && (in.at(pos) != '-'))
    {
        ++pos;
    }

    // generate those with the restrictions
    if (numFloatings)
    {
        for (char potential: floating)
        {
            in.at(pos) = potential;
            wordleHelper(in, floating, unknowns - 1, numFloatings - 1, validWords, dict);
            in.at(pos) = '-';
        }
    }
    else // generate those without the restrictions 
    {
        for (unsigned i = 97; i <= 122; ++i)
        {
            in.at(pos) = static_cast<char>(i);
            wordleHelper(in, floating, unknowns - 1, numFloatings, validWords, dict);
            in.at(pos) = '-';
        }
    }
}
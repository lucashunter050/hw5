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

std::string wordleHelper(std::string in, std::string floating, unsigned unknowns, unsigned numFloatings);

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

    validWords.insert(wordleHelper(in, floating, unknown, floating.size()));


    return validWords;

}

std::string wordleHelper(
    std::string in, 
    std::string floating, 
    unsigned unknowns,
    unsigned numFloatings)
{
    // base case - we have a leaf of the recursive tree structure
    if (!unknowns)
    {
        return in;
    }

    // recursive step
    
    size_t pos = 0;
    while (in.at(pos) != '-')
    {
        ++pos;
    }

    // generate those with the restrictions
    if (numFloatings)
    {
        for (char potential: floating)
        {
            in.at(pos) = potential;
            --unknowns;
            --numFloatings;
            return wordleHelper(in, floating, unknowns, numFloatings);
        }
    }
    else // generate those without the restrictions 
    {
        for (unsigned i = 97; i <= 122; ++i)
        {
            --unknowns;
            in.at(pos) = static_cast<char>(i);
            return wordleHelper(in, floating, unknowns, numFloatings);
        }
    }
}

// Define any helper functions here
/*size_t charCount(std::string tester, char toCheck)
{
    size_t occurences = 0;
    for (char& t: tester)
    {
        if (t == toCheck)
        {
            ++occurences;
        }
    }

    return occurences;
}

std::set<std::string> setIntersection(std::set<std::string>& s1, std::set<std::string>& s2)
{
    std::set<std::string> intersection;

    std::set<std::string>::iterator it1 = s1.begin();
    // typename T::iterator it2 = s2.begin();

    // while loop is theta(n)
    while (it1 != s1.end()) {
        // std::set has O(log(n)) find
        if (s2.find(*it1) != s2.end()) {
            // insert is O(1)
            intersection.insert(*it1);
        }
        ++it1;
    }

    return intersection;
}*/


// old and fraudulent code
/*unsigned long unknowns = 0;
    for (char i : in)
    {
        if (i == '-')
        {
            ++unknowns;
        }
    }
    */
    /*if (!floating.size())
    {
        validWords.insert(in);
        return validWords;
    }

    // iterate over every element in the dict set
    for (const std::string& englishWord : dict)
    {
        // only bother checking if a word is valid if it is the same size as our target
        if (englishWord.size() == in.size())
        {
            // check 1: it has matching greens with input
            bool isAMatch = true;
            for (size_t i; i < englishWord.size(); ++i)
            {
                if (!((englishWord.at(i) == in.at(i)) || (in.at(i) == '-')))
                {
                    // we know this word will not be a match for the greens, stop the loop
                    isAMatch = false;
                    break;
                }
            }
            if (isAMatch)
            {
                validWords.insert(englishWord);
            }

            // check 2: it has letters corresponding to the floating yellows
            if (!isAMatch)
            {
                size_t yellowsMatching = 0;
                for (const char& c : englishWord)
                {
                    // add a check for duplicate letters
                    yellowsMatching += charCount(floating, c);
                }

                if (yellowsMatching == floating.size())
                {
                    validWords.insert(englishWord);
                }
            }
        }
    }
    */
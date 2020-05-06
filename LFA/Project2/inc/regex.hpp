#ifndef REGEX_
#define REGEX_

#include "DFA.hpp"

#include <string>

/**
 * Class able to convert a DFA from and to a regular expression
 * The regular expression respects:
 * 1. R = c
 * 2. R = ST
 * 3. R = S*
 * 4. R = S|T
 * 5. lambda is noted with '@'
 * The operations (except the paranthesis) all have the same
 * priority and are executed from left to right
 * E.G.: a(b)*|(ab|c)* accepts abb and abc but not aab
 */
class Regex {
    std::string regex_;

public:

    /// Empty constructor
    Regex();

    /// Constructing regex from a string
    Regex(const std::string & s);

    /// Constructing regex from a DFA
    Regex(const DFA & dfa);

    /// convers the regex to a dfa
    DFA ToDfa() const;

    /// converts curent regex to the regex coresponding to dfa
    void FromDfa(const DFA & dfa);

    /// returns the regex string
    std::string GetContent() const;


    /// I/O Operations
    friend std::istream & operator>> (std::istream & in, Regex & reg);
    friend std::ostream & operator<< (std::ostream & out, const Regex & reg);
};

#endif // REGEX_
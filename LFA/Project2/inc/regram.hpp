#ifndef REGRAM_
#define REGRAM_

#include "DFA.hpp"

#include <string>
#include <vector>
#include <map>

/**
 * Class able to convert a DFA from and to a regular grammar
 * The regular grammar respects:
 * Lambda is noted with '@' in input and \0 in Regram
 * The grammar is a right-grammar (A -> xB)
 */
class Regram {
    std::map <std::string, std::vector <std::pair <char, std::string>>> regram_;
    std::string initial_state_;

public:

    /// Empty constructor
    Regram();

    /// Constructing a grammar from the operations
    Regram(const std::string & initial_state, const std::map <std::string,
        std::vector <std::pair <char, std::string>>> & gram);

    /// Constructing a grammar from a DFA
    Regram(const DFA & dfa);

    /// convers the regex to a dfa
    DFA ToDfa() const;

    /// converts curent regex to the regex coresponding to dfa
    void FromDfa(const DFA & dfa);

    /// returns the regex string
    std::map <std::string, std::vector <std::pair <char, std::string>>> GetContent() const;


    /// I/O Operations
    friend std::istream & operator>> (std::istream & in, Regram & reg);
    friend std::ostream & operator<< (std::ostream & out, const Regram & reg);
};

#endif // REGEX_
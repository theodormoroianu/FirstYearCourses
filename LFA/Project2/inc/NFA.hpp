#ifndef INC_NFA_
#define INC_NFA_

#include <bits/stdc++.h>
#include "DFA.hpp"

/**
 * Automaton is given by (Q, Epsilon, delta, q0, F), where:
 *  1. Q is the number of states
 *  2. Epsilon is the alphabet we are working with
 *  3. delta is the transition function, delta : Q x Epsion -> Q
 *  4. q0 is the starting point
 *  5. F is the set of ending points
**/
class NFA
{
    /// accepted characters
    static const std::string EPSILON;
    /// edges
    std::vector <std::map <char, std::set <int>>> edges_;
    /// start node
    int start_node_;
    /// end nodes
    std::set <int> end_nodes_;

public:
    /// constructor with transitions, start node and end nodes
    NFA(std::vector <std::map <char, std::set <int>>> edges, int start_node, std::set <int> end_nodes);
    
    /// empty constructor
    NFA();

    /// explicit conversion to DFA
    explicit operator DFA();

    /// I/O operators
    friend std::istream & operator>> (std::istream & in, NFA & nfa);
    friend std::ostream & operator<< (std::ostream & out, const NFA & nfa);
};

#endif // INC_NFA_
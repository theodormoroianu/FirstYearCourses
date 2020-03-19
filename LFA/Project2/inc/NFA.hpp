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

/// Only purpuse of this automaton is to be able to convert a lambda-NFA to a DFA

class NFA
{
    static const std::string EPSILON;

    std::vector <std::map <char, std::set <int>>> edges_;
    int start_node_;
    std::set <int> end_nodes_;

public:
    NFA(std::vector <std::map <char, std::set <int>>>, int start_node, std::set <int> end_nodes);
    
    explicit operator DFA();
};

#endif // INC_NFA_
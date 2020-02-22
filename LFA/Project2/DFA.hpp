#include <bits/stdc++.h>

/**
 * Automaton is given by (Q, Epsilon, delta, q0, F), where:
 *  1. Q is the number of states
 *  2. Epsilon is the alphabet we are working with
 *  3. delta is the transition function, delta : Q x Epsion -> Q
 *  4. q0 is the starting point
 *  5. F is the set of ending points
**/

/**
 * Rules for reading the automaton:
 *  1. St line contains Q, szTranz    -> Number of states, number of edges
 *  2. Next sz lines contain X Y c    -> edge from X to Y with color c
 *  3. Next line contains q0          -> starting point
 *  4. Next line contains szF         -> number of ending states
 *  5. Last line contains szF number  -> the ending states
**/

const std::string EPSILON = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

class DFA
{
    // edges store the transition function delta
    std::vector <std::map <char, int>> edges;
    // a state is rechable if it can get to end_nodes and is accesibile from start_node
    std::vector <bool> reachable;
    // start_node = q0
    int start_node;
    /// end_nodes = F
    std::set <int> end_nodes;
    
    void compute_reachability();

public:
    DFA();
    DFA(std::vector <std::map <char, int>> edges, int start_node, std::set <int> end_nodes);

    // checks whether a string is accepted by the automata or not
    bool IsAccepted(const std::string & s) const;


    // DFA minimization
    DFA Minimize() const;

    friend std::istream & operator>> (std::istream & in, DFA & dfa);
    friend std::ostream & operator<< (std::ostream & out, DFA & dfa);
};
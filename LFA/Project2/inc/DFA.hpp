#ifndef INC_DFA_
#define INC_DFA_

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


class DFA
{
    /// alphabet
    static const std::string EPSILON;

    // edges store the transition function delta
    std::vector <std::map <char, int>> edges_;
    // a state is rechable if it can get to end_nodes and is accesibile from start_node
    std::vector <bool> reachable_;
    // start_node = q0
    int start_node_;
    /// end_nodes = F
    std::set <int> end_nodes_;
    
    /// computes for each node if it can get to an end node and if it is
    /// visible from the start node
    void compute_reachability();

public:
    
    /// default constructor
    DFA();

    /// constructor with edges, start node, transitions and end node
    DFA(std::vector <std::map <char, int>> edges, int start_node, std::set <int> end_nodes);

    // checks whether a string is accepted by the automata or not
    bool IsAccepted(const std::string & s) const;

    /// returns the number of states in the automaton
    int CountStates() const;

    // DFA minimization, returns the minimised DFA
    DFA Minimize() const;

    /**
     * new automaton accepts a word <=> initial DFA does not
     * Computes the complement of an automaton
     */
    friend DFA operator~(const DFA & dfa);


    /**
     * At least one of the two DFAs accept the word
     * Computes the reunion of the two automata
     */
    friend DFA operator|(const DFA & a, const DFA & b);
    
    /**
     * both of the DFAs accept the word
     * Computes the intersection of two automata
     */
    friend DFA operator&(const DFA & a, const DFA & b);
    
    /**
     * both DFAs accept the same language
     * computes the equivalence of two automata
     */
    friend bool operator==(const DFA & a, const DFA & b);

    /**
     * the two DFAs don't accept the same language
     * Computes the negation of the equivalence of two automata
     */
    friend bool operator!=(const DFA & a, const DFA & b);
    
    /// I/O Operations
    friend std::istream & operator>> (std::istream & in, DFA & dfa);
    friend std::ostream & operator<< (std::ostream & out, const DFA & dfa);
};

#endif // INC_DFA_
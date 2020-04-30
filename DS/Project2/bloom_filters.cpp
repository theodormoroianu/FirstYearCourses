/**
 * Bloom filters
 */

#include <bits/stdc++.h>
using namespace std;


/**
 * Template datatype is expected to be iterable with integer-compatible elements.
 * If the elements are not of integer type they should implement AT LEAST the explicit conversion.
 */
template <class T, int M = 1000000, int K = 1000>
class BloomFilter
{
    bitset <M> bits;
    vector <int> primes;
    int added;

    void compute_primes()
    {
        vector <int> viz(600);
        for (int i = 2; primes.size() < K; i++) {
            if (!viz[i]) {
                primes.push_back(i);
                for (int j = 2 * i; j < 600; j += i)
                    viz[j] = 1;
            }
        }   
    }

    vector <int> positions(T elem)
    {
        vector <int> ans;
        for (auto p : primes) {
            int h = 0;
            for (auto i : elem)
                h = (1LL * h * p + i) % M;
            ans.push_back(h);
        }
        return ans;
    }

public:

    /// adds an element to the bloom filter
    void Add(T elem)
    {
        auto v = positions(elem);
        added++;
        for (auto i : v)
            bits[i] = 1;
    }

    /// probability the Bloom filter DS throws a false positive from it's curent state (aproximation)
    double FalsePositiveProbability()
    {
        double p = 1. - exp(-1. * K * added / M);
        return pow(p, K);
    }

    /// returns true if the element is `maybe` inside
    bool FilterCheck(T elem)
    {
        auto v = positions(elem);
        bool min_value = true;
        for (auto i : v)
            min_value = min(min_value, (bool)bits[i]);
        return min_value;
    }

    /// constructor with intial elements
    BloomFilter(vector <T> init = { }) : added(0)
    {
        if (K > 100)
            throw runtime_error("Number of filters is WAAAY to big");
        else if (K < 1)
            throw runtime_error("Need at least one filter");
        else if (M < 1)
            throw runtime_error("Table dimension is too small");
        else if (M > (int)1e9)
            throw runtime_error("Dimension of table is too big");

        compute_primes();
        for (auto i : init)
            Add(i);
    }
};


int main()
{
    BloomFilter <string, 666013, 10> filter;

    cout << "Insert elements in the filter:\n$ ";

    while (true) {
        string s;
        cin >> s;
        cout << "Verdict: " << (filter.FilterCheck(s) ? "Exists" : "Doesn\'t Exist") << '\n';
        cout << "False positive probability: " << filter.FalsePositiveProbability() << '\n';
        filter.Add(s);
        cout << "Added \'" << s << "\' in the filter...\n$ ";
    }

    return 0;
}
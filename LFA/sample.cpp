#include <bits/stdc++.h>
using namespace std;

class T {
public:
    int x;
    T() { }

    friend istream & operator>> (istream & in, T & x) {
        in >> x.x;
        return in;
    }
};

int main()
{
    T a, b;
    cin >> a;
    cout << a.x << ' ' << b.x << '\n';
}
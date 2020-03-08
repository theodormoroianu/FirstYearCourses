#include <iostream>
#include "Sortari.hpp"
using namespace std;

int main()
{
    int v[] = { 1, 4, 3, 2 };

    SkipListSort(v, 4);

    for (int i = 0; i < 4; i++)
        cout << v[i] << ' ';
    cout << "Hello world!" << endl;
    return 0;
}

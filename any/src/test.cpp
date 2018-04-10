#include <string>
#include <iostream>
#include "any.h"

using utils::any;
using utils::any_cast;
using namespace std;
int main()
{
    any a(5), b(string("6"));
    any c(a);
    swap(a, b);
    const any d(5);
    const int* f = any_cast<int>(&d);
    cout << *f << endl;
    const any g(7);
    const int& h = any_cast<const int&>(g);
    cout << h << endl;
    int* k = new int(100);
    any any_p(k);
    return 0;
}

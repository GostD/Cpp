#include <iostream>
#include <functional>
#include <cmath>
#include "enumerable.h"
#include "wrapper.h"

using namespace std;

int main()
{
    std::vector<int> vec = {1, 2, 3, 4 ,5 ,6, 7, 8, 9, 10};

    auto result_vector = from(vec)
    .where([](int i){return std::move(i) < 5;})
    .toVector();

    cout << result_vector.back() << endl;

    vector<wrapper<int>> test;
    for (size_t i = 0; i < 100; ++i) { test.emplace_back(i); }
 
    auto data = from(std::move(test))
    .where([](wrapper<int> const& i){return i.value() < 51;});
    // .toVector();
    
    cout << data.count([](wrapper<int> const& i){return i.value() < 41;}) << endl;
    cout << data.toVector().back().value() << endl;

    vector<int> ints_vector = {1, 2, 3};
    auto result = from(ints_vector)
    .select<double>([](int i) {return sqrt((double)i);})
    .toVector();
    cout << result.back() << endl;
}
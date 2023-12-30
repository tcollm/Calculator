#ifndef VEC_TO_INT_HPP
#define VEC_TO_INT_HPP

#include <vector>
#include <algorithm>

int VecToInt(std::vector<int> v) {
    reverse(v.begin(), v.end());
    int decimal = 1;
    int total = 0;
    for (auto& it : v)
    {
        total += it * decimal;
        decimal *= 10;
    }
    return total;
}



#endif // VEC_TO_INT_HPP
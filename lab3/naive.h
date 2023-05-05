#pragma once

#include <vector>

using namespace std;

namespace naive
{
    vector<int> arr;

    void ins(int x) { arr.push_back(x); }

    bool query(int x)
    {
        for(auto y : arr)
            if(x == y) return true;
        return false;
    }
}
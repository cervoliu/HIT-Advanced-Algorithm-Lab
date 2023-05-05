#include "naive.h"
namespace naive
{
    void ins(int x) { arr.push_back(x); }

    bool query(int x)
    {
        for(auto y : arr)
            if(x == y) return true;
        return false;
    }
}

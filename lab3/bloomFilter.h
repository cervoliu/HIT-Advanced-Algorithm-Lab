#pragma once

#include <bits/stdc++.h>

using namespace std;

extern int Random(int l, int r);

struct bloomFilter
{
    int n, k;
    vector<pair<int, int> > hashFunc;
    int *cnt;
    bloomFilter(int _n, int _k) : n(_n), k(_k)
    {
        assert(n <= int(1e7) && "Bloom Filter bit number too big!");
        for(int i = 1, j = 0; j < k; ++i)
        {
            if(__gcd(i, n) == 1)
            {
                ++ j;
                hashFunc.push_back(make_pair(i, Random(0, n - 1)));
            }
        }
        cnt = new int[n];
    }
    ~bloomFilter()
    {
        n = k = 0;
        hashFunc.clear();
        delete[] cnt;
    }
    int myhash(int x, int p, int q)
    {
        return (int)((1LL * p * x + q) % n);
    }
    void ins(int x)
    {
        for(auto h : hashFunc)
        {
            int pos = myhash(x, h.first, h.second);
            cnt[pos] ++;
        }
    }
    void del(int x)
    {
        for(auto h : hashFunc)
        {
            int pos = myhash(x, h.first, h.second);
            cnt[pos] --;
        }
    }
    bool query(int x)
    {
        for(auto h : hashFunc)
        {
            int pos = myhash(x, h.first, h.second);
            if(!cnt[pos]) return false;
        }
        return true;
    }
};
#ifndef _TUPLES_H_
#define _TUPLES_H_
#define LL long long
#include <bits/stdc++.h>

using namespace std;

class tuples
{

public:
    int pk, fk, id, walkTimes;
    double val; //weight function
    vector<int> nxt; // ids of tuples in next table to which *this connect.
    vector<double> preSum;

    tuples(int _pk, int _id, int _fk) : pk(_pk), id(_id), fk(_fk)
    {
        val = 0;
        walkTimes = 0;
        nxt.clear();
        preSum.clear();
    }
};

class database
{

private:
    char foo[20]; // char buffer

public:
    vector<vector<tuples>> w;
    void init(int n)
    {
        w.clear();
        static vector<tuples> sig;
        for (int i = 0; i <= n; ++i)
            w.push_back(sig);
        int pk, fk, id;
        for (int i = 1; i <= n; ++i)
        {
            sprintf(foo, "table/table%d.tab", i);
            freopen(foo, "r", stdin);
            cerr << i << " ";
            while (~scanf("%d%d%d", &pk, &id, &fk))
                w[i].push_back(tuples(pk, id, fk));
            if (i != 1)
            {
                for (auto &x : w[i - 1])
                {
                    for (int j = 0; j < w[i].size(); ++j)
                    {
                        auto y = w[i][j];
                        if (y.pk == x.fk)
                            x.nxt.push_back(j);
                    }
                }
            }
            fclose(stdin);
        }
        w[0].push_back(tuples(0, 0, 0)); // an super start tuple
        for (int i = 0; i < w[1].size(); ++i)
        {
            w[0][0].nxt.push_back(i);
        }
    }
};

#endif
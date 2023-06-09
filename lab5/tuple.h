#ifndef _TUPLE_H_
#define _TUPLE_H_
#define LL long long
#include <bits/stdc++.h>

using namespace std;

class Tuple
{

public:
    int leftkey, rightkey; // tuple in R(leftkey, rightkey)
    int id;
    int walkCnt;
    double W; //weight function
    vector<int> nxt; // id of tuples in next table to which it connect.
    vector<double> preSum; // aid selecting a tuple in nxt

    Tuple(int _leftkey, int _id, int _rightkey) : leftkey(_leftkey), id(_id), rightkey(_rightkey)
    {
        W = 0;
        walkCnt = 0;
        nxt.clear();
        preSum.clear();
    }
};

class database
{

private:
    char foo[20]; // char buffer

public:
    vector<vector<Tuple>> t;
    void init(int n)
    {
        t.clear();
        static vector<Tuple> sig;
        for (int i = 0; i <= n; ++i)
            t.push_back(sig);
        int leftkey, rightkey, id;
        for (int i = 1; i <= n; ++i)
        {
            sprintf(foo, "table/table%d.tab", i);
            freopen(foo, "r", stdin);
            cerr << i << " ";
            while (~scanf("%d%d%d", &leftkey, &id, &rightkey)) //while not EOF
                t[i].push_back(Tuple(leftkey, id, rightkey));
            if (i != 1)
            {
                for (auto &x : t[i - 1])
                {
                    for (auto &y : t[i])
                    {
                        if (y.leftkey == x.rightkey)
                            x.nxt.push_back(y.id);
                    }
                }
            }
            fclose(stdin);
        }
        t[0].push_back(Tuple(0, 0, 0)); // an super start tuple
        for (int i = 0; i < t[1].size(); ++i)
        {
            t[0][0].nxt.push_back(i);
        }
    }
};

#endif
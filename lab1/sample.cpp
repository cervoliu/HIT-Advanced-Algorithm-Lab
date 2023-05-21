#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

string getOutName(string s, int r)
{
    int len = s.length();
    for (int i=len-1; i>=0; --i) 
        if (s[i] == '.')
        {
            s = s.substr(0, i);
            break;
        }
    s += "_" + to_string(r) + ".txt";
    return s;
}

vector<pair<int, int> > vec;

vector<unordered_set<int> > sets;

int main(int argc, char **argv)
{
    registerGen(argc, argv, 1);
    ifstream infile;
    ofstream outfile;
    string filename = "data/Booking/Booking.txt";
    int rate = 10;

    infile.open(filename);
    int n = 0, x, y;
    while(!infile.eof())
    {
        infile >> x >> y;
        vec.push_back(make_pair(x, y));
        n = max(n, x);
    }
    infile.close();

    sets.resize(n + 1);
    for(auto p : vec)
    {
        sets[p.first].insert(p.second);
    }

    outfile.open(getOutName(filename, rate));
    int cnt = 0;
    for(int i = 1; i <= n; ++i)
    {
        if(rnd.next() * 100 <= rate)
        {
            ++cnt;
            for(auto j : sets[i])
            {
                outfile << cnt << ' ' << j << endl;
            }
        }
    }
    printf("%d %d\n", n, cnt);
    return 0;
}
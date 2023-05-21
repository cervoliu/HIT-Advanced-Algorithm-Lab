#include "testlib.h"
#include "naive.h"
#include "minhash.h"
#include "lsh.h"
#include "mix.h"
#include <bits/stdc++.h>
#include <ctime>
using namespace std;

int n, m, cnt[4000];
ifstream inFile;
vector<vector<int>> sets;


int randit(int n) { return rnd.next(n); }

void init(ifstream &inFile, vector<vector<int>> &sets)
{
    vector<pair<int, int>> data;
    int x, y;
    while (!inFile.eof())
    {
        inFile >> x >> y;
        data.push_back(make_pair(x, y));
        m = max(m, x);
        n = max(n, y);
    }
    static vector<int> single_set;
    single_set.clear();
    for (int i = 0; i <= m; ++i)
        sets.push_back(single_set);
    sort(data.begin(), data.end());
    data.erase(unique(data.begin(), data.end()), data.end());
    for (auto p : data)
    {
        sets[p.first].push_back(p.second);
    }
    int max_set = 0;
    for (auto s : sets)
    {
        int sz = s.size();
        max_set = max(max_set, sz);
        cnt[sz]++;
    }
    printf("%d\n", max_set);
    for(int i = 1; i <= max_set; ++i) printf("%d\n", cnt[i]);
}

int main(int argc, char **argv)
{
    registerGen(argc, argv, 1);
    inFile.open("data/Booking/Booking.txt");
    freopen("data/Booking/Booking_info.txt","w",stdout);
    if (inFile.fail())
    {
        cerr << "Input Error\n";
        exit(0);
    }
    init(inFile, sets);

    inFile.close();
}
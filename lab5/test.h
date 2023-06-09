#ifndef _TEST_H_
#define _TEST_H_
#include "tuple.h"
#include <bits/stdc++.h>
#define LL long long
using namespace std;
map<vector<int>, int> cnt;

class test
{

private:
    vector<int> ans;
    bool flag;
    vector<vector<Tuple>> t;
    map<vector<int>, int> cnt;

    void dfs(int now, int c, int n) //clear cnt
    {
        if (now == n - 1)
        {
            cnt[ans] = 0;
            // for (auto x:ans) cerr << x << " ";
            // cerr << endl;
            return;
        }
        for (int i = 0; i < t[now + 1].size(); ++i)
        {
            auto x = t[now + 1][i];
            if (x.leftkey != t[now][c].rightkey)
                continue;
            ans.push_back(x.id);
            dfs(now + 1, i, n);
            ans.pop_back();
        }
    }

public:
    int pt()
    {
        return cnt.size();
    }

    test(vector<vector<Tuple>> &db)
    {
        cnt.clear();
        ans.clear();
        t.clear();
        flag = false;
        int tot = 0;
        for (auto x : db)
            tot += x.size();
        if (tot <= 200)
            flag = true;
        else
            return;
        t = db;
        int n = t.size();
        dfs(0, 0, n);
    }

    void insert(vector<int> now)
    {
        if (flag == false)
            return;
        cnt[now]++;
    }

    void printRes(char *s)
    {
        freopen(s, "w", stdout);
        for (auto x : cnt)
            printf("%d\n", x.second);
        fclose(stdout);
    }

    void clear()
    {
        for (auto &x : cnt)
            x.second = 0;
    }
};

#endif
#ifndef _TEST_H_
#define _TEST_H_
#include "tuples.h"
#include <bits/stdc++.h>
#define LL long long
using namespace std;
map<vector<int>, int> cnt;

class test
{

private:
    vector<int> ans;
    bool flag;
    vector<vector<tuples>> w;
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
        for (int i = 0; i < w[now + 1].size(); ++i)
        {
            auto x = w[now + 1][i];
            if (x.pk != w[now][c].fk)
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

    test(vector<vector<tuples>> &db)
    {
        cnt.clear();
        ans.clear();
        w.clear();
        flag = false;
        int tot = 0;
        for (auto x : db)
            tot += x.size();
        if (tot <= 200)
            flag = true;
        else
            return;
        w = db;
        int n = w.size();
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
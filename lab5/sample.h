#ifndef _SAMPLE_H_
#define _SAMPLE_H_
#define LL long long
#include "testlib.h"
#include "test.h"
#include "tuple.h"
#include <bits/stdc++.h>

using namespace std;

class sampling
{

private:
    bool Accept(double x, double y)
    {
        return rnd.next(x) <= y;
    }

    vector<int> getit(database &data, int n)
    {
        int now = 0;
        vector<int> ret{};
        for (int i = 0; i < n; ++i)
        {
            if (!data.t[i][now].preSum.size() || !Accept(data.t[i][now].W, *(data.t[i][now].preSum.end() - 1)))
                return ret;
            double rd = rnd.next(*(data.t[i][now].preSum.end() - 1));
            now = data.t[i][now].nxt[upper_bound(data.t[i][now].preSum.begin(), data.t[i][now].preSum.end(), rd) - data.t[i][now].preSum.begin()];
            ret.push_back(now);
        }
        return ret;
    }

    virtual void getW(database &data, int n) = 0; //pure virtual function, to be inherited

    vector<int> sample(database &data, int n)
    {
        vector<int> ret{};
        do
        {
            times++;
            ret = getit(data, n);
        } while (ret.size() != n); // check integrity - not rejected halfway
        return ret;
    }

public:
    int times;

    void Main(database &data, test &tt, int n, int o)
    {

        for (int i = 0; i < n; ++i)
            for (auto &x : data.t[i])
                x.preSum.clear();

        cerr << "Getting weight now...\n";
        LL time_1 = clock();
        getW(data, n);
        LL time_2 = clock();
        cerr << "Getting weight over with time cost " << 1.0 * (time_2 - time_1) / CLOCKS_PER_SEC << "s " << endl;

        for (int i = 0; i < n; ++i)
            for (auto &x : data.t[i])
            {
                double sum = 0;
                for (auto j : x.nxt)
                {
                    auto y = data.t[i + 1][j];
                    sum += y.W;
                    x.preSum.push_back(sum);
                }
            }

        // cerr << data.t[0][0].W << " " << *(data.t[0][0].preSum.end()-2) << "\n";
        LL tot = 1;
        if (o == 1)
        {
            for (auto x : data.t)
                tot *= data.t.size();
            tot *= 1000000;
        }
        else
            tot = 1000000;
        time_1 = clock();
        cerr << "Start sampling...\n";
        LL ti = tot / 100;
        for (LL i = 1; i <= tot; ++i)
        {
            if (i % ti == 0)
                cerr << i / ti << " ";
            auto sam = sample(data, n);
            tt.insert(sam);
        }
        cerr << "\n"
             << "Estimated join size:" << data.t[0][0].W << ",  sampling times: " << times << '\n';
        time_2 = clock();
        cerr << "\nSampling over with time cost each time " << 1.0 * (time_2 - time_1) / CLOCKS_PER_SEC << "s " << endl;

        // cerr << data.t[0][0].W << " " << tt.pt();
    }
};

class ExactWeight : public sampling
{

private:
    void getW(database &data, int n)
    {
        for (auto &x : data.t[n])
            x.W = 1.0;
        for (int i = n - 1; i >= 0; --i)
        {
            for (auto &x : data.t[i])
            {
                x.W = 0;
                for (auto j : x.nxt)
                {
                    auto y = data.t[i + 1][j];
                    x.W += y.W;
                }
            }
        }
    }
};

class ExtendedOlken : public sampling
{

private:
    void getW(database &data, int n)
    {
        times = 0;
        for (auto &x : data.t[n])
            x.W = 1.0;
        for (int i = n - 1; i >= 0; --i)
        {
            double mx = 0;
            for (auto x : data.t[i])
                mx = max(mx, 1.0 * x.nxt.size());
            mx *= data.t[i + 1][0].W;
            for (auto &x : data.t[i])
                x.W = mx;
        }
    }
};

class OnlineExploration : public sampling
{

private:
    int randomWalkTimes;
    const int theta = 13;

    bool randomWalk(database &data, int n)
    {
        int now = 0;
        vector<int> walk{0};
        for (int i = 0; i < n; ++i)
        {
            if (data.t[i][now].nxt.empty())
                return false;
            int rd = rnd.next(data.t[i][now].nxt.size());
            now = data.t[i][now].nxt[rd];
            walk.push_back(now);
        }
        for(int i = n - 1; i >= 0; --i)
        {
            auto &x = data.t[i][walk[i]];
            x.walkCnt++;
            x.W = ((x.walkCnt - 1) * x.W + data.t[i + 1][walk[i + 1]].W * x.nxt.size()) / x.walkCnt;
        }
        return true;
    }

    void getW(database &data, int n)
    {
        times = 0;
        for (auto &x : data.t[n])
            x.W = 1;
        int m = 0;
        for (auto x : data.t)
            m += x.size();
        randomWalkTimes = m / n * 100;
        // cerr << randomWalkTimes << "\n";
        for (int i = 1; i <= randomWalkTimes; ++i)
            while(!randomWalk(data, n));
        for (int i = n - 1; i; --i)
        {
            for (auto &x : data.t[i])
            {
                if (x.walkCnt >= theta)
                    continue;
                x.W = 0;
                for (auto j : x.nxt)
                {
                    auto y = data.t[i + 1][j];
                    x.W += y.W;
                }
            }
        }
    }
};

#endif

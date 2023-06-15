#include <vector>
#include <random>
#include <algorithm>

using namespace std;

typedef pair<int, int> PII;

const int INF = 1e9;
const int mo = 1e9 + 7; // must be a prime

int random(int l, int r) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(l, r);
    return dis(gen);
}

class Sketch
{
protected:
    int n; // the size of hash table
    vector<int> tbl; // the hash table
    int m; // the number of hash functions, such as h(x) = (px + q) mod mo mod n
    vector<PII> h;
    int hash(int x, PII p)
    {
        return (1LL * p.first * x % mo + p.second) % mo % n;
    }
public:
    int total, max_x; // the maximum value of x
    Sketch(int _n, int _m) : n(_n), m(_m)
    {
        tbl.resize(n);
        for(int i = 0; i < m; ++i)
        {
            h.push_back(make_pair(random(1, mo - 1), random(0, mo - 1)));
        }
    }
    virtual ~Sketch() {}
    virtual void insert(int x) = 0;
    virtual int query(int x) = 0;
};

class CM_Sketch : public Sketch
{
    using Sketch::Sketch; // implicitly inherit constructer
public:
    void insert(int x)
    {
        total++, max_x = max(max_x, x);
        for(auto p : h)
        {
            int pos = hash(x, p);
            tbl[pos]++;
        }
    }
    int query(int x)
    {
        int res = INF;
        for(auto p : h)
        {
            int pos = hash(x, p);
            res = min(res, tbl[pos]);
        }
        return res;
    }
};

class CU_Sketch : public Sketch
{
    using Sketch::Sketch;
public:
    void insert(int x)
    {
        total++, max_x = max(max_x, x);
        static vector<int> pos_vec;
        pos_vec.clear();
        int min_val = INF;
        for(auto p : h)
        {
            int pos = hash(x, p);
            pos_vec.push_back(pos);
            min_val = min(min_val, tbl[pos]);
        }
        for(auto pos : pos_vec)
        {
            if(tbl[pos] == min_val) tbl[pos]++;
        }
    }
    int query(int x)
    {
        int res = INF;
        for(auto p : h)
        {
            int pos = hash(x, p);
            res = min(res, tbl[pos]);
        }
        return res;
    }
};

class Count_Sketch : public Sketch
{
    using Sketch::Sketch;
public:
    int hash(int x, PII p, int &sig)
    {
        int val = (1LL * p.first * x % mo + p.second) % mo;
        sig = (val & 1) ? 1 : -1;
        return val % n;
    }
    void insert(int x)
    {
        total++, max_x = max(max_x, x);
        for(auto p : h)
        {
            int sig, pos = hash(x, p, sig);
            tbl[pos] += sig;
        }
    }
    int query(int x)
    {
        static vector<int> cnt_vec;
        cnt_vec.clear();
        for(auto p : h)
        {
            int sig, pos = hash(x, p, sig);
            cnt_vec.push_back(sig * tbl[pos]);
        }
        sort(cnt_vec.begin(), cnt_vec.end());
        if(m & 1) return cnt_vec[m / 2 + 1];
        else return (cnt_vec[m / 2] + cnt_vec[m / 2 + 1]) / 2;
    }
};
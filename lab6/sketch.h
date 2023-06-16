#include <random>
#include <algorithm>
#include <unordered_map>

using namespace std;

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
    int n; // the number of buckets
    int m; // the number of hash functions
    int **tbl, *a, *b;
    int hash(int x, int i)
    {
        return (1LL * a[i] * x % mo + b[i]) % mo % n;
    }
public:
    int total = 0, max_x = 0;
    Sketch(int _n, int _m) : n(_n), m(_m)
    {
        a = new int[m], b = new int[m];
        tbl = new int*[m];
        for(int i = 0; i < m; ++i)
        {
            a[i] = random(1, mo - 1), b[i] = random(0, mo - 1);
            tbl[i] = new int[n];
        }
    }
    virtual ~Sketch()
    {
        delete[] a, delete[] b;
        for(int i = 0; i < m; ++i) delete[] tbl[i];
        delete[] tbl;
    }
    virtual void insert(int x) = 0;
    virtual int query(int x) = 0;
};

class Naive_hash : public Sketch
{
public:
    unordered_map<int, int> hash_map;
    Naive_hash() : Sketch(0, 0) {}
    void insert(int x)
    {
        total++, max_x = max(max_x, x);
        hash_map[x]++;
    }
    int query(int x)
    {
        return hash_map[x];
    }
};
// Count-Min Sketch
class CM_Sketch : public Sketch
{
    using Sketch::Sketch; // implicitly inherit constructer
public:
    void insert(int x)
    {
        total++, max_x = max(max_x, x);
        for(int i = 0; i < m; ++i)
        {
            tbl[i][hash(x, i)]++;
        }
    }
    int query(int x)
    {
        int res = INF;
        for(int i = 0; i < m; ++i)
        {
            int pos = hash(x, i);
            res = min(res, tbl[i][pos]);
        }
        return res;
    }
};
// Count-Unique Sketch
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
        for(int i = 0; i < m; ++i)
        {
            int pos = hash(x, i);
            pos_vec.push_back(pos);
            min_val = min(min_val, tbl[i][pos]);
        }
        for(int i = 0; i < m; ++i)
        {
            int pos = pos_vec[i];
            if(tbl[i][pos] == min_val) tbl[i][pos]++;
        }
    }
    int query(int x)
    {
        int res = INF;
        for(int i = 0; i < m; ++i)
        {
            int pos = hash(x, i);
            res = min(res, tbl[i][pos]);
        }
        return res;
    }
};
// Count-Sketch
class Count_Sketch : public Sketch
{
    using Sketch::Sketch;
public:
    int hash(int x, int i, int &sig)
    {
        int val = (1LL * a[i] * x % mo + b[i]) % mo;
        sig = (val & 1) ? 1 : -1;
        return val % n;
    }
    void insert(int x)
    {
        total++, max_x = max(max_x, x);
        for(int i = 0; i < m; ++i)
        {
            int sig, pos = hash(x, i, sig);
            tbl[i][pos] += sig;
        }
    }
    int query(int x)
    {
        static vector<int> e;
        e.clear();
        for(int i = 0; i < m; ++i)
        {
            int sig, pos = hash(x, i, sig);
            e.push_back(tbl[i][pos] * sig);
        }
        nth_element(e.begin(), e.begin() + m / 2, e.end());
        return e[m / 2];
    }
};
// Count-Mean-Min Sketch
class CMM_Sketch : public Sketch
{
    using Sketch::Sketch;
public:
    void insert(int x)
    {
        total++, max_x = max(max_x, x);
        for(int i = 0; i < m; ++i)
        {
            tbl[i][hash(x, i)]++;
        }
    }
    int query(int x)
    {
        static vector<int> e;
        e.clear();
        for(int i = 0; i < m; ++i)
        {
            int val = tbl[i][hash(x, i)];
            int noise = (total - val) / (n - 1);
            e.push_back(val - noise);
        }
        nth_element(e.begin(), e.begin() + m / 2, e.end());
        return e[m / 2];
    }
};
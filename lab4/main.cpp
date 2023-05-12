#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 2000;

double w[MAXN][MAXN];

void random_graph(int n)
{
    for(int i = 0; i < n; ++i)
        for(int j = i + 1; j < n; ++j)
        {
            w[i][j] = w[j][i] = rnd.next();
        }
}

double prim(int n)
{
    double res = 0;
    static double cost[MAXN];
    static bool flag[MAXN];
    for(int i = 0; i < n; ++i) cost[i] = n, flag[i] = false;
    cost[0] = 0;
    for(int i = 0; i < n; ++i)
    {
        int x = 0;
        double val = n;
        for(int j = 0; j < n; ++j)
            if(!flag[j] && cost[j] < val)
            {
                val = cost[j], x = j;
            }
        //printf("%d %.3lf\n", x, val);
        res += val;
        flag[x] = true;
        for(int j = 0; j < n; ++j)
            cost[j] = min(cost[j], w[x][j]);
    }
    return res;
}

int main(int argc, char **argv)
{
    registerGen(argc, argv, 1);
    int n = opt<int>("n");
    long clock_st = clock();
    int m = int(1e9) / n / n;
    double sum = 0;
    for(int i = 0; i < m; ++i)
    {
        random_graph(n);
        sum += prim(n);
    }
    long clock_en = clock();
    puts("------------------");
    printf("n = %d, m = %d\n", n, m);
    printf("E[val(MST)] = %.10lf\n", sum / m);
    printf("runtime = %.3lf sec\n", 1.0 * (clock_en - clock_st) / CLOCKS_PER_SEC);
    return 0;
}
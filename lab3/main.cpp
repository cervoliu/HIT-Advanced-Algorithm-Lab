#include "testlib.h"
#include "naive.h"
#include "bloomFilter.h"
#include <bits/stdc++.h>

using namespace std;

char outfile[30];

int Random(int l, int r) { return rnd.next(l, r); }

int main(int argc, char **argv)
{
    registerGen(argc, argv, 1);
    int method = opt<int>("M"), bitNum = opt<int>("N"), hashNum = opt<int>("K");
    sprintf(outfile, "%s.out", method == 0 ? "naive" : "bloomFilter");
    freopen("bloomFilter.in", "r", stdin);
    freopen(outfile, "w", stdout);
    long clock_st = clock();
    if(method == 0) //naive
    {
        for(int type, x; scanf("%d %d", &type, &x) != EOF; )
        {
            if(type == 0) //insert
            {
                naive::ins(x);
            }
            else //query
            {
                printf("%d\n", naive::query(x));
            }
        }
    }
    else //bloomFilter
    {
        bloomFilter filter(bitNum, hashNum);
        for(int type, x; scanf("%d %d", &type, &x) != EOF; )
        {
            if(type == 0) //insert
            {
                filter.ins(x);
            }
            else
            if(type == 1) //delete
            {
                filter.del(x);
            }
            else //query
            {
                printf("%d\n", filter.query(x));
            }
        }
    }
    long clock_en = clock();
    printf("runtime = %.3lf\n", (clock_en - clock_st) / CLOCKS_PER_SEC);
    fclose(stdin);
    fclose(stdout);
    return 0;
}
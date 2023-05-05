#include "testlib.h"
#include "naive.h"
#include "bloomFilter.h"
#include <bits/stdc++.h>

using namespace std;

char outname[30];

int Random(int l, int r) { return rnd.next(l, r); }

int main(int argc, char **argv)
{
    registerGen(argc, argv, 1);
    int method = opt<int>("M");
    
    FILE *fin = fopen("bloomFilter.in", "r"), *fout;
    long clock_st = clock();
    if(method == 0) // naive
    {
        sprintf(outname, "naive.out");
        fout = fopen(outname, "w");
        for(int type, x; fscanf(fin, "%d %d", &type, &x) != EOF; )
        {
            if(type == 0) //insert
            {
                naive::ins(x);
            }
            else //query
            {
                fprintf(fout, "%d\n", naive::query(x));
            }
        }
    }
    else
    if(method == 1) // unordered_multiset
    {
        sprintf(outname, "unordered_multiset.out");
        fout = fopen(outname, "w");
        unordered_multiset<int> myset;
        myset.clear();
        for(int type, x; fscanf(fin, "%d %d", &type, &x) != EOF; )
        {
            if(type == 0) //insert
            {
                myset.insert(x);
            }
            else
            if(type == 1) //del
            {
                myset.erase(myset.find(x));
            }
            else //query
            {
                fprintf(fout, "%d\n", myset.find(x) != myset.end());
            }
        }
    }
    else            // bloomFilter
    {
        sprintf(outname, "bloomFilter.out");
        fout = fopen(outname, "w");
        int bitNum = opt<int>("N"), hashNum = opt<int>("K");
        bloomFilter filter(bitNum, hashNum);
        for(int type, x; fscanf(fin, "%d %d", &type, &x) != EOF; )
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
                fprintf(fout, "%d\n", filter.query(x));
            }
        }
    }
    fclose(fin);
    fclose(fout);
    long clock_en = clock();
    printf("runtime = %.3lf sec\n", 1.0 * (clock_en - clock_st) / CLOCKS_PER_SEC);
    return 0;
}
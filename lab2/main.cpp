#include "testlib.h"
#include "sort.h"
#include <bits/stdc++.h>
#include <cstdlib>

using namespace std;

char buff[50];

const int MAXN = 1e6;
int a[MAXN];

int Random(int l, int r) { return rnd.next(l, r); }

//usage ./sorter -M method -R rate
int main(int argc, char** argv)
{
    registerGen(argc, argv, 1);
    int method = opt<int>("M");
    assert((1 <= method && method <= 3) && "method should be 1, 2 or 3");
    
    int rate = opt<int>("R");
    assert((0 <= rate && rate <= 10) && "rate should be between 0 and 10");

    sprintf(buff, "./input/%d.in", rate * 10);
    FILE *fin = fopen(buff, "r");
    int n = 0;
    for(int x; fscanf(fin, "%d", &x) != EOF; )
        a[n++] = x;
    
    fclose(fin);

    sprintf(buff, "./output/%d_%d.out", rate * 10, method);
    FILE *fout = fopen(buff, "w");

    long clock_st = clock();
    if(method == 1) //naive quick sort
    {
        naive::QuickSort(a, 0, n - 1);
    }
    else
    if(method == 2) //3-way quick sort
    {
        improved::QuickSort(a, 0, n - 1);
    }
    else
    if(method == 3) //std::sort
    {
        sort(a, a + n);
    }
    long clock_en = clock();

    for(int i = 0; i < n; ++i)
        fprintf(fout, "%d\n", a[i]);
    fclose(fout);

    sprintf(buff, "./output/runtime_%d.out", method);
    fout = fopen(buff, "a");
    fprintf(fout, "method = %d, rate = %d, runtime = %.3lf\n",
            method, rate, 1.0 * (clock_en - clock_st) / CLOCKS_PER_SEC);
    fclose(fout);
    return 0;
}
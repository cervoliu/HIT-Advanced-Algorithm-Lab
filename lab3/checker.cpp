#include <bits/stdc++.h>

using namespace std;

int main()
{
    FILE *f1 = fopen("unordered_multiset.out", "r");
    if(f1 == NULL) f1 = fopen("naive.out", "r");
    if(f1 == NULL)
    {
        puts("standard output not exist");
        return 1;
    }
    FILE *f2 = fopen("bloomFilter.out", "r");
    if(f2 == NULL)
    {
        puts("test(bloomFilter) output not exist");
        return 2;
    }
    int diff = 0, total = 0;
    for(int x, y; fscanf(f1, "%d", &x) != EOF && fscanf(f2, "%d", &y) != EOF; ++total)
    {
        if(x != y) ++diff;
    }
    fclose(f1); fclose(f2);
    printf("error rate = %.8lf\n", 1.0 * diff / total);
    return 0;
}
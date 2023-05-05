#include <bits/stdc++.h>

using namespace std;

int main()
{
    FILE *f1 = fopen("naive.out", "r"), *f2 = fopen("bloomFilter.out", "r");
    int diff = 0, total = 0;
    for(int x, y; fscanf(f1, "%d", &x) != EOF && fscanf(f2, "%d", &y) != EOF; ++total)
    {
        if(x != y) ++diff;
    }
    fclose(f1); fclose(f2);
    printf("error rate = %.8lf\n", 1.0 * diff / total);
    return 0;
}
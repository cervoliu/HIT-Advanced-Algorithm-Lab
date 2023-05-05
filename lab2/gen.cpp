#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

const int N = 1e6;

int randint(int n)
{
    return rnd.next(n);
}

int arr[N + 5];
char filename[20];

int main(int argc, char** argv)
{
    registerGen(argc, argv, 1);
    FILE* fout;
    for(int rate = 0; rate <= 10; ++rate)
    {
        sprintf(filename, "./input/%d.in", rate * 10);
        fout = fopen(filename, "w");
        for(int i = 0; i < N; ++i)
            arr[i] = i;
        shuffle(arr, arr + N);
        int bound = N / 10 * rate;
        for(int i = 1; i < bound; ++i)
            arr[i] = arr[0];
        shuffle(arr, arr + N);
        for(int i = 0; i < N; ++i)
            fprintf(fout, "%d\n", arr[i]);
        fclose(fout);
        printf("N = %d, rate = %d\n", N, rate);
    }
    return 0;
}
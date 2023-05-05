#include "testlib.h"
using namespace std;

int Random(int l, int r) { return rnd.next(l, r); }
int main(int argc, char **argv)
{
    registerGen(argc, argv, 1);
    freopen("bloomFilter.in", "w", stdout);
    int q = 1000000;
    while(q--)
    {
        int type = Random(0, 2);
        if(type == 1) type = 2;
        int x = Random(1, 1000000);
        printf("%d %d\n", type, x);
    }
    return 0;
}
#include "sort.h"
#include <algorithm>

extern int Random(int l, int r);

namespace naive
{
    int Rand_Partition(int *A, int p, int r)
    {
        int i = Random(p, r);
        std::swap(A[r], A[i]);
        int x = A[r];
        i = p - 1;
        for (int j = p; j < r; ++j)
            if (A[j] <= x)
            {
                i++;
                std::swap(A[i], A[j]);
            }
        std::swap(A[i + 1], A[r]);
        return i + 1;
    }

    void QuickSort(int *A, int p, int r)
    {
        if (p < r)
        {
            int q = Rand_Partition(A, p, r);
            QuickSort(A, p, q - 1);
            QuickSort(A, q + 1, r);
        }
    }
}

namespace improved
{
    void QuickSort(int *A, int l, int r)
    {
        if(l >= r) return;
        int p = Random(l, r);
        int pivot = A[p];
        std::swap(A[l], A[p]);
        int i = l + 1, j = l, k = r + 1;
        while (i < k)
        {
            if(A[i] < pivot)
            {
                std::swap(A[i++], A[++j]);
            }
            else
            if(A[i] > pivot)
            {
                std::swap(A[i], A[--k]);
            }
            else i++;
        }
        std::swap(A[l], A[j]);
        QuickSort(A, l, j - 1); // < pivot
        QuickSort(A, k, r); // > pivot
    }
}
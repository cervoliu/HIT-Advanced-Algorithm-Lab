#pragma once

namespace naive
{
    int Rand_Partition(int *A, int p, int r);
    void QuickSort(int *A, int p, int r);
}

//3-way radix quick sort
namespace improved
{
    int Rand_Partition(int *A, int p, int r);
    void QuickSort(int *A, int p, int r);   
}
#include "mergesort_opt.h"
#include <string.h>
void merge(int src1[], int src2[], int dst[], int n)
{
    int i1 = 0, i2 = 0, id = 0;
    while (i1 < n && i2 < n) {
        if (src1[i1] < src2[i2])
            dst[id++] = src1[i1++];
        else
            dst[id++] = src2[i2++];
    }
    if (i1 < n)
        memcpy(dst+id,src1+i1,sizeof(int)*(n-i1));
    else
        memcpy(dst+id,src2+i2,sizeof(int)*(n-i2));
}

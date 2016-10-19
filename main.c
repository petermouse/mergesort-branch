#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

void merge(int src1[], int src2[], int dst[], int n)
{
    int i1 = 0, i2 = 0, id = 0;
    while (i1 < n && i2 < n) {
        if (src1[i1] < src2[i2])
            dst[id++] = src1[i1++];
        else
            dst[id++] = src2[i2++];
    }
    while (i1 < n)
        dst[id++] = src1[i1++];
    while (i2 < n)
        dst[id++] = src2[i2++];
}
int main()
{
    int number;
    int i;
    struct timespec start,end;
    double cpu_time;
    FILE *fp = fopen("testcase.txt","r");
    if( fp == NULL ) {
        printf("Can't open the file\n");
        return -1;
    }
    fscanf(fp,"%d",&number);
    int* src1 = (int *)malloc(sizeof(int)*number);
    if( src1 == NULL ) {
        printf("Can't allocate memory\n");
        return -1;
    }
    int* src2 = (int *)malloc(sizeof(int)*number);
    if( src2 == NULL ) {
        printf("Can't allocate memory\n");
        return -1;
    }
    int* dst  = (int *)malloc(sizeof(int)*number*2);
    if( dst == NULL ) {
        printf("Can't allocate memory\n");
        return -1;
    }

    for(i=0; i<number; i++)
        fscanf(fp,"%d",&src1[i]);
    for(i=0; i<number; i++)
        fscanf(fp,"%d",&src2[i]);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    merge(src1,src2,dst,number);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    cpu_time = diff_in_second(start,end);
    printf("execution time: %lf\n",cpu_time);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include IMPL

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

int main()
{
    int number;
    struct timespec start,end;
    double orig_time,opt_time;
    FILE *time_out;
    FILE *result_out;
    FILE *src_file = fopen("testcase.txt","r");
    if( src_file == NULL ) {
        printf("Can't open the file\n");
        return -1;
    }
    fscanf(src_file,"%d",&number);
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

    for(int i=0; i<number; i++)
        fscanf(src_file,"%d",&src1[i]);
    for(int i=0; i<number; i++)
        fscanf(src_file,"%d",&src2[i]);

    fclose(src_file);

#ifndef OPT
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    merge(src1,src2,dst,number);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    orig_time = diff_in_second(start,end);
    time_out=fopen("orig.txt","a");
    fprintf(time_out,"%lf\n",orig_time);
    fclose(time_out);

    printf("execution time: %lf\n",orig_time);
    result_out = fopen("ans_orig.txt","w");
#else
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    merge(src1,src2,dst,number);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    opt_time = diff_in_second(start,end);
    time_out=fopen("opt.txt","a");
    fprintf(time_out,"%lf\n",opt_time);
    fclose(time_out);
 
    printf("executon time: %lf\n",opt_time);
    result_out = fopen("ans_opt.txt","w");
#endif

    number*=2;
    for(int i=0;i<number;i++)
        fprintf(result_out,"%d ",dst[i]);
    free(src1);
    free(src2);
    free(dst);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int compare(const void *a,const void *b)
{
    return *(int *) a - *(int *)b;
}

int main(int argc,char* argv[])
{
    if(argc < 4) {
        printf("Usage:/gen_testcase [number] [src1_range] [src2_range]\n");
        return -1;
    }
    int number = atoi(argv[1]);
    int src1_range = atoi (argv[2]);
    int src2_range = atoi (argv[3]);
    int i;
    FILE *fp = fopen("testcase.txt","w");
    if(fp == NULL) {
        printf("Can't not open a file\n");
        return -1;
    }
    int *arr=(int *)malloc(sizeof(int)*number);
    if(arr == NULL) {
        printf("Can't allocate memory\n");
        return -1;
    }
    srand(time (NULL));
    fprintf(fp,"%d\n",number);

    for(i=0; i<number; i++)
        arr[i]=rand()%src1_range;

    qsort(arr,number,sizeof(int),compare);

    for(i=0; i<number; i++)
        fprintf(fp,"%d ",arr[i]);

    fprintf(fp,"\n");

    for(i=0; i<number; i++)
        arr[i]=rand()%src2_range;

    qsort(arr,number,sizeof(int),compare);

    for(i=0; i<number; i++)
        fprintf(fp,"%d ",arr[i]);

    free(arr);

    return 0;
}

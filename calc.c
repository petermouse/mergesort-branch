#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    double orig=0;
    double opt=0;
    double temp;
    int i=0;
    FILE *fp=fopen("orig.txt","r");
    while(fscanf(fp,"%lf",&temp)!=EOF)
    {
        orig+=temp;
        i++;
    }
    orig/=i;
    fclose(fp);
    i=0;
    fp=fopen("opt.txt","r");
    while(fscanf(fp,"%lf",&temp)!=EOF)
    {
        opt+=temp;
        i++;
    }
    opt/=i;
    printf("orig average time(s):%lf\n",orig);
    printf("opt average time(s):%lf\n",opt);
    return 0;
}

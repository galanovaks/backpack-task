#include <stdio.h>
#include <stdlib.h>
#include "solver.h"

int main()
{
    int n,K,j,**list;
    char files[18][11]={"ks_100_0","ks_10000_0","ks_100_2",  
    "ks_200_0","ks_30_0","ks_4_0","ks_400_0","ks_50_0","ks_50_1",
    "ks_1000_0","ks_100_1","ks_19_0","ks_200_1","ks_300_0","ks_40_0",
    "ks_45_0","ks_500_0","ks_60_0"};
    FILE *f;
//    for(j=0;j<18;j++)
//    {
        f=fopen(files[11],"r");
        fscanf(f,"%d %d",&n,&K);
        list=create_list(n,K,f);
        printf("%s-",files[11]);
        fclose(f);
//        solution(g,v);
        output_list(n,list);
//        printf("\n");
//    }
    return 0;
}

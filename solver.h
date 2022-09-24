int **create_list(int n,int K,FILE *f)
{
    int **list,i;
    list=malloc(n*sizeof(int*));
    for (i=0;i<n;i++)
    {
        list[i]=malloc(3*sizeof(int));
        fscanf(f,"%d %d",&list[i][0],&list[i][1]);
        if (list[i][1]>K)
            list[i][2]=-2;
        else
            list[i][2]=0;
    }
    return list;
}

void output_list(int n,int **list)
{
    int i;
    for (i=0;i<n;i++)
        printf("%d-%d,%d,%d\n",i,list[i][0],list[i][1],list[i][2]);
}


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

void exchange(int **list,int l,int r)
{
    int temp;
    temp=list[r][0];
    list[r][0]=list[l][0];
    list[l][0]=temp;
    temp=list[r][1];
    list[r][1]=list[l][1];
    list[l][1]=temp;
    temp=list[r][2];
    list[r][2]=list[l][2];
    list[l][2]=temp;
}

void sort(int left,int right,int **list,int var)
{
    int l=left,r=right;
    int ref=list[(r+l)/2][var];
    while (l<=r)
    {
        while (list[l][var]<ref)
            l++;
        while (list[r][var]>ref)
            r--;
        if (l<=r)
        {
            exchange(list,l,r);
            l++;
            r--;
        }
    }
    if (left<r)
        sort(left,r,list,var);
    if (right>l)
        sort(l,right,list,var);
}

void psort(int left,int right,int **list,int var)
{
    int l=left,r=right,prev=r-1;
    while((prev>l)&&(list[r][var]<list[prev][var]))
    {
        exchange(list,prev,r);
        r=prev;
        prev--;
    }
}

void indispensability(int n, int **list)
{
    int i,j,w,v;
    sort(0,n-1,list,1);
    list[0][1]=1;
    for (i=1;i<n;i++)
    {
        psort(0,i-1,list,0);
        w=list[i][1];
        v=0;
        for (j=i-1;j>=0;j--)
        {
            if ((list[j][2]!=-2)&&(list[j][1]<=w))
            {
                w-=list[j][1];
                v+=list[j][0];
            }
        }
        if (list[i][0]<=v)
            list[i][2]=-2;
        else
            list[i][2]=1;
    }
}

void solution(int **list, int n, int K)
{
    indispensability(n,list);
    output_list(n,list);
}

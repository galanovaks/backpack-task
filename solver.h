int **create_list(int n,int K,FILE *f)
{
    int **list,i;
    list=malloc(n*sizeof(int*));
    for (i=0;i<n;i++)
    {
        list[i]=malloc(5*sizeof(int));
        fscanf(f,"%d %d",&list[i][0],&list[i][1]);
        if (list[i][1]>K)
            list[i][2]=-2;
        else
            list[i][2]=0;
        list[i][3]=i;
        list[i][4]=0;
    }
    return list;
}

void output_list(int n,int **list)
{
    int i;
    for (i=0;i<n;i++)
        printf("%d-%d,%d,%d,%d,%d\n",i,list[i][0],list[i][1],list[i][2],list[i][3],list[i][4]);
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
    temp=list[r][3];
    list[r][3]=list[l][3];
    list[l][3]=temp;
    temp=list[r][4];
    list[r][4]=list[l][4];
    list[l][4]=temp;
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

int indispensability(int n, int **list,int W)
{
    int i,j,v,V=list[0][0],w,W1=list[0][1],res=1;
    list[0][2]=1;
    if (list[0][1]>W)
        return -1;
    for (i=1;i<n;i++)
    {
        if (list[i][2]==-2)
            continue;
        int *cand=malloc(i*sizeof(int));
        for (j=0;j<i;j++)
            cand[j]=-2;
        v=list[i][0];
        w=W-list[i][1];
        for (j=i-1;j>=0;j--)
        {   
            if (list[j][1]<=w)
            {
                    w-=list[j][1];
                    v+=list[j][0];
                    cand[j]=1;
            }
        }
        w=W-w;
        if ((V<v)||((V==v)&&(W1>w)))
        {
            V=v;
            W1=w;
            res=1;
            for (j=0;j<i;j++)
            {
                list[j][2]=cand[j];
                if (cand[j]==1)
                    res++;
            }
            list[i][2]=1;
        }
        else
            list[i][2]=-2;
        
    }
    return res;
}

void solution(int **list, int n, int K)
{
    int w=K,i,ind,res=0,f=0,wres=0,provres=0;
//    output_list(n,list);
    sort(0,n-1,list,0);
    ind=indispensability(n,list,w);
    while (f==0)
    {
        for (i=n-1;(i>=0)&&(ind>0);i--)
        {
            if ((list[i][4]==0)&&(list[i][2]==1)&&(list[i][1]<=w))
            {
                w-=list[i][1];
                res+=list[i][0];
                ind--;
                list[i][4]=1;
            }
        }
        f=-1;
        for (i=0;i<n;i++)
            if ((list[i][4]==1)||(list[i][1]>w))
                list[i][2]=-2;
            else
            {
                list[i][2]=0;
                f=0;
            }
        ind=indispensability(n,list,w);
    }
//    output_list(n,list);
    sort(0,n-1,list,3);
//    output_list(n,list);
    printf("%d\n",res);
    for (i=0;i<n;i++)
    {
//        printf("%d ",list[i][4]);
        if (list[i][4]==1)
        {
            provres+=list[i][0];
            wres+=list[i][1];
        }
    }
    if ((wres<=K)&&(provres==res))
        printf("OK\n");
    else
        printf("FATAL ERROR");

}

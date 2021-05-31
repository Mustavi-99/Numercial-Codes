#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout<<"n= ";
    cin>>n;
    float x,sum=0,p;
    float xi[n],f[n],d[n][n],a[n];
    for(int i=1; i<=n; i++)
    {
        cout<<"x["<<i<<"]: ";
        cin>>xi[i];
        cout<<"f["<<i<<"]: ";
        cin>>f[i];
    }
    for(int i=1; i<=n; i++)
    {
        d[i][1]=f[i];
    }
    for(int j=2; j<=n; j++)
    {
        for(int i=1; i<=n-j+1; i++)
        {
            d[i][j]=(d[i+1][j-1]-d[i][j-1])/(xi[i+j-1]-xi[i]);
        }

    }
    int k=n;
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<d[i][j]<<"\t";
        }
        cout<<endl;
    }
    for(int i=1; i<=n; i++)
    {
        a[i]=d[1][i];
    }
    cout<<a[2]<<"-"<<endl;
    cout<<"x= ";
    cin>>x;
    sum=a[1];
    for(int i=2; i<=n; i++)
    {
        p=1;
        for(int j=1; j<=i-1; j++)
        {
            p*=x-xi[j];
        }
        sum+=a[i]*p;
    }
    cout<<"sum= "<<sum<<endl;
    return 0;
}

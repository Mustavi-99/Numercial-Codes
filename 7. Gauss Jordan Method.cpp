#include<bits/stdc++.h>
using namespace std;

int i,j,k,n;

void showMatrix(double a[100][100])
{
    cout<<"\n\nGiven equation:"<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<=n;j++)
        {
            if(j<n)
            {
                cout<<a[i][j]<<"x"<<j+1;
                if(j<n-1&&a[i][j+1]>=0)
                    cout<<"+";
            }
            else
            {
                cout<<"= "<<a[i][j];
            }

        }
        cout<<endl;
    }
}

int main()
{
    cout<<"Enter order of matrix= ";
    cin>>n;
    double a[100][100],x[n],sum;
    double p;
    cout<<"Enter elements:"<<endl;
    for(i=0;i<n;i++)
        for(j=0;j<=n;j++)
        {
            cout<<i+1<<"."<<j+1<<"= ";
            cin>>a[i][j];
        }
    showMatrix(a);
    int n1=0;
    while(n1<n)
    {
        p=a[n1][n1];
        for(j=0;j<=n;j++)
            a[n1][j]/=p;
        showMatrix(a);
        for(k=0;k<n;k++)
        {
            p=a[k][n1];
            for(j=0;j<=n;j++)
            {
                if(k!=n1)
                {
                    a[k][j]-=p*a[n1][j];
                }
            }

        }
        showMatrix(a);
        n1++;
    }
    showMatrix(a);
    for(i=0;i<n;i++)
        x[i]=a[i][n]/a[i][i];
    cout<<"Solution:"<<endl;
    for(i=0;i<n;i++)
        cout<<"x"<<i+1<<"= "<<x[i]<<endl;
    return 0;
}


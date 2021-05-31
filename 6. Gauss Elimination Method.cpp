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
    double a[100][100],x[n],sum,p;
    cout<<"Enter elements:"<<endl;
    for(i=0;i<n;i++)
        for(j=0;j<=n;j++)
        {
            cout<<i+1<<"."<<j+1<<"= ";
            cin>>a[i][j];
        }
    showMatrix(a);
    for(k=0;k<n-1;k++)
    {
        for(i=k+1;i<n;i++)
        {
            p=a[i][k]/a[k][k];
            for(j=k;j<=n;j++)
              a[i][j]-=a[k][j]*p;
        }
        showMatrix(a);
    }
    showMatrix(a);
    x[n-1]=a[n-1][n]/a[n-1][n-1];
    for(i=n-2;i>=0;i--)
    {
        sum=0;
        for(j=i+1;j<n;j++)
            sum+=a[i][j]*x[j];
        x[i]=(a[i][n]-sum)/a[i][i];
    }
    cout<<"Solution:"<<endl;
    for(i=0;i<n;i++)
        cout<<"x"<<i+1<<"= "<<x[i]<<endl;
    return 0;
}

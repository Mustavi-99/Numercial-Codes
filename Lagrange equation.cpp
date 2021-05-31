#include<bits/stdc++.h>
using namespace std;
#define n 4

float denominator(int i,float x[])
{
    float m=1;
    for(int j=0; j<n; j++)
    {
        if(i!=j)
            m*=x[i]-x[j];
    }
    return m;
}
float var_less_coeffi(int i,float x[])
{
    float m=1;
    for(int j=0; j<n; j++)
    {
        if(i!=j)
            m*=-x[j];
    }
    return m;
}
float redu_var_coeffi(int i,float x[])
{
    float sum=0;
    for(int j=0; j<n; j++)
    {
        if(i!=j)
            sum-=x[j];
    }
    return sum;
}
float sq_var_coeffi(int i,float x[])
{
    float sum=0;
    for(int j=0; j<n; j++)
    {
        float m=1;
        if(i!=j)
        {
            for(int k=0; k<n; k++)
            {
                if(k!=j&&k!=i)
                    m*=-x[k];
            }
            sum+=m;
        }
    }
    return sum;
}
void showl(float l[100][100])
{
    for(int i=0; i<n; i++)
    {
        cout<<"(";
        for(int j=0; j<n; j++)
        {
            cout<<l[i][j]<<"x^"<<n-j-1;
            if(l[i][j+1]>0&&j<n-1)
                cout<<"+";
        }
        cout<<")/"<<l[i][n];
        cout<<endl;
    }
}
int main()
{
    float x[100],f[100],l[100][100];
    for(int i=0; i<n; i++)
    {
        cout<<"x["<<i<<"]: ";
        cin>>x[i];
        cout<<"f["<<i<<"]: ";
        cin>>f[i];
    }
    for(int i=0; i<n; i++)
    {
        l[i][0]=1;
        l[i][1]=redu_var_coeffi(i,x);
        l[i][2]=sq_var_coeffi(i,x);
        l[i][n-1]=var_less_coeffi(i,x);
        l[i][n]=denominator(i,x);
    }
    showl(l);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            l[i][j]=f[i]*l[i][j]/l[i][n];
        }
    }
    for(int i=0; i<n; i++)
    {
        l[n][i]=0;
        for(int j=0; j<n; j++)
        {
            l[n][i]+=l[j][i];
        }
    }
    for(int i=0; i<n; i++)
    {
        cout<<l[n][i]<<"x^"<<n-1-i;
        if(l[n][i+1]>=0&&i<n-1)
            cout<<"+";
    }
    return 0;
}

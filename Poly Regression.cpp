#include<bits/stdc++.h>
using namespace std;

#define max 10

double X[max],Y[max],C[max][max],A[max],B[max],Xt[max];
int N,MP,M;
double arr[10][10];



void Normal()
{
    int i,j,k;
    double L1,L2;

    for(j=1; j<=M; j++)
    {
        for(k=1; k<=M; k++)
        {
            C[j][k]=0.0;
            L1 = k+j-2;
            for(i=1; i<=N; i++)
            {
                C[j][k] = C[j][k] + pow(X[i],L1);
            }
        }
    }

    for(j=1; j<=M; j++)
    {
        B[j] = 0.0;
        L2 = j-1;
        for(i=1; i<=N; i++)
        {
            B[j] = B[j] + (Y[i] * pow(X[i],L2));
        }
    }
    /*for(i = 1; i<N; i++)
    {
        for(j=1; j<N; j++)
        {
            cout<<C[i][j]<<"   ";
        }
        cout<<endl;
    }*/
}

void Gauss()
{
    int k,i,j;
    double factor,sum;


    for(k=1; k<N-1; k++)
    {
        for(i=k+1; i<N; i++)
        {
            factor=C[i][k]/C[k][k];
            for(j=k+1; j<=N; j++)
            {
                C[i][j]=C[i][j]-C[k][j]*factor;
            }
            B[i] = B[i] - factor*B[k];
        }
    }

    Xt[N] = B[N]/C[N][N];

    for(k=N-1; k>=1; k--)
    {
        sum=0;
        for(j=k+1; j<M+1; j++)
        {
            sum = sum + (C[k][j]*Xt[j]);
        }

        Xt[k]=(B[k]-sum)/C[k][k];
    }

}



int main()
{
    int i,j,k;
    cout<<"Enter number of data points(n):"<<endl;
    cin>>N;
    cout<<"Enter order of polynomial required"<<endl;
    cin>>MP;

    cout<<"Enter data values x and y:"<<endl;
    for (i=1; i<=N; i++)
    {
        cin>>X[i];
        cin>>Y[i];
    }

    if(N <= MP)
    {
        cout<<"Regression not possible"<<endl;
        return 0;
    }

    M = MP+1;

    Normal();
    Gauss();

    for(i=1; i<=M; i++)
    {
        cout<<Xt[i]<<" ";
    }
    cout<<endl;
}

/*
4
2
1
6
2
11
3
18
4
27
*/

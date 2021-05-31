#include<bits/stdc++.h>
using namespace std;
int n;
double f(double arr[],double x)
{
    double result=0;
    for(int i=n;i>=0;i--)
        result=result*x+arr[i];
    return result;
}
double df(double arr[],double x)
{
    double result=0;
    for(int i=n;i>0;i--)
        result=result*x+i*arr[i];
    return result;
}
int main()
{
    cout<<"Enter highest order of equation= ";
    cin>>n;
    double x0,e=.001,root[n],xr,brr[n];
    double arr[n];
    cout<<"Enter the value of coefficients:"<<endl;
    for(int i=n;i>=0;i--)
    {
        cout<<"x^"<<i<<"::";
        cin>>arr[i];
    }
    cout<<"The Equation is:"<<endl;
    for(int i=n;i>=0;i--)
    {
        cout<<arr[i]<<"x^"<<i;
        if(arr[i-1]>=0&&i>0)
            cout<<"+";
    }
    cout<<"\nEnter initial estimate= ";
    cin>>x0;
    int _n=n,count=1;
    do
    {
        /*cout<<"The Equation is:"<<endl;
    for(int i=n;i>=0;i--)
    {
        cout<<arr[i]<<"x^"<<i;
        if(arr[i-1]>=0&&i>0)
            cout<<"+";
    }
    cout<<endl;
        */
        while(1)
        {
            xr=x0-f(arr,x0)/df(arr,x0);
            ///cout<<x0<<","<<xr<<"+++"<<abs((xr-x0)/xr)<<endl;
            if(abs((xr-x0))<.001)
            {
                break;
            }
            x0=xr;
        }
        root[n-1]=xr;
        brr[n]=0;
        for(int i=n-1;i>=0;i--)
        {
            brr[i]=arr[i+1]+brr[i+1]*xr;
        }
        n--;
        for(int i=n;i>=0;i--)
        {
            arr[i]=brr[i];
        }
        x0=xr;
    }while(n>1);
    root[0]=-arr[0]/arr[1];
    cout<<"Roots are= ";
    for(int i=0;i<=_n-1;i++)
        cout<<root[i]<<" ";
    cout<<endl;
    return 0;
}

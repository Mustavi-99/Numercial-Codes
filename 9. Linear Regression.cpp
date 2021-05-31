#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout<<"Input number of data points N"<<endl;
    cin>>n;
    double x[n],y[n],a,b;
    cout<<"Input x and y values"<<endl;
    for(int i=0; i<n; i++)
    {
        cout<<"x"<<i+1<<": ";
        cin>>x[i];
        cout<<"y"<<i+1<<": ";
        cin>>y[i];
    }

    double sumx=0;
    cout<<endl;
    cout<<"x"<<endl;
    for(int i=0; i<n; i++)
    {
        sumx+=x[i];
        cout<<x[i]<<endl;
    }
    cout<<">x= "<<sumx<<endl;
    cout<<endl;
    cout<<"y"<<endl;
    double sumy=0;
    for(int i=0; i<n; i++)
    {
        sumy+=y[i];
        cout<<y[i]<<endl;
    }
    cout<<">y= "<<sumy<<endl;
    cout<<endl;
    cout<<"x^2"<<endl;
    double sumxx=0;
    for(int i=0; i<n; i++)
    {
        sumxx+=x[i]*x[i];
        cout<<x[i]*x[i]<<endl;
    }
    cout<<">x^2= "<<sumxx<<endl;
    cout<<endl;
    cout<<"xy"<<endl;
    double sumxy=0;
    for(int i=0; i<n; i++)
    {
        sumxy+=x[i]*y[i];
        cout<<x[i]*y[i]<<endl;
    }
    cout<<">xy= "<<sumxy<<endl;
    cout<<endl;
    double xmean=sumx/n;
    double ymean=sumy/n;
    double denom=n*sumxx-sumx*sumx;
    b=(n*sumxy-sumx*sumy)/denom;
    cout<<"b = (n*>xy->x>y)/(n*>x^2-(>x)^2) = ";
    cout<<"("<<n<<"*"<<sumxy<<"-"<<sumx<<"*"<<sumy<<")/("<<n<<"*"<<sumxx<<"-("<<sumx<<")^2) = "<<b<<endl;
    a= ymean - b* xmean;
    cout<<"a = (>y-b>x)/n = ";
    cout<<"("<<sumy<<"-"<<b<<"*"<<sumx<<")/"<<n<<" = "<<a<<endl;
    cout<<"The coefficients are:\nA:: "<<a<<"\nB:: "<<b<<endl;
    return 0;
}

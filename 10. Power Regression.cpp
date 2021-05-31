#include<bits/stdc++.h>
using namespace std;

double f(double n)
{
    return log(n)/log(2.718281828);
}
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
    cout<<endl;
    cout<<"x"<<endl;
    double sumx=0;
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
    cout<<"ln(xi)"<<endl;
    double sumfx=0;
    for(int i=0; i<n; i++)
    {
        sumfx+=f(x[i]);
        cout<<f(x[i])<<endl;
    }
    cout<<">lnxi: "<<sumfx<<endl;
    cout<<endl;
    cout<<"ln(yi)"<<endl;
    double sumfy=0;
    for(int i=0; i<n; i++)
    {
        sumfy+=f(y[i]);
        cout<<f(y[i])<<endl;
    }
    cout<<">lnyi: "<<sumfy<<endl;
    cout<<endl;
    cout<<"{ln(xi)}^2"<<endl;
    double sumfxx=0;
    for(int i=0; i<n; i++)
    {
        sumfxx+=f(x[i])*f(x[i]);
        cout<<f(x[i])*f(x[i])<<endl;
    }
    cout<<">{ln(xi)}^2: "<<sumfxx<<endl;
    cout<<endl;
    cout<<"ln(xi)*ln(yi)"<<endl;
    double sumfxy=0;
    for(int i=0; i<n; i++)
    {
        sumfxy+=f(x[i])*f(y[i]);
        cout<<f(x[i])*f(y[i])<<endl;
    }
    cout<<">ln(xi)*ln(yi): "<<sumfxy<<endl;
    cout<<endl;
    double fxmean=sumfx/n;
    double fymean=sumfy/n;
    b=(n*sumfxy-sumfx*sumfy)/(n*sumfxx-sumfx*sumfx);
    double lna= fymean - b* fxmean;
    a=exp(lna);
    cout<<"The coefficients are:\nA:: "<<a<<"\nB:: "<<b<<endl;
    return 0;
}

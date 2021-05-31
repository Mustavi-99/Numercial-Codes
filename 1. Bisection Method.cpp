#include<bits/stdc++.h>
using namespace std;
int n;
double f(int arr[],double x)
{
    double result=0;
    for(int i=n;i>=0;i--)
        result=result*x+arr[i];
    return result;
}
int main()
{
    cout<<"Enter highest order of equation= ";
    cin>>n;
    int arr[n];
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
    cout<<endl;
    double a,b;
    cout<<"Choose limits:"<<endl;
    cout<<"a::";
    cin>>a;
    cout<<"b::";
    cin>>b;
    double f1=f(arr,a);
    double f2=f(arr,b);
    while(1)
    {
        if(f1*f2>0)
        {
            cout<<"Root does not exist within given limits."<<endl;
            cout<<"Choose new limits:"<<endl;
            cout<<"a::";
            cin>>a;
            cout<<"b::";
            cin>>b;
            f1=f(arr,a);
            f2=f(arr,b);
        }
        else
        {
            cout<<"Root exists within the given limits."<<endl;
            break;
        }
    }
    double x0,f0,root,es,xp=a;
    cout<<"Enter stopping criteria= ";
    cin>>es;
    int n1=1;
    while(1)
    {
        cout<<endl;
        cout<<endl;
        cout<<"Iteration "<<n1<<":"<<endl;
        cout<<"f("<<a<<")= "<<f1<<" and f("<<b<<")= "<<f2<<endl;
        cout<<"so f(a)f(b)<0"<<endl;
        cout<<"root lies between "<<a<<" and "<<b<<endl;
        x0=(a+b)/2;
        cout<<"x0 = a+b/2 = "<<a<<"+"<<b<<"/2 = "<<x0<<endl;
        f0=f(arr,x0);
        cout<<"f(x0) = f("<<x0<<")="<<f0<<endl;
        ///cout<<"a= "<<a<<"\tb= "<<b<<"\tx0= "<<x0<<"\tf(a)= "<<f1<<"\tf(b)= "<<f2<<"\tf(x0)= "<<f0<<endl;
        if(f0==0)
        {
            root=x0;
            break;
        }
        if(f1*f0<0)
            b=x0;
        else
            a=x0;
        cout<<"relative error = "<<"|"<<x0<<"-"<<xp<<"/"<<x0<<"|= "<<abs((x0-xp)/x0)<<endl;
        if(abs((x0-xp)/x0)<es)
        {
            root=(a+b)/2;
            break;
        }
        xp=x0;
        f1=f(arr,a);
        f2=f(arr,b);
        n1++;
    }
    cout<<"Root is= "<<root<<endl;
    return 0;
}

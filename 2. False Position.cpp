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
    double x1,x2;
    cout<<"Choose limits:"<<endl;
    cout<<"x1::";
    cin>>x1;
    cout<<"x2::";
    cin>>x2;
    double f1=f(arr,x1);
    double f2=f(arr,x2);
    while(1)
    {
        if(f1*f2>0)
        {
            cout<<"Root does not exist within given limits."<<endl;
            cout<<"Choose new limits:"<<endl;
            cout<<"x1::";
            cin>>x1;
            cout<<"x2::";
            cin>>x2;
            f1=f(arr,x1);
            f2=f(arr,x2);
        }
        else
        {
            cout<<"Root exists within the given limits."<<endl;
            break;
        }
    }
    double x0,f0,root,E,xp=x1;
    cout<<"Enter stopping criteria= ";
    cin>>E;
    int n1=1;
    while(1)
    {
        cout<<endl;
        cout<<endl;
        cout<<"Iteration "<<n1<<":"<<endl;
        cout<<"f("<<x1<<")= "<<f1<<" and f("<<x2<<")= "<<f2<<endl;
        cout<<"so f(x1)f(x1)<0"<<endl;
        cout<<"root lies int the interval between "<<x1<<" and "<<x2<<endl;
        x0=x1-f1*(x2-x1)/(f2-f1);
        cout<<"x0 = x1-f1*(x2-x1)/(f2-f1) = "<<x1<<"-"<<f1<<"*("<<x2<<"-"<<x1<<")/("<<f2<<"-"<<f1<<")="<<x0<<endl;
        f0=f(arr,x0);
        cout<<"f(x0) = f("<<x0<<")="<<f0<<endl;
        ///cout<<"x1= "<<x1<<"\tx2= "<<x2<<"\tx0= "<<x0<<"\tf(x1)= "<<f1<<"\tf(x2)= "<<f2<<"\tf(x0)*f(x1)= "<<f0*f1<<endl;
        if(f0*f1<0)
            x2=x0;
        else
            x1=x0;
        cout<<"relative error = "<<"|"<<x0<<"-"<<xp<<"/"<<x0<<"|= "<<abs((x0-xp)/x0)<<endl;
        if(abs((x0-xp)/x0)<E)
        {
            root=x0;
            break;
        }
        xp=x0;
        n1++;
        f1=f(arr,x1);
        f2=f(arr,x2);
    }
    cout<<"Root ="<<root<<endl;
    return 0;
}

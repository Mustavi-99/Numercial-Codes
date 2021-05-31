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
double df(int arr[],double x)
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
    double x0,E,x1,root;
    cout<<"Enter initial value= ";
    cin>>x0;
    cout<<"Enter specified error= ";
    cin>>E;
    double f0,df0;
    int n1=1;
    cout<<"Iteration "<<n1<<":"<<endl;
    cout<<"x"<<n+1<<" = x"<<n1<<"-f(x"<<n1<<")/f'(x"<<n1<<")="<<x0<<"-"<<f(arr,x0)<<"/"<<df(arr,x0)<<"="<<x0-f(arr,x0)/df(arr,x0)<<endl;
    while(1)
    {
        if(n!=1)
        {
            cout<<"Iteration "<<n1<<":"<<endl;
            cout<<"x"<<n+1<<" = "<<x0<<"-"<<f(arr,x0)<<"/"<<df(arr,x0)<<"="<<x0-f(arr,x0)/df(arr,x0)<<endl;
        }
        f0=f(arr,x0);
        df0=df(arr,x0);
        x1=x0-f0/df0;
        //cout<<x1<<"--"<<endl;
        ///cout<<"x0= "<<x0<<"\tx1= "<<x1<<"\tf(x0)= "<<f0<<"\tf'(x0)= "<<df0<<endl;
        cout<<"relative error = "<<"|"<<x1<<"-"<<x0<<"/"<<x1<<"|= "<<abs((x1-x0)/x1)<<endl;
        if(abs((x1-x0)/x1)<E)
        {
            root=x1;
            break;
        }
        n1++;
        x0=x1;
    }
    cout<<"Root= "<<root<<endl;
    return 0;
}

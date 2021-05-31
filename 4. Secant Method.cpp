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

int main()
{
    cout<<"Enter highest order of equation= ";
    cin>>n;
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
    cout<<endl;
    double x1,x2,x3,E,root;
    cout<<"Enter two initial points: "<<endl;
    cout<<"x1:: ";
    cin>>x1;
    cout<<"x2:: ";
    cin>>x2;
    cout<<"Enter accuracy level= ";
    cin>>E;
    double f1,f2,f3;
    f1=f(arr,x1);
    f2=f(arr,x2);
    cout<<"x3 = x2 - ((f(x2) * (x2 - x1)) // (f(x2) – f(x1)))"<<endl;
    int n1=1;
    while(1)
    {
        cout<<endl;
        cout<<"Iteration "<<n1<<":"<<endl;
        if(n1!=1)
        cout<<"x1=x2="<<x1<<"\tx2=x3"<<x2<<endl;
        cout<<"f(x1) = f("<<x1<<") = "<<f1<<endl;
        cout<<"f(x2) = f("<<x2<<") = "<<f2<<endl;
        x3=x2-f2*(x2-x1)/(f2-f1);
        cout<<"x3 = "<<x2<<" - "<<f2<<"*("<<x2<<"-"<<x1<<")/("<<f2<<"-"<<f1<<")="<<x3<<endl;
        ///cout<<"x1= "<<x1<<"\tx2= "<<x2<<"\tx3= "<<x3<<"\tf(x1)= "<<f1<<"\tf(x2)= "<<f2<<endl;
        cout<<"relative error = "<<"|"<<x3<<"-"<<x2<<"/"<<x3<<"|= "<<abs((x3-x2)/x3)<<endl;
        if(abs((x3-x2)/x3)>E)
        {
            x1=x2;
            f1=f2;
            x2=x3;
            f2=f(arr,x3);
        }
        else
        {
            root=x3;
            break;
        }
        n1++;
    }
    cout<<"Root= "<<root<<endl;
    return 0;
}

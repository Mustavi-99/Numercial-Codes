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
    cout<<"Choose limits:"<<endl;
    double a,b;
    cout<<"a::";
    cin>>a;
    cout<<"b::";
    cin>>b;
    cout<<"Enter the increment interval= ";
    double _x;
    cin>>_x;
    double x1,x2,x0,e=.00001;
    double f1,f2,f0;
    cout<<"Roots are: "<<endl;
    x2=INT_MIN;
    while(x2<b)
    {
        x1=a;
        x2=x1+_x;
        f1=f(arr,x1);
        f2=f(arr,x2);
        if(f1*f2>0)
        {

            a=x2;
            continue;
        }
        while(1)
        {
            f1=f(arr,x1);
            f2=f(arr,x2);
            x0=(x1+x2)/2;
            f0=f(arr,x0);
            if(f1*f0<0)
            {
                x2=x0;
            }
            else
            {
                x1=x0;
            }
            if(fabs((x2-x1)/x2)<e)
            {
                cout<<(x1+x2)/2<<" ";
                a=x2;
                break;
            }

        }

    }
    return 0;
}

#include<bits/stdc++.h>
#include<math.h>
using namespace std;

int degree, N, a[100];
double f(double x)
{
    double poly[100];
    poly[degree] = a[degree];
    for (int i=degree; i>0; i--)
        poly[i-1] = poly[i]*x+a[i-1];

    return poly[0];
}

double g(double x)
{
    return 1 + 1 / x;
}

void fixedPoint(double x)
{
    printf("Iteration         x                 g(x)            f(x)");
    double x1;
    int i = 1;
    while(true)
    {
        x1 = x;
        x = g(x);
        printf("\n%d                %lf        %lf         %lf", i, x, g(x), f(x));
        if(fabs(f(x)) == 0 || fabs(f(x)) < 0.00000001)
            break;
        i++;
    }
    cout<<endl<<"Approximate Root: "<<x;
}

int main()
{
    cout<<"ENTER THE TOTAL NO. OF POWER::::";
    cin>>degree;
    cout<<"Enter last iteration: ";
    cin>>N;
    for(int i = 0; i <=degree; i++)
    {
        cout<<"x^"<<i<< "::";
        scanf("%d", &a[i]);
    }
    int x;
    cout<<"INTIAL: X0----> ";
    cin>>x;
    fixedPoint(x);
    return 0;
}

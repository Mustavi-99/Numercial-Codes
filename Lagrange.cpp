#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout<<"n= ";
    cin>>n;
    float x,y=0;
    float xi[n],yi[n],li[n];
    for(int i=0; i<n; i++)
    {
        cout<<"x["<<i<<"]: ";
        cin>>xi[i];
        cout<<"y["<<i<<"]: ";
        cin>>yi[i];
    }
    cout<<"x= ";
    cin>>x;
    for(int i=0; i<n; i++)
    {
        li[i]=1;
        for(int j=0; j<n; j++)
        {
            if(i!=j)
            {
                li[i]*=(x-xi[j])/(xi[i]-xi[j]);
            }

        }
        y+=li[i]*yi[i];
    }
    cout<<"y= "<<y<<endl;
    return 0;
}


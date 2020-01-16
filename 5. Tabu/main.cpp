#include <bits/stdc++.h>
using namespace std;
int table[4];
int tt;
string tabu(string x)
   {
int index=rand()%4;
        int j=0;
while(table[index]!=0 && j<100)
{index=rand()%4;
                 j++;
}
         if(j==100)
   return x;
 if(index==-1)
       {
 cout<<"All the entries are non-zero"<<endl;
        return x;
}
else{
  x[index]=(x[index]=='0')?'1':'0';
  for(int i=0;i<4;i++)
                       {
                          if(i==index)
                             table[i]=tt;
                          else if(table[i]>0)
                             table[i]--;
                        }
                       return x;
                   }
       }

int main()
{
string s,d;
cout<<"Enter start state"<<endl;
cin>>s;
cout<<"Enter goal state"<<endl;
cin>>d;
cout<<"Enter the tabu tenure"<<endl;
cin>>tt;
string x=s;
while(x!=d){
 string m=x;
  x=tabu(x);
   if(x==m)
     {
        cout<<"100 iterations are already done"<<endl;
        goto falg;
      }
      cout<<endl;
     cout<<"string is "<<x<<endl;
      for(int i=0;i<4;i++){
        cout<<table[i]<<" ";
      }

}
cout<<endl;
 cout<<"Goal test is reached"<<endl;
 falg:
return 0;
}

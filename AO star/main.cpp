#include <iostream>
#include<bits/stdc++.h>
using namespace std;

vector<int> inp;
int ctr = 0;
struct node
{
 int data;
 vector< vector<node* >* >v;
 bool mark;
 bool solved;
};
int edge_cost=0;
void insert(node* root)
{
 //cout<<"Enter data of node :"<<endl;
 root->data = inp[ctr++];
 //vector<vector<node*> >vec=root->v;
 //cout<<"Enter number of OR nodes for value "<<root->data<<" :"<<endl;
     int or_no;
     //cin>>or_no;
     or_no = inp[ctr++];
     for(int i=0;i<or_no;i++)
     {
     vector<node*>* ans=new vector<node*>;
     //cout<<"Enter number of AND nodes for "<<i+1<<"th or node for value "<<root->data<<" :"<<endl;
     int and_no;
     //cin>>and_no;
     and_no = inp[ctr++];
     for(int j=0;j<and_no;j++)
     {
         node* n=new node;
         n->solved=false;
         n->mark=false;
         insert(n);
         (*ans).push_back(n);
         //cout<<"inserted node with value"<<n->data<<endl;
     }
        root->v.push_back(ans);
     }

}
void aostar(node* root)
{
     vector<node*>* min_ans=new vector<node*>;
     (*min_ans).push_back(root);
     while(!root->solved)
     {
        node* next_node=root;
        stack<node*>st;
         while(next_node && next_node->mark)
         {
            if((next_node->v).size()==0)
            {
                root->solved=true;
                return;
            }
         int cost=INT_MAX;
         st.push(next_node);
         for(unsigned int i=0;i<next_node->v.size();i++)
         {
             vector<node*>*ans=(next_node->v)[i];
             vector<node*> ans_v=*ans;
             int temp_cost=0;
             for(unsigned int j=0;j<(ans_v.size());j++)
             {
             node* n=ans_v[j];
             temp_cost+=n->data;
             }
             if(temp_cost<cost)
             {
             min_ans=ans;
             cost=temp_cost;
             }
        }
     vector<node*> min_ans_v=*min_ans;
     next_node=NULL;
     for(unsigned int j=0;j<min_ans_v.size();j++)
     {
        if(min_ans_v[j]->mark)
         {
         next_node=min_ans_v[j];
         break;
         }
     }

     }

     vector<node*> min_ans_v=*min_ans;
     for(unsigned int j=0;j<min_ans_v.size();j++)
     {
     node* n=min_ans_v[j];
     cout<<"Open:"<<n->data<<endl;
     int final_cost=INT_MAX;
     if(n->v.size()==0)
     {
     n->mark=true;
     }
     else{
     for(unsigned int i=0;i<n->v.size();i++)
     {
         vector<node*>*ans=(n->v)[i];
         vector<node*> ans_v=*ans;
         int temp_cost=0;
     for(unsigned int j=0;j<(ans_v.size());j++)
     {
         node* n=ans_v[j];
         temp_cost+=n->data;
         temp_cost+=edge_cost;
     }
        if(temp_cost<final_cost)
         {
            final_cost=temp_cost;
         }
     }
     n->data=final_cost;
     n->mark=true;
     }
     cout<<"Closed: "<<n->data<<endl;
     }

     while(!st.empty())
     {
     node* n=st.top();
     //cout<<n->data<<" ";
     st.pop();
     int final_cost=INT_MAX;
     for(unsigned int i=0;i<n->v.size();i++)
     {
     vector<node*>*ans=(n->v)[i];
     vector<node*> ans_v=*ans;
     int temp_cost=0;
     for(unsigned int j=0;j<(ans_v.size());j++)
     {
     node* n=ans_v[j];
     temp_cost+=n->data;
     temp_cost+=edge_cost;
     }
     if(temp_cost<final_cost)
     {
     min_ans=ans;
     final_cost=temp_cost;
     }
     }
     n->data=final_cost;
     }
     cout<<endl;
     next_node=root;

     }
}
void print(node* root)
{
 if(root)
 {
 cout<<root->data<<" ";
 vector<vector<node*>* >vec=root->v;
 for(unsigned int i=0;i<(root->v).size();i++)
 {
 vector<node*>* ans=(root->v)[i];
 vector<node*> ans_v=*ans;
 for(unsigned int j=0;j<ans_v.size();j++)
 {
 node* n=ans_v[j];
 print(n);
 }
 }
 }
 return;
}

int main()
{
     node* root=new node;
     root->solved=false;
     root->mark=false;
     fstream file;
     string   f2;
     f2 = "AO_star_node.txt";
     file.open(f2.c_str());
    string s;
     while (file>>s)
     {
         stringstream t(s);
         int tmp;
         t>>tmp;
         inp.push_back(tmp);
    }
    file.close();
     insert(root);
     cout<<endl;
     cout<<"Edge Cost: "<<endl;
     edge_cost = inp[ctr];
     cout<<edge_cost;
     cout<<endl;
     cout<<"Tree:"<<endl;
     print(root);
     cout<<endl;
     aostar(root);
     cout<<"The min cost: "<<root->data<<endl;
     return 0;
}

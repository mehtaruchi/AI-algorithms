#include <bits/stdc++.h>
#include<iostream>
#include <fstream>
#include <list>
#include<map>
using namespace std;

typedef pair<int, int> pi;
map<int,int> m;
int cost=-1;
int beam;

class Graph
{
    int V;
    // Pointer to an array containing adjacency lists
    list<int> *adj;
    public:

        Graph(int V);

        void addEdge(int v, int w);

        void BFS(int s,int goal,int g[],int h[],int w[][100],int parent[],int beam);

};

Graph::Graph(int V)
{
    this->V = V;

    adj = new list<int>[V];
}

void Graph::addEdge(int v, int b)
{

    adj[v].push_back(b);
    //w[v][b]=c;// Add w to v’s list.
}

void Graph::BFS(int s,int goal,int g[],int h[],int w[][100],int parent[],int beam)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];

    for(int i = 0; i < V; i++)

        visited[i] = false;

    list<int> open;

    // Mark the current node as visited and enqueue it

    visited[s] = true;

    open.push_back(s);

    priority_queue<pi, vector<pi>, greater<pi> > pq;

    list<int>::iterator i;

    list<int>::iterator itr;

    map<int,int>::iterator itr1;


    while(!open.empty())

    {
        for(itr=open.begin();itr!=open.end();++itr)

        {

         int x=*itr;

         if(!(adj[x].empty()))

         {
            for (i = adj[x].begin(); i != adj[x].end(); ++i)
            {

            if(*i==goal)

            {
                g[*i]=g[x]+w[x][*i];

                cost=g[*i];

                parent[*i]=x;
                return;
            }

            if (!visited[*i])

            {
                visited[*i] = true;

                //insert in map

                pq.push(make_pair(h[*i], *i));

                g[*i]=g[x]+w[x][*i];

                parent[*i]=x;
            }
            }
            }
        }
        open.clear();

        int b=0;

        for(int j=0;j<beam;j++)

        {
            pair<int,int> top=pq.top();

            open.push_back(top.second);

            cout<<"Selecting nodes "<<top.second<<endl;

            pq.pop();

        }
        while(!pq.empty())
            pq.pop();
    }
}

void path(int i,int parent[])
{
    if(parent[i]==-1)
        cout<<i;
    else
    {
        path(parent[i],parent);

        cout<<i;
    }
}

int main()

{
    int v,e,beam;
    int source ,goal;
    int w[100][100];
    //take file input

    ifstream inFile;

    int a,b,c,x;

    inFile.open("datafile.txt");

    if (!inFile)
    {
    std::cout << "Unable to open file datafile.txt";
    exit(1);
    }

    if(inFile>>v>>e)
    {
        Graph g1(v);
        int g[v];
        g[0]=0;
        int h[v];
        int parent[v];
        parent[0]=-1;

        for(int i=0;i<v;i++)
        {
            inFile>>x;

            h[i]=x;
        }

        for(int i=0;i<e;i++)
        {
            if(inFile>>a>>b>>c)
            {
                w[a][b]=c;

                g1.addEdge(a, b);
            }
        }

        inFile>>beam;

        inFile>>source>>goal;

        g1.BFS(source,goal,g,h,w,parent,beam);

        if(cost==-1)
        cout<<"path not found";

        else
        {
        int i=goal;

        cout<<"Path to goal is : ";

        path(i,parent);
        cout<<endl;
        cout<<"Cost: "<<cost;
        }
    }

inFile.close();

    return 0;
}

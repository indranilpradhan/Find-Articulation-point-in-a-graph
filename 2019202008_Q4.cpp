#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

list<int> *adj;
unordered_map<int,int> unm;
int visitedtime = 0;
int lowtime[99999];
int parent[99999];
int visitingtime[99999];

int printadjlist(int m)
{
	for(int i=0; i<m;i++)
	{
		cout << "\n Adjacency list of vertex "
             << i << "\n head "; 
        for (auto x : adj[i]) 
           cout << "-> " << x; 
        printf("\n");
	} 
}

int min(int a, int b)
{
	if(a<=b)
		return a;
	else
		return b;
}

bool isarticulationpoint(int src,int child, int parent[], bool issatisfy)
{
	if((parent[src] == 99999 && child >= 2) || (parent[src] != 99999 && issatisfy == true))
		return true;
	else
		return false;
}

void dfs(int src,bool visited[])
{
	lowtime[src] = visitedtime;
	visitingtime[src] = visitedtime;
	visited[src] = true;
	visitedtime++;
	bool issatisfy = false;
	int child=0;
	list<int>::iterator vertex;
	
	for(vertex = adj[src].begin(); vertex != adj[src].end(); vertex++)
	{
		int flag1 = 0;
		int flag2 = 0;
		if(visited[*vertex] == false)
		{
			flag1 = 1;
			child++;
			parent[*vertex] = src;
			dfs(*vertex,visited);

			if(visitingtime[src] <= lowtime[*vertex])
			{
				flag2 =1;
				issatisfy = true;
			}
		}

		if(flag1 == 1)
		{
			if(flag2==1)
			{
				lowtime[src] = min(lowtime[src],lowtime[*vertex]);	
			}
		}
		else
		{
			lowtime[src] = min(lowtime[src],visitingtime[*vertex]);
		}
	}

	if(isarticulationpoint(src,child,parent,issatisfy))
		cout<<"articulation point "<<src<<endl;

}

int main()
{
	int m;
	cin>>m;
	adj = new list<int>[m];

	int n;
	cin>>n;
	int temp = m;
	while(n--)
	{
		int a;
		cout<<"First point ";
		cin>>a;
		int b;
		cout<<"Second point ";
		cin>>b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		cout<<endl;
	}

	printadjlist(m);

	bool visited[m];


	for(int i=0; i<m; i++)
	{
		visited[i] = false;
	}

	parent[3] = 99999;
	
	dfs(3,visited);
}

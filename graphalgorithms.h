#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include<bits/stdc++.h>
using namespace std;
class graphfunctions
{
    private:
    vector<vector<pair<int,int>>> graph;
    vector<int> distance;
    int matrix[20][20];
    bool visited[20]={0};
    const int INF=1e9;
    public:
    void helloworld(int x,int y)
    {
        cout<<"ans "<<x+y<<endl;
    }
    vector<vector<pair<int,int>>> build_adj_list(int n,int e)
    {
        graph=vector<vector<pair<int,int>>> (n);
        for(int i=0;i<e;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            graph[u].push_back({v,w});
            graph[v].push_back({u,w});
        }
        return graph;
    }
    void displaygraph(int n,vector<vector<pair<int,int>>> graph)
    {
        for(int i=0;i<n;i++)
        {
            cout<<i<<"->";
            for(auto k:graph[i])
            {
                cout<<k.first<<","<<k.second<<" ";
            }
            cout<<endl;
        }
    }
    vector<int> dijkistra(int n,int source,vector<vector<pair<int,int>>> graph)
    {
        int source;
        cin>>source;
        distance=vector<int> (n,INF);
        distance[source]=0;
        for(int i=0;i<n;i++)
        {
            for(auto k:graph[source])
            {
                if(distance[k.first]>distance[source]+k.second)
                {
                    distance[k.first]=distance[source]+k.second;
                }
            }
            visited[source]=true;
            int mindist=INT_MAX;
            for(int i=0;i<n;i++)
            {
                if(!visited[i] && distance[i]<mindist)
                {
                    source=i;
                    mindist=distance[i];
                }
            }
        }
        return distance;
    }
};
#endif
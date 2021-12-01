#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H

#include<bits/stdc++.h>
using namespace std;

struct wtEdge
{
    int u,v,weight;
};

class graphfunctions
{
    private:
    vector<vector<pair<int,int>>> weighted_graph;
    vector<vector<int>> unweighted_graph;
    vector<int> distance;
    vector<vector<int>> matrix;
    vector<wtEdge> edgelist;
    vector<bool> visited;
    vector<int> parent;
    const int INF=1e9;
    public:
    void helloworld(int x,int y)
    {
        cout<<"ans "<<x+y<<endl;
    }
    vector<vector<pair<int,int>>> build_weighted_list(int n,int e)
    {
        weighted_graph=vector<vector<pair<int,int>>> (n);
        for(int i=0;i<e;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            weighted_graph[u].push_back({v,w});
            weighted_graph[v].push_back({u,w});
        }
        return weighted_graph;
    }
    vector<vector<int>> build_unweighted_list(int n,int e)
    {
        unweighted_graph=vector<vector<int>> (n+1);
        for(int i=0;i<e;i++)
        {
            int u,v;
            cin>>u>>v;
            unweighted_graph[u].push_back(v);
            unweighted_graph[v].push_back(u);
        }
        return unweighted_graph;
    }
    vector<vector<int>> build_weighted_matrix(int n,int e)
    {
        unweighted_graph=vector<vector<int>> (n,vector<int>(n,INF));
        for(int i=0;i<e;i++)
        {
            int u,v,w;
            cin>>u>>v>>w;
            unweighted_graph[u][v]=w;
            unweighted_graph[v][u]=w;
        }
        return unweighted_graph;
    }
    vector<vector<int>> build_unweighted_matrix(int n,int e)
    {
        unweighted_graph=vector<vector<int>> (n,vector<int>(n,INF));
        for(int i=0;i<e;i++)
        {
            int u,v;
            cin>>u>>v;
            unweighted_graph[u][v]=1;
            unweighted_graph[v][u]=1;
        }
        return unweighted_graph;
    }
    vector<wtEdge> build_weighted_edge_list(int e)
    {
        edgelist=vector<wtEdge>(e);
        wtEdge edg;
        for(int i=0;i<e;i++)
        {
            cin>>edg.u>>edg.v>>edg.weight;
            edgelist.push_back(edg);
        }
        return edgelist;
    }
    void display_weighted_graph(int n,vector<vector<pair<int,int>>> graph)
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
    void display_unweighted_graph(int n,vector<vector<int>> graph)
    {
        for(int i=0;i<n;i++)
        {
            cout<<i<<"->";
            for(auto k:graph[i])
            {
                cout<<k<<" ";
            }
            cout<<endl;
        }
    }
    vector<int> dijkistra(int n,vector<vector<pair<int,int>>> graph,int source)
    {
        distance=vector<int> (n,INF);
        visited=vector<bool> (n+1,0);
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
    bool cycle_detect_sub(vector<vector<int>> graph,int n,int source)
    {
        visited[source]=1;
        for(auto k:graph[source])
        {
            if(k!=parent[source])
            {
                if(visited[k])  return 1;
                parent[k]=source;
                cycle_detect_sub(graph,n,k);
            }
        }
        return 0;
    }
    bool cycle_detect(vector<vector<int>> graph,int n,int source)
    {
        visited=vector<bool> (n+1,0);
        parent=vector<int> (n+1,-1);
        return cycle_detect_sub(graph,n,source);
    }
    vector<vector<int>> floyd_warshall(vector<vector<int>> graph,int n,int startvertex)
    {
        vector<vector<int>> dist(n,vector<int>(n+1,INF));
        for(int i=startvertex;i<startvertex+n;i++)
        {
            for(int j=startvertex;j<startvertex+n;j++)
            {
                dist[i][j]=graph[i][j];
            }
        }
        for(int k=startvertex;k<startvertex+n;k++)
        {
            for(int i=startvertex;i<startvertex+n;i++)
            {
                for(int j=startvertex;j<startvertex+n;j++)
                {
                    if (dist[i][j]>(dist[i][k]+dist[k][j])&&(dist[k][j]!=INF&&dist[i][k]!=INF))
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        return dist;
    }
    static bool Edgesortcmp(wtEdge e1,wtEdge e2)
    {
        return e1.weight<e2.weight;
    }
    vector<wtEdge> Kruskals(vector<wtEdge> Edgelist,int n,int e)
    {
        vector<wtEdge> ans;
        vector<int> group(n+1);
        for(int i=0;i<n+1;i++)  group[i]=i;
        sort(Edgelist.begin(),Edgelist.end(),Edgesortcmp);
        for(auto k:Edgelist)
        {
            if(group[k.u]!=group[k.v])
            {
                ans.push_back(k);
                int oldid=group[k.u],newid=group[k.v];
                for(int i=0;i<n+1;i++)
                {
                    if(group[i]==oldid)
                    {
                        group[i]=newid;
                    }
                }
            }
        }
        return ans;
    }
};
#endif

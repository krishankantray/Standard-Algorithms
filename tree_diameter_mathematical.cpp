#include <bits/stdc++.h>
using namespace std;

int point;
int dist;

// Proof : https://stackoverflow.com/q/20010472/6883777
void getFarthestPoint(vector<vector<int>>& adj, vector<bool>&vis, int cur, int d) {
    
    vis[cur] = true;
    if(d > dist) {
        dist=d;
        point = cur;
    }

    for(auto node:adj[cur]) {
        if(vis[node]) continue;
        getFarthestPoint(adj, vis, node, d+1);
    }
}

int main() {
    int n;
    cin>>n;
    vector<vector<int>>adj(n+1);
    vector<bool>vis(n+1, false);
    int a,b;
    for(int i=1; i<n; i++) {
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    point = 0;
    dist=0;
    getFarthestPoint(adj, vis, 1, 0);
    int newPoint = point;
    point = 0;
    dist = 0;
    vis = vector<bool>(n+1, false);
    getFarthestPoint(adj, vis, newPoint, 0);
    cout<<dist;

    return 0;
}
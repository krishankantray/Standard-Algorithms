#include "bits/stdc++.h"
using namespace std;

vector<int>startsFromNode;
vector<int>containsNode;
int diameter = -1;

// A generalised tree-diameter function that considers weight of the edges
void getDiameter(vector<vector<pair<int,int>>>& adj, int parent, int node) {
    vector<int>childrenMaxDiameters;
    for(auto neighbour:adj[node]) {
        if(neighbour.first == parent) continue;
        getDiameter(adj, node, neighbour.first);
        childrenMaxDiameters.push_back(startsFromNode[neighbour.first] + neighbour.second ); // for unweighted trees just replace the neighbour.second with 1
    }

    int maxWeight = -1, secondMaxWeight = -1 ;
    // this will not increase the time complexity of the algorithm because
    // each element will be inserted only once in the vector childrenMaxDiameters
    for(auto weight:childrenMaxDiameters) {
        if(weight >= maxWeight) {
            secondMaxWeight = maxWeight;
            maxWeight = weight;
        }
        else if(weight > secondMaxWeight) {
            secondMaxWeight = weight;
        }
    }
    startsFromNode[node]=0;
    if(maxWeight > 0)
        startsFromNode[node] = maxWeight;
    if(secondMaxWeight > 0 && maxWeight > 0)
        containsNode[node] = maxWeight + secondMaxWeight ;
    
    diameter = max(diameter, max(startsFromNode[node], containsNode[node]));
}

int main() {
    int n;
    cin>>n;
    vector<vector<pair<int,int>>>adj(n+1);
    vector<bool>vis(n+1, false);

    // Take Input
    int a,b;
    for(int i=1; i<n; i++) {
        cin>>a>>b;
        adj[a].push_back({b, 1});
        adj[b].push_back({a, 1});
    }

    startsFromNode = vector<int>(n+1, 0);
    containsNode = vector<int>(n+1, 0);
    getDiameter(adj, -1, 1);

    cout<<diameter;

    return 0;
}
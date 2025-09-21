#include "bits/stdc++.h"
using namespace std;

class Solution {
    public:
    // Custom comparator for priority_queue
    struct Comparator {
        bool operator()(const pair<int,int>& a, const pair<int,int>& b) {
            return a.second > b.second ; // note: in priority_queue, this compare leads to max element at top ( opposite to sort comparator)
        }
    };
    
    /**
     * Dijkstra algorithm, to return cost of path of all edges
    */
    vector<int> dijkstra(int nodeCount, vector<vector<int>> edges, int source) {
        vector<int>distances(nodeCount+1, INT_MAX);
        // build the adjacency list
        vector<vector<pair<int,int>>> adj(nodeCount+1);
        for(auto edge:edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }
        // maintain visited list
        vector<bool>visited(nodeCount+1,false);

        priority_queue<pair<int,int>, vector<pair<int,int>>, Comparator>pq;
        pq.push({source, 0});
        distances[source] = 0;

        while(!pq.empty()) {
            auto [node, weight] = pq.top();
            pq.pop();
            visited[node] = true;
            for(auto neighbour:adj[node]) {
                if(!visited[neighbour.first]) {
                    pq.push({neighbour.first, weight+neighbour.second});
                    distances[neighbour.first] = min(distances[neighbour.first], weight + neighbour.second);
                }
            }
        }
        return distances;
    }

    /**
     * Dijkstra algorithm, to return minimum cost path from source to destination 
    */

    vector<int> dijkstraPath(int nodeCount, vector<vector<int>> edges, int source, int destination) {
        // build the adjacency list
        vector<vector<pair<int,int>>> adj(nodeCount+1);
        for(auto edge:edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
            adj[edge[1]].push_back({edge[0], edge[2]});
        }
        // maintain visited list
        vector<bool>visited(nodeCount+1,false);

        vector<int>distances(nodeCount+1, INT_MAX);
        distances[source] = 0;

        // maintain parent of each node
        vector<int>parent(nodeCount+1, -1);
        // for (int i = 1; i <= nodeCount; i++)
        //     parent[i] = i;

        priority_queue<pair<int,int>, vector<pair<int,int>>, Comparator>pq;
        pq.push({source, 0});

        while(!pq.empty()) {
            auto [node, weight] = pq.top();
            pq.pop();
            visited[node] = true;
            for(auto neighbour:adj[node]) {
                if(!visited[neighbour.first] && weight + neighbour.second < distances[neighbour.first]) {
                    pq.push({neighbour.first, weight+neighbour.second});
                    distances[neighbour.first] = min(distances[neighbour.first], weight + neighbour.second);
                    parent[neighbour.first] = node;
                }
            }
        }

        vector<int>path;
        path.push_back(destination);
        for(int i=1; i<=nodeCount; i++) {
            int lastNode = path[path.size()-1];
            path.push_back(parent[lastNode]);
            if(parent[lastNode] == source) break;
        }

        reverse(path.begin(), path.end());
        return path;
    }


};


int main() {

    int nodesCount = 5, edgesCount = 6;
    vector<vector<int>> edges = { // {from, to, weight}
        {1, 2, 2}, 
        {2, 5, 5}, 
        {2, 3, 4}, 
        {1, 4, 1}, 
        {4, 3, 3}, 
        {3, 5, 1}
    };
    Solution obj;
    int source = 1;
    // find cost to reach from source to all nodes
    vector<int> nodesDistances = obj.dijkstraPath(nodesCount, edges, source, 5);
    
    // Print path to destination
    for(auto dist:nodesDistances) 
        cout<<dist<<", ";
    
    return 0;
}

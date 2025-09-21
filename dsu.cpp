#include "bits/stdc++.h"
using namespace std;
#define pi pair<int,int>
#define pii pair<pair<int,int>, int>
#define pid pair<int,double>

class Solution {
    public:
    vector<int>parent;
    vector<int>rank;
    void dsu(int n) {
        parent = vector<int>(n+1);
        rank = vector<int>(n+1,1);
        for(int i=1; i<=n; i++) parent[i]=i;
    }

    int find(int node) {
        int p = node;
        while(p != parent[p]) {
            parent[p] = parent[parent[p]]; // path compression
            p = parent[p];
        }
        return p;
    }

    bool unionByRank(int u, int v) {
        int parent_u = find(u);
        int parent_v = find(v);
        
        if(parent_u == parent_v) 
            return false; // already in same set, no union possible

        int rank_parent_u = rank[parent_u];
        int rank_parent_v = rank[parent_v];
        if(rank_parent_u > rank_parent_v) {
            parent[parent_v] = parent_u;
            rank[parent_u] += rank[parent_v]; 
        }
        else {
            parent[parent_u] = parent_v;
            rank[parent_v] += rank[parent_u];
        }
        return true;
    }

};

int main() {

    Solution obj;
    // vector<vector<int>> input {{0,1,1},{0,2,5},{1,2,1},{2,3,1}};

    obj.dsu(7);
    obj.unionByRank(1, 2);
    obj.unionByRank(2, 3);
    obj.unionByRank(4, 5);
    obj.unionByRank(6, 7);
    obj.unionByRank(5, 6);
    
    if (obj.find(3) == obj.find(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";

    obj.unionByRank(3, 7);

    if (obj.find(3) == obj.find(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";

    return 0;
}
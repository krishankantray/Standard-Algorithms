#include "bits/stdc++.h"
using namespace std;

class Solution{
    public:
    map<pair<int,int>, int> memo;
    
    // Top-Down approach
    int getMinCost(int freq[], int l, int r) {
        if(l>r) {
            return 0;
        }

        if(memo.find({l,r}) != memo.end()) {
            return memo[{l,r}];
        }

        int sum = accumulate(freq+l, freq+r+1, 0);
        int minCost = INT_MAX;
        for(int root=l; root<=r; root++) {
            int leftCost = getMinCost(freq, l, root-1);
            int rightCost = getMinCost(freq, root+1, r);
            minCost = min(minCost, leftCost+rightCost+sum);
        }
        memo[{l,r}] = minCost;
        return minCost;
    }

    // bottom-up approach
    int getMinCost(int freq[], int n) {
        vector<vector<int>>cost(n, vector<int>(n, INT_MAX));
        
        // when sub-tree is a single node
        for(int i=0; i<n; i++)
            cost[i][i] = freq[i];
        
        for(int gap=1; gap<n; gap++) {
            for(int left=0; left+gap<n; left++) {
                
                int right = left+gap;
                int sum = accumulate(freq+left, freq+right+1, 0);

                for(int root = left; root<=right; root++) {
                    int leftCost = root-1 < left ? 0 : cost[left][root-1];
                    int rightCost = root+1 > right ? 0 : cost[root+1][right];
                    int currentCost = sum + leftCost + rightCost;
                    cost[left][right] = min(cost[left][right], currentCost);
                }
            }
        }

        return cost[0][n-1];
    }

    int optimalSearchTree(int keys[], int freq[], int n) {
        memo = map<pair<int,int>, int>();
        // return getMinCost(freq, 0, n-1);
        return getMinCost(freq, n);
    }
};


int main() {
    Solution obj;

    int keys[] = {1,2,3,4,5,6,7} ;
    int freq[] = {6, 1, 4, 8, 3, 6, 5}; 
    int n = 7 ;
    
    int res = obj.optimalSearchTree(keys, freq, n);
    cout<<res;

    return 0;
}
/**
 * LC : https://leetcode.com/problems/design-search-autocomplete-system/description/
 * SS: https://drive.google.com/file/d/17qMIjrF5oBGPVat6NmJ12gUbSxBZlZoQ/view?usp=sharing
*/

#include "bits/stdc++.h"
using namespace std;
#define pi pair<int, int>
#define pii pair<pair<int, int>, int>
#define pid pair<int, double>

#define PQ priority_queue<TrieNode*, vector<TrieNode*>, comparator>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    string word;
    int frequency;

    TrieNode(): frequency(0), word("") {}

    // destructor
    ~TrieNode() {
        for(auto child:children) {
            delete child.second;
        }
    }
};

class comparator {
    public:
    bool operator()(TrieNode* a, TrieNode* b) {
        if(a->frequency == b->frequency) {
            return a->word < b->word;
        }
        return a->frequency > b->frequency;
    }
};

class Trie {
    private: 
    TrieNode* root;
    
    public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word, int freq=0) {
        TrieNode* cur = root;
        for(char ch:word) {
            if(cur->children.find(ch) == cur->children.end() ) {
                cur->children[ch] = new TrieNode();
                cur->children[ch]->word = cur->word + ch;
            }
            cur = cur->children[ch];
        }
        cur->frequency += freq;
    }

    TrieNode* search(string word) {
        TrieNode* cur = root;
        for(char ch:word) {
            if(cur->children.find(ch) == cur->children.end()) {
                return nullptr;
            }
            cur = cur->children[ch];
        }
        return cur;
    }
};

class Autocomplete {
    private:
    Trie trie;
    string inputSoFar;
    void searchTopK(TrieNode* root, PQ& minHeap) {
        
        if(root->children.size() == 0) {
            minHeap.push(root);
            if(minHeap.size() > 3) minHeap.pop();
        }
        for(auto neighbour: root->children) {
            searchTopK(neighbour.second, minHeap);
        }
    }
    
    public:

    Autocomplete(vector<string>v, vector<int>f) {
        for(int i=0; i<v.size(); i++) {
            trie.insert(v[i], f[i]);
        }
    }

    vector<string>input(char ch) {
        if(ch=='#') {
            trie.insert(inputSoFar, 1);
            inputSoFar = "";
            return vector<string>();
            
        }
        
        TrieNode* prefix = trie.search(inputSoFar+ch);

        if(prefix == nullptr) {
            return vector<string>();
        }

        inputSoFar+= ch;

        PQ minHeap;
        searchTopK(prefix, minHeap);
        vector<string>topK;
        while(!minHeap.empty()) {
            topK.push_back(minHeap.top()->word);
            minHeap.pop();
        }
        reverse(topK.begin(), topK.end());
        return topK;
    }

};

int main() {
    // Solution sol;
    vector<string>v = {"i love you", "island", "iroman", "i love leetcode"}; 
    vector<int>f = {5,3,2,2};
    Autocomplete ac(v,f);
    
    vector<string>res = ac.input('i');
    for(string str:res) cout<<str<<endl;

    cout<<endl<<"---------"<<endl;

    res = ac.input(' ');
    for(string str:res) cout<<str<<endl;

    cout<<endl<<"---------"<<endl;

    res = ac.input('a');
    for(string str:res) cout<<str<<endl;

    cout<<endl<<"---------"<<endl;

    res = ac.input('#');
    for(string str:res) cout<<str<<endl;
    
    return 0;
}
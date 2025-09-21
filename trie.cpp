#include "bits/stdc++.h"
using namespace std;
#define pi pair<int,int>
#define pii pair<pair<int,int>, int>
#define pid pair<int,double>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a word into the trie
    void insert(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }

    // Search for a word in the trie
    bool search(string word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current != nullptr && current->isEndOfWord;
    }

    // Delete a word from the trie
    bool deleteWord(string word) {
        return deleteWordHelper(root, word, 0);
    }

private:
    bool deleteWordHelper(TrieNode* current, string word, int index) {
        if (index == word.length()) {
            if (!current->isEndOfWord) {
                return false;
            }
            current->isEndOfWord = false;
            return current->children.empty(); // Return true if current node has no other children
        }

        char c = word[index];
        if (current->children.find(c) == current->children.end()) {
            return false; // Word not found
        }

        bool shouldDeleteCurrentNode = deleteWordHelper(current->children[c], word, index + 1);

        if (shouldDeleteCurrentNode) {
            delete current->children[c];
            current->children.erase(c);
            return current->children.empty();
        }

        return false;
    }
};

int main() {
    Trie trie;

    // Insertion
    trie.insert("apple");
    trie.insert("banana");
    trie.insert("app");
    trie.insert("application");

    // Searching
    cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << endl;
    cout << "Search 'application': " << (trie.search("application") ? "Found" : "Not found") << endl;
    cout << "Search 'orange': " << (trie.search("orange") ? "Found" : "Not found") << endl;

    // Deletion
    trie.deleteWord("app");
    cout << "Search 'app': " << (trie.search("app") ? "Found" : "Not found") << endl;

    return 0;
}

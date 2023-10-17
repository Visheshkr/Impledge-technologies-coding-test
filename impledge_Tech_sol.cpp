#include<bits/stdc++.h>
using namespace std;
class Trie {
	private:
	    // Inner class, only for the use of Trie
	    class TrieNode {
	    public:
	        char val;                       // Character stored in the node
	        unordered_map<char, TrieNode*> children;  // Map name of string to the node
	        bool isWord;                    // If the node is at the end of a word

	        // Constructor
	        TrieNode(char value) : val(value), isWord(false) {}
	        
	        // Add a child to the TrieNode
	        void addChild(char child) {
	            children[child] = new TrieNode(child);
	        }

	        // Get child of TrieNode that has the same character as the given one
	        TrieNode* getChild(char child) {
	            if (children.find(child) == children.end()) {
	                return nullptr;
	            }
	            return children[child];
	        }

	        // Return true if child exists
	        bool containsChild(char child) {
	            return children.find(child) != children.end();
	        }
	    };

	    TrieNode* root;
	    TrieNode* curr;

	public:
	    Trie() {
	        root = new TrieNode(' ');   // Root
	        curr = root;
	    }

	    // Insert a word into the Trie
	    void insert(string s) {
	        char letter;
	        curr = root;

	        // Traverse every letter of a word
	        // Update the Trie if a letter is not in the structure
	        for (int i = 0; i < s.length(); i++) {
	            letter = s[i];

	            if (!curr->containsChild(letter)) {
	                curr->addChild(letter);
	            }

	            curr = curr->getChild(letter);
	        }

	        // Mark the last letter as the end of a word
	        curr->isWord = true;
	    }

	    // Return starting indices of all suffixes of a word
	    vector<int> getSuffixesStartIndices(string s) {
	        vector<int> indices;    // Store indices
	        char letter;
	        curr = root;    // Start from root

	        for (int i = 0; i < s.length(); i++) {
	            letter = s[i];

	            // If the current letter doesn't have one letter as a child,
	            // which means the Trie currently doesn't have the relationship,
	            // return indices of suffixes
	            if (!curr->containsChild(letter)) {
	                return indices;
	            }

	            // Move on to the child node
	            curr = curr->getChild(letter);

	            // If the letter is the end of a word, it means after the letter is a suffix
	            // Update indices
	            if (curr->isWord) {
	                indices.push_back(i + 1);
	            }
	        }

	        return indices;
	    }
};

int main() {
    // Change the file name accordingly
    clock_t start,end;
    start=clock();
    ifstream file;
    file.open("Input_02.txt");
    Trie trie;
    queue<pair<string, string>> q;

    unordered_set<string> compoundWords;

    string word;
    vector<int> sufIndices;

    while(file >> word) {
        sufIndices = trie.getSuffixesStartIndices(word);

        for (int i : sufIndices) {
            if (i >= word.length()) {
                break;
            }
            q.push(make_pair(word, word.substr(i)));
        }
        trie.insert(word);
    }
    pair<string, string> p;
    int maxLength = 0;
    string longest = "";
    string secLongest = "";

    while (!q.empty()) {
        p = q.front();
        q.pop();

        string word = p.second;
        sufIndices = trie.getSuffixesStartIndices(word);

        if (sufIndices.empty()) {
            continue;
        }

        for (int i : sufIndices) {
            if (i > word.length()) {
                break;
            }

            if (i == word.length()) {
                if (p.first.length() > maxLength) {
                    secLongest = longest;
                    maxLength = p.first.length();
                    longest = p.first;
                }

                compoundWords.insert(p.first);
            } else {
                q.push(make_pair(p.first, word.substr(i)));
            }
        }
    }
    end=clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Longest Compound Word: " << longest << endl;
    cout << "Second Longest Compound Word: " << secLongest << endl;
    cout << "Total Number of Compound Words: " << compoundWords.size() << endl;
    cout << "Execution time of the program is: "<< fixed << time_taken << setprecision(5) << "sec" << endl;

    return 0;
}
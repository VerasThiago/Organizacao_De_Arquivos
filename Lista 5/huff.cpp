// C++ program for Huffman Coding
#include <bits/stdc++.h>
using namespace std;
 
// A Huffman tree node
struct MinHeapNode {
 
    // One of the input characters
    char data;
 
    // Frequency of the character
    unsigned freq;
 
    // Left and right child
    MinHeapNode *left, *right;
 
    // Constructor
    MinHeapNode(char data, unsigned freq){
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};
 
// For comparison of
// two heap nodes (needed in min heap)
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r){
        return (l->freq > r->freq);
    }
};
 
// Prints huffman codes from
// the root of Huffman Tree.
void printCodes(struct MinHeapNode* root, string str){
 
    if (!root)
        return;
 
    if (root->data != '$')
        cout << root->data << " : " << str << "\n";
 
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
 
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(vector<char> data, vector<int> freq, int size){
    struct MinHeapNode *left, *right, *top;
 
    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
 
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));
 
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
 
        // Extract the two minimum
        // freq items from min heap
        left = minHeap.top();
        minHeap.pop();
 
        right = minHeap.top();
        minHeap.pop();
 
        // Create a new internal node with
        // frequency equal to the sum of the
        // two nodes frequencies. Make the
        // two extracted node as left and right children
        // of this new node. Add this node
        // to the min heap '$' is a special value
        // for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);
 
        top->left = left;
        top->right = right;
 
        minHeap.push(top);
    }
 
    // Print Huffman codes using
    // the Huffman tree built above
    printCodes(minHeap.top(), "");
}
void create(vector<char> *carcteres, vector<int> *freq, int *n){

    // Open File
    ifstream file("sample.txt");
    
    // String to read file
    string s;

    // Count freq
    map<char,int> mp;

    // Walk through file and walk through chars
    while(file >> s)
        for(auto x: s)
            mp[x]++;

    // Walk through map and set vector of char and freq.
    for(auto x: mp){
        carcteres->push_back(x.first);
        freq->push_back(x.second);
    }

    // Set carcteres size
    *n = mp.size();
}
 
// Driver program to test above functions
int main(){

    // Vetors size
    int n;

    // Chars on file
    vector<char> carcteres;

    // Frequency of each char
    vector<int> freq;

    // Create vector with chars and each frequency
    create(&carcteres,&freq,&n);

    // Compress all data
    HuffmanCodes(carcteres, freq, n);
 
    return 0;
}
 

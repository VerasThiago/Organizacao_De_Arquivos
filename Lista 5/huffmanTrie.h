#include <iostream>
#include <bitset>
#include <map>
#include <vector>
#include <fstream>
#include <queue>
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
    MinHeapNode(char data, unsigned freq, MinHeapNode *left, MinHeapNode *right){
        this->left = left;
        this->right = right;
        this->data = data;
        this->freq = freq;
    }

    // Check if node is leaf
    bool isLeaf(){
        return !left and !right;
    }
};


// Print trie chars and values
void printTrie(struct MinHeapNode* root, string str){
    if (!root)
        return;
    
    // If root is leaf, so have a char
    if (root->isLeaf()){

        // For in case char are \n, to improve visualization
        if(root->data == '\n')
            cout << "\\n" << " : " << str << "\n";
        else
            cout << root->data << " : " << str << "\n";

    }
    
    // Pre order construction
    printTrie(root->left, str + "0");
    printTrie(root->right, str + "1");
}

// For comparison of two heap nodes (needed in min heap)
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r){
        return (l->freq > r->freq);
    }
};



struct MinHeapNode* HuffmanCodes(struct MinHeapNode* esquerda, struct MinHeapNode* direita,  struct MinHeapNode* top, vector<char> data, vector<int> freq, int size ){
 
    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
 
    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i], NULL, NULL));
 
    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
 
        // Remove first node with least frequency
        esquerda = minHeap.top();
        minHeap.pop();
        
        // Remove the second node with least frequency
        direita = minHeap.top();
        minHeap.pop();
 
        
        // Create a new node with frequency equal to the sum of the others 2 nodes
        top = new MinHeapNode('\0', esquerda->freq + direita->freq, NULL, NULL);
        
        top->left = esquerda;
        top->right = direita;
        
        // Insert in queue
        minHeap.push(top);
    }

    return minHeap.top();
 
}

// Read 8 bits in chars and transform to binary char value
char readChar(int idx, string trieCode){

    // String that will recieve bits in binary
    string letter;
    
    // Get 8 binary chars

    
    for(int i = idx; i < idx+8; i++)
        letter += trieCode[i];
    
    
    // Transfor to bynary value
    bitset<8> y(letter);

    // Return respective char binary value
    return(char)y.to_ulong();
}

// Build trie with binary code
struct MinHeapNode* buildTrie(string trieCode, int *n){

    // Just to help
    int idx = *n;

    // With bit is 1, so need to create a leaf with a 8bit char
    if(trieCode[idx] == '1'){
        // Read next 8 binary digist to create a char
        char c = readChar(idx+1, trieCode);

        // Shift that 8 bit read (+9 because char start from idx + 1, so idx + 1 + 8 = idx + 9)
        idx += 9;

        // Reset pointer value
        *n = idx;

        // Return leaf
        return new MinHeapNode(c, 0, NULL, NULL);
    }

    // If bit are 0, so need to build 2 children
    *n = *n + 1;

    // Return this node
    return new MinHeapNode('\0', 0, buildTrie(trieCode, n), buildTrie(trieCode, n));
    
}
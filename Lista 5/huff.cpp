// C++ program for Huffman Coding
#include <bits/stdc++.h>
#include <bitset>

using namespace std;

// Open File
ifstream file;

// Table created by tree
map<char,string> table;
 
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
 
    if (root->data != '$'){
        cout << root->data << " : " << str << "\n";
        table[root->data] = str;
    }
 
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}
 
// The main function that builds a Huffman Tree and
// print codes by traversing the built Huffman Tree
void HuffmanCodes(vector<char> data, vector<int> freq, int size ){
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

    // String to read file
    string s;

    // Count freq
    map<char,int> mp;

    // Walk through file and walk through chars
    while(getline(file,s))
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

void encode(){
    // Close file to reopen at the top
	file.close();

    // Open message code 
	file.open("input.txt");

    // Open output file compressed
	ofstream saida("compressed.txt");

    // Binary Code format
    ofstream teste("binary.txt");

    // Strings to read file and final result
    string line, total, aux ;

    // Walktrough file lines and create binary code with table
    while(getline(file,line))
        for(auto x: line)
            total += table[x];
        
    //Write binary form
    teste << total;

    // Close binary form file
    teste.close();

    // Total binary form need to be multiple of 8
    while((int)total.size()%8) total += "0";

    // Walk through all bits
	for(int i = 0; i < total.size(); i++){

        // Add bit to string aux
		aux += total[i];

        // Work only with 8 bits number
		if( aux.size() != 8) continue;

        // Transform to binary
		bitset<8> y(aux);

        // Get respective char according to binary value and save on compressed file
        saida << (char)y.to_ulong();

        // Reset numer;        
		aux.clear();
	}

    // Close message file
	file.close();

    // Close compressed file
	saida.close();
}

void compress(){
    // open message file
    file.open("input.txt");

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
    
    // Create compressed file
    encode();
}

void decompress(){
    // open compressed file
    ifstream compressed("compressed.txt");
    
    // Char to read byte to byte
    char num;

    // Final result
    string total;

    // Walktrough bytes
    while(compressed >> num){
        
        // Get binary value from byte value
        bitset<8> y(num);

        // Add binary to the final string
        total += y.to_string();
    }

    // Final result
    ofstream retorno("rebinary.txt");

    // Write the binary form
    retorno << total;

    // Close final result file in binary
    retorno.close();

    // Close compressed file
    compressed.close();

}
 

int main(){
    
    // Interaction with user
    printf("1 - Compress file\n");
    printf("2 - Read compressed file\n");

    // Operation variable
    int op;

    // Read operation
    cin >> op;

    // Go to huffman compression
    if(op == 1)
        compress();

    // Decompress
    else if(op == 2)
        decompress();

    return 0;
}

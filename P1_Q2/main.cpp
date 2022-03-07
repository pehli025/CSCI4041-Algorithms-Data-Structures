#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <cstring>
using namespace std;

struct Node{
    char data;
    int num;
    Node *left, *right;
};
 
Node* getNode(char data, int num, Node* left, Node* right) {
    Node* node = new Node();
 
    node->data = data;
    node->num = num;
    node->left = left;
    node->right = right;
 
    return node;
}

struct comp { // Comparison object to be used to order the heap
    bool operator()(Node* l, Node* r) {
        return l->num > r->num; // the highest priority item has the lowest frequency
    }
};
 

bool isLeaf(Node* root) { // check to see if there is only one node in the tree
    return root->left == nullptr && root->right == nullptr;
}
 
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode) { // Traverse the Huffman Tree and store Huffman Codes in a map.
    if (root == nullptr) {
        return;
    }
    // found a leaf node
    if (isLeaf(root)) {
        huffmanCode[root->data] = (str != "") ? str : "1";
    }
    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}


void decode(Node* root, int &index, string str)
{
    if (root == nullptr) { // if root is empty, the tree is empty, so return
        return;
    }
 
    // found a leaf node data
    if (isLeaf(root)) {
        cout << root->data;
        return;
    }
    index++;
    if (str[index] == '0') {
        decode(root->left, index, str);
    } else {
        decode(root->right, index, str);
    }
}
 
void buildTree(string text) {// Builds Huffman Tree and decodes the given input text
    unordered_map<char, int> nums; // count the frequency of appearance of each character and store it in a map
    for (char ch: text) {
        nums[ch]++;
    }

    priority_queue<Node*, vector<Node*>, comp> pq;  // Create a priority queue to store live nodes of the Huffman tree
 
    for (auto pair: nums) { 
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr)); // Create a leaf node for each character and add it to the priority queue.
    }
 
    // do till there is more than one node in the queue
    while (pq.size() != 1)
    {
        Node *left = pq.top(); pq.pop(); // Remove the two nodes of the highest priority
        Node *right = pq.top();    pq.pop(); // (the lowest frequency) from the queue
        int sum = left->num + right->num;
        pq.push(getNode('\0', sum, left, right)); // Add the new node to the priority queue.
    }
 
    Node* root = pq.top(); // root stores pointer to the root of Huffman Tree
 
    unordered_map<char, string> huffmanCode; // Traverse the Huffman Tree and store Huffman Codes in a map. Also, print them
    encode(root, "", huffmanCode);
 
    //cout << "Huffman Codes are:\n" << '\n'; // printing 
    for (auto pair: huffmanCode) {
        cout << pair.first << ":" << pair.second << '\n';
    }
    
    
}

int main(int argc, const char * argv[]) { 
    ifstream in (argv[1]);
    if(in.fail()){ // file checking, if it doens't open, exit the program and return the message.
        cout << "ERROR: FILE " << argv[1] << " COULD NOT OPEN" << endl;
        return 1; 
    }
    string line;
    getline(in, line);
    buildTree(line);
    return 0;
}


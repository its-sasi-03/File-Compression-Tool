#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node
{
    char ch;
    int freq;

    Node *left;
    Node *right;

    Node(char c, int f)
    {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare
{
    bool operator()(Node* a, Node* b)
    {
        return a->freq > b->freq;
    }
};

void generateCodes(Node* root,
                   string code,
                   unordered_map<char, string>& huffmanCode)
{
    if(root == nullptr)
        return;

    // Leaf node
    if(!root->left && !root->right)
    {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left,
                  code + "0",
                  huffmanCode);

    generateCodes(root->right,
                  code + "1",
                  huffmanCode);
}

int main()
{
    string text;

    cout << "Enter text: ";
    getline(cin, text);

    // Handle empty input
    if(text.empty())
    {
        cout << "No text entered!" << endl;
        return 0;
    }

    // Count frequencies
    unordered_map<char, int> frequency;

    for(char ch : text)
    {
        frequency[ch]++;
    }

    // Build Min Heap
    priority_queue<Node*,
                   vector<Node*>,
                   Compare> pq;

    for(auto pair : frequency)
    {
        pq.push(new Node(pair.first,
                         pair.second));
    }

    // Handle single character case
    if(pq.size() == 1)
    {
        Node* onlyNode = pq.top();

        unordered_map<char, string> huffmanCode;
        huffmanCode[onlyNode->ch] = "0";

        cout << "\nHuffman Codes:\n";

        cout << onlyNode->ch
             << " : 0" << endl;

        string encoded = "";

        for(char ch : text)
        {
            encoded += "0";
        }

        cout << "\nEncoded Text:\n";
        cout << encoded << endl;

        cout << "\nDecoded Text:\n";
        cout << text << endl;

        return 0;
    }

    // Build Huffman Tree
    while(pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* merged =
            new Node('\0',
                     left->freq +
                     right->freq);

        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    Node* root = pq.top();

    // Generate Huffman Codes
    unordered_map<char, string> huffmanCode;

    generateCodes(root,
                  "",
                  huffmanCode);

    cout << "\nHuffman Codes:\n";

    for(auto pair : huffmanCode)
    {
        if(pair.first == ' ')
            cout << "[space]";
        else
            cout << pair.first;

        cout << " : "
             << pair.second
             << endl;
    }

    // Encode
    string encoded = "";

    for(char ch : text)
    {
        encoded += huffmanCode[ch];
    }

    cout << "\nEncoded Text:\n";
    cout << encoded << endl;

    // Decode
    string decoded = "";

    Node* current = root;

    for(char bit : encoded)
    {
        if(bit == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }

        // Leaf node
        if(current->left == nullptr &&
           current->right == nullptr)
        {
            decoded += current->ch;
            current = root;
        }
    }

    cout << "\nDecoded Text:\n";
    cout << decoded << endl;

    return 0;
}
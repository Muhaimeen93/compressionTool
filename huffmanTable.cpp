#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define MAX_TREE_HT 100
struct encodedTable
{
    unsigned char chars;
    string bin_seq = "";
};
int x = 0;

encodedTable table[256];
struct MinHeapNode {

    unsigned char data;

    unsigned freq;

    struct MinHeapNode* left, * right;
};

struct MinHeap {

    unsigned size;

    unsigned capacity;

    struct MinHeapNode** array;
};

struct MinHeapNode* newNode(unsigned char data, unsigned freq)
{
    struct MinHeapNode* temp
        = (struct MinHeapNode*)malloc
        (sizeof(struct MinHeapNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

struct MinHeap* createMinHeap(unsigned capacity)

{

    struct MinHeap* minHeap
        = (struct MinHeap*)malloc(sizeof(struct MinHeap));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array
        = (struct MinHeapNode**)malloc(minHeap->
            capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a,
    struct MinHeapNode** b)

{

    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->
        freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->
        freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest],
            &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

int isSizeOne(struct MinHeap* minHeap)
{

    return (minHeap->size == 1);
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0]
        = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapify(minHeap, 0);

    return temp;
}

void insertMinHeap(struct MinHeap* minHeap,
    struct MinHeapNode* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap* minHeap)

{

    int n = minHeap->size - 1;

    for (int i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

void printArr(int arr[], int n)
{
   
    string y = "";
    for (int i = 0; i < n; ++i)
    {
        y+= to_string(arr[i]);
    }
    table[x].bin_seq = y;
    x++;
}

int isLeaf(struct MinHeapNode* root)

{

    return !(root->left) && !(root->right);
}

struct MinHeap* createAndBuildMinHeap(unsigned char data[], long int freq[], int size)

{

    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(unsigned char data[], long int freq[], int size)

{
    struct MinHeapNode* left, * right, * top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (!isSizeOne(minHeap)) {

        // Step 2: Extract the two minimum
        // freq items from min heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

void getBinary(struct MinHeapNode* root, int arr[], int top)

{

    // Assign 0 to left edge and recur
    if (root->left) {

        arr[top] = 0;
        getBinary(root->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (root->right) {

        arr[top] = 1;
        getBinary(root->right, arr, top + 1);
    }

    // If this is a leaf node, then
    // it contains one of the input
    // characters, print the character
    // and its code from arr[]
    if (isLeaf(root)) {
        table[x].chars = (char)root->data;
        printArr(arr, top);
    }
}

// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
//void HuffmanCodes(unsigned char data[], long int freq[], int size)
int main()
{
    ifstream getFreqCount;
    getFreqCount.open("freqSize.txt");
    int size;
    getFreqCount >> size;
    getFreqCount.close();

    ifstream read_freq;
    read_freq.open("frequency.txt");
    long int* freq = new long int[size];
    unsigned char* data = new unsigned char[size];
    int i = 0;
    while (1)
    {
        if (read_freq.eof()) break;
        int x;
        int y;
        read_freq >> x >> y;
        data[i] = (char)x;
        freq[i] = y;
        i++;
    }
    read_freq.close();

    //int height = floor(log2(size));
    // Construct Huffman Tree
    struct MinHeapNode* root
        = buildHuffmanTree(data, freq, size);

    // Print Huffman codes using
    // the Huffman tree built above
    int arr[MAX_TREE_HT], top = 0;

    getBinary(root, arr, top);
    
    ofstream wdata;
    wdata.open("huffmanTable.txt");

    cout << endl << "Encoding TABLE: " << endl;
    for (int i = 0; i < x-1; i++)
    {
        cout <<(int) table[i].chars << " " << table[i].bin_seq << endl;
        wdata <<(int)table[i].chars <<" "<< table[i].bin_seq  << endl;
    }
    cout << (int) table[x - 1].chars << " " << table[x - 1].bin_seq << endl;
    wdata << (int)table[x-1].chars << " " << table[x-1].bin_seq;
    wdata.close();

    return 0;
}

//#endif

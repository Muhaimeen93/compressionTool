#include<iostream>
#include<fstream>
#include<map>
#include<queue>
#include <iomanip>
#include <sstream>  
#include <chrono>
#define MAX_TREE_HT 256
using namespace std;
using namespace std::chrono;
vector<unsigned char> frC;
vector<int> frI;

struct MinHeapNodeDecoder {

    unsigned char data;

    unsigned freq;

    struct MinHeapNodeDecoder* left, * right;
};

struct MinHeapDecoder {

    unsigned size;

    unsigned capacity;

    struct MinHeapNodeDecoder** array;
};

struct MinHeapNodeDecoder* newNodeDecoder(unsigned char data, unsigned freq)
{
    struct MinHeapNodeDecoder* temp
        = (struct MinHeapNodeDecoder*)malloc
        (sizeof(struct MinHeapNodeDecoder));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;

    return temp;
}

struct MinHeapDecoder* createMinHeapDecoder(unsigned capacity)

{

    struct MinHeapDecoder* minHeap
        = (struct MinHeapDecoder*)malloc(sizeof(struct MinHeapDecoder));

    // current size is 0
    minHeap->size = 0;

    minHeap->capacity = capacity;

    minHeap->array
        = (struct MinHeapNodeDecoder**)malloc(minHeap->
            capacity * sizeof(struct MinHeapNodeDecoder*));
    return minHeap;
}

void swapMinHeapNodeDecoder(struct MinHeapNodeDecoder** a,
    struct MinHeapNodeDecoder** b)

{

    struct MinHeapNodeDecoder* t = *a;
    *a = *b;
    *b = t;
}

void minHeapifyDecoder(struct MinHeapDecoder* minHeap, int idx)

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
        swapMinHeapNodeDecoder(&minHeap->array[smallest],
            &minHeap->array[idx]);
        minHeapifyDecoder(minHeap, smallest);
    }
}

int isSizeOneDecoder(struct MinHeapDecoder* minHeap)
{

    return (minHeap->size == 1);
}

struct MinHeapNodeDecoder* extractMinDecoder(struct MinHeapDecoder* minHeap)

{

    struct MinHeapNodeDecoder* temp = minHeap->array[0];
    minHeap->array[0]
        = minHeap->array[minHeap->size - 1];

    --minHeap->size;
    minHeapifyDecoder(minHeap, 0);

    return temp;
}

void insertMinHeapDecoder(struct MinHeapDecoder* minHeap,
    struct MinHeapNodeDecoder* minHeapNode)

{

    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

void buildMinHeapDecoder(struct MinHeapDecoder* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapifyDecoder(minHeap, i);
}

struct MinHeapDecoder* createAndBuildMinHeapDecoder(unsigned char data[], long int freq[], int size)

{

    struct MinHeapDecoder* minHeap = createMinHeapDecoder(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNodeDecoder(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeapDecoder(minHeap);

    return minHeap;
}

struct MinHeapNodeDecoder* buildHuffmanTreeDecoder(unsigned char data[], long int freq[], int size)

{
    struct MinHeapNodeDecoder* left, * right, * top;

    struct MinHeapDecoder* minHeap = createAndBuildMinHeapDecoder(data, freq, size);

    while (!isSizeOneDecoder(minHeap)) {

        left = extractMinDecoder(minHeap);
        right = extractMinDecoder(minHeap);
        top = newNodeDecoder('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeapDecoder(minHeap, top);
    }

    return extractMinDecoder(minHeap);
}

string decode_file(struct MinHeapNodeDecoder* root, string s)
{
    string ans = "";
    struct MinHeapNodeDecoder* curr = root;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        if (curr->left == NULL && curr->right == NULL)
        {
            ans += curr->data;
            curr = root;
        }
    }
    return ans;
}



int main(int argc, char** argv)
{
    auto start = high_resolution_clock::now();
    ifstream f(argv[1],ios::binary | ios::in);
    f >> std::noskipws;
    string code = "";
    unsigned char buffer;
    while (f.read((char*)&buffer, sizeof(buffer)))
    {
        for (int j = 7; j >= 0; j--) 
            if ((buffer >> j) & 1)
                code += "1";
            else code += "0";
    }
    f.close();

    
    ofstream x_string;
    x_string.open("decompressed.txt");
    x_string << code;
    x_string.close();

    
    ifstream frequency;
    frequency.open("frequency.txt");

    while (1)
    {
        if (frequency.eof()) break;
        int x;
        int y;
        frequency >> x >> y;
        frC.push_back((unsigned char)x);
        frI.push_back(y);
        
    }
    frequency.close();
   
    string decodedString;
    long int* freqe = new long int[frC.size()];
    unsigned char* chars = new unsigned char[frC.size()];
    for (int i = 0; i < frC.size(); i++)
    {
        chars[i] = frC.at(i);
        freqe[i] = frI.at(i);
    }
    for (int i = 0; i < frC.size() - 1; i++)
    {
        long int temp1;
        unsigned char temp2;
        for (int j = i + 1; j < frC.size(); j++)
        {
            bool x = (freqe[i] > freqe[j]) ? true : (freqe[i] == freqe[j]) ? (chars[i] > chars[j]) ? true : false:false;
            if (x)
            {
                temp1 = freqe[i];
                temp2 = chars[i];
                freqe[i] = freqe[j];
                chars[i] = chars[j];
                freqe[j] = temp1;
                chars[j] = temp2;
            }
        }
    }
    struct MinHeapNodeDecoder* root=buildHuffmanTreeDecoder(chars, freqe, frC.size());
   
  
    decodedString = decode_file(root, code);

    ofstream e_string;
    e_string.open(argv[2], ios::binary | ios::out);
    e_string << decodedString;
    e_string.close();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "DECOMPRESSION IS SUCCESSFUL!" << endl;

    cout << "Decompression Speed: " << duration.count() << endl;
    return 0;
}
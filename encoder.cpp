#include<iostream>
#include<fstream>
#include<string>
#include <bitset>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace std::chrono;
static int cnt;
struct encodedTable
{
	int chars;
	string bin_seq = "";
};
int y = 0;
static char byt;
int byteWritten = 0;

encodedTable table2[256];
void writeBit(int b, FILE* f)
{
    
    b = b - 48;
    
    
    int temp;
    if (b == 1)
    {
        temp = 1;
        temp = temp << (7 - cnt);	
        byt = byt | temp;
    }
    cnt++;
    if (cnt == 8)	
    {
        byteWritten += cnt;
        fwrite(&byt, sizeof(char), 1, f);
        cnt = 0; byt = 0;	
        return;
    }

    return;
}

int main(int argc, char** argv)
{
    auto start = high_resolution_clock::now();
    FILE* orgFile;
    orgFile = fopen(argv[1], "rb");
    fseek(orgFile, 0, SEEK_END);
    int length = ftell(orgFile);
    rewind(orgFile);
    unsigned char* data = (unsigned char*)malloc((length + 1) * sizeof(unsigned char));

    fread(data, length + 1, 1, orgFile);
    fclose(orgFile);



	ifstream file;
	file.open("huffmanTable.txt");
    
	while (true)
	{
        if (file.eof()) break;
		file >> table2[y].chars;
		file >> table2[y].bin_seq;
		y++;
	}
    file.close();

   
    ofstream e_string;
    e_string.open("encodedString.txt");
    string encoded_string = "";
    FILE* compressHuff = fopen(argv[2], "wb");
   
    
    for (int i = 0; i < length; i++)
    {
       int x = (int)data[i];
       for (int k = 0; k < y ; k++)
       {
           if (x == table2[k].chars)
           {
               e_string << table2[k].bin_seq;
               for (int j = 0; j < table2[k].bin_seq.length(); j++)
               {
                   writeBit((int)table2[k].bin_seq[j],compressHuff);
                   
               }
               
           }
       }
    }

    if (cnt > 0 && cnt < 8)
    {
        fwrite(&byt, sizeof(char), 1, compressHuff);
        byteWritten += cnt;
    }
    byteWritten /= 8;
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << endl<< "COMPRESSION IS SUCCESSFUL!" << endl;

    cout << "Original File bytes: " << length << endl;
    cout << "Compressed File bytes: " << byteWritten << endl;

    cout << endl << "Compression Ratio: " << ((float)byteWritten / (float)length) * 100 << "%" << endl;

    cout << "Compression Speed: " << duration.count() << endl;

    e_string.close();
    fclose(compressHuff);
    return 0;
}

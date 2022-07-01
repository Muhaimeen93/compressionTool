#include<iostream>
#include<vector>
#include<fstream>
#include <queue>
#include <unordered_map>
#include<string>
using namespace std;


int main(int argc, char** argv)
{
	FILE* fp;
	fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	int length = ftell(fp);
	rewind(fp);
	unsigned char* file_data = (unsigned char*)malloc((length + 1) * sizeof(unsigned char));

	fread(file_data, length + 1, 1, fp);
	fclose(fp);


	long int occurrence[256] = { 0 };
	int l = 0;

	for (int i = 0; i < length; i++)
	{
		occurrence[file_data[i]] += 1;
		if (occurrence[file_data[i]] > 0)
			l++;
	}
	int sum = 0;

	char characters[256];

	long int* freq = new long int[l];
	unsigned char* chars = new unsigned char[l];
	int c_count = 0;
	for (int i = 0; i < 256; i++)
	{
		if (occurrence[i] > 0)
		{
			freq[c_count] = occurrence[i];
			chars[c_count] = char(i);
			c_count++;
		}
	}
	for (int i = 0; i < c_count - 1; i++)
	{
		long int temp1;
		char temp2;
		for (int j = i + 1; j < c_count; j++)
		{
			bool x = (freq[i] > freq[j]) ? true : (freq[i] == freq[j]) ? (chars[i] > chars[j]) ? true : false : false;
			if (x)
			{
				temp1 = freq[i];
				temp2 = chars[i];
				freq[i] = freq[j];
				chars[i] = chars[j];
				freq[j] = temp1;
				chars[j] = temp2;
			}
		}
	}
	cout << endl << "Frequency:" << endl;
	ofstream e_string;
	e_string.open("frequency.txt");
	int ssum = 0;
	for (int i = 0; i < c_count - 1; i++) {
		cout << (int)chars[i] << " " << freq[i] << endl;
		ssum += freq[i];
		e_string << (int)chars[i] << " " << freq[i] << endl;
	}
	cout << (int)chars[c_count - 1] << " " << freq[c_count - 1] << endl;
	e_string << (int)chars[c_count - 1] << " " << freq[c_count - 1];
	e_string.close();
	cout << endl;
	fclose(fp);

	int size = c_count;
	ofstream freqSize;
	freqSize.open("freqSize.txt");
	freqSize << size;
	freqSize.close();

	return 0;
}
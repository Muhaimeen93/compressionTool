# compressionTool
Compression and decompression tools using Huffman Algorithm


Process flow to Compress & Decompress a file:

1. Open Terminal

2. To Compile:  
	  i. Type: MinGW32-make [This command will create all the stand-alone executables]  

3. To Compress:   
	  i. Perform steps 1 & 2 if not performed already	
	  i. Type: frequency "file-name" [This command will count the frequency of the bytes]  
	 ii. Type: huffmanTable [This command will create the huffman encoding/decoding table]  
	iii. Type: compress "file-name" "compressed-file-name" [This command will compress the file]  

4. To Decompress:  
	  i. Perform steps 1,2,3 if not performed already  
	 ii. Type: decompress "compressed-file-name" "decompressed-file-name" [This command will decompress the file]  

5. Verification:   
	  i. Type: fc "file-name" "decompressed-file-name" [This command will verify if there is any type of difference in the files]  


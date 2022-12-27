# Huffman Encoding
Implememtation of Huffman encoding to demonstrate file compression and decompression of files.

## Features
- Prints the codes for compression on to the console
- self sufficient compression and decompression. Huffman codes are stored along with the compressed file.
- Implemenets huffman min heap encoding method.
- Compressed file larger in size as, code made for demonstration purposes. Ascii charecters converted to ascii codes rather than binary, as it is for compressing files.

## Test
To test the code, create the huffman executable that can be generated via the make command for the makefile. On running the executable, the code prompts you for the input file, output file and compression(0) or decompression(1).

for testing purposes in.txt is provides, that maybe compressed to out.txt, then out.txt can be decompressed to another chk.txt . To compare chk.txt and in.txt, apart from manual chekcing you can run the followin command

```bash
diff chk.txt in.txt
```
no output means both files are indentical

## Appendix
The project doens't actually compress the text files, but rather demostrate compression. Text files use ascii to store charecters, huffman encoding converts the 8 bit ascii to a format specific to a file that uses least bit, for most efficient representation of charecters. The test file is converted to binary file. 

For demostration purposes a text file that replaces charecters with their huffman equivalent is produced, and on decompressing re produces the original file.

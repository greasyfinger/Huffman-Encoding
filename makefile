all: huffman

huffman: huffman.c
	gcc Huffman.c -o huffman

clean:
	rm -r huffman out.txt chk.txt
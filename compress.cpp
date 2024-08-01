/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: compress.cpp
 * Description: Reades in file, builds huffman tree and then encodes data
 * into outfile. 
 *
 */ 
#include <iostream>
#include <fstream>
#include <vector>

#include "HCTree.h"

using namespace std;

int main(int argc, char ** argv){
    const char * infile = argv[1]; 
    const char * outfile = argv[2];

    int c; // unsigned char to store input 
    byte nextByte; // next byte from the input stream

    ifstream in; // input fstream to encode
    in.open(infile, ios::binary);
    vector<int> freqs (ASCII, 0); // a vector of frequencies of all ASCII character
    
    // obtain the frequencies for all ASCII character in infile
    while(( c = in.get()) != EOF){
        freqs[(byte)c]++;
    }
    
    in.close();


    // build the Huffman Coding tree for infile
    HCTree tree;
    tree.build(freqs);
    
    ofstream out; // output fstream to put header and encoded bits 
    out.open(outfile, ios::binary); 

    // write the header 
    tree.write(out);

    // open the input file for encoding
    in.open(infile, ios::binary);
    
    
    BitOutputStream bitOut(out); // bit output stream to support bitwise I/O
    // encodes data into outfile 
    while (( c = in.get())!= EOF ){
        if(in.eof()) break;
        tree.encode(c, bitOut);
    }

    bitOut.flushLastByte(); // flush the last byte

    out.write((char*)& tree.counter, sizeof(tree.counter));

    // closes streams 
    in.close();
    out.close();


    return 0;

}




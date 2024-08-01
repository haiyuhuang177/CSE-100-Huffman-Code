/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: uncompress.cpp
 * Description: Reades in file, builds huffman tree and then decodes data
 * into outfile. 
 *
 */ 
#include <iostream>
#include <fstream>
#include <vector>

#include "HCTree.h"

using namespace std;

int main(int argc, char ** argv){
    // read in input parameter
    const char * infile = argv[1];
    const char * outfile = argv[2];


    ifstream in; // input fstream to encode
    in.open(infile, ios::binary); 
    
    vector<int> freqs; // a vector of frequencies of all ASCII character
    int num; // freqeuencies

    unsigned int counter; // read the number of times encode is run 
    in.seekg(-4, in.end);
    in.read((char*)& counter, sizeof(counter));
    in.seekg(0, in.beg);


    /* build the Huffman Coding tree for infile */
    HCTree tree;
    tree.build(in); // reconstruct the tree from the header
    

    ofstream out; // output fstream to put header and encoded bits 
    out.open(outfile, ios::binary); 
    
    BitInputStream bitIn(in); // bit output stream to support bitwise I/O

    while (counter > 0){
        byte c = tree.decode(bitIn);
        out.put(c);
        counter--;
    }

    // closes streams 
    in.close();
    out.close();


    return 0;

}




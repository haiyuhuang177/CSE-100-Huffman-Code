/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: BitInputStream.h
 * Description: Input stream to read 8 bits at a time 
 *
 */ 
#include <iostream>

class BitInputStream{
    private:
        char buf; // one byte buffer of bits
        int nbits; // how many bits have been writeen to buf
        std::istream & in; // reference to the input stream to use

    public:
        /** Initialize a BitOutput Stream that will use
         * the given ostream for output */
        BitInputStream(std::istream & is);

        /** Fill the buffer from the input */
        void fill();

        /** Read and return the next bit from the bit buffer.
         * Fill it first if necessary. */
        int readBit();

};

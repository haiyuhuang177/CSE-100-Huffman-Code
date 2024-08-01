/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: BitOutputStream.h 
 * Description: Output stream to write 8 bits at a time
 *
 */ 
#include <iostream>

class BitOutputStream{
    private: 
        unsigned char buf; // one byte buffer of bits
        int nbits; // how many bits have been written to buf
        std::ostream& out; // reference to the output stream to use

    public:
        /** Initialize a BitOutputStream that will use
         * the given ostream for output */
        BitOutputStream(std::ostream & os);

        /** Send the buffer to the output, and clear it */
        void flush();

        /** Write the least significant bit of the argument to 
         * the bit buffer, and increment the bit buffer index.
         * But flush the buffer first, if it is full. */
        void writeBit(int i);

        /** flush the last byte */
        void flushLastByte();

};

/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: BitInputStream.cpp
 * Description: Input stream to read 8 bits at a time 
 *
 */ 
#include "BitInputStream.h"

/**
 * Constructor for a BitInputStream object
 * Initialize a BitInputStream that will use the given istream for input.
 */
BitInputStream::BitInputStream(std::istream & is) : in(is), buf(0), nbits(8){}

/** Fill the buffer from the output */
void BitInputStream::fill(){
    buf = in.get();
    nbits = 0;
}

/**
 * Read the next bit from the bit buffer.
 * Fill the buffer from the input stream first if needed.
 * Return 1 if the bit read is 1.
 * Return 0 if the bit read is 0.
 */
int BitInputStream::readBit(){
    // If all bits in the buffer are read, fill the buffer first
    if ( nbits == 8 )
        fill();

    // Get the bit at the appropriate location in the bit buffer, and 
    // return the appropriate bit
   
    int bit = ( (buf | (1 << nbits)) == buf );

    // Increment the index
    nbits++;

    return bit;
}



/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: BitOutputStream.cpp 
 * Description: Output stream to write 8 bits at a time
 *
 */ 
#include "BitOutputStream.h"

/**
 * Constructor for BitOutputStream
 * Purpose: Initialize a BitOutputStream that will use the given 
 *          ostream for output
 */
BitOutputStream::BitOutputStream(std::ostream &os): out(os), buf(0), nbits(0){}

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}

/** 
 * Write the least significant bit of the argument to the bit buffer, and 
 * increment the bit buffer index.
 * But flush the buffer first, if it is full
 */
void BitOutputStream::writeBit(int i) {

    // If the buffer is full, flush it
    if ( nbits == 8 )
        flush();

    // Write the least significant bit of i into the buffer at the current index
    i = i % 2;

    // first clear the n-th bits of buf ( 0 -based counting from the right ) 
    // using bitwise &, then set the n-th bit of buf to i using bitwise |
    buf = buf & ((~0)^(1 << nbits)) | (i << nbits);
    
    // Increment the index
    nbits++;

}

/** Flush the last byte */
void BitOutputStream::flushLastByte(){
    if ( nbits )
        flush();
}

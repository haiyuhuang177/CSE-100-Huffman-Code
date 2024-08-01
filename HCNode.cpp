/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: HCNode.cpp
 * Description: Overloaded operators in Node class 
 *
 */ 
#include "HCNode.h"


/**
 * Compare this HCNode and other for priority ordering.
 * Smaller count means higher priority.
 * Use node symbol for deterministic tiebreaking
 */
bool HCNode::operator<(const HCNode& other){
    // if counts are different, just compare counts
    if (count != other.count) return count > other.count;

    // counts are equal. Use symbol value to break tie.
    return symbol < other.symbol;
}














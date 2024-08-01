/**
 * Name: Haiyu Huang, Kyle Chang
 * Date: October 28, 2016
 * CSE 100 Fall 2016
 * PA3: Huffman
 * File: HCTree.cpp
 * Description: Function definitions to build Huffman tree, decode, 
 * and encode files
 *
 */ 
#include <queue>
#include <stack>
#include "HCTree.h"
#include "HCNode.h"

using namespace std;


// destructor for HCTree
HCTree::~HCTree(){
    deleteAll(root);    
}

/** helper method for destructor to deallocate all HCNode in the tree
 * Automatically called when function returns. 
 */ 
void HCTree::deleteAll(HCNode* n){
    // only delete if node exists 
    if (!n)
        return;
    // deallocate left subtree
    if (n->c0)
        deleteAll(n->c0);
    // deallocate right subtree
    if (n->c1)
        deleteAll(n->c1);
    delete n; 
}

/** Write the tree into our file header
 */
void HCTree::write(ofstream& out){
    writeTree(root, out);
}

/** Writes our Huffman tree using preorder traversal
 *  and recursion
 */
void HCTree::writeTree(HCNode* n, ofstream& out){
    // only write if node exists
    if (!n)
        return;
    // put 0 in ofstream if the current both has both children
    if (n->c0 || n->c1){
        out.put('0');
        writeTree(n->c0, out);
        writeTree(n->c1, out);
    }
    // put 1 in ofstream if we reach a leaf node
    else{
        out.put('1');
        out.put(n->symbol);
    }
}

/** Reconstruct the Huffman tree from our header
 */
void HCTree::build(ifstream& in){
    root = new HCNode (0,0);
    build(root, in);
}

/** Reads our huffman tree from our header in a preorder
 *  traversal and recursion
 */
void HCTree::build(HCNode*n, ifstream& in){
    // if a 0 is read, construct both children
    if (in.get() == '0'){
        n->c0 = new HCNode(0,0);
        n->c0->p = n; 
        n->c1 = new HCNode(0,0);
        n->c1->p = n; 
        build(n->c0, in);
        build(n->c1, in);
    }
    else
        n->symbol = in.get();

}



/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */
void HCTree::build(const vector<int>& freqs){
    // priorty queue to build the Huffman Coding tree
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pqueue; 

    // push HCNode with symbol of nonzero frequencies onto the priority queue
    for (int i = 0; i < ASCII; i++){
        if (freqs[i]){
            HCNode* node = new HCNode(freqs[i],i); 
            pqueue.push(node);
            leaves[i] = node;
        }

    }

    // build the Huffman coding tree
    while ( pqueue.size() > 1 ){

        // Pops off top two nodes from priority queue 
        HCNode* c0 = pqueue.top();
        pqueue.pop();
        HCNode* c1 = pqueue.top();
        pqueue.pop();

        // a new HCNode combining the two HCNode with symbol of smallest frequencies
        HCNode* p = new HCNode(c0->count + c1->count, c0->symbol);
        // linking parent and children
        p->c0 = c0;
        p->c1 = c1;
        c0->p = p;
        c1->p = p;

        // adds parent to priority queue
        pqueue.push(p);

    }

    // root is the last HCNode in the priority queue
    if (!pqueue.empty())
        root = pqueue.top();

}


/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const{
    HCNode* curr = leaves[symbol]; // pointer to the leaf node we are encoding
    stack<byte> encode; // stack to reverse the encoding string

    // if curr is root, i.e. only one node exist in the tree
    if (!curr->p)
        encode.push('0');

    // construct the encoding of the symbol in reverse order
    while (curr->p){
        // if curr is its parent's left child
        if (curr->p->c0 == curr)
            encode.push('0');
        else
            encode.push('1');

        curr = curr->p;
    }
    // output the symbol into ofstream one by one in the correct order
    while( !encode.empty() ){
        out.put(encode.top());
        encode.pop();

    }
}


/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 */
int HCTree::decode(ifstream& in) const{
    HCNode* curr = root; // sets current to root node

    // if nothing is in the tree, i.e. empty file
    if (!curr){
        in.get();
        return 0;
    }

    // if only root exists in the tree
    if (!curr->c0 && !curr->c1){
        if (in.get() == '0')
            return curr->symbol;

    }

    // Traverses down tree to decode 
    while ( curr->c0 || curr->c1 ){
        byte bit = in.get();
        if (bit == '0')
            curr = curr->c0;
        else
            curr = curr->c1;

    }

    // returns decoded symbol 
    return curr->symbol;
}





/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const{
    HCNode* curr = leaves[symbol]; // pointer to the leaf node we are encoding
    stack<int> encode; // stack to reverse the encoding string

    // if curr is root, i.e. only one node exist in the tree
    if (!curr->p)
        encode.push(0);

    // construct the encoding of the symbol in reverse order
    while (curr->p){
        // if curr is its parent's left child
        if (curr->p->c0 == curr)
            encode.push(0);
        else
            encode.push(1);

        curr = curr->p;
    }
    // output the symbol into ofstream one by one in the correct order
    while( !encode.empty() ){
        out.writeBit(encode.top());
        encode.pop();

    }
    counter++;
}




/** Return symbol coded in the next sequence of bits from the stream.
 *
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const{
    HCNode* curr = root; // sets current to root node
    
    // if nothing is in the tree, i.e. empty file
    if (!curr){
        in.readBit();
        return 0;
    }

    // if only root exists in the tree
    if (!curr->c0 && !curr->c1){
        if (in.readBit() == 0)
            return curr->symbol;

    }

    // Traverses down tree to decode 
    while ( curr->c0 || curr->c1 ){
        int bit = in.readBit();
        if (bit == 0)
            curr = curr->c0;
        else
            curr = curr->c1;
    }

    // returns decoded symbol 
    return curr->symbol;
    
}



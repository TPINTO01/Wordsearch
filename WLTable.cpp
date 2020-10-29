/* WLTable Class 
 * Instantiates Hash Table, 
 *  - Keys are strings
 *  - Values are lNodes 
 *  - String hash
 *  - String compare
 *  - Add key value (word-line) pairs
 *  - Find value by key (line by word)
 */

#include <iostream>
#include <functional>
#include "WLTable.h"

int TABLESIZE = 15487469;

int  wHash   (std::string word);
bool wCompare(std::string w1, std::string w2);


WLTable::WLTable() : pairs(TABLESIZE, wHash, wCompare)
{}

WLTable::~WLTable() 
{}

/* First instance (lNode) of arbitrary word will always point to last 
 * instance of arbitrary word, for constant time addition of word
 * instances
 * Inner nodes' last member (lNode->last) points to NULL */
void WLTable::addWLPair(std::string word, lNode *newLNode)
{
    lNode *node = pairs.find(word);

    if (node != NULL) {
        node->last->next = newLNode;
        node->last       = newLNode; 
    } else {
        newLNode->last = newLNode;
        pairs.bind(word, newLNode);
    }
}

lNode *WLTable::findL(std::string word)
{
    return pairs.find(word);
}

/**************************************************************************
 *                                                                        *
 *                           PRIVATE MEMBERS                              *
 *                                                                        *
 **************************************************************************/

int wHash(std::string word)
{
    std::hash<std::string> strHash;
    return (int) (strHash(word) % TABLESIZE);
}

bool wCompare(std::string str1, std::string str2)
{
    return str1 == str2;
}


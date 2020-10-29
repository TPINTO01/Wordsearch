#include "../datastructures/hashtable/Hash.h"

#ifndef WLTABLE_H_
#define WLTABLE_H_

/* for any text file, each line has unique line number, as well as words in
 * that line and name of file. For WordFinder, I want to return this line 
 * data for an arbitrary word (a string with no whitespace) search */
struct line {
    std::string fileName, line;
    int lineNum;    
};

/* lNode analagous to word instance, a single, unique occurrence of
 * a word in file. For WordFinder, not only do I want to return line data 
 * for one instance or the first instance of a word, I want to return the 
 * line data for every instance of an arbitrary word. A linked list of 
 * lines will be the value of the key-value pair (word -> list of lines in 
 * which word occurs) 
 * Note, a word may occur more than once in a single line, I will count 
 * these as separate instances. 
 *
 * I expect a lot of words to occur in the same lines, for example, in the 
 * line;
 *
 *  "The quick brown fox jumps over the lazy dog"
 *
 * the words "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy",
 * and "dog" all occur in the same line. Therefore I will have each instance
 * of a word refer to a line via pointer, as opposed to copying the same 
 * line data for each word. */
struct lNode {
    line       *linePtr;
    std::size_t wordPos;
    lNode      *next;
    lNode      *last;
};

class WLTable 
{
    public:

	    WLTable();
	    ~WLTable();

        /* Add pair word, word-instance (lNode) pair */
        void addWLPair(std::string word, lNode *newLNode);

        /* find line node from key 
         * return ptr to first node of linked list of lines, or first 
         * instance of word. Caller's responsibilty to traverse through 
         * all instances of that word */
        lNode *findL(std::string word);

    private:
        
        /* I will use my hash table template class Hash to hold word-line 
         * pairs. Best-Case constant time access to first instance of a 
         * word, then up to caller of findL to traverse through all 
         * instances of that word.
         *
         * Since my hash table utilizes linked-list chaining, Worst-case
         * O(n) time access to elements, where n is number of entries in
         * the table. This is unlikely, depending on hash function.
         *
         * Load factor of n/k, where n is number of words and k is number of
         * buckets. I use a big, prime k in WordFinder (15487469) 
         *
         * Spacewise, looking at O(n) complexity. */
        Hash<std::string, lNode*> pairs;
};

#endif

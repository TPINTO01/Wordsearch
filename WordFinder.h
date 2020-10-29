#include <vector>
#include "WLTable.h"

#ifndef WORDFINDER_H_
#define WORDFINDER_H_

class WordFinder
{
    public:

	    WordFinder ();
	    ~WordFinder();

        /* Handles the opening and indexing of files (for the sake of 
         * knowing the file name, a member of line data), as well as 
         * command loop, reading in word requests from stream in and 
         * writing word instances to out */
        void run(char* fNames[], int numFiles, std::istream &in, 
                                               std::ostream &out); 

    private:

        WLTable table;

        /* NOTE: I really want to use my own class template Sequence for my 
         * auxilliary deletion containers, but its finnicky. Back to work
         * on that I guess. 
         *
         * Also a better option altogether may be the usage of smart ptrs 
         *
         * Overall theres a lot of pointer indirection going on throughout 
         * WordFinder, and the fact that I need to address it (both in code 
         * and here in writing) may be an indicator of some poor design 
         * choices.*/
        std::vector<line*>  linePtrs;  /* For deletion */
        std::vector<lNode*> lNodePtrs; /* For deletion */

        void indexFile(std::string fName, std::ostream &out);
        void findWord (std::string word,  std::ostream &out);
        
        void bindWordsToLine(int lineNum, std::string lineStr,
                                          std::string fName); 

        line  *newLine (int lineNum,   std::string fileName, 
                                       std::string lineStr);  
        lNode *newLNode(line *linePtr, std::size_t wordPos); 
};

#endif

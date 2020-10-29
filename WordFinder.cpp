#include <iostream>
#include <fstream>
#include <sstream>
#include "output.h"
#include "WordFinder.h"


WordFinder::WordFinder () {}
WordFinder::~WordFinder() 
{
    int numLines  = linePtrs.size();
    int numLNodes = lNodePtrs.size();
    
    for (int i = 0; i < numLines; ++i) 
        delete linePtrs[i];

    for (int i = 0; i < numLNodes; ++i) 
        delete lNodePtrs[i];
}

void WordFinder::run(char* fNames[], int numFiles, std::istream &in, 
                                                   std::ostream &out)
{
    for (int i = 1; i < numFiles; ++i) {
        std::string fName(fNames[i]);
        indexFile(fName, out);       
    }

    std::string word;
    out << "What word would you like to find? \n";
    for (in >> word; ! in.eof(); in >> word) {
        findWord(word, out); 
        out << "What word would you like to find? \n";
    }
}


/**************************************************************************
 *                                                                        *
 *                          Private Members                               *
 *                                                                        *
 *************************************************************************/

void WordFinder::indexFile(std::string fName, std::ostream &out)
{
    std::ifstream inFile;
    inFile.open(fName);
    if (!inFile) {
        out << "Error: Could not open " << fName << std::endl;
        return; 
    }

    std::string lineStr;
    int lineNum = 1;
       
    out << "Indexing " << fName << std::endl;
    while (std::getline(inFile, lineStr)) {
        bindWordsToLine(lineNum, lineStr, fName);
        ++lineNum;
    } 
    inFile.close();
}

void WordFinder::findWord(std::string word, std::ostream &out)
{
    lNode *node = table.findL(word);        
    int wordCount = 0;
    while (node != NULL) {
        ++wordCount;        
        line *linePtr = node->linePtr;
        if (supportsColor()) {
            printColorLine(word, linePtr, node->wordPos, out); 
        } else {
            printLine(linePtr, out);
        }
        node = node->next;
    } 
    if (supportsColor()) {
        printColorWC(word, wordCount, out); 
    } else {
        printWC(word, wordCount, out);
    }
}

void WordFinder::bindWordsToLine(int lineNum, std::string lineStr, 
                                              std::string fName)
{
    std::string word;
    std::size_t wordPos;

    if (lineStr.length() > 0) {
        line *linePtr = newLine(lineNum, fName, lineStr);

        std::stringstream ss(lineStr);
        ss >> std::ws;
        wordPos = ss.tellg();
        while (ss >> word) {

            lNode *lNodePtr = newLNode(linePtr, wordPos);
            table.addWLPair(word, lNodePtr);

            ss >> std::ws;
            wordPos = ss.tellg();
        } 
    }    	 
}

line *WordFinder::newLine(int lineNum, std::string fileName, 
                                       std::string lineStr)
{
    line *newLine     = new line;
    newLine->lineNum  = lineNum;
    newLine->fileName = fileName;
    newLine->line     = lineStr;
    linePtrs.push_back(newLine);
    return newLine;
}

lNode *WordFinder::newLNode(line *linePtr, std::size_t wordPos)
{
    lNode *newLNode   = new lNode;
    newLNode->linePtr = linePtr;
    newLNode->wordPos = wordPos;
    newLNode->next    = NULL;
    newLNode->last    = NULL;
    lNodePtrs.push_back(newLNode);
    return newLNode;
}

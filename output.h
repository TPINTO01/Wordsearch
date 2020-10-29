#include <cstring>
#include "WLTable.h"

#ifndef OUTPUT_H_
#define OUTPUT_H_

#define resetColor "\033[0m"
#define green      "\033[32m"
#define cyan       "\033[36m"
#define red        "\033[1;31m"
#define yellowHighlight "\033[1;30;43m"

bool supportsColor ();
void printColorLine(std::string word, line *linePtr, std::size_t wordPos, 
                                                     std::ostream &out);
void printLine     (line *linePtr, std::ostream &out);
void printColorWC  (std::string word, int wordCount, std::ostream &out);
void printWC       (std::string word, int wordCount, std::ostream &out);

bool supportsColor()
{
    if (const char *env_p = std::getenv("TERM")) {
        const char *const terms[] = {
            "xterm", "xterm-256", "xterm-256color", "vt100",
            "color", "ansi", "cygwin", "linux"};
        for (auto const term: terms) {
            if(std::strcmp(env_p, term) == 0) return true;
        } 
    }
    return false;
}

void printColorLine(std::string word, line *linePtr, std::size_t wordPos, 
                                                     std::ostream &out)
{
    std::string fullLine = linePtr->line;
    out << cyan << linePtr->fileName << resetColor << ": "  << green 
        << linePtr->lineNum << resetColor << " : ";
    
    std::string highlight(yellowHighlight);
    std::string no_highlight(resetColor); 
    fullLine.replace(wordPos, word.length(), 
                     highlight.append(word).append(no_highlight));

    out << fullLine << std::endl;
}

void printLine(line *linePtr, std::ostream &out)
{
    out << linePtr->fileName << ": "  << linePtr->lineNum << " : "  
        << linePtr->line << std::endl;
}

void printColorWC(std::string word, int wordCount, std::ostream &out)
{
    out << red << word << resetColor << " found " << wordCount 
        << " times.\n";
}

void printWC(std::string word, int wordCount, std::ostream &out)
{
    out << word << " found " << wordCount << " times.\n";
}

#endif

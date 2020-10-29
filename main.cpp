#include <iostream>
#include <fstream>
#include "WordFinder.h"

void usage(char *progName);

int main(int argc, char* argv[])
{
    WordFinder finder;

    if (argc > 1) {
        finder.run(argv, argc, std::cin, std::cout);       
    } else {
        usage(argv[0]); 
    }
    
    return 0; 
}

void usage(char *progName)
{
    std::cerr << "usage: " << progName << " input_file1 input_file2 ..." <<std::endl;
}

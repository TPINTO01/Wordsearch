CXX      = clang++
CXXFLAGS = -std=c++11 -O3 -g3 -Wall -Wextra
LDFLAGS  = -g3
 
#
WordFinder: main.o WordFinder.o WLTable.o 
	${CXX} ${LDFLAGS} -o WordFinder main.o WordFinder.o WLTable.o

#
#testRPNCalc: testRPNCalc.cpp RPNCalc.o
WordFinder.o:     WordFinder.cpp
WLTable.o:		WLTable.cpp
 

#
clean:
	rm WordFinder *.o 


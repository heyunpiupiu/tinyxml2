all: xmltest2
xmltest2: xmltest2.cpp tinyxml2.cpp tinyxml2.h
	g++  -std=c++11   xmltest2.cpp  -o xmltest2
tinyxml2: tinyxml2.h
	g++ -std=c++11 tinyxml2.cpp 
test: clean xmltest2
	./xmltest2
clean:
	rm -f *.o xmltest xmltest2

all: xmltest2
xmltest2: xmltest2.cpp tinyxml2.cpp tinyxml2.h
	g++  -std=c++11   xmltest2.cpp tinyxml2.cpp tinyxml2.h   -o xmltest2
test: clean xmltest2
	./xmltest2
clean:
	rm -f *.o xmltest xmltest2

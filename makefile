all: sets maps

sets:
	g++ -std=c++11 -o sets sets.cpp

maps:
	g++ -std=c++11 -o maps maps.cpp

clean:
	rm -f sets
	rm -f maps
	rm -f word_set*.txt
	rm -f unordered_word_set*.txt
	rm -f word_map*.txt

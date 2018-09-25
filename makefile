sets:	sets.cpp 
	g++ -std=c++11 -o sets sets.cpp

clean:
	rm -f sets
	rm -f word_set*.txt
	rm -f unordered_word_set*.txt

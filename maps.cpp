#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

/*
 * Print map to an output stream
 * @param stringIntMap - map of string => int to print out
 * @param os - output stream (default: cout)
 */
void printMap(map<string, int> stringIntMap, ostream& os = cout)
{
	os << "Map size: " << stringIntMap.size() << endl;

	// Iterate over all elements of a map
	map<string, int>::iterator it;
	for(it = stringIntMap.begin(); it != stringIntMap.end(); ++it)
	{
		os << it->first << " => " << it->second << endl;
	}
}

/*
 * Get map of word counts from input file stream
 * @param ifs - input file stream
 * @return map of string word => int word_count
 */
map<string, int> getWordCountMap(ifstream& ifs)
{
	map<string, int> word_map;
	string line;
	while(getline(ifs, line)) // Read each line from file
	{
		string word = "";
		string::iterator it;
		for(it=line.begin(); it != line.end(); ++it)
		{
			char c = *it;
			// End word when these characters are reached
			if(c == ' ' || c == '\n' || c == '-')
			{
				// If word is not empty, modify map
				if(word != "")
				{
					// If word not found in map, make new entry with count of 1
					if(word_map.find(word) == word_map.end())
						word_map.insert(make_pair(word, 1));
					// If word found in map, increment count
					else
						word_map[word]++;
				}
				// Clear word
				word = "";
			}
			// If the next character is alphabetical, add it to word
			else if(isalpha(c))
			{
				word += c;
			}
		}
	}
	return word_map;
}

int main(int argc, char* argv[])
{
	// Read text file into map of words => word count
	string filename = "harry_potter_book_1.txt"; // Default if no arg passed in
	if(argc > 1)
		filename = argv[1];
	ifstream fileIn(filename);
	map<string, int> wordCountMap = getWordCountMap(fileIn);
	fileIn.close();

	// Print to text file
	string mapFilename = "word_map_" + filename;
	ofstream fileOut(mapFilename);
	printMap(wordCountMap); // This will print it to cout
	printMap(wordCountMap, fileOut); // This will print it to output file
	fileOut.close();
}

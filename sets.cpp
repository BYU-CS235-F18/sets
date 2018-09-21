#include <set>
#include <unordered_set>
#include <vector>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

void printSet(set<string> words)
{
  cout << "Set size: " << words.size() << endl;

  // Iterate over all elements of a set
  set<string>::iterator it;
  for(it = words.begin(); it != words.end(); ++it)
  {
    cout << *it << endl;
  }
  cout << endl;
}

void testPairs()
{
  // Make some pairs
  pair<string, string> pair1 = make_pair("first name", "Albus");
  pair<string, string> pair2 = make_pair("last name", "Dumbledore");
  pair<string, string> pair3 = make_pair("favorite gift", "socks");

  // Push them into a vector
  vector<pair<string, string> > pairs;
  pairs.push_back(pair1);
  pairs.push_back(pair2);
  pairs.push_back(pair3);
  pairs.push_back(make_pair("password", "\"lemon drop\"")); // You can skip a step and just do this

  // Print out stuff using the vector of pairs
  for(int i = 0; i < pairs.size(); i++)
  {
    // Use ".first" to access the first element from a pair and ".second" to access the second element
    cout << "My " << pairs[i].first << " is " << pairs[i].second << "." << endl;
  }
}

void testFindSpeeds()
{
  clock_t oldtime, newtime;
  double seconds;
  int itemCount = 50000000;
  int findValue = 999999999;

  // Test find speed in vector
  vector<int> numVec;
  oldtime = clock(); 
  for(int i = 0; i < itemCount; i++)
    numVec.push_back(i);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Vector insert end took " << seconds << " s" << endl;
  oldtime = clock(); 
  vector<int>::iterator vit = find(numVec.begin(), numVec.end(), findValue);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Vector find took " << seconds << " s" << endl;

  // Test find speed in list
  list<int> numList;
  oldtime = clock(); 
  for(int i = 0; i < itemCount; i++)
    numList.push_back(i);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Linked List insert end took " << seconds << " s" << endl;
  oldtime = clock(); 
  list<int>::iterator lit = find(numList.begin(), numList.end(), findValue);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Linked List find took " << seconds << " s" << endl;

  // Test find speed in set
  set<int> numSet;
  oldtime = clock(); 
  for(int i = 0; i < itemCount; i++)
    numSet.insert(i);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Set insert took " << seconds << " s" << endl;
  oldtime = clock(); 
  set<int>::iterator sit = numSet.find(findValue);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Set find took " << seconds << " s" << endl;

  // Test find speed in unordered_set
  unordered_set<int> numUnSet;
  oldtime = clock(); 
  for(int i = 0; i < itemCount; i++)
    numUnSet.insert(i);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Unordered Set insert took " << seconds << " s" << endl;
  oldtime = clock(); 
  unordered_set<int>::iterator usit = numUnSet.find(findValue);
  newtime = clock();
  seconds = (double)(newtime-oldtime)/CLOCKS_PER_SEC;
  cout << "Unordered Set find took " << seconds << " s" << endl;
}

void testSetUniqueValues()
{
  set<string> wordSet;

  wordSet.insert("nitwit");
  wordSet.insert("blubber");
  wordSet.insert("oddment");
  wordSet.insert("tweak");
  printSet(wordSet);

  // This won't make a difference because elements in set must be unique
  wordSet.insert("tweak");
  printSet(wordSet);

  // If you want to test whether or not an element was added to a set,
  // you can look at the ".second" value returned by the set insert
  // function. It will be true on success and false on failure.
  pair<set<string>::iterator,bool> result = wordSet.insert("tweak");
  if(result.second == true)
  {
    cout << "'tweak' added to set!" << endl;
  }
  else
  {
    cout << "'tweak' not added to set because it's already there" << endl;
  }
}

set<string> getWordSet(ifstream& ifs)
{
  set<string> word_set;
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
        if(word != "")
          word_set.insert(word);
        word = "";
      }
      // If the next character is alphabetical, add it to word
      else if(isalpha(c))
      {
        word += c;
      }
    }
    // At the end of a line, add the last word
    if(word != "")
      word_set.insert(word);
  }
  return word_set;
}

int main(int argc, char *argv[])
{
  // Test pairs
  testPairs();

  // Test set unique values
  testSetUniqueValues();

  // Test find speeds
  testFindSpeeds();

  // Read text file into set of words
  string filename = "harry_potter_book_1.txt"; // Default if no arg passed in
  if(argc > 1)
    filename = argv[1];
  ifstream fileIn(filename);
  set<string> wordSet = getWordSet(fileIn);

  // Output set of words to text file
  string setFilename = "word_set_" + filename;
  ofstream fileOut(setFilename);
  fileOut << "Unique word count: " << wordSet.size() << endl;
  for(set<string>::iterator it = wordSet.begin(); it != wordSet.end(); ++it)
  {
    fileOut << *it << endl;
  }
  fileOut.close();

  // Copy word set into unordered_set
  unordered_set<string> unWordSet;
  for(set<string>::iterator it = wordSet.begin(); it != wordSet.end(); ++it)
  {
    unWordSet.insert(*it);
  }

  // Output unordered set of words to text file
  string unSetFilename = "unordered_word_set_" + filename;
  ofstream unFileOut(unSetFilename);
  unFileOut << "Unique word count: " << unWordSet.size() << endl;
  for(unordered_set<string>::iterator it = unWordSet.begin(); it != unWordSet.end(); ++it)
  {
    unFileOut << *it << endl;
  }
  unFileOut.close();
}

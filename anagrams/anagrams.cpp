#include <iostream>
#include <string>
#include <cassert>
#include <fstream>
#include <istream>
#include <cstring>

using namespace std;


bool searchAndFound(const string dictArr[], int size, string perms);
void printPermutations(string word, string perms, const string dict[], int size, int& numMatches, string results[]);		//back to void
int vocabularyCreatorCount(istream& dictfile, string dict[], int count);
bool inResultsHelper(string perms, int size, string results[]);
void loop(string word, string perms, const string dict[], int size, int& numMatches, string results[], int i);
void printPermutations(string word, string perms, const string dict[], int size, int& numMatches, string results[]);


const int MAXRESULTS = 20; // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


//Puts each string in dictfile into the array dict.
//Returns the number of words read into dict.
//The number should NOT be larger than MAXDICTWORDS,
//since that is the size of the array.


int vocabularyCreator(istream& dictfile, string dict[]) {
	return vocabularyCreatorCount(dictfile, dict, 0);
}

int vocabularyCreatorCount(istream& dictfile, string dict[], int count) {
	if (count >= MAXDICTWORDS) {
		return MAXDICTWORDS;
	}


	if (dictfile >> dict[0]) {
		return (vocabularyCreatorCount(dictfile, dict + 1, count + 1));
	}
	return count;
}



//Puts all the possibilities of 'word' which are found
//in 'dict' into 'results.' Returns the max number of 
//matched words found. This number should NOT be larger 
//than MAXRESULTS since that is the size of the array.
//The 'size' is the number of words inside the 'dict' array

//The 'results' array returned must have NO duplicates
int potentialSequences(string word, const string dict[], int size, string results[]) {
	int numMatches = 0;

	if (numMatches >= MAXRESULTS) {
		return MAXRESULTS;
	}

	if (word.length() == 0) {
		return numMatches;
	}

	if (word.length() == 1) {
		if (searchAndFound(dict, size, word)) {
			results[numMatches] = word;
			numMatches++;
		}
	} else {
		printPermutations(word, "", dict, size, numMatches, results);
		return numMatches;
	}
	return numMatches;
}






bool searchAndFound(const string dictArr[], int size, string perms) {

	if (size == 0) {
		return false;

	}else if (perms == dictArr[0]) { 

		return true;
	} else {
		return searchAndFound(dictArr + 1, size - 1, perms); 
	}
}



//recursive binary search. ended up not being able to use this...
/*
bool searchAndFound(const string dictArr[], int bot, int top, string word) {
	if (top > bot) {
		return false;
	}
	else {
		int mid = bot + (top - bot) / 2;

		if (word == dictArr[mid]) {
			return true;
		}
		else if (toLower(word) < toLower(dictArr[mid])) {
			return (searchAndFound(dictArr, mid - 1, top, word));
		}
		else if (toLower(word) > toLower(dictArr[mid])) {
			return (searchAndFound(dictArr, bot, mid + 1, word));
		}
	}

}
*/

//this was previously used for the binary recursive search to handles cases
/*
string toLower(string toLowerCase) {
	if (toLowerCase.length() == 0) {
		return "";
	}

	char character = tolower(toLowerCase[0]);
	string remaining = toLower(toLowerCase.substr(1, toLowerCase.size() - 1));

	return character + remaining;
}
*/



bool inResults(string perms, string results[]) {
	int size = MAXRESULTS;

	return inResultsHelper(perms, size, results);
}


bool inResultsHelper(string perms, int size, string results[]) {
	if (size == 0) {
		return false;
	}

	if (results[0] == "") {
		return false;
	} else if (perms == results[0]) {
		return true;
	} 
	return inResultsHelper(perms, size - 1, results + 1);
}





void printPermutations(string word, string perms, const string dict[], int size, int &numMatches, string results[]) {		//back to void

	if (numMatches >= MAXRESULTS) {

		numMatches = MAXRESULTS;
		return;
	}


	if (word.length() == 0) {
		if (searchAndFound(dict, size, perms)) {
			if (inResults(perms, results)) {
				return;
			}else {
				results[numMatches] = perms;
				numMatches++;
			} 
		} 
	}

	loop(word, perms, dict, size, numMatches, results, 0);
}



void loop(string word, string perms, const string dict[], int size, int& numMatches, string results[], int i) {
	if (i >= word.length()) {
		return;
	}

	printPermutations(word.substr(0, i) + word.substr(i + 1), perms + word[i], dict, size, numMatches, results);
	loop(word, perms, dict, size, numMatches, results, i + 1);
}




//Displays 'size' number of strings from results.
//The results can be printed in any order
void outcomeDisclosure(const string results[], int size) {
	
	if (size == 0) {
		return;
	}

	cout << "Matching word: " + results[0] << endl;
	return outcomeDisclosure(results + 1, size - 1);
}




int main(void) {

	string results[MAXRESULTS];
	string dict[MAXDICTWORDS];
	ifstream dictfile; // file containing the list of words
	int nwords; // number of words read from dictionary
	string word;
	dictfile.open("words.txt");
	if (!dictfile) {
		cout << "File not found!" << endl;
		return (1);
	}
	nwords = vocabularyCreator(dictfile, dict);
	
	cout << "Please enter a string for an anagram: ";
	cin >> word;
	

	int numMatches = potentialSequences(word, dict, nwords, results);
	
	/*
	if (!numMatches) {
		cout << "No matches found" << endl;
	}
	*/
	
	outcomeDisclosure(results, 5);

	return 0;
	
}


#ifndef SEARCHTREE_H
#define SEARCHTREE_H

#include "ITreeType.h"
#include <fstream>

using std::ifstream;
using std::ofstream;

class SearchTree
{
private:
	TreeType C1Tree;
	TreeType C2Tree;
public:
	bool ProcessItems(ifstream&, ofstream&);
	void PrintItems(ofstream&);
	void UserInput(ifstream&, ofstream&);
	void CapitalizeLetters();
	string Contestant1;
	string Contestant2;
	string Phrase;
	string ContestantToStore;
};

#endif


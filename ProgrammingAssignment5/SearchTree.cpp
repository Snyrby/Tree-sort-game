#include "SearchTree.h"
#include <iostream>
#include <string>


using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::getline;

/*****************************************************************************************
*  function Name: ProcessItems(ifstream& inFile, ofstream& outFile)
*  Parameters: outFile, inFile
*  Return Value: bool
*  Purpose: loops through every magic word of the input file and places each word into 2 different binary search trees
*****************************************************************************************/

bool SearchTree::ProcessItems(ifstream& inFile, ofstream& outFile)
{
	string CurrentWord;
	/* trys to loop through every word in the file */
	try
	{
		//while (InFile >> Title >> Author >> Subject) //Loop through each book in the file
		/* loops through every word in the file */
		while (inFile >> CurrentWord)
		{
			/* if the trees are full then it says an error messages and returns false*/
			if (C1Tree.IsFull() || C2Tree.IsFull())
			{
				cerr << "Error: Tree is full!\n\n";
				return false;
			}
			/* puts each of the magic words into 2 different trees for different contestants */
			C1Tree.PutItem(CurrentWord);
			C2Tree.PutItem(CurrentWord);

			/* displays each word */
			cout << "Word " << C1Tree.GetLength() << ": " << CurrentWord << endl << endl;
			outFile << "Word " << C1Tree.GetLength() << ": " << CurrentWord << endl << endl;
		}
	}
	catch (string ex) 
	{
		cerr << "An error occurred. " << ex;
		system("pause");
		return false;
	}
	return true;
}

/*****************************************************************************************
*  function Name: UserInput(ifstream& inFile, ofstream& outFile)
*  Parameters: outFile, inFile
*  Return Value: none
*  Purpose: loops through every line of the input file and places determines if each line is a contestant or a phrase
*****************************************************************************************/

void SearchTree::UserInput(ifstream& inFile, ofstream& outFile)
{
	string Input;
	int LineNumber = 1;

	try {
		//while (InFile >> Title >> Author >> Subject) //Loop through each book in the file
		while (getline(inFile, Input))
		{
			if (LineNumber % 4 == 1) //Contestant1 line
			{
				Contestant1 = Input;

				//calls function
				CapitalizeLetters();
			}
			else if (LineNumber % 4 == 2) //phrase line
			{
				Phrase = Input;
				CapitalizeLetters();

				//says the phrase each contestant says
				cout << Contestant1 << " says: " << Phrase << "\n\n";
				outFile << Contestant1 << " says: " << Phrase << "\n\n";
			}
			else if (LineNumber % 4 == 3) // Contestant2 line
			{
				Contestant2 = Input;
				CapitalizeLetters();
			}
			else if (LineNumber % 4 == 0) //phrase line
			{
				Phrase = Input;
				CapitalizeLetters();
				cout << Contestant2 << " says: " << Phrase << "\n\n";
				outFile << Contestant2 << " says: " << Phrase << "\n\n";
			}
			LineNumber++;
		}
	}
	catch (string ex) {
		cerr << "An error occurred. " << ex;
		system("pause");
		return;
	}
}

/*****************************************************************************************
*  function Name: CapitalizeLetters()
*  Parameters: none
*  Return Value: none
*  Purpose: prints Capitalizes all first letters, lowercases every letter. searches a binary search tree for each word
*****************************************************************************************/

void SearchTree::CapitalizeLetters()
{
	string PhraseToDelete;

	bool found;

	// splits the data by 1 as contestant or 2 by phrase
	if (Contestant1[0] == '1')
	{
		ContestantToStore = "";

		//removes the 1 at the beginning
		Contestant1.substr(1);
		Contestant1.replace(0, 1, "");

		// sets the first letter to capitalize 
		Contestant1[0] = toupper(Contestant1[0]);

		// puts each the first letter to Contestanttoscore
		ContestantToStore += Contestant1[0];

		// loops through each letter and adds to contestant to score and lower
		for (int i = 1; i < Contestant1.length(); i++)
		{
			ContestantToStore += Contestant1[i];
			Contestant1[i] = tolower(Contestant1[i]);
		}
	}

	// same thing as contestant 1, but for contestant 2
	else if (Contestant2[0] == '1')
	{
		ContestantToStore = "";
		Contestant2.substr(1);
		Contestant2.replace(0, 1, "");
		Contestant2[0] = toupper(Contestant2[0]);
		ContestantToStore += Contestant2[0];
		for (int i = 1; i < Contestant2.length(); i++)
		{
			ContestantToStore += Contestant2[i];
			Contestant2[i] = tolower(Contestant2[i]);
		}
	}

	// confirms that it is a phrase
	else if (Phrase[0] == '2')
	{
		// removes the 2 at the beginning of the string
		Phrase.substr(1);
		Phrase.replace(0, 1, "");

		// sets the first letter of phrase to capitalize and adds it to phrase to delete
		Phrase[0] = toupper(Phrase[0]);
		PhraseToDelete += Phrase[0];

		//loops through every letter of the phrase
		for (int i = 1; i < Phrase.length(); i++)
		{
			//if the phrase contains a space, it Sets the next letter to capitalize and adds it the phrase to delete
			if (Phrase[i - 1] == ' ')
			{
				Phrase[i] = toupper(Phrase[i]);
				PhraseToDelete += Phrase[i];
				
			}

			// if the phrase is a space or at the end of the phrase
			else if (Phrase[i] == ' ' || i == Phrase.length() - 1)
			{
				// resets both trees
				C1Tree.ResetTree(IN_ORDER);
				C2Tree.ResetTree(IN_ORDER);

				//if it's contestant1's phrase
				if (Contestant1 == ContestantToStore)
				{
					// checks to find each word in the tree and if found, deletes it
					C1Tree.GetItem(PhraseToDelete, found);
					if (found)
					{
						C1Tree.DeleteItem(PhraseToDelete);
					}
				}
				//if it's contestant2's phrase
				else if (Contestant2 == ContestantToStore)
				{
					// checks to find each word in the tree and if found, deletes it
					C2Tree.GetItem(PhraseToDelete, found);
					if (found)
					{
						C2Tree.DeleteItem(PhraseToDelete);
					}
				}
				//resets the phrase back to null
				PhraseToDelete = "";
			}
			else
			{
				//ignores all of these punctuation
				if (!(Phrase[i] == '?' || Phrase[i] == '!' || Phrase[i] == ',' || Phrase[i] == '.' || Phrase[i] == '\''))
				{
					//if it's not the punctuation, it lowers the letter and adds it to the phrase to delete
					Phrase[i] = tolower(Phrase[i]);
					PhraseToDelete += Phrase[i];
				}
			}
		}
	}
} 

/*****************************************************************************************
*  function Name: PrintItems(ofstream& outFile)
*  Parameters: outFile
*  Return Value: none
*  Purpose: prints all data within the each binary search tree back to the text file
*****************************************************************************************/

void SearchTree::PrintItems(ofstream& outFile)
{
	//prints out if each contestant either wins or loses and says the words the didn't say if they lost
	if (!C1Tree.IsEmpty())
	{
		C1Tree.ResetTree(IN_ORDER);
		cout << "Sorry, " << Contestant1 << ", you failed to say the following magic words: ";
		outFile << "Sorry, " << Contestant1 << ", you failed to say the following magic words: ";
		C1Tree.Print(outFile);
		cout << endl << endl;
	}
	else
	{
		cout << "Congratulations, " << Contestant1 << ", you have won the prize!\n\n";
		outFile << "Congratulations, " << Contestant1 << ", you have won the prize!\n\n";
	}

	if (!C2Tree.IsEmpty())
	{
		C2Tree.ResetTree(IN_ORDER);
		cout << "Sorry, " << Contestant2 << ", you failed to say the following magic words: ";
		outFile << "Sorry, " << Contestant2 << ", you failed to say the following magic words: ";
		C2Tree.Print(outFile);
		cout << endl << endl;
		outFile << endl << endl;
	}
	else
	{
		cout << "Congratulations, " << Contestant2 << ", you have won the prize!\n";
		outFile << "Congratulations, " << Contestant2 << ", you have won the prize!";
	}
}
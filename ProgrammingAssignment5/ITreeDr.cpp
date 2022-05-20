/*****************************************************************************************
*  Program Name: ProgrammingAssignment5
*  Created Date: 5/10/19
*  Created By: Shawn Ruby
*  Purpose: creates a game that has contestants guess magic words
*  Acknowledgements: None
*****************************************************************************************/

#include <iostream>
#include <fstream>
#include "SearchTree.h"

using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;
using std::exception;
int main()
{
	try
	{
		ifstream inFile; //Get an input file of data to process
		inFile.open("Magic.txt"); //Get file ready to read input

		ofstream outFile; //Get an output file to write data out to
		outFile.open("Output.txt"); //Get file ready to write data to

		SearchTree myTree;
		myTree.ProcessItems(inFile, outFile); //Read and process all magical words
		inFile.close();
		inFile.open("TextPass.txt");
		myTree.UserInput(inFile, outFile);
		myTree.PrintItems(outFile); //Print out all the magic words said to the output file

		inFile.close(); //Need to close our input and output files
		outFile.close();
	}
	catch (exception& ex) //Catch any errors that occure and display them in the console to the user
	{
		cerr << "An error occured: " << ex.what() << endl;
		system("pause");
		return 1;
	}

	system("pause");
	return 0;
}





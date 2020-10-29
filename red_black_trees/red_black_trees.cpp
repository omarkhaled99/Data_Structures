#include <iostream>
#include "Rbtree.h"
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
#include<fstream>
using namespace std;
int main()
{
	system("color 1a");
	Rbtree tree;
	char temp[50] = "";
	string filename;
	ifstream file("dictionary.txt", std::ios_base::in);
	while (file.getline(temp, 50)) {
		tree.insert(temp);
	}
    cout <<"The tree height is:\t"<< tree.height() << endl;
	cout << "The number of elements in the dictionary is:\t"<<tree.size() << endl;
	while (true)
	{
		cout << "PLEASE ENTER A NUMBER" << endl;
		cout << "1. insert a word				2. search for a word" << endl;
		char choice[20];
	
		cin.getline(choice,20, '\n');
		if(!strcmp(choice,"1")){
			cout << "Please enter the word : \n";
			char word[50];
			cin.getline(word, 50,'\n');
			int y = tree.findElement(word);
			if (y == 0)
			{
				tree.insert(word);
				cout << "insertion done !" << endl;
				cout << "The tree height after insertion is:\t" << tree.height() << endl;
				cout << "The number of elements in the dictionary is:\t" << tree.size() << endl;
				ofstream myfile("dictionary.txt", ofstream::app);
				if (myfile.is_open())
				{
					myfile << "\n";
					myfile << word;

					myfile.close();
				}
			}
			else{
				cout << "The word already exists!" << endl;
			
			}

		
		}
		else if (!strcmp(choice, "2")) {
			cout << "Please enter the word : \n";
			char word[50];
			cin.getline(word, 50,'\n');
			int x = tree.findElement(word);
			if (x == 1)cout << "WORD FOUND\n";
			else
				cout << "WORD NOT FOUND\n";
		}
	}
	

	
}
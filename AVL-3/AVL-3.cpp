// Assignment1-AVLTrees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "TreeHeader.h"
#include <string>

using namespace std;
int ShowMenu(void);
bool quitFlag = false;
void DoQuit(void);

AVLType<string> AVLTree;

int main()
{
	int option;
	string item;



	do
	{
		option = ShowMenu();
		switch (option)
		{
		case 1:
			cout << "Enter Item" << endl;
			cin >> item;
			AVLTree.InsertItem(item);
			break;
		case 2:
			AVLTree.PrintTree();
			break;
		case 3:
			cout << "Enter Item" << endl;
			cin >> item;
			AVLTree.SearchItem(item);
			break;
		case 4:
			cout << "Enter Item to Delete" << endl;
			cin >> item;
			AVLTree.DeleteItem(item);
			break;
		case 5:
			DoQuit();
			break;
		default:
			cout << "Invalid Option";
			break;
		}
	} while (!quitFlag);

	return 0;
}

int ShowMenu(void)
{
	int option;

	cout << endl;


	cout << "1. Insert Item \n";
	cout << "2. Print Tree\n";
	cout << "3. Search Item\n";
	cout << "4. Delete Item \n";
	cout << "5. Exit \n";

	cout << endl;
	cin >> option;
	return option;
}
void DoQuit(void)
{
	quitFlag = true;
}
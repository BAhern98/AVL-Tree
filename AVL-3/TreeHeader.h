#pragma once
#include <iostream>
using namespace std;

typedef enum { LH, EH, RH } Balfactor;

template <class ItemType>
struct TreeNode
{
	ItemType info;
	TreeNode *left;
	TreeNode *right;
	Balfactor bf;
	ItemType root;
};

template<class ItemType>
class AVLType
{
public:
	AVLType();
	~AVLType();
	void InsertItem(ItemType item);
	void PrintTree();
	void SearchItem(ItemType item);
	void DeleteItem(ItemType item);
	//void DeleteNode(TreeNode <ItemType> * & tree, bool & shorter);
private:
	void Insert(TreeNode<ItemType>*& tree, ItemType item, bool &taller);
	void RightBalance(TreeNode<ItemType>*& tree, bool &taller);
	void LeftBalance(TreeNode<ItemType>*& tree, bool &taller);
	//void RotateRight(TreeNode<ItemType>*& tree);
	//void RotateLeft(TreeNode<ItemType>*& tree);
	void Print(TreeNode<ItemType>*& tree);
	void Search(TreeNode<ItemType>*& tree, ItemType item);
	void Delete(TreeNode<ItemType>*& tree, ItemType item, bool & shorter);
	void DeleteNode(TreeNode <ItemType> * & tree, bool & shorter);
	TreeNode<ItemType>* root;
};

template <class ItemType>
AVLType<ItemType>::AVLType()
{
	root = NULL;
}

template <class ItemType>
AVLType<ItemType>::~AVLType()
{
}

template <class ItemType>
void AVLType<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
	bool taller;
	Insert(root, item, taller);
}

template <class ItemType>
void AVLType<ItemType> ::Insert(TreeNode<ItemType>*& tree, ItemType item, bool & taller)
// Inserts item into tree.
// Post:	item is in tree; search property is maintained.
{
	if (tree == NULL)
	{					// Insertion place found.
		tree = new TreeNode<ItemType>;
		tree->left = NULL;
		tree->right = NULL;
		tree->info = item;
		tree->bf = EH;
		taller = true;
	}
	else if (item == tree->info)
	{
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	}
	else if (item < tree->info)
	{
		Insert(tree->left, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case LH: LeftBalance(tree, taller); break;
			case EH: tree->bf = LH; break;
			case RH: tree->bf = EH; taller = false; break;
			}
	}
	else if (item > tree->info)
	{
		Insert(tree->right, item, taller);
		if (taller)
			switch (tree->bf)
			{
			case RH: RightBalance(tree, taller); break;
			case EH: tree->bf = RH; break;
			case LH: tree->bf = EH; taller = false; break;
			}
	}
}





template <class ItemType>
void AVLType<ItemType> ::PrintTree()
{
	Print(root);
}

template <class ItemType>
void AVLType<ItemType> ::Print(TreeNode<ItemType>*& tree)
{
	if (tree == NULL)
		return;
	string bf, left, right;
	Print(tree->left);

	cout << "\t" << tree->info << ":";

	if (tree->left == NULL)
	{
		left = "NULL";
		cout << "\tLeft: " << left;
	}
	else
		cout << "\tLeft: " << tree->left->info << "  ";

	if (tree->right == NULL)
	{
		right = "NULL";
		cout << "\tRight: " << right;
	}
	else
		cout << "\tRight: " << tree->right->info << "  ";



	switch (tree->bf)
	{
	case 0: bf = "LH";
		break;
	case 1: bf = "EH";
		break;
	case 2: bf = "RH";
		break;
	}
	cout << "\tBF: " << bf << endl;

	




	Print(tree->right);
}


template <class ItemType>
void AVLType<ItemType> ::SearchItem(ItemType item)
{
	Search(root, item);
}


template <class ItemType>
void AVLType<ItemType> ::Search(TreeNode<ItemType>*& tree, ItemType item)
{
	if (tree != NULL)
	{
		if (item < tree->info)
			Search(tree->left, item);
		else if (item > tree->info)
			Search(tree->right, item);
		else
			cout << "Item found in tree!" << endl;
	}
	else
		cout << "Item NOT found in tree!" << endl;

}



template <class ItemType>
void AVLType<ItemType> ::DeleteItem(ItemType item)
{
	bool shorter;
	Delete(root, item, shorter);

}



template <class ItemType>
void AVLType<ItemType> ::Delete(TreeNode<ItemType>*& tree, ItemType item, bool & shorter)
{
	if (tree != NULL)
	{
		if (item < tree->info)
		{
			Delete(tree->left, item, shorter);
			// Look in left subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: tree->bf = EH; break;
				case EH: tree->bf = RH; shorter = false;
					break;
				case RH: DelRightBalance(tree, shorter);
				} // END SWITCH	
		}
		else if (item > tree->info)
		{
			Delete(tree->right, item, shorter);
			// Look in right subtree.
			if (shorter)
				switch (tree->bf)
				{
				case LH: DelLeftBalance(tree, shorter);
				break;				case EH: tree->bf = LH; shorter = false; 							
				case RH: tree->bf = EH; break;
				} // END SWITCH
		}
		else
			DeleteNode(tree, shorter);

	}
	else
	{
		cout << "\nNOTE: " << item
			<< " not in the tree so cannot be deleted.";
	}
}






template <class ItemType>
void AVLType<ItemType> ::DeleteNode(TreeNode <ItemType> * & tree, bool & shorter)
{
	ItemType data;	TreeNode <ItemType> * tempPtr;
	tempPtr = tree;
	if (tree->left == NULL)
	{
		tree = tree->right;
		delete tempPtr;
		shorter = true;
	}
	else if (tree->right == NULL)
	{
		tree = tree->left;
		delete tempPtr;
		shorter = true;
	}
	else
	{
		GetPredecessor(tree, data);
		tree->info = data;
		Delete(tree->left, data, shorter);
		// Delete the predecessor node
		if (shorter)
		{
			switch (tree->bf)
			{
			case LH: tree->bf = EH; break;
			case EH: tree->bf = RH; shorter = false;
				break;
			case RH: DelRightBalance(tree, shorter);
			}
		}
	}
}

template <class ItemType>
void GetPredecessor(TreeNode<ItemType> * tree, ItemType & data)
// Sets data to the info member of the right-most node in tree.
{
	tree = tree->left;
	while (tree->right != NULL)
	{
		tree = tree->right;
	}
	data = tree->info;
}

template <class ItemType>
void DelRightBalance(TreeNode<ItemType> *& tree, bool & shorter)
{
	TreeNode<ItemType> * rs = tree->right;
	TreeNode<ItemType> * ls;
	switch (rs->bf)
	{
	case RH:	tree->bf = rs->bf = EH;
		RotateLeft(tree);
		shorter = true; break;
	case EH:	tree->bf = RH;
		rs->bf = LH;
		RotateLeft(tree);
		shorter = false; break;
	case LH:	ls = rs->left;
		switch (ls->bf)
		{
		case RH:	tree->bf = LH;
			rs->bf = EH; break;
		case EH:	tree->bf = rs->bf = EH;
			break;
		case LH:	tree->bf = EH;
			rs->bf = RH; break;
		} // END SWITCH

		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		shorter = true;
	}
}




template <class ItemType>
void DelLeftBalance(TreeNode<ItemType> *& tree, bool & shorter)
{
	TreeNode<ItemType> * ls = tree->left;
	TreeNode<ItemType> * rs;
	switch (ls->bf)
	{
	case LH:	tree->bf = ls->bf = EH;
		RotateRight(tree);
		shorter = true; break;
	case EH:	tree->bf = LH;
		ls->bf = RH;
		RotateRight(tree);
		shorter = false; break;
	case RH:	rs = ls->right;
		switch (rs->bf)
		{
		case LH:	tree->bf = RH;
			ls->bf = EH; break;
		case EH:	tree->bf = ls->bf = EH;
			break;
		case RH:	tree->bf = EH;
			ls->bf = LH; break;
		} // END SWITCH
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		shorter = true;
	}
}



template <class ItemType>
void AVLType<ItemType> ::RightBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * rs = tree->right;
	TreeNode<ItemType> * ls;

	switch (rs->bf)
	{
	case RH:	tree->bf = rs->bf = EH;
		RotateLeft(tree);
		taller = false;
		break;
	case EH:	cerr << "Tree already balanced " << endl;
		break;
	case LH:	ls = rs->left;
		switch (ls->bf)
		{
		case RH:	tree->bf = LH;
			rs->bf = EH;		break;
		case EH:	tree->bf = rs->bf = EH;	break;
		case LH:	tree->bf = EH;
			rs->bf = RH;		break;
		}
		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}
}




template <class ItemType>
void AVLType<ItemType> ::LeftBalance(TreeNode<ItemType> *& tree, bool & taller)
{
	TreeNode<ItemType> * ls = tree->left;
	TreeNode<ItemType> * rs;

	switch (ls->bf)
	{
	case LH:	tree->bf = ls->bf = EH;
		RotateRight(tree);
		taller = false;
		break;
	case EH:	cerr << "Tree already balanced " << endl;
		break;
	case RH:	rs = ls->right;
		switch (rs->bf)
		{
		case LH:	tree->bf = RH;
			ls->bf = EH;		break;
		case EH:	tree->bf = ls->bf = EH;	break;
		case RH:	tree->bf = EH;
			ls->bf = LH;		break;
		}
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}



template <class ItemType>
void RotateLeft(TreeNode<ItemType> * & tree)
{
	TreeNode<ItemType> * rs;

	if (tree == NULL)
		cerr << "Cannot rotate an empty tree in RotateLeft" << endl;
	else if (tree->right == NULL)
		cerr << "Cannot make an empty subtree the root in RotateLeft" << endl;
	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}



template <class ItemType>
void RotateRight(TreeNode<ItemType> * & tree)
{
	TreeNode<ItemType> * ls;

	if (tree == NULL)
		cerr << "Cannot rotate an empty tree in RotateRight" << endl;
	else if (tree->left == NULL)
		cerr << "Cannot make an empty subtree the root in RotateRight" << endl;
	else
	{
		ls = tree->left;
		tree->left = ls->right;
		ls->right = tree;
		tree = ls;
	}
}

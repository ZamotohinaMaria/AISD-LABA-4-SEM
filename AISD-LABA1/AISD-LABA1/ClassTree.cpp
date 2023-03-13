#include <iostream>
#include "ClassTree.h"
#include <stdio.h>

using namespace std;

ClassTree::ClassTree(int data)
{
	root = new Tree(data, NULL, NULL);
}

ClassTree::ClassTree(const ClassTree& t)
{
	root = t.root;
}

ClassTree::~ClassTree()
{
	delete root;
}

void ClassTree:: print(Tree* root = NULL, int level = 3)
{
	if (root)
	{
		if (root)
		{
			print(root->right, level + 1);
			for (int i = 0; i < level; i++) cout << "   ";
			cout << root->data << endl;
			print(root->left, level + 1);
		}
	}
}

bool ClassTree::insert(int key)
{
	while (root)
	{
		if (key < root->data)
		{
			if (root->left == NULL)
			{
				root->left = new Tree(key, NULL, NULL);
				return true;
			}
			else
				root = root->left;
		}
		if (key > root->data)
		{
			if (root->right == NULL)
			{
				root->right = new Tree(key, NULL, NULL);
				return true;
			}
			else
				root = root->right;
		}
		if (key == root->data)
		{
			cout << "The value is exist";
			return false;
		}
	}
}

bool ClassTree::contains(int key)
{
	while (root)
	{
		if (root->data == key) return true;
		if (root->data < key) root = root->right;
		if (root->data > key) root = root->left;
	}
	return false;
}

Tree* ClassTree::Poisk(int key, Tree* root = NULL)
{
	while (root)
	{
		if (root->data == key) return root;
		if (root->data < key) root = root->right;
		if (root->data > key) root = root->left;
	}
	return NULL;
}

Tree* ClassTree::PrevPoisk(int key, Tree* root = NULL)
{
	while (root)
	{
		if (root->left != NULL && (root->left)->data == key) return root;
		if (root->right != NULL && (root->right)->data == key) return root;
		if (root->data < key) root = root->right;
		else if (root->data > key) root = root->left;
	}
	return NULL;
}

bool ClassTree::erase(int key, Tree* root = NULL)
{
	Tree* tmp = Poisk(key, root);

	if (tmp == NULL) return false;

	if (tmp->left != NULL && tmp->right != NULL)
	{
		Tree* tmp_max = tmp->left;
		int max_val = tmp_max->data;
		while (tmp_max)
		{
			if (tmp_max->data > max_val) max_val = tmp_max->data;
			if (tmp_max->right == NULL) tmp_max = tmp_max->left;
			else tmp_max = tmp_max->right;
		}
		tmp_max = Poisk(max_val, tmp);
		erase(max_val, tmp);
		tmp->data = max_val;
		return true;
	}

	if (tmp == root)
	{
		if (tmp->left == NULL && tmp->right == NULL)
		{
			delete tmp;
			tmp = NULL;
		}
		//------------------------------------------------------------
		if (tmp->left != NULL && tmp->right == NULL)
		{
			Tree* tmp_del = tmp;
			tmp = tmp->left;
			delete tmp_del;
			tmp_del = NULL;
		}
		if (tmp->left == NULL && tmp->right != NULL)
		{
			Tree* tmp_del = tmp;
			tmp = tmp->right;
			delete tmp_del;
			tmp_del = NULL;
		}
	}

	Tree* prev_tmp = PrevPoisk(key, root);
	cout << "Prev data:" << prev_tmp->data;

	if (tmp->left == NULL && tmp->right == NULL)
	{
		if ((prev_tmp->left)->data == key)
		{
			prev_tmp->left = NULL;
			delete tmp;
		}
		if ((prev_tmp->right)->data == key)
		{
			prev_tmp->right = NULL;
			delete tmp;
		}
		tmp = NULL;
		return true;
	}
	//------------------------------------------------------------
	if (tmp->left != NULL && tmp->right == NULL)
	{
		if (prev_tmp->data > key) prev_tmp->left = tmp->left;
		if (prev_tmp->data < key) prev_tmp->right = tmp->left;
		delete tmp;
		tmp = NULL;
		return true;
	}
	if (tmp->right != NULL && tmp->left == NULL)
	{
		if (prev_tmp->data > key) prev_tmp->left = tmp->right;
		if (prev_tmp->data < key) prev_tmp->right = tmp->right;
		delete tmp;
		tmp = NULL;
		return true;
	}
}
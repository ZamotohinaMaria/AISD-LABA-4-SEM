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
	root = new Tree(-999999, NULL, NULL);
	//root = t.root;
	CopyTree(t.root, root);
}

ClassTree::~ClassTree()
{
	Delete(root);
}

void ClassTree:: Delete(Tree* t)
{
	if (t->left != NULL)   Delete(t->left);
	if (t->right != NULL)  Delete(t->right);
	delete t;
	t = NULL;
}

ClassTree ClassTree:: operator=(const ClassTree& t)
{
	root = new Tree(-999999, NULL, NULL);
	this->root = CopyTree(t.root, root);
	return *this;
}

Tree* ClassTree:: CopyTree(Tree* copy, Tree* t) const
{
	if (copy == NULL)
		t = NULL;
	if (copy != NULL)
	{
		t = new Tree(copy->data, NULL, NULL);
		if (copy->left != NULL)
		{
			t->left = CopyTree(copy->left, t->left);
		}
		else
			t->left = NULL;

		if (copy->right != NULL)
		{
			t-> right = CopyTree(copy->right, t->right);
		}
		else
			t->right = NULL;
	}
	return t;
}

Tree* ClassTree::GetRoot() const { return this->root; }

void ClassTree:: print(Tree* root = NULL, int level = 3) const
{
	if (root)
	{
		if (root)
		{
			print(root->right, level + 1);
			for (int i = 0; i < level; i++) cout << "      ";
			cout << root->data << endl;
			print(root->left, level + 1);
		}
	}
}

bool ClassTree::insert(int key)
{
	Tree* tmp = root;
	while (tmp)
	{
		if (key < tmp->data)
		{
			if (tmp->left == NULL)
			{
				tmp->left = new Tree(key, NULL, NULL);
				return true;
			}
			else
				tmp = tmp->left;
		}
		if (key > tmp->data)
		{
			if (tmp->right == NULL)
			{
				tmp->right = new Tree(key, NULL, NULL);
				return true;
			}
			else
				tmp = tmp->right;
		}
		if (key == tmp->data)
		{
			cout << "The value is exist";
			return false;
		}
	}
}

bool ClassTree::contains(int key) const
{
	Tree* tmp = root;
	while (tmp)
	{
		if (tmp->data == key) return true;
		else if (tmp->data < key) tmp = tmp->right;
		else if (tmp->data > key) tmp = tmp->left;
		else return false;
	}
	return false;
}

Tree* ClassTree::Poisk(int key, Tree* root = NULL) const
{
	while (root)
	{
		if (root->data == key) return root;
		else if (root->data < key) root = root->right;
		else if (root->data > key) root = root->left;
	}
	return NULL;
}

Tree* ClassTree::PrevPoisk(int key, Tree* root = NULL) const
{
	while (root)
	{
		if (root->left != NULL && (root->left)->data == key) return root;
		else if (root->right != NULL && (root->right)->data == key) return root;
		else if (root->data < key) root = root->right;
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
			this->root = tmp->left;
			delete tmp_del;
			tmp_del = NULL;
		}
		if (tmp->left == NULL && tmp->right != NULL)
		{
			Tree* tmp_del = tmp;
			this->root = tmp->right;
			delete tmp_del;
			tmp_del = NULL;
		}
		return true;
	}

	Tree* prev_tmp = PrevPoisk(key, root);
	//cout << "Prev data:" << prev_tmp->data << endl;

	if (tmp->left == NULL && tmp->right == NULL)
	{
		if (prev_tmp->left != NULL && (prev_tmp->left)->data == key)
		{
			prev_tmp->left = NULL;
			delete tmp;
		}
		if (prev_tmp->right != NULL && (prev_tmp->right)->data == key)
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
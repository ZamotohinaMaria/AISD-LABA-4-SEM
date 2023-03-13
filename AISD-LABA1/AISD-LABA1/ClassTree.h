#pragma once

struct Tree
{
	int data;
	Tree* left;
	Tree* right;

	Tree(int data, Tree* left, Tree* right)
	{
		this->data = data;
		this->left = left;
		this->right = right;
	}
};

class ClassTree
{
private:
	Tree* root;
public:
	ClassTree(int data);
	ClassTree(const ClassTree& tree);
	~ClassTree();
	void print(Tree* root, int level);
	bool insert(int key);
	bool contains(int key);
	Tree* Poisk(int key, Tree* root);
	Tree* PrevPoisk(int key, Tree* root);
	bool erase(int key, Tree* root);
};
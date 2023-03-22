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
	ClassTree(int data = -999999);
	ClassTree(const ClassTree& tree);
	~ClassTree();
	ClassTree operator = (const ClassTree& t);
	Tree* CopyTree(Tree* copy, Tree* t) const;
	Tree* GetRoot() const;
	void print(Tree* root, int level) const;
	bool insert(int key);
	bool contains(int key) const;
	Tree* Poisk(int key, Tree* root) const;
	Tree* PrevPoisk(int key, Tree* root) const;
	bool erase(int key, Tree* root);
};
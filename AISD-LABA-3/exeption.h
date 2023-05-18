#pragma once

#include <stdio.h>

using namespace std;

class Exeption
{
public:
	virtual void print_exeption() const = 0;
};

class EZeroVertexesSize : public Exeption
{
public:
	EZeroVertexesSize();
	void print_exeption() const;
};

class EElementNotExist : public Exeption
{
public:
	int id;
	EElementNotExist(int id) : id(id) {};
	void print_exeption() const;
};
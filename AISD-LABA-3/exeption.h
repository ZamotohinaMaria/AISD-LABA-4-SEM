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
	void print_exeption() const;
};

class EElementNotExist : public Exeption
{
public:
	int id;
	EElementNotExist(int id);
	void print_exeption() const;
};
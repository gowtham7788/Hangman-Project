#pragma once
#include<string>
#include<iostream>
#include "Property.h"

using namespace std;

class Coder
{
private:
	int Key;
public:
	Coder();
	~Coder();
	void set_key(int Key);
	int get_key();
	string encoder(string Word);
	string decoder(string Word);
};


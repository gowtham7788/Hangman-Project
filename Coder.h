#pragma once
#include<string>
#include<iostream>
#include "Property.h"

using namespace std;

class Coder
{
public:
	Coder();
	~Coder();
	string encoder(string Word);
	string decoder(string Word);
};


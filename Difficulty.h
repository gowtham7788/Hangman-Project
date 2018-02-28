#pragma once

#include <iostream>

using namespace std;

class Difficulty
{
private:
	int Id;
	string Name;
	int IsActive;

public:
	void set_id(int Id);
	int get_id();
	void set_is_active(int IsActive);
	int get_is_active();
	void set_name(string Name);
	string get_name();
};


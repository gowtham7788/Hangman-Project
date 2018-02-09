#pragma once
#include <string>

using namespace std;

class Category
{
private:
	int Id;
	string Name;
	int IsActive;

public:
	Category();
	~Category();
	void set_id(int Id);
	int get_id();
	void set_is_active(int IsActive);
	int get_is_active();
	void set_name(string Name);
	string get_name();
};


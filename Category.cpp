#include "Category.h"

/*This file contains the geter and setter methods for the class Category*/

void Category::set_id(int Id)
{
	this->Id = Id;
}
int Category::get_id()
{
	return this->Id;
}

void Category::set_is_active(int IsActive)
{
	this->IsActive = IsActive;
}
int Category::get_is_active()
{
	return this->IsActive;
}

void Category::set_name(string Name)
{
	this->Name = Name;
}
string Category::get_name()
{
	return this->Name;
}
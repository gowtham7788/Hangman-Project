#include "Difficulty.h"

/*This file contains the geter and setter methods for the class Difficulty*/

void Difficulty::set_id(int Id)
{
	this->Id = Id;
}
int Difficulty::get_id()
{
	return this->Id;
}

void Difficulty::set_is_active(int IsActive)
{
	this->IsActive = IsActive;
}
int Difficulty::get_is_active()
{
	return this->IsActive;
}

void Difficulty::set_name(string Name)
{
	this->Name = Name;
}
string Difficulty::get_name()
{
	return this->Name;
}
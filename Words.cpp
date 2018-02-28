#include "Words.h"

/*This file contains the geter and setter methods for the class Words*/

void Words::set_id(int Id)
{
	this->Id = Id;
}
int Words::get_id()
{
	return this->Id;
}

void Words::set_category_id(Category CategoryId)
{
	this->CategoryId = CategoryId;
}
Category Words::get_category_id()
{
	return this->CategoryId;
}

void Words::set_difficulty_id(Difficulty DifficultyId)
{
	this->DifficultyId = DifficultyId;
}
Difficulty Words::get_difficulty_id()
{
	return this->DifficultyId;
}

void Words::set_word(string Word)
{
	this->Word = Word;
}
string Words::get_word()
{
	return this->Word;
}

void Words::set_is_active(int IsActive)
{
	this->IsActive = IsActive;
}
int Words::get_is_active()
{
	return this->IsActive;
}
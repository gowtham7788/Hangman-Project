#pragma once

#include "Category.h"
#include "Difficulty.h"

class Words
{
private:
	int Id;
	Category CategoryId;
	Difficulty DifficultyId;
	string Word;
	int IsActive;

public:
	void set_id(int Id);
	int get_id();
	void set_category_id(Category CategoryId);
	Category get_category_id();
	void set_difficulty_id(Difficulty DifficultyId);
	Difficulty get_difficulty_id();
	void set_word(string Word);
	string get_word();
	void set_is_active(int IsActive);
	int get_is_active();
	
};


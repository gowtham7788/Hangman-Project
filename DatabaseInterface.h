#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "GameDetails.h"

using namespace std;

class DatabaseInterface
{
public:
	virtual void load_data() = 0;
	virtual vector<Category>  get_category() = 0;
	virtual vector<Difficulty> get_difficulty() = 0;
	virtual string get_word(char* CategoryName,char* DifficultyName) = 0;
	virtual string insert_into_game_details(int GameId, char* Username, int SocketAddress, char* Word) = 0;
	virtual vector<GameDetails> get_playing_game_detail() = 0;
	virtual vector<GameDetails> get_playing_game_detail(int GameId) = 0;
	virtual string update_game_result(int GameId,char* Result) = 0;
	virtual int get_maximum_game_id() = 0;
};

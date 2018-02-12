#pragma once
#include "DatabaseInterface.h"
#include "DatabaseConnection.h"
#include "Coder.h"
#include "Category.h"
#include "Difficulty.h"
#include "Words.h"
#include "GameDetails.h"
#include "XmlParser.h"
#include "Property.h"

class DatabaseImplementation :
	public DatabaseInterface
{
private:
	SQLHANDLE SqlConnHandle;
	DatabaseConnection Connection;
	Coder Cryption;
	string insert_into_category(char* Name, int IsActive);
	string insert_into_difficulty(char* Name, int IsActive);
	string insert_into_words(int CategoryId, int DifficultyId, char* Word, int IsActive);
public:
	DatabaseImplementation();
	~DatabaseImplementation();
protected:
	void load_data();
	vector<Category>  get_category();
	vector<Difficulty> get_difficulty();
	string get_word(char* CategoryName, char* DifficultyName);
	string insert_into_game_details(int GameId, char* Username, int SocketAddress, char* Word);
	vector<GameDetails> get_playing_game_detail();
	vector<GameDetails> get_playing_game_detail(int GameId);
	string update_game_result(int GameId, char* Result);
	int get_maximum_game_id();
};


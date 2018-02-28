#pragma once
#include "DatabaseInterface.h"
#include "DatabaseConnection.h"
#include "Coder.h"
#include "Category.h"
#include "Difficulty.h"
#include "Words.h"
#include "GameDetails.h"
#include "DatabaseXmlParser.h"
#include "Property.h"

class DatabaseImplementation :
	public DatabaseInterface
{
private:
	SQLHANDLE SqlConnHandle;
	DatabaseConnection Connection;
	Coder Cryption;
	SQLRETURN procedure_call(SQLWCHAR* Query);
	vector<GameDetails> get_game_details(SQLHANDLE SqlHandle);
	SQLHANDLE select(SQLHANDLE SqlHandle, SQLWCHAR* Query);
	void insert_into_category(vector<Category>);
	void insert_into_difficulty(vector<Difficulty>);
	void insert_into_words(vector<Words>);
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
	string update_game_result(int GameId, int SocketAddress, char* Result);
	int get_maximum_game_id();
	vector<int> get_socket_address_by_game_id(int GameId);
	vector<GameDetails> get_updated_result(int GameId);
	vector<GameDetails> get_updated_result(int GameId, int SocketAddress);
};


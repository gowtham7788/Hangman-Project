#pragma once
#include <string>
#include <vector>
#include "DatabaseInterface.h"
#include "DatabaseImplementation.h"
#include "Property.h"
#include "GameDetails.h"
using namespace std;
#define MaximumGuess 6
class GameLogic
{
private:
	
	DatabaseInterface* DbInterface = new DatabaseImplementation();
	char WrongGuess[MaximumGuess];
	int RemainingGuess = MaximumGuess;
	string Result;
	int DashCount = 0;

public:
	GameLogic();
	~GameLogic();
	int get_remaining_guess();
	char* get_wrong_guess();
	string get_result();
	int calculate_number_of_dash(char*);
	char* input_character(char*, char[],char);
	char* fill_dash(char*,char*);
	string calculate_result(GameLogic,char*,char*,int );
	vector<GameDetails> get_particular_gameid_details(int GameId);
	vector<GameDetails> get_all_game_details();
	string get_word_from_database(char* CategoryName, char* DifficultyName);
	string insert_into_database(int GameId, char* Username, int SocketAddress, char* Word);
	string insert_into_database(int GameId, char* UserName, int SocketAddress);
	int generate_gameid();
	string get_all_playing_game();
	vector<Category>  get_category_list();
	vector<Difficulty> get_difficulty_list();
	string category_list_and_difficulty_level();
};


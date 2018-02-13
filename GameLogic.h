#pragma once
#include "DatabaseImplementation.h"
using namespace std;

class GameLogic
{
private:
	DatabaseInterface* DbInterface = new DatabaseImplementation();
	char WrongGuess[MAXIMUMGUESS] ;
	int RemainingGuess = MAXIMUMGUESS;
	string Result;
	int DashCount = 0;
	int get_remaining_guess();
	string get_wrong_guess();
public:
	GameLogic();
	~GameLogic();
	int generate_gameid();
	int calculate_number_of_dash(string Word);
	string input_character(string Word, string Dash, char Letter);
	string fill_dash(string Word);
	string calculate_result(GameLogic, string Dash, string FillDash, int GameId, char Letter);

	string get_word_from_database(string CategoryName, string DifficultyName);
	string insert_into_database(int GameId, string Username, int SocketAddress, string Word);
	string insert_into_database(int GameId, string UserName, int SocketAddress);
	string get_all_playing_game();
	string category_list_and_difficulty_level();
	vector<GameDetails> get_particular_gameid_details(int GameId);
	vector<GameDetails> get_all_game_details();
	vector<int> get_socket_address_by_gameid_from_database(int GameId);
	
};


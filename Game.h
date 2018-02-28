#pragma once
#include "DatabaseImplementation.h"
using namespace std;

class Game
{
private:
	DatabaseInterface* DbInterface = new DatabaseImplementation();
	char WrongGuess[MAXIMUMGUESS];
	int RemainingGuess = MAXIMUMGUESS;
	int DashCount = 0;
public:
	int generate_gameid();
	int get_remaining_guess();
	string get_wrong_guess();
	int calculate_number_of_dash(string Word);
	string input_character(string Word, string Dash, char Letter);
	string fill_dash(string Word);
	string calculate_result(Game, string Dash, string FillDash, int GameId, char Letter);

	string fetch_word_from_database(string CategoryName, string DifficultyName);
	string insert_into_database(int GameId, string Username, int SocketAddress, string Word);
	string insert_into_database(int GameId, string UserName, int SocketAddress);
	string fetch_all_playing_game();
	string fetch_category_list_and_difficulty_level();
	vector<GameDetails> fetch_particular_gameid_details(int GameId);
	string update_game_details(int GameId, int SocketAddress, string Result);
	string update_game_details(int GameId, string Result);
	vector<GameDetails> check_game_detail();
};


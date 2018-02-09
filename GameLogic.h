#pragma once
#include <string>
using namespace std;
#define MaximumGuess 6
class GameLogic
{
private:
	
	
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
};


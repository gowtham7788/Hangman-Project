#include "GameLogic.h"


GameLogic::GameLogic()
{
}


GameLogic::~GameLogic()
{
}
int GameLogic::get_remaining_guess()
{
	return RemainingGuess;
}
char* GameLogic::get_wrong_guess()
{
	return WrongGuess;
}
string GameLogic::get_result()
{
	return Result;
}
char* GameLogic::fill_dash(char* Word, char* Dash)
{
	size_t Index = 0;
	for (Index = 0; Index < strlen(Word); Index++)
	{
		if (!isspace(Word[Index]))
		{
			Dash[Index] = '_';
		}
		else
		{
			Dash[Index] = ' ';
		}
	}
	return Dash;
}

char* GameLogic::input_character(char* Word, char* Dash, char Letter)
{
	size_t CharIndex;
	for (CharIndex = 0; CharIndex < strlen(Word); CharIndex++)
	{
		if (Word[CharIndex] == tolower(Letter) || Word[CharIndex] == toupper(Letter))
		{
			Dash[CharIndex] = Word[CharIndex];
		}
	}
	return Dash;
}
int GameLogic::calculate_number_of_dash(char* Word)
{
	size_t Index;
	int Count = 0;
	for (Index = 0; Index < strlen(Word); Index++)
	{
		if (Word[Index] == '_')
		{
			Count++;
		}
	}
	return Count;
}

string GameLogic::calculate_result(GameLogic logic,char* Dash,char* FillDash,int GameId)
{
	if (strcmp(Dash, FillDash) == 0)
	{
		WrongGuess[MaximumGuess-RemainingGuess]=
		RemainingGuess--;
	}
	else
	{
		strcpy_s(Dash, sizeof(FillDash), FillDash);
	}
	DashCount = logic.calculate_number_of_dash(Dash);
	if (DashCount == 0)
	{
		Result = "win";
	}
	else if (RemainingGuess == 0)
	{
		Result = "loss";
	}
	else
	{
		Result = "playing";
	}
	string GameInfo = "<hangman></gameinfo><gameid> " + to_string(GameId) + "</gameid><word>" + Dash + "</word><remainingguess>" + to_string(logic.get_remaining_guess()) + "</remainingguess><wrongguess>" + logic.get_wrong_guess() + "</wrongguess><result>" + logic.get_result() + "</result></gameinfo></hangman>";
	return GameInfo;
}
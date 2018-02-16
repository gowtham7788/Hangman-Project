
#include <iostream>
#include "rapidxml.hpp"
#include "GameLogic.h"
#define MaximumGuess 7
using namespace std;
using namespace rapidxml;
char WrongGuess[MaximumGuess];
int RemainingGuess = 7;

string fill_dash(string Word);
string input_character(string Word, string Dash, char Letter);
string calculate_result(string Dash, string FillDash, int GameId, char Letter);
int calculate_number_of_dash(string Word);
char get_letter(char Buffer[]);
int create_or_join(string Buffer);

void main()
{
	string Word = "computer";
	char Letter = 't';
	int DashCount = 0;
	string Dash = fill_dash(Word);

	string FillDash;
	FillDash = Dash;
	if (Dash.size() == 8)
	{
		cout << "Fill Dash Success"<<endl;
	}
	else
	{
		cout << "Fill Dash Failed" << endl;
	}
	DashCount = calculate_number_of_dash(Dash);
	if (DashCount == 8)
	{
		cout << "DashCount Success" << endl;
	}
	else
	{
		cout << "DashCount Failed" << endl;
	}

	FillDash = input_character(Word, Dash, Letter);
	if (FillDash == "_____t__")
	{
		cout << "input character successful" << endl;
	}
	else
	{
		cout << "input character failed" << endl;
	}
	DashCount = calculate_number_of_dash(FillDash);
	if (DashCount == 7)
	{
		cout << "DashCount Success" << endl;
	}
	else
	{
		cout << "DashCount Failed" << endl;
	}
	string game = calculate_result(Dash, FillDash, 1, Letter);
	//cout << game << endl;
	if (!game.empty())
	{
		cout << "calculate_result successfull" << endl;
	}
	else
	{
		cout << "calculate_result failed" << endl;
	}
	char Buffer[] = "<Hangman><Letter>r</Letter></Hangman>";
	char l = get_letter(Buffer);
	if (l == 'r')
	{
		cout << "get_letter successsful" << endl;
	}
	else
	{
		cout << "get_letter failed" << endl;
	}
	cin.get();
	cin.ignore(1000, '\n');
}

　
string fill_dash(string Word )
{
	size_t Index = 0;
	string Dash;
	for (Index = 0; Index < Word.size(); Index++)
	{
		if (!isspace(Word[Index]))
		{
			Dash.append("_");
		}
		else
		{
			Dash.append(" ");
		}
	}
	return Dash;
}
string input_character(string Word, string Dash, char Letter)
{
	size_t CharIndex;
	for (CharIndex = 0; CharIndex < Word.size(); CharIndex++)
	{
		if (Word[CharIndex] == tolower(Letter) || Word[CharIndex] == toupper(Letter))
		{
			Dash[CharIndex] = Word[CharIndex];
		}
	}
	return Dash;
}

string calculate_result(string Dash, string FillDash, int GameId, char Letter)
{
	
	int DashCount;
	string Result;
	
	if (Dash.compare(FillDash) == 0)
	{
		WrongGuess[MaximumGuess - RemainingGuess] = Letter;
		RemainingGuess--;
	}
	else
	{
		Dash = FillDash;
	}
	DashCount = calculate_number_of_dash(Dash);
	if (DashCount == 0)
	{
		Result = "WIN";
		/*string status = DbInterface->update_game_result(GameId, (char*)Result.c_str());*/
	}
	else if (RemainingGuess == 0)
	{
		Result = "LOSE";
		/*string status = DbInterface->update_game_result(GameId, (char*)Result.c_str());*/
	}
	else
	{
		Result = "PLAYING";
	}

	string GameInfo = "<"HANGMAN"></"GAMEINFO"><"GAMEID"> " + to_string(GameId) + "</"GAMEID"><"WORDS">" + Dash + "</"WORDS"><"REMAININGGUESS">" + to_string(RemainingGuess) + "</"REMAININGGUESS"><"WRONGGUESS">" + WrongGuess + "</"WRONGGUESS"><result>" + Result + "</"RESULT">";
	return GameInfo;
}

int calculate_number_of_dash(string Word)
{
	size_t Index;
	int Count = 0;
	for (Index = 0; Index < Word.size(); Index++)
	{
		if (Word[Index] == '_')
		{
			Count++;
		}
	}
	return Count;
}

char get_letter(char Buffer[])
{
	xml_document<> document;
	char Letter;
	string XmlLetter;
	document.parse<0>(&Buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName == LETTER)
	{
		XmlLetter = FirstNode->value();
		Letter = XmlLetter[0];
	}
	return Letter;
}


#include <iostream>
#include "rapidxml.hpp"
#include "GameLogic.h"
#include "SocketXmlParser.h"
#define MaximumGuess 7
using namespace std;
using namespace rapidxml;
char WrongGuess[MaximumGuess];
int RemainingGuess = 7;


void fill_dash();
void calculate_number_of_dash();
void input_character();
void calculate_result();
void get_letter();
void create_or_join();
GameLogic Logic;
void main()
{
	fill_dash();
	calculate_number_of_dash();
	input_character();
	get_letter();
	calculate_result();
	create_or_join();
	cin.get();
	cin.ignore(1000, '\n');
}


void fill_dash()
{
	string Word = "computer";
	string Dash = Logic.fill_dash(Word);
	if (Dash.size() == 8)
	{
		cout << "Fill Dash Successful" << endl;
	}
	else
	{
		cout << "Fill Dash Failed" << endl;
	}
}
void calculate_number_of_dash()
{
	string Word = "********";
	int DashCount = Logic.calculate_number_of_dash(Word);
	if (DashCount == 8)
	{
		cout << "DashCount Successful" << endl;
	}
	else
	{
		cout << "DashCount Failed" << endl;
	}

}
void input_character()
{
	char Letter = 't';
	string Word = "computer";
	string Dash = "********";
	string FillDash = Logic.input_character(Word, Dash, Letter);
	if (FillDash == "*****t**")
	{
		cout << "input character successful" << endl;
	}
	else
	{
		cout << "input character failed" << endl;
	}
}
void get_letter()
{
	SocketXmlParser Xml;
	char Buffer[] = "<Hangman><Letter>r</Letter></Hangman>";
	char Letter = Xml.get_letter(Buffer);
	if (Letter == 'r')
	{
		cout << "get_letter successsful" << endl;
	}
	else
	{
		cout << "get_letter failed" << endl;
	}
}
void calculate_result()
{
	string Dash = "********";
	string FillDash = "*******r";
	int GameId = 7; 
	char Letter = 't';
	string game = Logic.calculate_result(Logic, Dash, FillDash, GameId, Letter);
	if (!game.empty())
	{
		cout << "calculate_result successfull" << endl;
	}
	else
	{
		cout << "calculate_result failed" << endl;
	}
}
void create_or_join()
{
	char Buffer[1024] = "<Hangman><Join></Join></Hangman>";
	SocketXmlParser Xml;
	if (Xml.create_or_join(Buffer))
	{
		cout << "Received Create Request" << endl;
	}
	else
	{
		cout << "Received JOin Request" << endl;
	}
}
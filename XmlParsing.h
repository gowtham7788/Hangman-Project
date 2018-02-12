#pragma once
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "GameLogic.h"
#include "Property.h"

#include <WinSock2.h>
using namespace std;
using namespace rapidxml;
class XmlParsing
{
private:
	GameLogic logic;

public:
	XmlParsing();
	~XmlParsing();
	char* parse_letter(char buffer[], int GameId, char* Word,char* Dash);
	//char* parse_game_type(char bufffer[]);
	int create_or_join(char buffer[]);

};


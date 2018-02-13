#pragma once
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "GameLogic.h"
#include "Property.h"


class SocketXmlParser
{
public:
	SocketXmlParser();
	~SocketXmlParser();	
	string parse_letter(char Letter, int GameId, string Word, string Dash);
	char get_letter(string Buffer);
	int create_or_join(string Buffer);
	string get_dash(string Buffer);
	

};


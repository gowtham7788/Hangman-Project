#pragma once
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "GameLogic.h"
#include "Property.h"
class SocketXmlParser
{
public:
	char parse_letter(char Buffer[]);
	int create_or_join(char Buffer[]);
	string parse_dash(string Buffer);
	string creategame_or_joingame(int client,GameLogic,char Buffer[],int GameId);
};


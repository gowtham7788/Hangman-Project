#pragma once
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "Game.h"
#include "Property.h"
class SocketXmlParser
{
public:
	char parse_letter(char Buffer[]);
	bool parse_user_option(char Buffer[]);
	string parse_dash(string Buffer);
	string parse_category_difficulty_and_fetch_word(int client, Game Game, char Buffer[], int GameId);
};


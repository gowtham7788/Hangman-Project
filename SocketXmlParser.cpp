#include "SocketXmlParser.h"
SocketXmlParser::SocketXmlParser()
{
}
SocketXmlParser::~SocketXmlParser()
{
}
string SocketXmlParser::get_dash(string Buffer)
{
	string Dash;
	xml_document<> document;
	document.parse<0>(&Buffer[0]);
	xml_node<> *RootNode = document.first_node(HANGMAN);
	xml_node<> *FirstNode = RootNode->first_node(GAMEINFO);
	xml_node<> *Element = FirstNode->first_node(WORDS);												//parse the given buffer and get the Word		
	return Dash = Element->value();
}
char SocketXmlParser::get_letter(char Buffer[])
{
	xml_document<> document;
	char Letter;
	string XmlLetter;
	document.parse<0>(&Buffer[0]);
	xml_node<> *RootNode = document.first_node(HANGMAN);
	xml_node<> *FirstNode = RootNode->first_node(LETTER);
	string TagName = FirstNode->name();
	if (TagName == LETTER)
	{
		XmlLetter = FirstNode->value();																	//parse the given buffer and get the letter which is given by client
		Letter = XmlLetter[0];
	}
	return Letter;
}
int SocketXmlParser::create_or_join(char buffer[])												//parse the buffer and identify whether the client send create or join game
{
	xml_document<> document;
	document.parse<0>(&buffer[0]);
	xml_node<> *RootNode = document.first_node(HANGMAN);
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName == CREATE)
	{
		return 1;																				//return 1 if client send create game
	}
	return 0;																					//return 0 if client send join game
}
string SocketXmlParser::creategame_or_joingame(int client, GameLogic GameLogic, char Buffer[],int GameId)
{
	string Word;
	xml_document<> document;
	document.parse<0>(&Buffer[0]);
	xml_node<> *RootNode = document.first_node(HANGMAN);
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName == CREATEGAME)
	{
		xml_node<> *CategoryNode = FirstNode->first_node(CATEGORY);
		string Category = CategoryNode->value();
		xml_node<> *LevelNode = FirstNode->first_node(LEVEL);
		string Level = LevelNode->value();
		xml_node<> *UserNameNode = RootNode->first_node(USERNAME);
		string UserName = UserNameNode->value();
		Word = GameLogic.get_word_from_database(Category, Level);													//send category and difficulty level to DB and get a word
		GameLogic.insert_into_database(GameId, UserName, client, Word);													//send game id , username ,client sockaddr , word to DB
	}
	else if (TagName == JOINGAME)
	{
		xml_node<> *GameIdNode = FirstNode->first_node(GAMEID);
		string GameIdUser = GameIdNode->value();
		GameId = stoi(GameIdUser);
		xml_node<> *UserNameNode = RootNode->first_node(USERNAME);
		string UserName = UserNameNode->value();
		GameLogic.insert_into_database(GameId, UserName, client);
		Word = "";
	}
	return Word;
}
#include "SocketXmlParser.h"


SocketXmlParser::SocketXmlParser()
{
}


SocketXmlParser::~SocketXmlParser()
{
}
string SocketXmlParser::get_dash(string Buffer)
{
	xml_document<> document;
	document.parse<0>(&Buffer[0]);
	xml_node<> *RootNode = document.first_node(HANGMAN);
	xml_node<> *FirstNode = RootNode->first_node(GAMEINFO);
	xml_node<> *Element = FirstNode->first_node(WORDS);
	string Dash = Element->value();
	return Dash;
}
string SocketXmlParser::parse_letter(char Letter, int GameId, string Word, string Dash)
{
	GameLogic logic;
	Dash = logic.input_character(Word, Dash, Letter);
	return Dash;
}

char SocketXmlParser::get_letter(string Buffer)
{
	xml_document<> document;
	char Letter[1];
	document.parse<0>(&Buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName == LETTER)
	{
		string XmlLetter = FirstNode->value();
		strcpy_s(Letter, XmlLetter.c_str());
	}
	return Letter[0];
}

int SocketXmlParser::create_or_join(string buffer)
{
	xml_document<> document;
	document.parse<0>(&buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName == CREATE)
	{
		return 1;
	}
	return 0;

}

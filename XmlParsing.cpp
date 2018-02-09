#include "XmlParsing.h"


XmlParsing::XmlParsing()
{
}


XmlParsing::~XmlParsing()
{
}

char* XmlParsing::parse_letter(char buffer[],  int GameId, char* Word,char* Dash)
{
	xml_document<> document;
	document.parse<0>(&buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	 if (TagName.compare("letter") == 0)
	{
		string XmlLetter = FirstNode->value();
		char Letter[1];
		strcpy_s(Letter, XmlLetter.c_str());
		Dash = logic.input_character(Word, Dash,Letter[0]);
	}
	 return Dash;
}

int XmlParsing::create_or_join(char buffer[])
{
	xml_document<> document;
	document.parse<0>(&buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName.compare("create") == 0)
	{
		return 1;
	}
return 0;
	
}


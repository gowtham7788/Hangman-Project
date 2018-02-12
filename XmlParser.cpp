#include "XmlParser.h"

XmlParser::XmlParser()
{
}


XmlParser::~XmlParser()
{
}

/*Getter and setter method for the varibale xml_node*/
void XmlParser::set_node(xml_node<>* Node)
{
	this->Node = Node;
}

xml_node<>* XmlParser::get_node()
{
	return this->Node;
}

/*This method reads a xml file for the category tag and return a vector of categories object*/
vector<Category> XmlParser::get_category_from_xml(xml_node<>* Node)
{
	Category CategoryObject;
	vector<Category> CategoryVector;
	xml_node<> *Child = Node->first_node(CATEGORIES);	
	xml_node<> *Child1 = Child->first_node(CATEGORY);
	while (Child1 != NULL)
	{
		xml_node<> *Element = Child1->first_node(NAME);
		CategoryObject.set_name(Element->value());
		Element = Child1->first_node(IS_ACTIVE);
		size_t SizeElement;
		int IsActive = stoi(Element->value(), &SizeElement);
		CategoryObject.set_is_active(IsActive);
		CategoryVector.push_back(CategoryObject);
		Child1 = Child1->next_sibling();
	}
	return CategoryVector;
}

/*This method reads a xml file for the difficulty tag and return a vector of difficulty object*/
vector<Difficulty> XmlParser::get_difficulty_from_xml(xml_node<>* Node)
{
	Difficulty DifficultyObject;
	vector<Difficulty> DifficultyVector;
	xml_node<> *Child = Node->first_node(DIFFICULTIES);
	xml_node<> *Child1 = Child->first_node(DIFFICULTY);
	while (Child1 != NULL)
	{
		xml_node<> *Element = Child1->first_node(NAME);
		DifficultyObject.set_name(Element->value());
		Element = Child1->first_node(IS_ACTIVE);
		size_t SizeElement;
		int IsActive = stoi(Element->value(), &SizeElement);
		DifficultyObject.set_is_active(IsActive);
		DifficultyVector.push_back(DifficultyObject);
		Child1 = Child1->next_sibling();
	}
	return DifficultyVector;
}

/*This method reads a xml file for the word tag and return a vector of word object*/
vector<Words> XmlParser::get_words_from_xml(xml_node<>* Node)
{
	Words WordObject;
	Category CategoryObject;
	Difficulty DifficultyObject;
	vector<Words> WordVector;
	size_t SizeElement;
	xml_node<> *Child = Node->first_node(WORDS);
	xml_node<> *Child1 = Child->first_node(WORDNAME);
	while (Child1 != NULL)
	{
		xml_node<> *Element = Child1->first_node(CATEGORY_ID);
		int CategoryId = stoi(Element->value(), &SizeElement);
		CategoryObject.set_id(CategoryId);
		WordObject.set_category_id(CategoryObject);
		Element = Child1->first_node(DIFFICULTY_ID);
		int DifficultyId = stoi(Element->value(), &SizeElement);
		DifficultyObject.set_id(DifficultyId);
		WordObject.set_difficulty_id(DifficultyObject);
		Element = Child1->first_node(NAME);
		WordObject.set_word(Element->value());
		Element = Child1->first_node(IS_ACTIVE);
		int IsActive = stoi(Element->value(), &SizeElement);
		WordObject.set_is_active(IsActive);
		WordVector.push_back(WordObject);
		Child1 = Child1->next_sibling();
	}
	return WordVector;
}


char* XmlParser::parse_letter(char buffer[], int GameId, char* Word, char* Dash)
{
	xml_document<> document;
	document.parse<0>(&buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName == LETTER)
	{
		string XmlLetter = FirstNode->value();
		char Letter[1];
		strcpy_s(Letter, XmlLetter.c_str());
		Dash = logic.input_character(Word, Dash, Letter[0]);
	}
	return Dash;
}

int XmlParser::create_or_join(char buffer[])
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

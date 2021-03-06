#include "DatabaseXmlParser.h"

DatabaseXmlParser::DatabaseXmlParser()
{
}
DatabaseXmlParser::~DatabaseXmlParser()
{

}

/*Getter and setter method for the varibale xml_node*/
void DatabaseXmlParser::set_node(xml_node<>* Node)
{
	this->Node = Node;
}

xml_node<>* DatabaseXmlParser::get_node()
{
	return this->Node;
}

/*This method reads a xml file for the category tag and return a vector of categories object*/
vector<Category> DatabaseXmlParser::get_category_from_xml(xml_node<>* Node)
{
	Category CategoryObject;
	vector<Category> CategoryVector;
	xml_node<> *NodeCategories = Node->first_node(CATEGORIES);	
	xml_node<> *NodeCategory = NodeCategories->first_node(CATEGORY);
	while (NodeCategory != NULL)
	{
		xml_node<> *Element = NodeCategory->first_node(NAME);
		CategoryObject.set_name(Element->value());
		Element = NodeCategory->first_node(IS_ACTIVE);
		size_t SizeElement;
		int IsActive = stoi(Element->value(), &SizeElement);
		CategoryObject.set_is_active(IsActive);
		CategoryVector.push_back(CategoryObject);
		NodeCategory = NodeCategory->next_sibling();
	}
	return CategoryVector;
}

/*This method reads a xml file for the difficulty tag and return a vector of difficulty object*/
vector<Difficulty> DatabaseXmlParser::get_difficulty_from_xml(xml_node<>* Node)
{
	Difficulty DifficultyObject;
	vector<Difficulty> DifficultyVector;
	xml_node<> *NodeDifficulties = Node->first_node(DIFFICULTIES);
	xml_node<> *NodeDifficulty = NodeDifficulties->first_node(DIFFICULTY);
	while (NodeDifficulty != NULL)
	{
		xml_node<> *Element = NodeDifficulty->first_node(NAME);
		DifficultyObject.set_name(Element->value());
		Element = NodeDifficulty->first_node(IS_ACTIVE);
		size_t SizeElement;
		int IsActive = stoi(Element->value(), &SizeElement);
		DifficultyObject.set_is_active(IsActive);
		DifficultyVector.push_back(DifficultyObject);
		NodeDifficulty = NodeDifficulty->next_sibling();
	}
	return DifficultyVector;
}

/*This method reads a xml file for the word tag and return a vector of word object*/
vector<Words> DatabaseXmlParser::get_words_from_xml(xml_node<>* Node)
{
	Words WordObject;
	Category CategoryObject;
	Difficulty DifficultyObject;
	vector<Words> WordVector;
	size_t SizeElement;
	xml_node<> *NodeWords = Node->first_node(WORDS);
	xml_node<> *NodeWord = NodeWords->first_node(WORDNAME);
	while (NodeWord != NULL)
	{
		xml_node<> *Element = NodeWord->first_node(CATEGORY_ID);
		int CategoryId = stoi(Element->value(), &SizeElement);
		CategoryObject.set_id(CategoryId);
		WordObject.set_category_id(CategoryObject);
		Element = NodeWord->first_node(DIFFICULTY_ID);
		int DifficultyId = stoi(Element->value(), &SizeElement);
		DifficultyObject.set_id(DifficultyId);
		WordObject.set_difficulty_id(DifficultyObject);
		Element = NodeWord->first_node(NAME);
		WordObject.set_word(Element->value());
		Element = NodeWord->first_node(IS_ACTIVE);
		int IsActive = stoi(Element->value(), &SizeElement);
		WordObject.set_is_active(IsActive);
		WordVector.push_back(WordObject);
		NodeWord = NodeWord->next_sibling();
	}
	return WordVector;
}

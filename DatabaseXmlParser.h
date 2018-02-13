#pragma once
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "Category.h"
#include "Difficulty.h"
#include "Words.h"
#include "Property.h"
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace rapidxml;

class DatabaseXmlParser
{
private:
	xml_document<> Document;
	xml_node<> *Node;
	
public:
	DatabaseXmlParser();
	~DatabaseXmlParser();
	xml_node<> *create_parser();
	vector<Category> get_category_from_xml(xml_node<> *Node);
	vector<Difficulty> get_difficulty_from_xml(xml_node<> *Node);
	vector<Words> get_words_from_xml(xml_node<> *Node);
	void set_node(xml_node<> *Node);
	xml_node<> *get_node();
};


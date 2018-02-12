#pragma once
#include "rapidxml.hpp"
//#include "rapidxml_print.hpp"
#include <iostream>
#include <thread>
#include <string>
#include "XmlParser.h"
#include "GameLogic.h"
#include "Property.h"

#include <winsock2.h>

#pragma comment(lib,"libws2_32.a")

//using namespace std;
//using namespace rapidxml;
class Server
{
private:
	XmlParser XmlParse;
	
	char* Word;
	int ClientCount = 0;
	int GameId = 0;
	SOCKET server, client;
	thread receive[4];
	SOCKADDR_IN serverAddr, clientAddr;
	
public:
	Server();
	~Server();
	void accept_connection();
	void receive_message(int client,int GameId,char* Word);
	void choose_game_type(int);
};


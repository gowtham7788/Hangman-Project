#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "rapidxml.hpp"
#include <iostream>
#include <thread>
#include <string>
#include "SocketXmlParser.h"
#include "GameLogic.h"
#include "Property.h"
#pragma comment(lib,"libws2_32.a")

class Server
{
private:
	SocketXmlParser XmlParse;
	//string Word;
	//int GameId = 0;
	SOCKET server, client;
	thread receive[10];
	SOCKADDR_IN serverAddr, clientAddr;
	
public:
	Server();
	~Server();
	void accept_connection();
	void receive_message(GameLogic Logic, int client, int GameId, string Word);
	void choose_game_type(int);
};


#pragma once
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include <iostream>
#include <thread>
#include <string>
#include "XmlParsing.h"
#include <winsock2.h>
#include "GameLogic.h"
#pragma comment(lib,"libws2_32.a")

using namespace std;
using namespace rapidxml;
class ServerClass :public DatabaseInterface
{
private:
	char* Word;
	int ClientCount = 0;
	int GameId = 0;
	SOCKET server, client[7];
	thread receive[4];
	WSADATA WSAData;
	SOCKADDR_IN serverAddr, clientAddr;
	XmlParsing xml;
public:
	ServerClass();
	~ServerClass();
	void accept_connection();
	void receive_message(int client,int GameId,char* Word);
	void choose_game_type(int);
};


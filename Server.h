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
	thread receive[50];
	thread GameType[50];
	SOCKADDR_IN serverAddr, clientAddr;
	int flag = 0;
	string get_result(GameLogic Logic, string GameInfo, string Word, int Chance);
	void process_message(GameLogic Logic, int client, int GameId, string Word);
	void choose_game_type(int);
	void send_message(int client, string message);
	string receive_message(int client);
public:
	void accept_connection();
};


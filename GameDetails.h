#pragma once

#include "Words.h"
#include <iostream>
#include <time.h>

using namespace std;

class GameDetails
{
private:
	int Id;
	int GameId;
	string UserName;
	int SocketAddress;
	Words WordId;
	time_t Date;
	string Result;

public:
	GameDetails();
	~GameDetails();
	void set_id(int Id);
	int get_id();
	void set_game_id(int GameId);
	int get_game_id();
	void set_socket_address(int SocketAddress);
	int get_socket_address();
	void set_username(string UserName);
	string get_username();
	void set_word_id(Words Word);
	Words get_word_id();
	void set_result(string Result);
	string get_result();
	void set_date(time_t Date);
	time_t get_date();

};


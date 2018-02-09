#include "GameDetails.h"

/*This file contains the geter and setter methods for the class GameDetails*/
GameDetails::GameDetails()
{
}


GameDetails::~GameDetails()
{
}

void GameDetails::set_id(int Id)
{
	this->Id = Id;
}
int GameDetails::get_id()
{
	return this->Id;
}

void GameDetails::set_game_id(int GameId)
{
	this->GameId = GameId;
}
int GameDetails::get_game_id()
{
	return this->GameId;
}

void GameDetails::set_socket_address(int SocketAddress)
{
	this->SocketAddress = SocketAddress;
}
int GameDetails::get_socket_address()
{
	return this->SocketAddress;
}

void GameDetails::set_username(string UserName)
{
	this->UserName = UserName;
}
string GameDetails::get_username()
{
	return this->UserName;
}

void GameDetails::set_word_id(Words WordId)
{
	this->WordId = WordId;
}
Words GameDetails::get_word_id()
{
	return this->WordId;
}

void GameDetails::set_result(string Result)
{
	this->Result = Result;
}
string GameDetails::get_result()
{
	return this->Result;
}

void GameDetails::set_date(time_t Date)
{
	this->Date = Date;
}
time_t GameDetails::get_date()
{
	return this->Date;
}
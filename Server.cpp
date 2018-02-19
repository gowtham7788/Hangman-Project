#include "Server.h"

void Server::send_message(int Client, string Message)
{
	char Data[1024];
	strcpy_s(Data, Message.c_str());
	send(Client, Data, sizeof(Data), 0);
}


void Server::process_message(GameLogic Logic, int Client, int GameId, string Word)
{
	string Dash;
	char Buffer[1024];
	int ReceivedBytes = 0;
	char Letter =' ' ;
	int Client1;
	Dash = Logic.fill_dash(Word);
	string FillDash = Dash;
	string Result;
	unsigned int iteration=0;
	unsigned int iteration1 = 0;
	vector<GameDetails> GameDetails;
		while ( (GameDetails = Logic.get_particular_gameid_details(GameId)).size()>0)								//change client sockaddr using DB
		{
			iteration = iteration % GameDetails.size();
			Client = GameDetails[iteration].get_socket_address();
			string GameInfo = Logic.calculate_result(Logic, Dash, FillDash, GameId,Letter);
			for (iteration1 = 0; iteration1 < GameDetails.size(); iteration1++)							//send game info to the all UI which is in same game id
			{
				Client1 = GameDetails[iteration1].get_socket_address();
				if (Client == Client1)
				{
					Result = get_result(Logic, GameInfo, Word, 1);
					send_message(Client1, Result);														//send game info  to the client
				}
				else
				{
					Result = get_result(Logic, GameInfo, Word, 0);
					send_message(Client1, Result);														//send game info  to the client
				}
			}
			Dash = XmlParse.parse_dash(Result);
			if ((Logic.get_particular_gameid_details(GameId)).size()>0)
			{
				ReceivedBytes = recv(Client, Buffer, sizeof(Buffer), 0);
				if (ReceivedBytes > 0)
				{
					Letter = XmlParse.parse_letter(Buffer);
					FillDash = Logic.input_character(Word, Dash, Letter);
				}
				else
				{
					Logic.update_game_details(GameId, Client, "EXITED");									//update result as EXITED if the client close
					cout << "connection closed" << endl;
				}
			}
			iteration++;
		}
		ExitThread(0);
}
void Server::choose_game_type(int Client)
{
	char Buffer[1024];
	char Buffer1[1024];
	int GameId;
	int Choice = -1;
	string Word;
	string List;
	GameLogic GameLogic;
	int ReceivedBytes = 0; 
	ReceivedBytes = recv(Client, Buffer, sizeof(Buffer), 0);
	if (ReceivedBytes > 0)
	{
		Choice = XmlParse.create_or_join(Buffer);
	}
	else
	{
		cout << "connection closed" << endl;
	}

	if (Choice == 1)
	{
		List = GameLogic.category_list_and_difficulty_level();														//send category and difficulty to UI
		send_message(Client, List);														//send game info  to the client
	}
	else if (Choice == 0)
	{
		List = GameLogic.get_all_playing_game();																	//get available game id from database
		send_message(Client, List);														//send game info  to the client
		if (GameLogic.check_game_detail().empty())
		{
			flag = 1;
			choose_game_type(Client);
			flag = 0;
		}
	}
	else
	{
		cout << "\nReceived wrong request ";
	}
	if (flag == 0)
	{
		ReceivedBytes = recv(Client, Buffer1, sizeof(Buffer1), 0);
		if (ReceivedBytes > 0)
		{
			GameId = GameLogic.generate_gameid();																		//generate game id
			Word = XmlParse.creategame_or_joingame(Client, GameLogic, Buffer1, GameId);
			if (!Word.empty())
			{
				receive[GameId % 50] = thread(&Server::process_message, this, GameLogic, Client, GameId, Word);
			}
		}
		else 
		{
			cout << "connection closed" << endl;
		}
	}
	ExitThread(0);
}
void Server::accept_connection()
{
	SOCKET Server, Client;
	WSADATA WSAData;
	if (WSAStartup(MAKEWORD(2, 0), &WSAData) != 0)
	{
		cout << "\nWSA startup failed ";
	}
	if ((Server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "\nCould not create socket ";
	}
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(138);
	if ((::bind(Server, (SOCKADDR *)&serverAddr, sizeof(serverAddr))) < 0)
	{
		cout << "\nbind error ";
	}
	listen(Server, 5);
	cout << "\nListening for incoming connections..." << endl;
	int iteration = 0;
	int clientAddrSize = sizeof(clientAddr);
	while (1)
	{
		if ((Client = accept(Server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)									//server accept the client request
		{
			
			cout << "Client connected!" << endl;
			GameType[iteration % 50] = thread(&Server::choose_game_type, this, Client);
			iteration++;
		}
		else 
		{
			cout << "Client not connected!" << endl;
		}
	}
	cout << "Client disconnected." << endl;
}
//It returns the game information
string Server::get_result(GameLogic logic, string GameInfo, string Word, int Chance)
{
	if (logic.get_remaining_guess() == 0)
	{
		return GameInfo + "<"WORDS">" + Word + "</"WORDS"><"REMAININGGUESS">" + to_string(logic.get_remaining_guess()) + "</"REMAININGGUESS"><"WRONGGUESS">" + logic.get_wrong_guess() + "</"WRONGGUESS"><"CHANCE">" + to_string(Chance) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
	}
	else
	{
		return GameInfo + "<"REMAININGGUESS">" + to_string(logic.get_remaining_guess()) + "</"REMAININGGUESS"><"WRONGGUESS">" + logic.get_wrong_guess() + "</"WRONGGUESS"><"CHANCE">" + to_string(Chance) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
	}
}
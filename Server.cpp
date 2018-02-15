#include "Server.h"
Server::Server()
{
}
Server::~Server()
{
}
void Server::receive_message(GameLogic logic,int client, int GameId, string Word)
{
	string Dash;
	char Buffer[1024];
	int ReceivedBytes = 0;
	char Letter =' ' ;
	int client1;
	Dash = logic.fill_dash(Word);
	string FillDash = Dash;
	string Result;
	unsigned int iteration=0;
	unsigned int iteration1 = 0;
	vector<GameDetails> GameDetails;				
		while ( (GameDetails = logic.get_particular_gameid_details(GameId)).size()>0)								//change client sockaddr using DB
		{
			iteration = iteration % GameDetails.size();
			client = GameDetails[iteration].get_socket_address();
			string GameInfo = logic.calculate_result(logic, Dash, FillDash, GameId,Letter);
			for (iteration1 = 0; iteration1 < GameDetails.size(); iteration1++)							//send game info to the all UI which is in same game id
			{
				client1 = GameDetails[iteration1].get_socket_address();
				if (client == client1)
				{
					if (logic.get_remaining_guess() == 0)
					{
						Result = GameInfo + "<"WORDS">" + Word + "</"WORDS"><"REMAININGGUESS">" + to_string(logic.get_remaining_guess()) + "</"REMAININGGUESS"><"WRONGGUESS">" + logic.get_wrong_guess() + "</"WRONGGUESS"><"CHANCE">" + to_string(1) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
					}
					else
					{
						Result = GameInfo + "<"REMAININGGUESS">" + to_string(logic.get_remaining_guess()) + "</"REMAININGGUESS"><"WRONGGUESS">" + logic.get_wrong_guess() + "</"WRONGGUESS"><"CHANCE">" + to_string(1) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
					}
					char Data[1024];
					strcpy_s(Data, Result.c_str());
					send(client1, Data, sizeof(Data), 0);
				}
				else
				{
					if (logic.get_remaining_guess() == 0)
					{
						Result = GameInfo + "<"WORDS">" + Word + "</"WORDS"><"REMAININGGUESS">" + to_string(logic.get_remaining_guess()) + "</"REMAININGGUESS"><"WRONGGUESS">" + logic.get_wrong_guess() + "</"WRONGGUESS"><"CHANCE">" + to_string(0) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
					}
					else
					{
						Result = GameInfo + "<"REMAININGGUESS">" + to_string(logic.get_remaining_guess()) + "</"REMAININGGUESS"><"WRONGGUESS">" + logic.get_wrong_guess() + "</"WRONGGUESS"><"CHANCE">" + to_string(0) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
					}
					char Data[1024];
					strcpy_s(Data, Result.c_str());
					send(client1, Data, sizeof(Data), 0);
				}
			}
			Dash = XmlParse.get_dash(Result);
			if ((GameDetails = logic.get_particular_gameid_details(GameId)).size()>0)
			{
				ReceivedBytes = recv(client, Buffer, sizeof(Buffer), 0);
				if (ReceivedBytes > 0)
				{
					Letter = XmlParse.get_letter(Buffer);
					FillDash = logic.input_character(Word, Dash, Letter);
				}
				else if (ReceivedBytes == 0)
				{
					//logic.update_game_details(GameId, client, "EXITED");
					cout << "connection closed" << endl;
				}
				else
				{
					logic.update_game_details(GameId, client, "EXITED");
					cout << "Client disconnected" << WSAGetLastError() << endl;
				}
			}
			else
			{
				vector<int> ClientAddress;
				unsigned int iteration2 = 0;
				ClientAddress = logic.get_socket_address_by_gameid_from_database(GameId);
				while (iteration2 < ClientAddress.size())
				{
					choose_game_type(ClientAddress[iteration2]);
					iteration2++;
				}
				break;
			}
			iteration++;
		}
}
void Server::choose_game_type(int client)
{
	char Buffer[1024];
	char Buffer1[1024];
	int GameId;
	int Choice = -1;
	string Word;
	string List;
	GameLogic GameLogic;
	int ReceivedBytes = 0; 
	ReceivedBytes = recv(client, Buffer, sizeof(Buffer), 0);
	if (ReceivedBytes > 0)
	{
		Choice = XmlParse.create_or_join(Buffer);
	}
	else if (ReceivedBytes == 0)
	{
		cout << "connection closed" << endl;
	}
	else
	{
		cout << "Client disconnected" << WSAGetLastError() << endl;
	}
	if (Choice == 1)
	{
		List = GameLogic.category_list_and_difficulty_level();														//send category and difficulty to UI
		char Data[1024];
		strcpy_s(Data, List.c_str());
		send(client,Data, sizeof(Data), 0);
		GameId = GameLogic.generate_gameid();
	}
	else if (Choice == 0)
	{
		List = GameLogic.get_all_playing_game();																	//send available game id to UI
		char Data[1024];
		strcpy_s(Data, List.c_str());
		send(client, Data, sizeof(Data), 0);
		if (GameLogic.check_game_detail().empty())
		{
			choose_game_type(client);
		}
	}
	ReceivedBytes = recv(client, Buffer1, sizeof(Buffer1), 0);
	if (ReceivedBytes > 0)
	{
		Word = XmlParse.creategame_or_joingame(client, GameLogic, Buffer1, GameId);
	}
	else if (ReceivedBytes == 0)
	{
		cout << "connection closed" << endl;
	}
	else
	{
		cout << "Client disconnected" << WSAGetLastError() << endl;
	}
	if (!Word.empty())
	{
		receive[GameId % 10] = thread(&Server::receive_message, this, GameLogic, client, GameId, Word);
	}
}
void Server::accept_connection()
{
	WSADATA WSAData;

	if (WSAStartup(MAKEWORD(2, 0), &WSAData) != 0)
	{
		cout << "\nWSA startup failed ";
	}

	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		cout << "\nCould not create socket ";
	}
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(138);
	if ((::bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr))) < 0)
	{
		cout << "\nbind error ";
	}
	listen(server, 5);
	cout << "\nListening for incoming connections..." << endl;
	
	int clientAddrSize = sizeof(clientAddr);
	while (1)
	{
		
		if ((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
		{
			cout << "Client connected!" << endl;

			choose_game_type(client);
		}
		else 
		{
			cout << "Client not connected!" << endl;
		}
	}
	cout << "Client disconnected." << endl;
	
}

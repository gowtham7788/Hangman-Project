#include "Server.h"

Server::Server()
{
}
Server::~Server()
{
}

void Server::receive_message(int client, int GameId, string Word)
{
	GameLogic logic;

	string Dash;
	char Buffer[1024];
	int ReceivedBytes = 0;
	char Letter=' ';
	int client1;

	Dash = logic.fill_dash(Word);
	string FillDash = Dash;

	unsigned int iteration=0;
	unsigned int iteration1 = 0;
	vector<GameDetails> GameDetails;				

		while ( (GameDetails = logic.get_particular_gameid_details(GameId)).size()>0)								//change client sockaddr using DB
		{
			iteration = iteration % GameDetails.size();
			client = GameDetails[iteration].get_socket_address();
			string GameInfo = logic.calculate_result(logic, Dash, FillDash, GameId,Letter);
			Dash = XmlParse.get_dash(GameInfo);
			for (iteration1 = 0; iteration1 < GameDetails.size(); iteration1++)							//send game info to the all UI which is in same game id
			{
				client1 = GameDetails[iteration1].get_socket_address();
				if (client == client1)
				{
					GameInfo = GameInfo + "<"CHANCE">" + to_string(1) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
					send(client1, GameInfo.c_str(), sizeof(GameInfo), 0);
				}
				else
				{
					GameInfo = GameInfo + "<"CHANCE">" + to_string(0) + "</"CHANCE"></"GAMEINFO"></"HANGMAN">";
					send(client1, GameInfo.c_str(), sizeof(GameInfo), 0);
				}
			}

			if ((GameDetails = logic.get_particular_gameid_details(GameId)).size()>0)
			{
				ReceivedBytes = recv(client, Buffer, sizeof(Buffer), 0);
				Letter = XmlParse.get_letter(Buffer);
				FillDash = XmlParse.parse_letter(Letter, GameId, Word, Dash);
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
	int GameId;
	string Word;
	string List;
	GameLogic GameLogic;
	recv(client, Buffer, sizeof(Buffer), 0);
	int Choice = XmlParse.create_or_join(Buffer);
	if (Choice == 1)
	{
		List = GameLogic.category_list_and_difficulty_level();														//send category and difficulty to UI
		send(client, List.c_str(), sizeof(List), 0);
	}
	else
	{
		List = GameLogic.get_all_playing_game();																	//send available game id to UI
		send(client, List.c_str(), sizeof(List), 0);
	}
	recv(client, Buffer, sizeof(Buffer), 0);
	xml_document<> document;
	document.parse<0>(&Buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName==CREATEGAME)
	{
		GameId = GameLogic.generate_gameid();
		xml_node<> *CategoryNode = FirstNode->first_node("category");
		string Category = CategoryNode->value();
		xml_node<> *LevelNode = FirstNode->first_node("level");
		string Level = LevelNode->value();
		xml_node<> *UserNameNode = RootNode->first_node("username");
		string UserName = UserNameNode->value();
		Word = (string)(GameLogic.get_word_from_database((string)Category.c_str(), (string)Level.c_str())).c_str();						//send category and difficulty level to DB and get a word
		GameLogic.insert_into_database(GameId, (string)UserName.c_str(), client, Word);													//send game id , username ,client sockaddr , word to DB
		receive[GameId] = thread(&Server::receive_message, this, client, GameId, Word);
	}
	else if (TagName==JOINGAME)
	{
		xml_node<> *GameIdNode = FirstNode->first_node("gameid");
		string GameIdUser = GameIdNode->value();
		GameId = stoi(GameIdUser);
		xml_node<> *UserNameNode = RootNode->first_node("username");
		string UserName = UserNameNode->value();
		GameLogic.insert_into_database(GameId, (string)UserName.c_str(), client);
	}
	document.clear();
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
	listen(server, 3);
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

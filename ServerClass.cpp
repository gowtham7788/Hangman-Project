#include "ServerClass.h"
ServerClass::ServerClass()
{
}
ServerClass::~ServerClass()
{
}

void ServerClass::receive_message(int client, int GameId,char* Word)
{
	GameLogic logic;
	char *Dash = "";
	char buffer[1024];
	char chance[100] = "<hangman><chance>your chance</chance></hangman>";
	int ReceivedBytes = 0;

	char* FillDash="";
	Dash = logic.fill_dash(Word,Dash);
	while (ReceivedBytes != -1)
	{

		//change client sockaddr using DB
		send(client, chance, sizeof(chance), 0);
		ReceivedBytes = recv(client, buffer, sizeof(buffer), 0);

		if (ReceivedBytes > 0)
		{
			FillDash = xml.parse_letter(buffer, GameId, Word, Dash);


			string GameInfo = logic.calculate_result(logic, Dash, FillDash,GameId);
			
			//send game info to the all UI which is in same game id
			send(client, GameInfo.c_str(), sizeof(GameInfo), 0);
		}
	}
}
void ServerClass::choose_game_type(int client)
{
	char buffer[1024];
	int GameId;
	char* Word;
	recv(client, buffer, sizeof(buffer), 0);
	int choice = xml.create_or_join(buffer);
	if (choice == 1)
	{
		//send category and difficulty to UI
	}
	else
	{
		//send available game id to UI
	}
	recv(client, buffer, sizeof(buffer), 0);
	
	xml.parse_game_type(buffer);

	xml_document<> document;
	document.parse<0>(&buffer[0]);
	xml_node<> *RootNode = document.first_node();
	xml_node<> *FirstNode = RootNode->first_node();
	string TagName = FirstNode->name();
	if (TagName.compare("creategame") == 0)
	{
		GameId = get_maximum_game_id() + 1;
		xml_node<> *CategoryNode = FirstNode->first_node("category");
		string Category = CategoryNode->value();
		xml_node<> *LevelNode = FirstNode->first_node("level");
		string Level = LevelNode->value();
		xml_node<> *UserNameNode = RootNode->first_node("username");
		string UserName = UserNameNode->value();

		Word = (char*)(get_word((char*)Category.capacity(), (char*)Level.c_str())).c_str();									//send category and difficulty level to DB and get a word
		
		insert_into_game_details(GameId, (char*)UserName.c_str(), client, Word);											//send game id , username ,client sockaddr , word to DB
		
		receive[GameId] = thread(&ServerClass::receive_message, this, client, GameId, Word);
	}
	else if (TagName.compare("joingame") == 0)
	{
		xml_node<> *GameIdNode = FirstNode->first_node("gameid");
		string GameIdUser = GameIdNode->value();
		xml_node<> *UserNameNode = RootNode->first_node("username");
		string UserName = UserNameNode->value();


		get_playing_game_detail()
		//send  game id , username ,client sockaddr to DB
	}
	document.clear();
	//std::memset(buffer, 0, sizeof(buffer));
	ClientCount++;
}
void ServerClass::accept_connection()
{
	if (WSAStartup(MAKEWORD(2, 0), &WSAData) != 0)
	{
		cout << "\nWSA startup faild ";
	}
	WSAStartup(MAKEWORD(2, 0), &WSAData);

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
		ClientCount++;
		if ((client[ClientCount] = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
		{
			cout << "Client connected!" << endl;

			choose_game_type(client[ClientCount]);
		}
		else 
		{
			cout << "Client not connected!" << endl;
		}
	}
	cout << "Client disconnected." << endl;
	for (int j = 0; j < ClientCount; j++)
	{
		receive[j].join();
	}
}

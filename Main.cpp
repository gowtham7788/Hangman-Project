#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>

#include <winsock2.h>
#include <thread>
#include "Server.h"

#pragma comment(lib,"libws2_32.a")
using namespace std;




int main()
{
	Server ServerObject;
	//ServerObject.accept_connection();
	
	ServerObject.receive_message(1, 1, "Lion");

	//DatabaseInterface *none = new DatabaseImplementation();
	//string status = none->insert_into_game_details(1, "mahesh", 4563, "Lion");
	//cout << status << endl;

	cin.get();
	cin.ignore(1000, '\n');
	return 0;
}


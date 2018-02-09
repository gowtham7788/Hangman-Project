#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>

#include <winsock2.h>
#include <thread>
#include "ServerClass.h"

#pragma comment(lib,"libws2_32.a")
using namespace std;




int main()
{
	ServerClass ServerObject;
	ServerObject.accept_connection();
	



	cin.get();
	cin.ignore(1000, '\n');
	return 0;
}


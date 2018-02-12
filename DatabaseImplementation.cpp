#include "DatabaseImplementation.h"

/*In constructor the connection handler is get from the Database connection class and stored in a class instance for future use
then the encryption key value is set here*/
DatabaseImplementation::DatabaseImplementation()
{
	SqlConnHandle = Connection.get_connection_handler();
	Cryption.set_key(KEY);
}

/*In destructor the connection handler is delete to free memory*/
DatabaseImplementation::~DatabaseImplementation()
{
	SQLDisconnect(SqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, SqlConnHandle);
}

/*This method is to get list of category from database and return it as vector of category object*/
vector<Category> DatabaseImplementation::get_category()
{
	vector<Category> CategoryVector;
	Category CategoryObject;
	SQLHANDLE SqlHandle = NULL; 
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string Temp;
	/*check whether the query is executed successfully if not then it will return empty vector*/
	if (SQL_SUCCESS != SQLExecDirect(SqlHandle, (SQLWCHAR*)GET_CATEGORY, SQL_NTS))
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return CategoryVector;
	}
	else 
	{
		SQLINTEGER Id, IsActive, PtrSqlVersion;
		SQLCHAR Name[50];
		/*while loop to fetch the data from the handler and store it into vector*/
		while (SQLFetch(SqlHandle) == SQL_SUCCESS)
		{
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &Id, 0, &PtrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, Name, 50, &PtrSqlVersion);
			SQLGetData(SqlHandle, 3, SQL_INTEGER, &IsActive, 0, &PtrSqlVersion);

			CategoryObject.set_id(Id);
			Temp = Cryption.decoder((char*)Name);//method to decrypt the string from human non-understandable form to readable string
			CategoryObject.set_name(Temp);
			CategoryObject.set_is_active(IsActive);
			CategoryVector.push_back(CategoryObject);
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return CategoryVector;
}

/*This method is to get list of difficulty from database and return it as vector of difficulty object*/
vector<Difficulty> DatabaseImplementation::get_difficulty()
{
	vector<Difficulty> DifficultyVector;
	Difficulty DifficultyObject;
	SQLHANDLE SqlHandle = NULL;
	string Temp;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	/*check whether the query is executed successfully if not then it will return empty vector*/
	if (SQL_SUCCESS != SQLExecDirect(SqlHandle, (SQLWCHAR*)GET_DIFFICULTY, SQL_NTS)) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return DifficultyVector;
	}
	else 
	{
		SQLINTEGER Id, IsActive, PtrSqlVersion;
		SQLCHAR Name[50];
		/*while loop to fetch the data from the handler and store it into vector*/
		while (SQLFetch(SqlHandle) == SQL_SUCCESS)
		{
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &Id, 0, &PtrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, Name, 50, &PtrSqlVersion);
			SQLGetData(SqlHandle, 3, SQL_INTEGER, &IsActive, 0, &PtrSqlVersion);

			DifficultyObject.set_id(Id);
			Temp = Cryption.decoder((char*)Name);//method to decrypt the string from human non-understandable form to readable string
			DifficultyObject.set_name(Temp);
			DifficultyObject.set_is_active(IsActive);
			DifficultyVector.push_back(DifficultyObject);
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return DifficultyVector;
}

/*This method is to get the currently playing game details and send the list as vector of Gamedetails object to business logic */
vector<GameDetails> DatabaseImplementation::get_playing_game_detail()
{
	vector<GameDetails> GameDetailsVector;
	GameDetails GameDetailsObject;
	Words WordObject;
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string Temp;
	/*check whether the query is executed successfully if not then it will return empty vector*/
	if (SQL_SUCCESS != SQLExecDirect(SqlHandle, (SQLWCHAR*)GET_PLAYING_GAME_DETAILS, SQL_NTS)) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return GameDetailsVector;
	}
	else 
	{
		SQLINTEGER GameId, SocketAddress, PtrSqlVersion;
		SQLCHAR UserName[50], Word[50];
		/*while loop to fetch the data from the handler and store it into vector*/
		while (SQLFetch(SqlHandle) == SQL_SUCCESS)
		{
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &GameId, 0, &PtrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, UserName, 50, &PtrSqlVersion);
			SQLGetData(SqlHandle, 3, SQL_INTEGER, &SocketAddress, 0, &PtrSqlVersion);
			SQLGetData(SqlHandle, 4, SQL_CHAR, Word, 50, &PtrSqlVersion);
			GameDetailsObject.set_game_id(GameId);
			Temp = Cryption.decoder((char*)UserName);//method to decrypt the string from human non-understandable form to readable string
			GameDetailsObject.set_username(Temp);
			GameDetailsObject.set_socket_address(SocketAddress);
			Temp = Cryption.decoder((char*)Word);//method to decrypt the string from human non-understandable form to readable string
			WordObject.set_word(Temp);
			GameDetailsObject.set_word_id(WordObject);
			GameDetailsVector.push_back(GameDetailsObject);
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return GameDetailsVector;
}

/*This method is to get a particular currently playing game detail and sent it as vector of gamedetails to business logic*/
vector<GameDetails> DatabaseImplementation::get_playing_game_detail(int GameId)
{
	vector<GameDetails> GameDetailsVector;
	GameDetails GameDetailsObject;
	Words WordObject;
	SQLHANDLE SqlHandle = NULL;
	SQLRETURN ReturnCode;
	SQLINTEGER SqlGameId, PtrValue = SQL_NTS;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	string Temp;
	ReturnCode = SQLPrepare(SqlHandle, GET_PLAYING_GAME_DETAILS_BY_ID, SQL_NTS);
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlGameId, 0, &PtrValue);
	SqlGameId = GameId;
	ReturnCode = SQLExecute(SqlHandle);
	/*check whether the query is executed successfully if not then it will return empty vector*/
	if (SQL_SUCCESS != ReturnCode)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return GameDetailsVector;
	}
	else
	{
		SQLINTEGER GameId, SocketAddress, PtrSqlVersion;
		SQLCHAR UserName[50], Word[50];
		/*while loop to fetch the data from the handler and store it into vector*/
		while (SQLFetch(SqlHandle) == SQL_SUCCESS)
		{
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &GameId, 0, &PtrSqlVersion);
			SQLGetData(SqlHandle, 2, SQL_CHAR, UserName, 50, &PtrSqlVersion);
			SQLGetData(SqlHandle, 3, SQL_INTEGER, &SocketAddress, 0, &PtrSqlVersion);
			SQLGetData(SqlHandle, 4, SQL_CHAR, Word, 50, &PtrSqlVersion);
			GameDetailsObject.set_game_id(GameId);
			Temp = Cryption.decoder((char*)UserName);//method to decrypt the string from human non-understandable form to readable string
			GameDetailsObject.set_username(Temp);
			GameDetailsObject.set_socket_address(SocketAddress);
			Temp = Cryption.decoder((char*)Word);//method to decrypt the string from human non-understandable form to readable string
			WordObject.set_word(Temp);
			GameDetailsObject.set_word_id(WordObject);
			GameDetailsVector.push_back(GameDetailsObject);
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	return GameDetailsVector;
}

/*This method is to give the maximum game id to the business logic for creating a new unique game id for new game*/
int DatabaseImplementation::get_maximum_game_id()
{
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	/*check whether the query is executed successfully if not then it will return -1 to indicate no execution failed*/
	if (SQL_SUCCESS != SQLExecDirect(SqlHandle, (SQLWCHAR*)GET_MAXIMUM_GAME_ID, SQL_NTS)) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return -1;
	}
	else 
	{
		SQLINTEGER GameId, PtrSqlVersion;
		/*while loop to fetch the data from the handler*/
		while (SQLFetch(SqlHandle) == SQL_SUCCESS)
		{
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &GameId, 0, &PtrSqlVersion);
		}

		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		if (GameId > 0)
		{
			return GameId;
		}
		else
		{
			return 0;
		}
	}
}

/*This method id to update the game result by using the game id*/
string DatabaseImplementation::update_game_result(int GameId, char* Result)
{
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN ReturnCode;
	char SqlResult[50];
	SQLINTEGER SqlGameId, PtrValue=SQL_NTS;
	ReturnCode = SQLPrepare(SqlHandle,UPDATE_GAME_RESULT, SQL_NTS);
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(Result), 0, &SqlResult, 0, &PtrValue);
	ReturnCode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlGameId, 0, &PtrValue);
	strcpy_s((char*)SqlResult, _countof(SqlResult), Result);
	SqlGameId = GameId;
	ReturnCode = SQLExecute(SqlHandle);
	/*check whether the query is executed successfully if not then it will return a string*/
	if (SQL_SUCCESS != ReturnCode) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Error querying SQL Server";
	}
	else 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Updated Successfully";
	}
}

/*This method will give a random word from database for a new game based on category name and difficulty name choosen by the user*/
string DatabaseImplementation::get_word(char* CategoryName, char* DifficultyName)
{
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN ReturnCode;
	char SqlCategory[50], SqlDifficulty[50];
	SQLINTEGER PtrValue = SQL_NTS, PtrSqlVersion;
	string Temp;
	ReturnCode = SQLPrepare(SqlHandle, GET_WORD, SQL_NTS);
	Temp = Cryption.encoder(CategoryName); //method to encrypt the string to human non-understandable form
	strcpy_s((char*)SqlCategory, _countof(SqlCategory), Temp.c_str());
	Temp = Cryption.encoder(DifficultyName);//method to encrypt the string to human non-understandable form
	strcpy_s((char*)SqlDifficulty, _countof(SqlDifficulty), Temp.c_str());
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(CategoryName), 0, &SqlCategory, 0, &PtrValue);
	ReturnCode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(DifficultyName), 0, &SqlDifficulty, 0, &PtrValue);
	/*check whether the query is executed successfully if not then it will return string*/
	if (SQL_SUCCESS != SQLExecute(SqlHandle)) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Error querying SQL Server";
	}
	else 
	{
		char Word[50];
		/*while loop to fetch the data from the handler*/
		while (SQLFetch(SqlHandle) == SQL_SUCCESS)
		{
			SQLGetData(SqlHandle, 1, SQL_CHAR, Word, 50, &PtrSqlVersion);
		}
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		Temp = Cryption.decoder(Word);//method to decrypt the string from human non-understandable form to readable string
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return Temp;
	}
}

/*This method is used to insert game details into databse for maintaining game records*/
string DatabaseImplementation::insert_into_game_details(int GameId, char* UserName, int SocketAddress, char* Word)
{
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN ReturnCode;
	int WordId;
	char SqlUserName[50], SqlWord[50];
	SQLINTEGER SqlGameId, SqlWordId, SqlSocketAddress, PtrValue = SQL_NTS, PtrSqlVersion;
	string Temp;

	ReturnCode = SQLPrepare(SqlHandle, SELECT_WORD_ID, SQL_NTS);
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(Word), 0, &SqlWord, 0, &PtrValue);
	Temp = Cryption.encoder(Word);//method to encrypt the string to human non-understandable form
	strcpy_s((char*)SqlWord, _countof(SqlWord), Temp.c_str());
	/*check whether the query is executed successfully if not then it will return string*/
	if (SQL_SUCCESS != SQLExecute(SqlHandle)) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Error querying SQL Server";
	}
	else
	{
		/*while loop to fetch the data from the handler*/
		while (SQLFetch(SqlHandle) == SQL_SUCCESS)
		{
			SQLGetData(SqlHandle, 1, SQL_INTEGER, &WordId, 50, &PtrSqlVersion);
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	ReturnCode = SQLPrepare(SqlHandle,INSERT_INTO_GAME_DETAILS, SQL_NTS);
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlGameId, 0, &PtrValue);
	SqlGameId = GameId;
	ReturnCode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(UserName), 0, &SqlUserName, 0, &PtrValue);
	Temp = Cryption.encoder(UserName);//method to encrypt the string to human non-understandable form
	strcpy_s((char*)SqlUserName, _countof(SqlUserName), Temp.c_str());
	ReturnCode = SQLBindParameter(SqlHandle, 3, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlWordId, 0, &PtrValue);
	SqlWordId = WordId;
	ReturnCode = SQLBindParameter(SqlHandle, 4, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlSocketAddress, 0, &PtrValue);
	SqlSocketAddress = SocketAddress;
	/*check whether the query is executed successfully if not then it will return string*/
	if (SQL_SUCCESS != SQLExecute(SqlHandle)) 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Error querying SQL Server";
	}
	else 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Inserted Successfully";
	}
}

/*This is private class method for inserting into category table while starting the server
the input is read from the xml file*/
string DatabaseImplementation::insert_into_category(char* Name, int IsActive)
{
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN ReturnCode;
	char SqlName[50];
	SQLINTEGER SqlIsActive, PtrValue = SQL_NTS;
	string Temp;
	ReturnCode = SQLPrepare(SqlHandle, (SQLWCHAR*)INSERT_INTO_CATEGORY, SQL_NTS);
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(Name), 0, &SqlName, 0, &PtrValue);
	Temp = Cryption.encoder(Name);//method to encrypt the string to human non-understandable form
	strcpy_s((char*)SqlName, _countof(SqlName), Temp.c_str());
	ReturnCode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlIsActive, 0, &PtrValue);
	SqlIsActive = IsActive;
	ReturnCode = SQLExecute(SqlHandle);
	/*check whether the query is executed successfully if not then it will return string*/
	if (SQL_SUCCESS != ReturnCode)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Error querying SQL Server";
	}
	else 
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Inserted Successfully";
	}
}

/*This is private class method for inserting into difficulty table while starting the server
the input is read from the xml file*/
string DatabaseImplementation::insert_into_difficulty(char* Name, int IsActive)
{
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN ReturnCode;
	char SqlName[50];
	SQLINTEGER  SqlIsActive, PtrValue = SQL_NTS;
	string Temp;
	ReturnCode = SQLPrepare(SqlHandle, (SQLWCHAR*)INSERT_INTO_DIFFICULTY, SQL_NTS);
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(Name), 0, &SqlName, 0, &PtrValue);
	Temp = Cryption.encoder(Name);//method to encrypt the string to human non-understandable form
	strcpy_s((char*)SqlName, _countof(SqlName), Temp.c_str());
	ReturnCode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlIsActive, 0, &PtrValue);
	SqlIsActive = IsActive;
	ReturnCode = SQLExecute(SqlHandle);
	/*check whether the query is executed successfully if not then it will return string*/
	if (SQL_SUCCESS != ReturnCode)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Error querying SQL Server";
	}
	else
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Inserted Successfully";
	}
}

/*This is private class method for inserting into words table while starting the server
the input is read from the xml file*/
string DatabaseImplementation::insert_into_words(int CategoryId, int DifficultyId, char* Word, int IsActive)
{
	SQLHANDLE SqlHandle = NULL;
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	SQLRETURN ReturnCode;
	char SqlWord[50];
	SQLINTEGER SqlIsActive,SqlCategoryId,SqlDifficultyId, PtrValue = SQL_NTS;
	string Temp;
	ReturnCode = SQLPrepare(SqlHandle, (SQLWCHAR*)INSERT_INTO_WORDS, SQL_NTS);
	ReturnCode = SQLBindParameter(SqlHandle, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlCategoryId, 0, &PtrValue);
	SqlCategoryId = CategoryId;
	ReturnCode = SQLBindParameter(SqlHandle, 2, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlDifficultyId, 0, &PtrValue);
	SqlDifficultyId = DifficultyId;
	ReturnCode = SQLBindParameter(SqlHandle, 3, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, strlen(Word), 0, &SqlWord, 0, &PtrValue);
	Temp = Cryption.encoder(Word);//method to encrypt the string to human non-understandable form
	strcpy_s((char*)SqlWord, _countof(SqlWord), Temp.c_str());
	ReturnCode = SQLBindParameter(SqlHandle, 4, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, &SqlIsActive, 0, &PtrValue);
	SqlIsActive = IsActive;
	ReturnCode = SQLExecute(SqlHandle);
	/*check whether the query is executed successfully if not then it will return string*/
	if (SQL_SUCCESS != ReturnCode)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Error querying SQL Server";
	}
	else
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return "Inserted Successfully";
	}
}

/*This is the starting method which will load data to database from xml file
Before loading the data it will delete the already available data along with the table
and create a new table and insert the new data*/
void DatabaseImplementation::load_data()
{
	XmlParser Xml;
	xml_document<> Document;
	xml_node<> *Node;
	ifstream File(XML_FILE);
	stringstream Buffer;
	Buffer << File.rdbuf();
	File.close();
	string Content(Buffer.str());
	Document.parse<0>(&Content[0]);
	Node = Document.first_node();
	Xml.set_node(Node);
	vector<Category> CatergoryVector;
	vector<Difficulty> DifficultyVector;
	vector<Words> WordVector;
	SQLHANDLE SqlHandle = NULL;
	SQLRETURN ReturnCode;
	string Status;
	
	SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
	ReturnCode = SQLExecDirect(SqlHandle, (SQLWCHAR*)CHECK_TABLE_PROCEDURE, SQL_NTS);
	if ((SQL_SUCCESS != ReturnCode) && (ReturnCode != SQL_SUCCESS_WITH_INFO))
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		return;
	}
	else
	{
		SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
		SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
		ReturnCode = SQLExecDirect(SqlHandle, (SQLWCHAR*)CREATE_CATEGORY_PROCEDURE, SQL_NTS);
		if ((SQL_SUCCESS != ReturnCode) && (ReturnCode != SQL_SUCCESS_WITH_INFO))
		{
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			return;
		}
		else
		{
			CatergoryVector = Xml.get_category_from_xml(Xml.get_node());
			for (size_t i = 0; i < CatergoryVector.size(); i++)
			{
				Status = insert_into_category((char*)CatergoryVector[i].get_name().c_str(),CatergoryVector[i].get_is_active());
			}
			SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
			SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
			ReturnCode = SQLExecDirect(SqlHandle, (SQLWCHAR*)CREATE_DIFFICULTY_PROCEDURE, SQL_NTS);
			if ((SQL_SUCCESS != ReturnCode) && (ReturnCode != SQL_SUCCESS_WITH_INFO))
			{
				SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
				return;
			}
			else
			{
				DifficultyVector = Xml.get_difficulty_from_xml(Xml.get_node());
				for (size_t i = 0; i < DifficultyVector.size(); i++)
				{
					Status = insert_into_difficulty((char*)DifficultyVector[i].get_name().c_str(), DifficultyVector[i].get_is_active());
				}
				SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
				SQLAllocHandle(SQL_HANDLE_STMT, SqlConnHandle, &SqlHandle);
				ReturnCode = SQLExecDirect(SqlHandle, (SQLWCHAR*)CREATE_WORDS_PROCEDURE, SQL_NTS);
				if ((SQL_SUCCESS != ReturnCode) && (ReturnCode != SQL_SUCCESS_WITH_INFO))
				{
					SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
					return;
				}
				else
				{
					WordVector = Xml.get_words_from_xml(Xml.get_node());
					for (size_t i = 0; i < WordVector.size(); i++)
					{
						Status = insert_into_words(WordVector[i].get_category_id().get_id(), WordVector[i].get_difficulty_id().get_id(), (char*)WordVector[i].get_word().c_str(), WordVector[i].get_is_active());
					}
				}
			}
		}
	}
	SQLFreeHandle(SQL_HANDLE_STMT, SqlHandle);
}

#include "GameLogic.h"
GameLogic::GameLogic()
{
	DbInterface->load_data();
}
GameLogic::~GameLogic()
{
}
int GameLogic::get_remaining_guess()
{
	return RemainingGuess;																		//return the Remaining guess
}
string GameLogic::get_wrong_guess()
{
	return WrongGuess;
}
vector<GameDetails> GameLogic::get_particular_gameid_details(int GameId)
{
	return DbInterface->get_playing_game_detail(GameId);
}

string GameLogic::get_word_from_database(string CategoryName, string DifficultyName)
{
	return DbInterface->get_word((char*)CategoryName.c_str(), (char*)DifficultyName.c_str());
}
string GameLogic::insert_into_database(int GameId, string UserName, int SocketAddress, string Word)
{
	return DbInterface->insert_into_game_details(GameId, (char*)UserName.c_str(), SocketAddress, (char*)Word.c_str());
}
string GameLogic::insert_into_database(int GameId, string UserName, int SocketAddress)
{
	vector<GameDetails> GameDetail = DbInterface->get_playing_game_detail(GameId);
	string DbWord = (GameDetail[0].get_word_id().get_word());
	string Status = DbInterface->insert_into_game_details(GameId, (char*)UserName.c_str(), SocketAddress, (char*)DbWord.c_str());
	return Status;
}
int GameLogic::generate_gameid()
{
	int GameId = DbInterface->get_maximum_game_id();
	return GameId + 1;
}
string GameLogic::category_list_and_difficulty_level()
{
	string List;
	unsigned int iteration = 0;
	List = "<"HANGMAN"><"CATEGORYLIST">";
	vector<Category> CategoryList = DbInterface->get_category();
	for (iteration = 0; iteration < CategoryList.size(); iteration++)
	{
		List = List + "<"CATEGORY">" + CategoryList[iteration].get_name() + "</"CATEGORY">";
	}
	List = List + "</"CATEGORYLIST"><"DIFFICULTYLEVEL">";
	vector<Difficulty> DifficultyLevel = DbInterface->get_difficulty();
	for (iteration = 0; iteration < DifficultyLevel.size(); iteration++)
	{
		List = List + "<"LEVEL">" + DifficultyLevel[iteration].get_name() + "</"LEVEL">";
	}
	List = List + "</"DIFFICULTYLEVEL"></"HANGMAN">";
	return List;
}
vector<int> GameLogic::get_socket_address_by_gameid_from_database(int GameId)
{
	return DbInterface->get_socket_address_by_game_id(GameId);
}
string GameLogic::get_all_playing_game()
{
	unsigned int iteration = 0;
	int GameId = 0;
	string JoinGameidList;
	vector<GameDetails> GameDetail = DbInterface->get_playing_game_detail();
	JoinGameidList = "<"HANGMAN"><"JOIN">";
	for (iteration; iteration < GameDetail.size(); iteration++)
	{
		if (GameId != GameDetail[iteration].get_game_id())
		{
			JoinGameidList = JoinGameidList + "<"GAMEID">" + to_string(GameDetail[iteration].get_game_id()) + "</"GAMEID">";
		}
	}
	JoinGameidList = JoinGameidList + "</"JOIN"></"HANGMAN">";
	return JoinGameidList;
}
string GameLogic::fill_dash(string Word)
{
	size_t Index = 0;
	string Dash;
	for (Index = 0; Index < Word.size(); Index++)
	{
		if (!isspace(Word[Index]))
		{
			Dash.append("_");
		}
		else
		{
			Dash.append(" ");
		}
	}
	return Dash;
}
string GameLogic::input_character(string Word, string Dash, char Letter)
{
	size_t CharIndex;
	for (CharIndex = 0; CharIndex < Word.size(); CharIndex++)
	{
		if (Word[CharIndex] == tolower(Letter) || Word[CharIndex] == toupper(Letter))
		{
			Dash[CharIndex] = Word[CharIndex];
		}
	}
	return Dash;
}
int GameLogic::calculate_number_of_dash(string Word)
{
	size_t Index;
	int Count = 0;
	for (Index = 0; Index < Word.size(); Index++)
	{
		if (Word[Index] == '_')
		{
			Count++;
		}
	}
	return Count;
}
string GameLogic::calculate_result(GameLogic logic, string Dash, string FillDash, int GameId, char Letter)
{
	if (Dash.compare(FillDash) == 0)
	{
		WrongGuess[MAXIMUMGUESS - RemainingGuess] = Letter;
		RemainingGuess--;
	}
	else
	{
		Dash = FillDash;
	}
	DashCount = logic.calculate_number_of_dash(Dash);
	if (DashCount == 0)
	{
		Result = "WIN";
		string status = DbInterface->update_game_result(GameId, (char*)Result.c_str());
	}
	else if (RemainingGuess == 0)
	{
		Result = "LOSE";
		string status = DbInterface->update_game_result(GameId, (char*)Result.c_str());
	}
	else
	{
		Result = "PLAYING";
	}
	string GameInfo = "<"HANGMAN"><"GAMEINFO"><"GAMEID"> " + to_string(GameId) + "</"GAMEID"><"WORDS">" + Dash + "</"WORDS"><"RESULT">" + Result + "</"RESULT">";
	return GameInfo;
}
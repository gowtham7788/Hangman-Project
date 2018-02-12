#include "GameLogic.h"


GameLogic::GameLogic()
{
}


GameLogic::~GameLogic()
{
}
int GameLogic::get_remaining_guess()
{
	return RemainingGuess;
}
char* GameLogic::get_wrong_guess()
{
	return WrongGuess;
}
string GameLogic::get_result()
{
	return Result;
}
vector<GameDetails> GameLogic::get_particular_gameid_details(int GameId)
{
	vector<GameDetails> GameDetails = DbInterface->get_playing_game_detail(GameId);
	return GameDetails;
}

string GameLogic::get_word_from_database(char* CategoryName, char* DifficultyName)
{
	string Word = DbInterface->get_word(CategoryName,DifficultyName);	
	return Word;
}
string GameLogic::insert_into_database(int GameId, char* UserName, int SocketAddress, char* Word)
{
	DbInterface->insert_into_game_details(GameId, UserName, SocketAddress, Word);
}
string GameLogic::insert_into_database(int GameId, char* UserName, int SocketAddress)
{
	vector<GameDetails> GameDetail = DbInterface->get_playing_game_detail(GameId);
	char* DbWord = (char*)(GameDetail[0].get_word_id().get_word()).c_str();
	DbInterface->insert_into_game_details(GameId, UserName, SocketAddress, DbWord);
}
int GameLogic::generate_gameid()
{
	int GameId = DbInterface->get_maximum_game_id();
	return GameId + 1;
}

string GameLogic::category_list_and_difficulty_level()
{
	string List;
	int iteration = 0;
	List = "<"HANGMAN"><"CATEGORYLIST">";
	vector<Category> CategoryList = DbInterface->get_category();
	for (iteration = 0; iteration < CategoryList.size(); iteration++)
	{
		string Category = CategoryList[iteration].get_name();
		List = List + "<"CATEGORY">" + Category + "</"CATEGORY">";
	}
	List = List + "</"CATEGORYLIST"><"DIFFICULTYLEVEL">";

	vector<Difficulty> DifficultyLevel = DbInterface->get_difficulty();
	for (iteration = 0; iteration < DifficultyLevel.size(); iteration++)
	{
		string Level = DifficultyLevel[iteration].get_name();
		List = List + "<"LEVEL">" + Level + "</"LEVEL">";
	}
	List = List + "</"DIFFICULTYLEVEL"></"HANGMAN">";
	return List;
}

string GameLogic::get_all_playing_game()
{
	int iteration = 0;
	string JoinGameidList;
	vector<GameDetails> GameDetail = DbInterface->get_playing_game_detail();
	JoinGameidList = "<"HANGMAN"><"JOIN">";
	for (iteration = 0; iteration < GameDetail.size(); iteration++)
	{
		int Id = GameDetail[iteration].get_game_id();
		JoinGameidList = JoinGameidList + "<"GAMEID">" + to_string(Id) + "</"GAMEID">";
	}
	JoinGameidList = JoinGameidList + "</"JOIN"></"HANGMAN">";

	return JoinGameidList;
}
char* GameLogic::fill_dash(char* Word, char* Dash)
{
	size_t Index = 0;
	for (Index = 0; Index < strlen(Word); Index++)
	{
		if (!isspace(Word[Index]))
		{
			Dash[Index] = '_';
		}
		else
		{
			Dash[Index] = ' ';
		}
	}
	return Dash;
}

char* GameLogic::input_character(char* Word, char* Dash, char Letter)
{
	size_t CharIndex;
	for (CharIndex = 0; CharIndex < strlen(Word); CharIndex++)
	{
		if (Word[CharIndex] == tolower(Letter) || Word[CharIndex] == toupper(Letter))
		{
			Dash[CharIndex] = Word[CharIndex];
		}
	}
	return Dash;
}
int GameLogic::calculate_number_of_dash(char* Word)
{
	size_t Index;
	int Count = 0;
	for (Index = 0; Index < strlen(Word); Index++)
	{
		if (Word[Index] == '_')
		{
			Count++;
		}
	}
	return Count;
}

string GameLogic::calculate_result(GameLogic logic,char* Dash,char* FillDash,int GameId)
{
	if (strcmp(Dash, FillDash) == 0)
	{
		WrongGuess[MaximumGuess-RemainingGuess]=
		RemainingGuess--;
	}
	else
	{
		strcpy_s(Dash, sizeof(FillDash), FillDash);
	}
	DashCount = logic.calculate_number_of_dash(Dash);
	if (DashCount == 0)
	{
		Result = "win";
		string status = DbInterface->update_game_result(GameId, (char*)Result.c_str());
	}
	else if (RemainingGuess == 0)
	{
		Result = "loss";
		string status = DbInterface->update_game_result(GameId, (char*)Result.c_str());
	}
	else
	{
		Result = "playing";
	}
	
	string GameInfo = "<"HANGMAN"></"GAMEINFO"><"GAMEID"> " + to_string(GameId) + "</"GAMEID"><"WORDS">" + Dash + "</"WORDS"><"REMAININGGUESS">" + to_string(logic.get_remaining_guess()) + "</"REMAININGGUESS"><"WRONGGUESS">" + logic.get_wrong_guess() + "</"WRONGGUESS"><result>" + logic.get_result() + "</"RESULT">";
	return GameInfo;
}
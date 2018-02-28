#include "Game.h"

//It returns the Remaining guess
int Game::get_remaining_guess()
{
	return RemainingGuess;																		
}
//It returns the wrong guessess
string Game::get_wrong_guess()
{
	return WrongGuess;
}
//It returns the particular game id details
vector<GameDetails> Game::fetch_particular_gameid_details(int GameId)
{
	return DbInterface->get_playing_game_detail(GameId);
}
//It returns a word according to Category and Difficulty from database
string Game::fetch_word_from_database(string CategoryName, string DifficultyName)
{
	return DbInterface->get_word((char*)CategoryName.c_str(), (char*)DifficultyName.c_str());
}
//It will insert the game details into database and returns the status
string Game::insert_into_database(int GameId, string UserName, int SocketAddress, string Word)
{
	return DbInterface->insert_into_game_details(GameId, (char*)UserName.c_str(), SocketAddress, (char*)Word.c_str());
}
//It will get the wordfrom databaseand insert the game details into database and returns the status
string Game::insert_into_database(int GameId, string UserName, int SocketAddress)
{
	vector<GameDetails> GameDetail = DbInterface->get_playing_game_detail(GameId);
	string DbWord = (GameDetail[0].get_word_id().get_word());
	return DbInterface->insert_into_game_details(GameId, (char*)UserName.c_str(), SocketAddress, (char*)DbWord.c_str());
}
//It will generate the new game id for new game
int Game::generate_gameid()
{
	return (DbInterface->get_maximum_game_id() + 1);
}
//It will get the category list and difficulty list from the database
string Game::fetch_category_list_and_difficulty_level()
{
	string List;
	unsigned int iteration = 0;
	List = "<"HANGMAN"><"CATEGORYLIST">";																				//open root tags
	vector<Category> CategoryList = DbInterface->get_category();
	for (iteration = 0; iteration < CategoryList.size(); iteration++)
	{
		List = List + "<"CATEGORY">" + CategoryList[iteration].get_name() + "</"CATEGORY">";                           //add the category name
	}
	List = List + "</"CATEGORYLIST"><"DIFFICULTYLEVEL">";
	vector<Difficulty> DifficultyLevel = DbInterface->get_difficulty();
	for (iteration = 0; iteration < DifficultyLevel.size(); iteration++)
	{
		List = List + "<"LEVEL">" + DifficultyLevel[iteration].get_name() + "</"LEVEL">";								//add the difficulty level
	}
	List = List + "</"DIFFICULTYLEVEL"></"HANGMAN">";																	//close the root tags
	return List;
}
//It will update the database if client closes their interface
string Game::update_game_details(int GameId, int SocketAddress, string Result)
{
	return DbInterface->update_game_result(GameId, SocketAddress, (char*)Result.c_str());
}
//It will update the databse after game finished whether win or lose
string Game::update_game_details(int GameId, string Result)
{
	return DbInterface->update_game_result(GameId, (char*)Result.c_str());
}
//It will return the GameDetails 
vector<GameDetails> Game::check_game_detail()
{
	return DbInterface->get_playing_game_detail();
}
//It returns string which contains available game id 
string Game::fetch_all_playing_game()
{
	unsigned int iteration = 0;
	int GameId = 0;
	string JoinGameidList;
	vector<GameDetails> GameDetail = DbInterface->get_playing_game_detail();
	JoinGameidList = "<"HANGMAN"><"JOIN">";
	if (!GameDetail.empty())
	{
		for (iteration; iteration < GameDetail.size(); iteration++)
		{
			if (GameId != GameDetail[iteration].get_game_id())
			{
				JoinGameidList = JoinGameidList + "<"GAMEID">" + to_string(GameDetail[iteration].get_game_id()) + "</"GAMEID">";
				GameId = GameDetail[iteration].get_game_id();
			}
		}
		JoinGameidList = JoinGameidList + "</"JOIN"></"HANGMAN">";
	}
	else
	{
		JoinGameidList = JoinGameidList + "<"GAMEID">0</"GAMEID"></"JOIN"></"HANGMAN">";
	}
	return JoinGameidList;
}
//It will return the Dash which is same size as the given Word
string Game::fill_dash(string Word)
{
	size_t Index = 0;
	string Dash;
	for (Index = 0; Index < Word.size(); Index++)
	{
		if (!isspace(Word[Index]))
		{
			Dash.append("*");
		}
		else
		{
			Dash.append(" ");
		}
	}
	return Dash;
}
//It will replace the dash with given letter if the letter available in word otherwise it returns the Dash
string Game::input_character(string Word, string Dash, char Letter)
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
//It will returns number dash present in the given word
int Game::calculate_number_of_dash(string Word)
{
	int Index;
	int Count = 0;
	int WordSize = Word.size();
	for (Index = 0; Index < WordSize; Index++)
	{
		if (Word[Index] == '*')
		{
			Count++;
		}
	}
	return Count;
}
//It will return the string with Game id , Result and the dashed word 
string Game::calculate_result(Game Game, string Dash, string FillDash, int GameId, char Letter)
{
	string Result;
	if (Dash.compare(FillDash) == 0)
	{
		WrongGuess[MAXIMUMGUESS - RemainingGuess] = Letter;
		RemainingGuess--;
	}
	else
	{
		Dash = FillDash;
	}
	DashCount = Game.calculate_number_of_dash(Dash);
	string GameInfo = "<"HANGMAN"><"GAMEINFO"><"GAMEID"> " + to_string(GameId) + "</"GAMEID">";
	if (DashCount == 0)
	{
		Result = "WIN";
		GameInfo = GameInfo + "<"RESULT">" + Result + "</"RESULT"><"WORDS">" + Dash + "</"WORDS">";
		string status = update_game_details(GameId, Result);
		
	}
	else if (RemainingGuess == 0)
	{
		Result = "LOSE";
		GameInfo = GameInfo + "<"RESULT">" + Result + "</"RESULT">";
		string status = update_game_details(GameId,Result);
	}
	else
	{
		Result = "PLAYING";
		GameInfo = GameInfo + "<"RESULT">" + Result + "</"RESULT"><"WORDS">" + Dash + "</"WORDS">";
	}
	return GameInfo;
}
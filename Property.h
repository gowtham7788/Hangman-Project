#define HANGMAN "Hangman"

#define CREATE "Create"

#define JOIN "Join"

#define MAXIMUMGUESS 7

#define CATEGORYLIST "CategoryList"

#define DIFFICULTYLEVEL "DifficultyLevel"

#define LEVEL "Level"

#define GAMEID "GameId"

#define CREATEGAME "CreateGame"

#define USERNAME "UserName"

#define JOINGAME "JoinGame"

#define REQUEST "Request"

#define RESPONSE "Response"

#define GAMEINFO "GameInfo"

#define REMAININGGUESS "RemainingGuess"

#define WRONGGUESS "WrongGuess"

#define RESULT "Result"

#define LETTER "Letter"

#define CHANCE "Chance"

#define KEY 2

#define CATEGORY "Category"

#define CATEGORIES "Categories"

#define DIFFICULTIES "Difficulties"

#define DIFFICULTY "Difficulty"

#define WORDS "Words"

#define WORDNAME "Word"

#define NAME "Name"

#define IS_ACTIVE "IsActive"

#define CATEGORY_ID "CategoryId"

#define DIFFICULTY_ID "DifficultyId"

#define XML_FILE "./Data.xml"

#define CONNECTION_DRIVER L"DRIVER={SQL Server};SERVER=IN11W-TRAINEE5\\SQLEXPRESS,49400;DATABASE=Hangman;Trusted=true;"

#define CHECK_TABLE_PROCEDURE L"{ CALL CheckTable}"

#define CREATE_CATEGORY_PROCEDURE L"{ CALL CreateCategory}"

#define CREATE_DIFFICULTY_PROCEDURE L"{ CALL CreateDifficulty}"

#define CREATE_WORDS_PROCEDURE L"{ CALL CreateWords}"

#define INSERT_INTO_WORDS L"insert into words(categoryid, difficultyid, word, isActive) values(?,?,?,?)"

#define INSERT_INTO_DIFFICULTY L"insert into difficulty(name, isActive) values(?,?)"

#define INSERT_INTO_CATEGORY L"insert into category(name, isActive) values(?,?)"

#define INSERT_INTO_GAME_DETAILS L"insert into gamedetails(gameid, username, wordid, socketaddress) values(?,?,?,?)"

#define SELECT_WORD_ID L"select id from words where word = ?"

#define GET_WORD L"select top 1 word from words join category on category.id = words.categoryid join difficulty on difficulty.id = words.difficultyid where category.name = ? and difficulty.name = ? order by newid()"

#define UPDATE_GAME_RESULT L"update gamedetails set result = ? where GameId = ? and Result = 'playing'"

#define UPDATE_GAME_RESULT_EXIT L"update gamedetails set result = ? where GameId = ? and Result = 'playing' and socketaddress = ?"

#define GET_MAXIMUM_GAME_ID L"select max(gameid) from gamedetails"

#define GET_PLAYING_GAME_DETAILS_BY_ID L"select gameid, username, socketaddress, words.word from gamedetails join words on gamedetails.wordid = words.id where Result = 'playing' and gameid= ?"

#define GET_SOCKET_ADDRESS_BY_GAME_ID L"select socketaddress from gamedetails where gameid= ?"

#define GET_PLAYING_GAME_DETAILS L"select gameid, username, socketaddress, words.word from gamedetails join words on gamedetails.wordid = words.id where Result = 'playing' order by gameid asc"

#define GET_DIFFICULTY L"select * from difficulty where isactive = 1"

#define GET_CATEGORY L"select * from category where isactive = 1"
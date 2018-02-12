#include "DatabaseInterface.h"
#include "DatabaseImplementation.h"
#include "XmlParser.h"

void main(){

	vector<Category> cat;
	vector<Difficulty> dif;
	vector<GameDetails> game;


	DatabaseInterface* object = new DatabaseImplementation();


	//object->load_data();
	
	cat=object->get_category();

	for (unsigned int i = 0; i < cat.size(); i++){
		cout << endl;
		cout << cat[i].get_id() << endl;
		cout << cat[i].get_name() << endl;
		cout << cat[i].get_is_active() << endl;
		cout << endl;
	}

	//dif = object->get_difficulty();

	//for (unsigned int i = 0; i < dif.size(); i++){
	//	cout << endl;
	//	cout << dif[i].get_id() << endl;
	//	cout << dif[i].get_name() << endl;
	//	cout << dif[i].get_is_active() << endl;
	//	cout << endl;
	//}

	/*string status = object->update_game_result(1, "loss");

	cout << endl;
	cout << status << endl;
	cout << endl;*/
	
	//game = object->get_playing_game_detail();

	//for (unsigned int i = 0; i < game.size(); i++){
	//	cout << endl;
	//	cout << game[i].get_game_id() << endl;
	//	cout << game[i].get_username() << endl;
	//	cout << game[i].get_socket_address() << endl;
	//	cout << game[i].get_word_id().get_word() << endl;
	//	cout << endl;
	//}


	//int word = object->get_maximum_game_id();
	//cout << endl;
	//cout << word << endl;
	//cout << endl;

	//string words = object->get_word("Animals","hard");
	//cout << endl;
	//cout << words << endl;
	//cout << endl;
	

	//string word = object->insert_into_game_details(2,"mani",12655,"Lion");
	//cout << endl;
	//cout << word << endl;
	//cout << endl;
	

	cin.get();
	cin.ignore(1000, '\n');
}
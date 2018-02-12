#include "Coder.h"


Coder::Coder()
{
}

Coder::~Coder()
{
}
/*Getter and setter methods for the variable key*/
void Coder::set_key(int Key)
{
	this->Key = Key;
}

int Coder::get_key()
{
	return this->Key;
}

/*this method encode the given string and return a encoded string*/
string Coder::encoder(string Word)
{
	string EncodeWord = Word;
	int WordLength;

	WordLength = (int)EncodeWord.length();

	for (int i = 0; i < WordLength; i++)
	{
		if (isalpha(EncodeWord[i]))
		{
			for (int j = 0; j < Key; j++)
			{
				if (EncodeWord[i] == 'z')
				{
					EncodeWord[i] = 'a';
				}
				else if (EncodeWord[i] == 'Z')
				{
					EncodeWord[i] = 'A';
				}
				else
				{
					EncodeWord[i]++;
				}
			}
		}
	}
	return EncodeWord;
}


/*this method decode the given encoded string and return a decoded string*/
string Coder::decoder(string Word)
{
	string DecodeWord = Word;
	int WordLength;

	WordLength = (int)DecodeWord.length();

	for (int i = 0; i < WordLength; i++)
	{
		if (isalpha(DecodeWord[i]))
		{
			for (int j = 0; j < Key; j++)
			{
				if (DecodeWord[i] == 'a')
				{
					DecodeWord[i] = 'z';
				}
				else if (DecodeWord[i] == 'A')
				{
					DecodeWord[i] = 'Z';
				}
				else
				{
					DecodeWord[i]--;
				}
			}
		}
	}
	return DecodeWord;
}
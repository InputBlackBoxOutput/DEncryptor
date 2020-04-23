///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cctype>
#include <string>
//#include <random>

///////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace std;

class CeasarCipher{

	public:
		CeasarCipher(int sft) {
			shift = sft;
		}

		void encryptText();
		void decryptText();

	private:
		int shift {1};
		string msg;
		string code;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class VigenereCipher{

	public:
		VigenereCipher(string keywrd) {
			keyword = keywrd;
		}

		void createVigeneresSquare();
		void encryptText();
		void decryptText();

	private:
		string keyword {"DUOSVAVVM"}; //Shugborough inscription
		string msg;
		string code;
		char vigenereSquare[26][26] {};
		string index {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class AlbertiDiskCipher{

	public:
		void encryptText();
		void decryptText();

	private:
		string stationary {"ABHCDJEWFGILMYKNOPQRUSTVXZ"};
		string rotating   {"qxsewfgknboaphcdjtvilmyzru"};
		int shift {0};
		string msg;
		string code;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
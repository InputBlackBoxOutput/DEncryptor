///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cctype>
#include <ctime>
#include <string>
#include <vector>
#include <utility>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
class UserInterface {
public:
	void getMessageFromUser() {
		cout << "Enter the message you want to encrypt: ";
   		getline(cin, msg);
		//cout << "Entered message:" << msg << endl;
	}
	void printCode() {
		cout << "Encrypted message:" << code << endl;
	}


	void getCodeFromUser() {
		cout << "Enter the message you want to decrypt: ";
   		getline(cin, code);
		//cout << "Entered message:" << code <<endl;
	}
	void printMessage() {
		cout << "Decrypted message:" << msg << endl;
	}

	string msg;
	string code;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class CaesarCipher: public UserInterface{

	public:
		CaesarCipher(int sft) {
			shift = sft;
		}

		void encryptText();
		void decryptText();

	private:
		int shift {1};

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class VigenereCipher: public UserInterface{

	public:
		VigenereCipher(string keywrd) {
			keyword = keywrd;
			createVigeneresSquare();
		}

		void createVigeneresSquare();
		void encryptText();
		void decryptText();

	private:
		string keyword {"DUOSVAVVM"}; //Shugborough inscription
		char vigenereSquare[26][26] {};
		string index {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class AlbertiDiskCipher: public UserInterface{

	public:
		void encryptText();
		void decryptText();

	private:
		string stationary {"ABHCDJEWFGILMYKNOPQRUSTVXZ"};
		string rotating   {"qxsewfgknboaphcdjtvilmyzru"};
		int shift {0};

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class PlayFairCipher {
public:
    PlayFairCipher(string key) {
        createEncoder( key, true );
    }

    string encrypt();
    string decrypt();
	void encryptDecryptPieces(string message);


private:
    void createEncoder( string k, bool m );
    void displayGrid();
	char getChar( int a, int b );
	bool getPos( char l, int &c, int &d );
    void getText( string t, bool m, bool e );

	char n[5][5];
	bool toEncrypt {true};
	string msg {};
	string inpt {};
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class MorseCode{

	public:
		MorseCode() {
			generateMorseCodeMap();
		}

	    void generateMorseCodeMap();
		void convertToMorseCode();
		void convertFromMorseCode();

	private:
		vector< pair <char, string>> morse;
		string msg;
		string code;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

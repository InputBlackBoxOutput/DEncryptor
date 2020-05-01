///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cctype>
#include <ctime>
#include <string>
#include <vector>
#include <utility>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
class MorseCode{

	public:
		MorseCode() {
			generateMorseCodeMap();
		}

	    void generateMorseCodeMap();
		string convertToMorseCode(string);
		string convertFromMorseCode(string);

	private:
		vector< pair <char, string>> morse;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
MorseCode M;

///////////////////////////////////////////////////////////////////////////////////////////////////////
class UserInterface {
public:
	string getMessageFromUser() {
		string msg;
		cout << "Enter the message you want to encrypt: ";
   		getline(cin, msg);
		//cout << "Entered message:" << msg << endl;
		return msg;
	}

	void printCode(string code) {
		code = M.convertToMorseCode(code);
		cout << "Encrypted message:" << code << endl;
	}


	string getCodeFromUser() {
		string code;
		cout << "Enter the message you want to decrypt: ";
   		getline(cin, code);
		//cout << "Entered message:" << code <<endl;
		code = M.convertFromMorseCode(code);
		return code;
	}

	void printMessage(string msg) {
		cout << "Decrypted message:" << msg << endl;
	}

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
UserInterface UI;

///////////////////////////////////////////////////////////////////////////////////////////////////////
class CaesarCipher{

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
class VigenereCipher{

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
class AlbertiDiskCipher{

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

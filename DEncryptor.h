///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cctype>
#include <ctime>
#include <string>
#include <vector>
#include <utility>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
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
class PlayFairCipher {
public:
    PlayFairCipher(string key, bool encrypt) {
        createEncoder( key, true );
        toEncrypt = encrypt;
    }

    string encryptDecrypt(string message);
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
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class PlayFairCipher {
public:
    PlayFairCipher(string key) {
        createEncoder( key, true );
    }

    string encrypt(string mssge);
    string decrypt(string code);
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
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
class MorseCode{

	public:
	    void generateMorseCodeMap();
		void convertToMorseCode();
		void convertFromMorseCode();

	private:
		vector< pair <char, string>> morse;
		string msg;
		string code;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

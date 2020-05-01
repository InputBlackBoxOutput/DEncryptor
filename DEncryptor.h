///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cctype>
#include <ctime>
#include <string>
#include <vector>
#include <utility>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 This class provides all functionalities related with Morse code.
*/

class MorseCode{

	public:
	    /**
         Constructor for class MorseCode
	    */
		MorseCode() {
			generateMorseCodeMap();
		}

        /**
         Generates a lookup table for roman alphabets and digits
         @note This function is called during by constructor
         @attention Do not call this function
	    */
	    void generateMorseCodeMap();

	    /**
         Converts roman alphabets and digits into Morse code
         @note Characters other than roman alphabets and digits are left unchanged
         @param morseIn Encrypted message
         @returns Encrypted message in Morse code
	    */
		string convertToMorseCode(string morseIn);

        /**
         Converts Morse code into roman alphabets and digits
         @note Characters other than roman alphabets and digits are left unchanged
         @param morseIn Encrypted message in Morse code
         @returns Encrypted message
	    */
		string convertFromMorseCode(string morseIn);

	private:
		vector< pair <char, string>> morse;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
MorseCode M;

///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 This class provides all functionalities related with text input and output.
*/
class UserInterface {
public:
    /**
     Prompts the user for message 
     @returns Message
    */
	string getMessageFromUser() {
		string msg;
		cout << "Enter the message you want to encrypt: ";
   		getline(cin, msg);
		//cout << "Entered message:" << msg << endl;
		return msg;
	}

	/**
     Prints encrypted message on the terminal
     @param code Encrypted message
    */
	void printCode(string code) {
		code = M.convertToMorseCode(code);
		cout << "Encrypted message:" << code << endl;
	}

    /**
     Prompts the user for encrypted message
     @returns Encrypted message
    */
	string getCodeFromUser() {
		string code;
		cout << "Enter the message you want to decrypt: ";
   		getline(cin, code);
		//cout << "Entered message:" << code <<endl;
		code = M.convertFromMorseCode(code);
		return code;
	}

	/**
     Prints decrypted message on the terminal
     @param msg Decrypted message
    */
	void printMessage(string msg) {
		cout << "Decrypted message:" << msg << endl;
	}

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
UserInterface UI;

///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 This class provides all functionalities related with Caesar cipher.
*/
class CaesarCipher{

	public:
		/**
         Constructor for class CaesarCipher
	    */
		CaesarCipher(int sft) {
			shift = sft;
		}

		void encryptText();
		void decryptText();

	private:
		int shift {1};

};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 This class provides all functionalities related with Vigenere cipher.
*/
class VigenereCipher{

	public:
		/**
         Constructor for class VigenereCipher
	    */
		VigenereCipher(string keywrd) {
			keyword = keywrd;
			createVigeneresSquare();
		}

		void createVigeneresSquare();
		void encryptText();
		void decryptText();

	private:
		string keyword {"DUOSVAVVM"};   //Shugborough inscription
		char vigenereSquare[26][26] {};
		string index {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 This class provides all functionalities related with Alberti's disk cipher.
*/
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
/**
 This class provides all functionalities related with Playfair cipher.
*/
class PlayFairCipher {
public:
	/**
     Constructor for class PlayFairCipher
	*/
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

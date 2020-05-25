/**
* @file
* @author  Rutuparn Pawar <https://github.com/InputBlackBoxOutput>
* @version 1.0
*
*/
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
		void generateMorseCodeMap();
		vector< pair <char, string>> morse;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 This class provides all functionalities related with text input and output.
*/
class UserInterface {
public:
    MorseCode M;

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

		/**
     	 Encrypts message using Caesar cipher
     	 @param msg Message
     	 @param isInteractive Prompt for message and print encrypted message on CLI
    	*/
		string encryptText(string msg="", bool isInteractive=true);

		/**
     	 Decrypts message using Caesar cipher
     	 @param code Encrypted message
     	 @param isInteractive Prompt for encrypted message and print decrypted message on CLI
    	*/
		string decryptText(string code="", bool isInteractive=true);

		/**
     	 Set the shift used by Caesar cipher
     	 @param sft Shift each character by this value
     	 @note Only positive shift is allowed
    	*/
		void setShift(int sft) {
		    if(sft > 0)
                shift = sft;
            else
                cout << "Only positive shift is allowed";
		}

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

		/**
     	 Encrypts message using Vigenere's cipher
     	 @param msg Message
     	 @param isInteractive Prompt for message and print encrypted message on CLI
    	*/
		string encryptText(string msg="", bool isInteractive=true);

		/**
     	 Decrypts message using Vigenere's cipher
     	 @param code Encrypted message
     	 @param isInteractive Prompt for encrypted message and print decrypted message on CLI
    	*/
		string decryptText(string code="", bool isInteractive=true);

		/**
     	 Set the keyword used by Vigenere's cipher
     	 @param kywrd This keyword used to build vigenere's square
    	*/
		void setKeyword(string kywrd) {
			keyword = kywrd;
			createVigeneresSquare();
		}

	private:
		void createVigeneresSquare();

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
		/**
     	 Constructor for class PlayFairCipher
		*/
		AlbertiDiskCipher(int initShift) {
			rotating = rotating.substr(initShift, rotating.length()) + rotating.substr(0,initShift);
		}
		/**
     	 Encrypts message using Alberti's disk cipher
     	 @param msg Message
     	 @param isInteractive Prompt for message and print encrypted message on CLI
    	*/
		string encryptText(string msg="", bool isInteractive=true);

		/**
     	 Decrypts message using Alberti's disk cipher
     	 @param code Encrypted message
     	 @param isInteractive Prompt for encrypted message and print decrypted message on CLI
    	*/
		string decryptText(string code="", bool isInteractive=true);

		/**
     	 Set the stationary disk used by Alberti's disk cipher
     	 @param stat This string is used as the stationary disk
     	 @attention Parameter 'stat' should have 26 characters (from a to z) with each character occurring only once.
    	*/
		void setStatDisk(string stat) {
			if(stat.length() == 26)
				stationary = stat;
			else
				cout << "Invalid Size: Should have exactly 26 characters" << endl;
		}

		/**
     	 Set the rotating disk used by Alberti's disk cipher
     	 @param rot This string is used as the rotating disk
     	 @attention Parameter 'stat' should have 26 characters (from a to z) with each character occurring only once.
    	*/
		void setRotDisk(string rot) {
			if(rot.length() == 26)
				rotating = rot;
			else
				cout << "Invalid Size: Should have exactly 26 characters" << endl;
		}

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

    /**
     Encrypts message using Playfair cipher
     @param inpt Message
     @param isInteractive Prompt for message and print encrypted message on CLI
    */
    string encrypt(string inpt="", bool isInteractive=true);

    /**
     Decrypts message using Playfair cipher
     @param inpt Encrypted message
     @param isInteractive Prompt for encrypted message and print decrypted message on CLI
    */
    string decrypt(string inpt="", bool isInteractive=true);


    /**
     Set the keyword used by Playfair cipher
	 @param keyword This string is used as keyword while generating grid
    */
    void setKeyword(string keyword) {
    	createEncoder(keyword, true);
    }

private:
	void encryptDecryptPieces(string message);
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

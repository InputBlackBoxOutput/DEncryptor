/**
* @file 
* @author  Rutuparn Pawar <https://github.com/InputBlackBoxOutput>
* @version 1.0
*
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////
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
		map<int, string> morse; 
		map<string, int> reverseMorse;            
		// vector< pair <char, string>> morse;

	// Use below code for testing
	// MorseCode mc;
	// cout << mc.convertToMorseCode("az") << endl;            //Gives "01-1100-"
	// cout << mc.convertFromMorseCode("01-1100-") << endl;    //Gives "AZ"
};

//////////////////////////////////////////////////////////////////////////////////////////////
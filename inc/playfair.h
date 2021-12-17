#include <iostream>
#include <string>

#include "../utils.h"

using namespace std;

/**
 This class provides all functionalities related with Playfair cipher.
*/
class PlayFairCipher: public Utils
{
public:
    /**
     Constructor for class PlayFairCipher
	*/
    PlayFairCipher(string key)
    {
        createEncoder(key, true);
    }

    /**
     Encrypts message using Playfair cipher
     @param inpt Message
    */
    string encryptText(string inpt = "");

    /**
     Decrypts message using Playfair cipher
     @param inpt Encrypted message
    */
    string decryptText(string inpt = "");

    /**
     Set the keyword used by Playfair cipher
	 @param keyword This string is used as keyword while generating grid
    */
    void setKeyword(string keyword)
    {
        createEncoder(keyword, true);
    }

    /**
    Display encoder grid
    */
    void displayGrid();

private:
    void encryptDecryptPieces(string message);
    void createEncoder(string k, bool m);
    char getChar(int a, int b);
    bool getPos(char l, int &c, int &d);

    char n[5][5];
    bool toEncrypt{true};
    string msg{};
};

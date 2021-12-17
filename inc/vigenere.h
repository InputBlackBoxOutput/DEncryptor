#include <iostream>
#include <string>

#include "../utils.h"

using namespace std;

/**
 This class provides all functionalities related with Vigenere cipher.
*/
class VigenereCipher: public Utils
{

public:
    /**
     Constructor for class VigenereCipher
    */
    VigenereCipher(string keywrd)
    {
        keyword = keywrd;
        createVigeneresSquare();
    }

    /**
     Encrypts message using Vigenere's cipher
     @param msg Message
    */
    string encryptText(string msg = "");

    /**
     Decrypts message using Vigenere's cipher
     @param code Encrypted message
    */
    string decryptText(string code = "");

    /**
     Set the keyword used by Vigenere's cipher
     @param kywrd This keyword used to build vigenere's square
    */
    void setKeyword(string kywrd)
    {
        keyword = kywrd;
        createVigeneresSquare();
    }

private:
    void createVigeneresSquare();

    string keyword{"DUOSVAVVM"}; //Shugborough inscription
    char vigenereSquare[26][26]{};
    string index{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
};

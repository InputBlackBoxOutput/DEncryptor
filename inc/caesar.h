#include <iostream>
#include <string>

#include "../utils.h"

using namespace std;

/**
 This class provides all functionalities related with Caesar cipher.
*/
class CaesarCipher: public Utils
{

public:
    /**
     Constructor for class CaesarCipher
    */
    CaesarCipher(int sft)
    {
        shift = sft;
    }

    /**
     Encrypts message using Caesar cipher
     @param msg Message
    */
    string encryptText(string msg = "");

    /**
     Decrypts message using Caesar cipher
     @param code Encrypted message
    */
    string decryptText(string code = "");

    /**
     Set the shift used by Caesar cipher
     @param sft Shift each character by this value
     @note Only positive shift is allowed
    */
    void setShift(int sft)
    {
        if (sft > 0)
            shift = sft;
        else
            cout << "Only positive shift is allowed";
    }

private:
    int shift{1};
};

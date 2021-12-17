#include <iostream>
#include <string>
#include <ctime>

#include "../utils.h"

using namespace std;

/**
 This class provides all functionalities related with Alberti's disk cipher.
*/
class AlbertiDiskCipher: public Utils
{

public:
    /**
    Constructor for class AlbertiDiskCipher
    */
    AlbertiDiskCipher(int initShift)
    {
        rotating = rotating.substr(initShift, rotating.length()) + rotating.substr(0, initShift);
    }
    /**
     Encrypts message using Alberti's disk cipher
     @param msg Message
    */
    string encryptText(string msg = "");

    /**
     Decrypts message using Alberti's disk cipher
     @param code Encrypted message
    */
    string decryptText(string code = "");

    /**
     Set the stationary disk used by Alberti's disk cipher
     @param stat This string is used as the stationary disk
     @attention Parameter 'stat' should have 26 characters (from a to z) with each character occurring only once.
    */
    void setStatDisk(string stat)
    {
        if (stat.length() == 26)
            stationary = stat;
        else
            cout << "Invalid Size: Should have exactly 26 characters" << endl;
    }

    /**
     	 Set the rotating disk used by Alberti's disk cipher
     	 @param rot This string is used as the rotating disk
     	 @attention Parameter 'stat' should have 26 characters (from a to z) with each character occurring only once.
    	*/
    void setRotDisk(string rot)
    {
        if (rot.length() == 26)
            rotating = rot;
        else
            cout << "Invalid Size: Should have exactly 26 characters" << endl;
    }

private:
    string stationary{"ABHCDJEWFGILMYKNOPQRUSTVXZ"};
    string rotating{"qxsewfgknboaphcdjtvilmyzru"};
    int shift{0};
};

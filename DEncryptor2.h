/**
* @file
* @author  Rutuparn Pawar <https://github.com/InputBlackBoxOutput>
* @version 1.0
*
*/

#ifndef DENCRYPTOR_2H
#define DENCRYPTOR_2H
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <ctime>
#include <cctype>
#include <array>
#include <map>
#include <string>
#include "Morse.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////
class XOR_Cipher {

public:
    XOR_Cipher(char XOR){
        XORwith = toBinary(XOR);
    }
    string toBinary(int n);
    int fromBinary(string bin);
    string encryptText(string text);
    string decryptText(string text);
    string bin {""};

private:
    string XORwith {""}; 
    
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class HillCipher {
public:
	HillCipher(string keyword) {
		// Maintain this order of function call
		createEncryptMatrix(keyword);
		createDecryptMatrix(keyword);
	}

    string encryptText(string message);
    string decryptText(string message);

private:
	string sanitizeKeyword(string kwrd);
	
    int mod26(int n);
    int modInverse(int a, int m);
    int createEncryptMatrix(string keyword);
    void createDecryptMatrix(string keyword);


    int encryptMatrix[3][3] {};
    int decryptMatrix[3][3] {};
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class TranspositionCipher {

public:
	TranspositionCipher(string keyword){
		key = keyword;
		setPermutationOrder();
	}

	string encryptText(string cipher);
	string decryptText(string cipher);

	void setKeyword(string keyword){
		key = keyword;
	}

private:
	void setPermutationOrder(void);

	string key {"DAMN"};
	map<int,int> keyMap;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class NullCipher {

public:
	NullCipher(){
		generateDictonary();
	}
	string decryptText(string text);
	string encryptText(string text);

private:
	void generateDictonary(void);
	map<char, array<string, 100>> dictonary;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif //DENCRYPTOR_2H

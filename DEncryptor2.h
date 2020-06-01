/**
* @file
* @author  Rutuparn Pawar <https://github.com/InputBlackBoxOutput>
* @version 1.0
*
*/
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
		XORwith = XOR;
	}
	string encryptDecrypt(string);

private:
	char XORwith {'I'};
};

///////////////////////////////////////////////////////////////////////////////////////////////////
class HillCipher {
public:
    string encrypt(string message, string keyword);

private:
    void createEncryptMatrix(string keyword);
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

	string encrypt(string cipher);
	string decrypt(string cipher);

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
	string decodeText(string text);
	string encodeText(string text);

private:
	void generateDictonary(void);
	map<char, array<string, 100>> dictonary;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

/**
* @file
* @author  Rutuparn Pawar <https://github.com/InputBlackBoxOutput>
* @version 1.0
*
*/

#include "Morse.h"

//////////////////////////////////////////////////////////////////////////////////////////
void MorseCode::generateMorseCodeMap() {

morse.insert( make_pair('A',"01") );
morse.insert( make_pair('B',"1000") );
morse.insert( make_pair('C',"1010") );
morse.insert( make_pair('D',"100") );
morse.insert( make_pair('E',"0") );
morse.insert( make_pair('F',"0010") );
morse.insert( make_pair('G',"110") );
morse.insert( make_pair('H',"0000") );
morse.insert( make_pair('I',"00") );
morse.insert( make_pair('J',"0111") );
morse.insert( make_pair('K',"101") );
morse.insert( make_pair('L',"0100") );
morse.insert( make_pair('M',"11") );
morse.insert( make_pair('N',"10") );
morse.insert( make_pair('O',"111") );
morse.insert( make_pair('P',"0110") );
morse.insert( make_pair('Q',"1101") );
morse.insert( make_pair('R',"010") );
morse.insert( make_pair('S',"000") );
morse.insert( make_pair('T',"1") );
morse.insert( make_pair('U',"001") );
morse.insert( make_pair('V',"0001") );
morse.insert( make_pair('W',"011") );
morse.insert( make_pair('X',"1001") );
morse.insert( make_pair('Y',"1011") );
morse.insert( make_pair('Z',"1100") );

morse.insert(make_pair('0',"11111"));
morse.insert(make_pair('1',"01111"));
morse.insert(make_pair('2',"00111"));
morse.insert(make_pair('3',"00011"));
morse.insert(make_pair('4',"00001"));
morse.insert(make_pair('5',"00000"));
morse.insert(make_pair('6',"10000"));
morse.insert(make_pair('7',"11000"));
morse.insert(make_pair('8',"11100"));
morse.insert(make_pair('9',"11110"));

reverseMorse.insert(make_pair("01",  'A'));
reverseMorse.insert(make_pair("1000",  'B'));
reverseMorse.insert(make_pair("1010", 'C'));
reverseMorse.insert(make_pair("100", 'D'));
reverseMorse.insert(make_pair("0", 'E'));
reverseMorse.insert(make_pair("0010", 'F'));
reverseMorse.insert(make_pair("110", 'G'));
reverseMorse.insert(make_pair("0000", 'H'));
reverseMorse.insert(make_pair("00", 'I'));
reverseMorse.insert(make_pair("0111", 'J'));
reverseMorse.insert(make_pair("101", 'K'));
reverseMorse.insert(make_pair("0100", 'L'));
reverseMorse.insert(make_pair("11", 'M'));
reverseMorse.insert(make_pair("10", 'N'));
reverseMorse.insert(make_pair("111", 'O'));
reverseMorse.insert(make_pair("0110", 'P'));
reverseMorse.insert(make_pair("1101", 'Q'));
reverseMorse.insert(make_pair("010", 'R'));
reverseMorse.insert(make_pair("000", 'S'));
reverseMorse.insert(make_pair("1", 'T'));
reverseMorse.insert(make_pair("001", 'U'));
reverseMorse.insert(make_pair("0001", 'V'));
reverseMorse.insert(make_pair("011", 'W'));
reverseMorse.insert(make_pair("1001", 'X'));
reverseMorse.insert(make_pair("1011", 'Y'));
reverseMorse.insert(make_pair("1100", 'Z'));

reverseMorse.insert(make_pair("11111", '0'));
reverseMorse.insert(make_pair("01111", '1'));
reverseMorse.insert(make_pair("00111", '2'));
reverseMorse.insert(make_pair("00011", '3'));
reverseMorse.insert(make_pair("00001", '4'));
reverseMorse.insert(make_pair("00000", '5'));
reverseMorse.insert(make_pair("10000", '6'));
reverseMorse.insert(make_pair("11000", '7'));
reverseMorse.insert(make_pair("11100", '8'));
reverseMorse.insert(make_pair("11110", '9'));


// Use below code for testing
// cout << morse['A']  << endl;   // A 01
// cout << morse['H']  << endl;   // H 0000

// cout << (char)reverseMorse["010"]  << endl;    // 010  R
// cout << (char)reverseMorse["0110"]  << endl;   // 0110 P
}

//////////////////////////////////////////////////////////////////////////////////////////
string MorseCode::convertToMorseCode(string morseIn) {
	string morseOut {};

	for(unsigned int i=0; i<morseIn.length(); i++) {
		morseIn.at(i) = toupper(morseIn.at(i));

		if(isalnum(morseIn.at(i)))
			morseOut += morse[morseIn.at(i)] + "-";
		else
			morseOut += (char)morseIn.at(i);

	}
	return morseOut;
}

//////////////////////////////////////////////////////////////////////////////////////////
string MorseCode::convertFromMorseCode(string morseIn) {
   	string morseOut {};
   	string temp {};

   	string::const_iterator it = morseIn.end();
   	if(*it != '-') morseIn += '-';

   	char check {};
   	for(unsigned int i=0; i<morseIn.length(); i++) {
   		check = morseIn.at(i);
   		if(check == '0' || check == '1' || check =='-') {
   			temp += check;

   			if(morseIn.at(i+1) == '-' && reverseMorse.count(temp) == 1) {
   			morseOut += reverseMorse[temp];
   			i++;
   			temp = "";
   			}
   		}
   		else {
   			morseOut += (char)check;
   		}
   	}

	return morseOut;
}
//////////////////////////////////////////////////////////////////////////////////////////
//EOF

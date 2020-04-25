//////////////////////////////////////////////////////////////////////////////////////////
#include "DEncryptor.h"
//////////////////////////////////////////////////////////////////////////////////////////
// Helper functions
string toUpper(string str) {
	for(unsigned int i=0; i<str.length(); i++) {
			str.at(i) = toupper(str.at(i));
	}
	return str;
}

string toLower(string str) {
	for(unsigned int i=0; i<str.length(); i++) {
			str.at(i) = tolower(str.at(i));
	}
	return str;
}


//////////////////////////////////////////////////////////////////////////////////////////
void CeasarCipher::encryptText() {
    cout << "Enter the message you want to encrypt: ";
   	getline(cin, msg);

	//cout << "Entered message:" << msg << endl;

    code = "";
    msg = toUpper(msg);
	for(unsigned int i=0; i< msg.length(); i++) {
		if(isalnum(msg.at(i))) {
			if(msg.at(i) + shift > 90)
				code += (char)(65 + ((msg.at(i) + shift) % ('A' + 26)));
			else
				code += (char)(msg.at(i) + shift);
		}
		else
			code += msg.at(i);
	}
	cout << "Encrypted message:" << code << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
void CeasarCipher::decryptText() {
    cout << "Enter the message you want to decrypt: ";
   	getline(cin, code);

	//cout << "Entered message:" << code <<endl;

    msg = "";
    code = toUpper(code);
	for(unsigned int i=0; i< code.length(); i++) {
		if(isalnum(code.at(i)))
			if(code.at(i) - shift < 65)
				msg += (char)(90 - 65 + (code.at(i) - shift) + 1);
			else
				msg += code.at(i) - shift;
		else
			msg += code.at(i);
	}
	cout << "Decrypted message:" << msg << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
void VigenereCipher::createVigeneresSquare() {
	int offset {0};

	for(int i=0; i<26; i++) {
		offset = i;
        for(int j=0; j<26-i; j++) {
			vigenereSquare[i][j] = (char) (65 + offset);
			offset++;
		}

		offset = 0;
        for(int k=i; k>0; k--) {
		  	vigenereSquare[i][26-k] = (char) (65 + offset);
		  	offset++;
        }
	}

	// Print out Vigeneres Sqaure
//	for(int i=0; i<26; i++) {
//		for(int j=0; j<26; j++) {
//			cout << vigenereSquare[i][j] << " ";
//		}
//		cout << endl;
//	}
}

//////////////////////////////////////////////////////////////////////////////////////////
void VigenereCipher::encryptText() {
	createVigeneresSquare();

    cout << "Enter the message you want to encrypt: ";
	getline(cin, msg);
	//cout << "Entered message:" << code <<endl;

	unsigned int iter {0};
	code = "";
	msg = toUpper(msg);
	keyword = toUpper(keyword);

	for(unsigned int i=0; i<msg.length(); i++) {

		if(isalpha(msg.at(i))){

			code += vigenereSquare[index.find(keyword.at(iter))][index.find(msg.at(i))];
			iter++;

			if(iter >= keyword.length())
				iter = 0;
		}
		else
			code += msg.at(i);
	}

	cout << "Encrypted message:" << code << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
void VigenereCipher::decryptText() {
    cout << "Enter the message you want to decrypt: ";
   	getline(cin, code);
	//cout << "Entered message:" << code <<endl;

   	unsigned int iter {0};
   	int loc;
	msg = "";
	code = toUpper(code);
	keyword = toUpper(keyword);

	for(unsigned int i=0; i<code.length(); i++) {

		if(isalpha(code.at(i))){
			loc = index.find(keyword.at(iter));
			iter++;

			if(iter >= keyword.length())
				iter = 0;

			for(unsigned int j=0; j<26; j++){
              if(vigenereSquare[loc][j] == code.at(i))
					msg += index.at(j);
			}
		}
		else
			msg += code.at(i);
	}


	cout << "Decrypted message:" << msg << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
void AlbertiDiskCipher::encryptText() {
    cout << "Enter the message you want to encrypt: ";
	getline(cin, msg);
	//cout << "Entered message:" << msg <<endl;

	code = "";
	msg = toUpper(msg);
	for(unsigned int i=0; i<msg.length(); i++) {
		if(isalpha(msg.at(i)))
			code += rotating.at((stationary.find(msg.at(i))+shift)%26);
		else {
			if((int)msg.at(i) == (int)" ")
				code += "_";
			else
				code += msg.at(i);

			shift = rand()%26;
			code += stationary.at(shift);
		}
	}

	cout << "Encrypted message:" << code << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
void AlbertiDiskCipher::decryptText() {
    cout << "Enter the message you want to decrypt: ";
   	getline(cin, code);
	//cout << "Entered message:" << code <<endl;

   	msg = "";
   	shift = 0;
	for(unsigned int i=0; i<code.length(); i++) {
		if(isalpha(code.at(i)) && isupper(code.at(i))){
			shift = stationary.find(code.at(i));
			//cout << shift << endl;
			continue;
		}

		if(isalpha(code.at(i))) {
			if((signed int)rotating.find(code.at(i))-shift < 0)
				msg += stationary.at(26 + (rotating.find(code.at(i))-shift));
			else
				msg += stationary.at((rotating.find(code.at(i))-shift));
			// cout << msg << endl;
		}
		else {
			if((int)code.at(i) == (int)"_")
				msg += " ";
			else
				msg += code.at(i);
		}
	}

	cout << "Decrypted message:" << msg << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
void MorseCode::generateMorseCodeMap() {

morse.push_back( make_pair('A',"01") );
morse.push_back( make_pair('B',"1000") );
morse.push_back( make_pair('C',"1010") );
morse.push_back( make_pair('D',"100") );
morse.push_back( make_pair('E',"0") );
morse.push_back( make_pair('F',"0010") );
morse.push_back( make_pair('G',"110") );
morse.push_back( make_pair('H',"0000") );
morse.push_back( make_pair('I',"00") );
morse.push_back( make_pair('J',"0111") );
morse.push_back( make_pair('K',"101") );
morse.push_back( make_pair('L',"0100") );
morse.push_back( make_pair('M',"11") );
morse.push_back( make_pair('N',"10") );
morse.push_back( make_pair('O',"111") );
morse.push_back( make_pair('P',"0110") );
morse.push_back( make_pair('Q',"1101") );
morse.push_back( make_pair('R',"010") );
morse.push_back( make_pair('S',"000") );
morse.push_back( make_pair('T',"1") );
morse.push_back( make_pair('U',"001") );
morse.push_back( make_pair('V',"0001") );
morse.push_back( make_pair('W',"011") );
morse.push_back( make_pair('X',"1001") );
morse.push_back( make_pair('Y',"1011") );
morse.push_back( make_pair('Z',"1100") );

// cout << morse[0].first << " " << morse[0].second << endl;   // A 01
// cout << morse[7].first << " " << morse[7].second << endl;   // H 0000
}

//////////////////////////////////////////////////////////////////////////////////////////
void MorseCode::convertToMorseCode() {
	cout << "Enter the message:";
	getline(cin, msg);
	//cout << "Entered message:" << msg <<endl;

	code = "";
	msg = toUpper(msg);
	for(unsigned int i=0; i<msg.length(); i++) {
		if(isalpha(msg.at(i)))
			for(unsigned int j=0; j<morse.size(); j++) {
				if(morse[j].first == msg.at(i)) {
					code += morse[j].second;
					if(i != msg.length() - 1) code += "-";
					break;
				}
			}
		else
			code += msg.at(i);

	}

	cout << "Morse code:" << code << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
void MorseCode::convertFromMorseCode() {
cout << "Enter the code: ";
   	getline(cin, code);
	//cout << "Entered message:" << code <<endl;

   	msg = "";
   	string temp;
   	unsigned int i {0};
   	bool found {false};
   	code += "~";

	while(i<code.length()) {
		temp = "";

		while((char)code.at(i) =='1' || (char)code.at(i) == '0') {
			temp += code.at(i);
			i++;
		}
		if(i<code.length()) i++;

		found = false;
		for(unsigned int j=0; j< morse.size(); j++) {
			if(morse[j].second == temp) {
				msg += morse[j].first;
				found = true;
				break;
			}
		}

		if(found == false) code+= " Error ";
	}

	cout << "Message:" << msg << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
int main() {
    cout << "--------------------------------------------------------------------" << endl;
    cout << "Ceasar Cipher\n" << endl;
    CeasarCipher DE1(5);  // Shift = 5
    DE1.encryptText();
    DE1.decryptText();
    cout << "--------------------------------------------------------------------" << endl;

    cout << "Vigenere Cipher\n" << endl;
    VigenereCipher DE2("BLACKBOX");
    DE2.encryptText();
    DE2.decryptText();
    cout << "--------------------------------------------------------------------" << endl;

    cout << "Alberti's Disk Cipher\n" << endl;
    AlbertiDiskCipher DE3;
    DE3.encryptText();
    DE3.decryptText();
    cout << "--------------------------------------------------------------------" << endl;

    cout << "Morse Code\n" << endl;
    MorseCode Morse;
    Morse.generateMorseCodeMap();
    Morse.convertToMorseCode();
    Morse.convertFromMorseCode();
    cout << "--------------------------------------------------------------------" << endl;

    // cout << " Press any key to exit..." << endl;
    // getchar();   //wait until any key is pressed
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

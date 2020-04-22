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
	for(unsigned int i=0; i< msg.length(); i++) {
		if(isalnum(msg.at(i)))
			code += msg.at(i) + shift;
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
	for(unsigned int i=0; i< code.length(); i++) {
		if(isalnum(code.at(i)))
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

     // cout << " Press any key to exit..." << endl;
     // getchar();   //wait until any key is pressed
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

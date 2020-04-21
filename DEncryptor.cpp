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
int main() {
    CeasarCipher DE(5);  // Shift = 5
    DE.encryptText();
    DE.decryptText();

     //cout << " Press any key to exit..." << endl;
     //getchar();   //wait until any key is pressed
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

/**
* @file
* @author  Rutuparn Pawar <https://github.com/InputBlackBoxOutput>
* @version 1.0
*
*/
//////////////////////////////////////////////////////////////////////////////////////////
#include "DEncryptor1.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////
UserInterface UI;

//////////////////////////////////////////////////////////////////////////////////////////
// Helper functions
void toUpper(string &str) {
	for(unsigned int i=0; i<str.length(); i++) {
			str.at(i) = toupper(str.at(i));
	}
}

void toLower(string &str) {
	for(unsigned int i=0; i<str.length(); i++) {
			str.at(i) = tolower(str.at(i));
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
string CaesarCipher::encryptText(string msg, bool isInteractive) {
	if(isInteractive)
		msg = UI.getMessageFromUser();
    string code {};

    toUpper(msg);
	for(unsigned int i=0; i< msg.length(); i++) {
		if(isalpha(msg.at(i))) {
			if(msg.at(i) + shift > 90)
				code += (char)(65 + ((msg.at(i) + shift) % ('A' + 26)));
			else
				code += (char)(msg.at(i) + shift);
		}
		else if(isdigit(msg.at(i))) {
				if((msg.at(i) + shift) < 58)
	                code += (int)(msg.at(i) + shift);
				else
					code += (int)(48 + (msg.at(i) + shift) % 58);
		}
		else
			code += msg.at(i);
	}
	if(isInteractive)
		UI.printCode(code);
    return code;
}

//////////////////////////////////////////////////////////////////////////////////////////
string CaesarCipher::decryptText(string code, bool isInteractive) {
	if(isInteractive)
		code = UI.getCodeFromUser();
    string msg {};

   toUpper(code);
	for(unsigned int i=0; i< code.length(); i++) {
		if(isalpha(code.at(i))) {
			if(code.at(i) - shift < 65)
				msg += (char)(90 - 65 + (code.at(i) - shift) + 1);
			else
				msg += code.at(i) - shift;
		}
		else if(isdigit(code.at(i))) {
				if(((int)code.at(i) - shift) >= 48)
	                msg += ((int)code.at(i) - shift);
				else
					msg += (58 - (48 - ((int)code.at(i) - shift)));
		}
		else
			msg += code.at(i);
	}
	if(isInteractive)
		UI.printMessage(msg);
    return msg;
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

//  Print out Vigeneres Sqaure
//	for(int i=0; i<26; i++) {
//		for(int j=0; j<26; j++) {
//			cout << vigenereSquare[i][j] << " ";
//		}
//		cout << endl;
//	}
}

//////////////////////////////////////////////////////////////////////////////////////////
string VigenereCipher::encryptText(string msg, bool isInteractive) {
	if(isInteractive)
		msg = UI.getMessageFromUser();
	string code {};

	unsigned int iter {0};
	toUpper(msg);
	toUpper(keyword);

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
	if(isInteractive)
		UI.printCode(code);
	return code;
}

//////////////////////////////////////////////////////////////////////////////////////////
string VigenereCipher::decryptText(string code, bool isInteractive) {
	if(isInteractive)
		code = UI.getCodeFromUser();
	string msg {};

   	unsigned int iter {0};
   	int loc;
	toUpper(code);
	toUpper(keyword);

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
	if(isInteractive)
		UI.printMessage(msg);
	return msg;
}

//////////////////////////////////////////////////////////////////////////////////////////
string AlbertiDiskCipher::encryptText(string msg, bool isInteractive) {
	if(isInteractive)
		msg = UI.getMessageFromUser();
	string code {};

	shift = 0;
	srand(time(nullptr));
	toUpper(msg);
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
	//cout << code << endl;
	if(isInteractive)
		UI.printCode(code, false);
	return code;
}

//////////////////////////////////////////////////////////////////////////////////////////
string AlbertiDiskCipher::decryptText(string code, bool isInteractive) {
	if(isInteractive)
		code = UI.getCodeFromUser(false);
	string msg {};

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
			//cout << msg << endl;
		}
		else {
			if((int)code.at(i) == (int)" ")
				msg += " ";
			else
				msg += code.at(i);
		}
	}
	if(isInteractive)
		UI.printMessage(msg);
	return msg;
}

//////////////////////////////////////////////////////////////////////////////////////////

string PlayFairCipher::encrypt(string inpt, bool isInteractive) {
	if(isInteractive)
		inpt = UI.getMessageFromUser();
	string code {};

	toEncrypt = true;
	char last_char {'~'};
	toUpper(inpt);

	if(inpt.length() != 0) {

		if(inpt.length()%2 != 0){
		    last_char = inpt.at(inpt.length()-1);
		    inpt.erase(inpt.length()-1);
		}

		size_t i {0};
		while(i<inpt.length()-1){
		    if(isalpha(inpt.at(i)) && isalpha(inpt.at(i+1))) {
		      encryptDecryptPieces(inpt.substr(i,2));
		      code += msg;
		    }
		    else {
		      code += inpt.substr(i,2);
		    }
		    i += 2;
		  }

		if(last_char != '~') code += last_char;
	}

	if(isInteractive)
		UI.printCode(code);
	return code;
}

string PlayFairCipher::decrypt(string inpt, bool isInteractive) {
	if(isInteractive)
		inpt = UI.getCodeFromUser();
	string mssge {};

    toEncrypt = false;
    char last_char {'~'};
    toUpper(inpt);

    if(inpt.length() != 0) {
	    if(inpt.length()%2 != 0){
	        last_char = inpt.at(inpt.length()-1);
	        inpt.erase(inpt.length()-1);
	    }
		size_t i {0};
		while(i<inpt.length()-1){
			if(isalpha(inpt.at(i)) && isalpha(inpt.at(i+1))) {
				encryptDecryptPieces(inpt.substr(i,2));
				mssge += msg;
			}
			else {
				mssge += inpt.substr(i,2);
			}
			i += 2;
		}

		if(last_char != '~') mssge += last_char;
	}

	if(isInteractive)
		UI.printMessage(mssge);
	return mssge;
}

void PlayFairCipher::encryptDecryptPieces(string message) {
    int j,k,p,q;
	string nmsg {};

    msg = message;

    // Sanitize text to deal with J
    for(size_t i=0; i< message.length(); i++ ) {
        if( message.at(i) < 65 || message.at(i) > 90 )
            continue;
        if( message.at(i) == 'J') {
            //message.at(i) = 'I';
            msg = message;
            return;
        }

    }

    msg = message;
    int dir = (toEncrypt)? 1: -1;

	for( string::const_iterator it = msg.begin(); it != msg.end(); it++ ) {
        if( getPos( *it++, j, k ))
	        if( getPos( *it, p, q)) {
	            //for same row
	            if( j == p ) {
	               nmsg += getChar( j, k + dir );
	               nmsg += getChar( p, q + dir );
	            }
	            //for same column
	            else if( k == q ) {
	               nmsg += getChar( j + dir, k );
	               nmsg += getChar( p + dir, q );
	            }
	            else {
	               nmsg += getChar( p, k );
	               nmsg += getChar( j, q );
	            }
            }
        msg = nmsg;
    }
}

char PlayFairCipher::getChar( int a, int b ) {
      return n[ (b + 5) % 5 ][ (a + 5) % 5 ];
}

bool PlayFairCipher::getPos( char l, int &c, int &d ) {
    for( int y = 0; y < 5; y++ )
    	for( int x = 0; x < 5; x++ )
      		if( n[y][x] == l ) {
        		c = x;
        		d= y;
      			return true;
      		}
    return false;
}


void PlayFairCipher::createEncoder( string key, bool m ) {
    if( key.length() < 1 )
    key= "KEYWORD";
    key += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string s= "";
    	for( string::iterator it = key.begin(); it != key.end(); it++ ) {
        	*it = toupper( *it );
        	if( *it < 65 || *it > 90 )
            	continue;
        	if( ( *it == 'J' && m ) || ( *it == 'Q' && !m ) )
            	continue;
        	if( s.find( *it ) == -1 )
            	s += *it;
      	}
	copy( s.begin(), s.end(), &n[0][0] );
}

void PlayFairCipher::displayGrid() {
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            cout << n[i][j];
        }
        cout << endl;
    }
}


// int main( int argc, char* argv[] ) {
//     PlayFairCipher pf("cool");
//     cout << pf.encrypt("Fun at school") << endl;
//     return 0;
// }


//////////////////////////////////////////////////////////////////////////////////////////
// EOF

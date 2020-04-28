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
void CaesarCipher::encryptText() {
	getMessageFromUser();

    code = "";
    msg = toUpper(msg);
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
	printCode();
}

//////////////////////////////////////////////////////////////////////////////////////////
void CaesarCipher::decryptText() {
	getCodeFromUser();

    msg = "";
    code = toUpper(code);
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
	printMessage();
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
	getMessageFromUser();

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
	printCode();
}

//////////////////////////////////////////////////////////////////////////////////////////
void VigenereCipher::decryptText() {
	getCodeFromUser();

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
	printMessage();
}

//////////////////////////////////////////////////////////////////////////////////////////
void AlbertiDiskCipher::encryptText() {
	getMessageFromUser();

	srand(time(nullptr));

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
	printCode();
}

//////////////////////////////////////////////////////////////////////////////////////////
void AlbertiDiskCipher::decryptText() {
	getCodeFromUser();

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
	printMessage();
}

//////////////////////////////////////////////////////////////////////////////////////////

string PlayFairCipher::encrypt() {
  cout << "Enter the message you want to encrypt: ";
  getline(cin, inpt);
  //cout << "Entered message:" << inpt <<endl;

    toEncrypt = true;

    string code {};
    char last_char {'~'};
    inpt = toUpper(inpt);

    if(inpt.length()%2 != 0){
        last_char = inpt.at(inpt.length()-1);
        inpt.erase(inpt.length()-1);
    }
  size_t i {0};
  while(i<inpt.length()-1){
    if(isalpha(inpt.at(i)) && isalpha(inpt.at(i+1))) {
      //cout << inpt.substr(i,2) << endl;
      encryptDecryptPieces(inpt.substr(i,2));
      code += msg;
    }
    else {
      //cout << inpt.substr(i,2) << endl;
      code += inpt.substr(i,2);
    }

    i += 2;
  }

  if(last_char != '~') code += last_char;

  cout << "Encrypted message:" << code << endl;
  return code;
}

string PlayFairCipher::decrypt() {
	cout << "Enter the message you want to decrypt: ";
   	getline(cin, inpt);
	//cout << "Entered message:" << inpt <<endl;

    toEncrypt = false;

    string mssge {};
    char last_char {'~'};
    inpt = toUpper(inpt);

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

  cout << "Decrypted message:" << mssge << endl;
  return mssge;
}

void PlayFairCipher::encryptDecryptPieces(string message) {
    int j,k,p,q;
	string nmsg {};

    getText( msg, true, toEncrypt );
    msg = message;
    int dir = (toEncrypt)? 1: -1;

	for( string::const_iterator it = msg.begin(); it != msg.end(); it++ ) {
        if( getPos( *it++, j, k ))
	        if( getPos( *it, p, q)) {
	            //for same row
	            if( j == p ) {
	               nmsg+= getChar( j, k + dir );
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

void PlayFairCipher::getText( string t, bool m, bool e ) {
    for( string::iterator it = t.begin(); it != t.end(); it++ ) {
        //to choose J = I or no Q in the alphabet.
        *it = toupper( *it );
        if( *it < 65 || *it > 90 )
            continue;
        if( *it == 'J' && m )
            *it = 'I';
        else if( *it == 'Q' && !m )
            continue;
        msg += *it;
      }

      if( e ) {
        string nmsg = ""; size_t len = msg.length();
        for( size_t x = 0; x < len; x += 2 ) {
            nmsg += msg[x];
            if( x + 1 < len ) {
               if( msg[x] == msg[x + 1] ) nmsg += 'X';
               nmsg += msg[x + 1];
            }
        }
        msg = nmsg;
      }

      if( msg.length() & 1 )
      msg += 'X';
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
	cout << "DEncryptor\n" << endl;
	cout << "--------------------------------------------------------------------" << endl;

	int choice {0};
	int process {0};
	do {
	cout << "\nWhich cipher do you want to use?" << endl;
	cout << "1 - Caesar cipher \n2 - Vigenere Cipher" << endl;
	cout << "3 - Alberti's Disk Cipher\n4 - Playfair Cipher\n" << endl;
	cout << "Enter choice:";
	cin >> choice;

	cout << "\nDo you want to encrypt or decrpyt?" << endl;
	cout << "0 - Encrypt \n1 - Decrypt" << endl;
	cout << "Enter choice:";
	cin >> process;

	} while((choice < 1 || choice > 4) && (process == 0 || process == 1 ));

    cin.sync(); // Clear buffer

	switch(choice) {
		case 1: cout << "--------------------------------------------------------------------" << endl;
			    cout << "Caesar Cipher\n" << endl;
                {
                    CaesarCipher DE1(5);  // Shift = 5
                    if(process)
                    	DE1.decryptText();
                    else
                    	DE1.encryptText();

                }
			    break;

		case 2: cout << "--------------------------------------------------------------------" << endl;
			    cout << "Vigenere Cipher\n" << endl;
			    {
                    VigenereCipher DE2("BLACKBOX");
                    if(process)
                    	DE2.decryptText();
                    else
                    	DE2.encryptText();
			    }
			    break;

		case 3: cout << "--------------------------------------------------------------------" << endl;
    			cout << "Alberti's Disk Cipher\n" << endl;
                {
                    AlbertiDiskCipher DE3;
                    if(process)
                    	DE3.decryptText();
                    else
                    	DE3.encryptText();

                }
    			break;

		case 4: cout << "--------------------------------------------------------------------" << endl;
			    cout << "Playfair Cipher\n" << endl;
			    {
                    PlayFairCipher pf("cool");
                    if(process)
                    	pf.decrypt();
                    else
                    	pf.encrypt();
			    }
			    break;

		default:cout << "Something went wrong!" << endl;
	}

	// cout << "--------------------------------------------------------------------" << endl;

 //    cout << "Morse Code\n" << endl;
 //    MorseCode Morse;
 //    Morse.convertToMorseCode();
 //    Morse.convertFromMorseCode();
 //    cout << "--------------------------------------------------------------------" << endl;

    // cout << " Press any key to exit..." << endl;
    // getchar();   //wait until any key is pressed
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
// EOF

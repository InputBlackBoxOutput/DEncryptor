/**
* @file
* @author  Rutuparn Pawar <https://github.com/InputBlackBoxOutput>
* @version 1.0
*
* @section LICENSE
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*
*/

/*! @mainpage DEncryptor
# DEncryptor
Encryptor and decryptor for those whose want additional data security

## Usage
### Using in interactive mode
Run <code>DEncryptor.exe</code> and enter relevant information when prompted.

### Using in the non-interactive mode
To encrypt a file using default settings:

<code> DEncryptor.exe -e Filename.ext </code>

To decrypt a file encrypted using default settings:

<code> DEncryptor.exe -d Filename.ext </code>

#### Options available in the non-interactive mode:
<dl>
	<dt>-e <filename></dt>
    <dd> Encrypt the specified file</dd>
	<dt>-d <filename></dt>
    <dd> Decrypt the specified file</dd>
	<dt>-c <Option></dt>
    <dd> Set the cipher to use. <p>Default cipher is 'Caesar cipher' </p>

    |Cipher|Option|
    |--|--|
    |4-Level Envelope |E|
    |Caesar cipher|C|
    |Vigenere's cipher|V|
    |Alberti's disk cipher|A|
    |Playfair cipher |P|

    </dd>
	<dt>-o <filename></dt>
    <dd> Specify output file
          <p>Default output file is named 'outfile'</p>
          <p>Use 'console' as file name to print output on console </p>
    </dd>
  <dt>- i</dt>
    <dd>Use in interactive mode</dd>
</dl>

## Disclaimer:
*This application has not been designed to deal with highly sensitive data.

*Under no circumstances will the creator/s of this application be held responsible or liable in any way for any claims, damages, losses, expenses, costs or liabilities whatsoever (including, without limitation, any direct or indirect damages for loss of profits, business interruption or loss of information) resulting or arising directly or indirectly from your use of or inability to use this application even if the creator/s of this application have been advised of the possibility of such damages in advance.

## License
GNU Lesser General Public License v3.0

## Copyright 2020 Rutuparn Pawar <InputBlackBoxOutput>

*/

//////////////////////////////////////////////////////////////////////////////////////////
#include "DEncryptor1.h"
//#include "DEncryptor2.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>

using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
/**
Prompts the user for a keyword.
@note A keyword is required for some ciphers
@returns Keyword fetched from user
*/
string getKeyword() {
    string keyword {};
    cout << "Enter keyword: ";
    cin >> keyword;
    cin.sync(); // Clear buffer
    return keyword;
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
Prompts the user for a shift.
Conditions:
c => Caesar cipher
a => Alberti's disk cipher

@note A shift is required for some ciphers
@param condition Sets the condition to be checked
@returns Shift fetched from user
*/

int getShift(char condition) {
    int shift {};

    switch(condition){
        case 'c': do {
                    cout << "Enter shift: ";
                    cin >> shift;
                    if(shift < 0) cout << "Shift cannot be negative" << endl;
                }while(shift < 0);
                break;

        case 'a': do {
                    cout << "Enter shift: ";
                    cin >> shift;
                    if(shift >= 26) cout << "Shift should be less than 26" << endl;
                    if(shift < 0) cout << "Shift cannot be negative " << endl;
                }while(shift >= 26 || shift < 0);
                break;

        default: shift = 0;
    }
    cin.sync(); // Clear buffer
    return shift;
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
Prints cipher headers when in interactive mode.
@param cipher Name of the cipher
*/
void printCipherHeader(const string cipher) {
    cout << "\n------------------------------------------------------------------------" << endl;
    cout << cipher << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
/**
To deal with files that do not have a new line at the end
@param filename Name of the file which does not have EOL at the EOF
@attention Not implemented yet. Do not use!
*/
void extendFile(const string filename) {
    ofstream fout;
    fout.open(filename, ios::app);
    while(fout) {
         fout << " " << endl;
         break;
     }
    fout.close();
    return;
}

//////////////////////////////////////////////////////////////////////////////////////////
/**
Provides four-level envelope encryption/decryption
@param isInteractive Sets whether operations need to be done in interactive mode
@param toEncrypt Sets whether to encrypt or decrypt
@param infile Name of the file to be read
@param outfile Name of the file where o/p should be written
@returns Returns 0 upon success
*/
int envelope4(bool isInteractive, bool toEncrypt=NULL, const string infile="", const string outfile=""){
    string keyword = getKeyword();
    const int shift = keyword.at(0)%5;

    // Uncomment the following for testing
    //string keyword = "WORD";
    //const int shift = keyword.at(0)%5;

    //cout << "\nKeyword:" << keyword  << endl;
    //cout << "Shift:" << shift << endl;

    string oupt {};
    string inpt {};

    if(isInteractive) {
        if(!toEncrypt)
            cout << "Encrypted text: ";
        else
            cout << "Text: ";

        getline(cin, inpt);
    }

    ifstream fin;
    if(infile != "")
        fin.open(infile);

    ofstream fout;
    if(outfile != "")
        fout.open(outfile);


    CaesarCipher CS = CaesarCipher(shift);
    VigenereCipher VC = VigenereCipher(keyword);
    AlbertiDiskCipher ADC = AlbertiDiskCipher(shift);
    PlayFairCipher PFC = PlayFairCipher(keyword);


    if(toEncrypt) {
    	if(infile == "") {
            oupt = CS.encryptText(inpt, false);
	        oupt = VC.encryptText(oupt, false);
	        oupt = PFC.encrypt(oupt, false);
	        oupt = ADC.encryptText(oupt, false);

    	}
       	else {
       		while(fin) {
            getline(fin, inpt);

            oupt = CS.encryptText(inpt, false);
	        oupt = VC.encryptText(oupt, false);
	        oupt = PFC.encrypt(oupt, false);
	        oupt = ADC.encryptText(oupt, false);

            if(outfile != "")
                fout << oupt << endl;
        	}
       	}


    }
    else {
    	if(infile == "") {
            oupt = ADC.decryptText(inpt, false);
            oupt = PFC.decrypt(oupt, false);
	        oupt = VC.decryptText(oupt, false);
	        oupt = CS.decryptText(oupt, false);

    	}
    	else {
    		while(fin) {
            getline(fin, inpt);

            oupt = ADC.decryptText(inpt, false);
            oupt = PFC.decrypt(oupt, false);
	        oupt = VC.decryptText(oupt, false);
	        oupt = CS.decryptText(oupt, false);

            if(outfile != "")
                fout << oupt << endl;
        	}
    	}

    }

    if(isInteractive) {
        if(!toEncrypt)
            cout << "Text: " << oupt << endl;
        else
            cout << "Encrypted text: " << oupt << endl;
    }
    return 0;
}

// Uncomment the following for testing 4-level envelope encryption/decryption
/*
int main() {

    // Interactive
    //envelope4(true, true);
    //envelope4(true, false);

    // Non-interactive
    envelope4(false, true, "test/randomText.txt", "test/Eout.txt");
    envelope4(false, false, "test/Eout.txt", "test/Dout.txt");
    return 0;
}*/

//////////////////////////////////////////////////////////////////////////////////////////
/**
Reads text form a file/CLI, encryts/decrypts and then gives output by writing to a file or printing on CLI.
@param isInteractive Sets whether operations need to be done in interactive mode
@param cipher Sets the cipher to use
@param toEncrypt Sets whether to encrypt or decrypt
@param infile Name of the file to be read
@param outfile Name of the file where o/p should be written
@returns Returns 0 upon success
@note Does all the managing work
*/
int processStuff(bool isInteractive, int cipher=0, bool toEncrypt=NULL, const string infile="", const string outfile="") {

    if(isInteractive == true) {
        cout << "------------------------------------------------------------------------" << endl;
        cout << "   DEncryptor" << endl;
        cout << "------------------------------------------------------------------------" << endl;

        do {
            cout << "\nWhich cipher do you want to use?" << endl;
            cout << "1 - Caesar cipher \n2 - Vigenere Cipher" << endl;
            cout << "3 - Alberti's Disk Cipher\n4 - Playfair Cipher" << endl;
            cout << "5 - Envelope\n" << endl;
            cout << "Enter choice:";
            cin >> cipher;
            if(cipher < 1 || cipher > 5) cout << "Please enter a valid choice!\n" << endl;
        } while(cipher < 1 || cipher > 5);

        do {
            cout << "\nDo you want to encrypt or decrpyt?" << endl;
            cout << "0 - Encrypt \n1 - Decrypt\n" << endl;
            cout << "Enter choice:";
            cin >> toEncrypt;
            if(!(toEncrypt == 0 || toEncrypt == 1)) cout << "Please enter a valid choice!\n" << endl;
        }while(!(toEncrypt == 0 || toEncrypt == 1));

        cin.sync(); // Clear buffer
    }


    ifstream fin;
    if(infile != "")
        fin.open(infile);

    ofstream fout;
    if(outfile != "")
        fout.open(outfile);

    string line {}, code {} ,message {};

    switch(cipher) {
        case 1:{
                    if(isInteractive == true) {
                        printCipherHeader("Caesar Cipher");
                        CaesarCipher CC(getShift('c'));
                        if(toEncrypt)
                            CC.decryptText();
                        else
                            CC.encryptText();
                    }
                    else {
                        CaesarCipher CC(getShift('c'));
                        if(toEncrypt)
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << CC.encryptText(line, false) << endl;
                                else
                                    cout << CC.encryptText(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << CC.decryptText(line, false) << endl;
                                else
                                    cout << CC.decryptText(line, false) << endl;
                            }
                    }
               }
               break;

        case 2:{
                    if(isInteractive == true) {
                        printCipherHeader("Vigenere's Cipher");
                        VigenereCipher VC(getKeyword());
                        if(toEncrypt)
                            VC.decryptText();
                        else
                            VC.encryptText();
                    }
                    else {
                        VigenereCipher VC(getKeyword());
                        if(toEncrypt)
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << VC.encryptText(line, false) << endl;
                                else
                                    cout << VC.decryptText(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << VC.decryptText(line, false) << endl;
                                else
                                    cout << VC.decryptText(line, false) << endl;
                            }
                    }
               }
               break;

        case 3:{
                    if(isInteractive == true) {
                        printCipherHeader("Alberti's Disk Cipher");
                        AlbertiDiskCipher ADC(getShift('a'));
                        if(toEncrypt)
                            ADC.decryptText();
                        else
                            ADC.encryptText();

                    }
                    else {
                        AlbertiDiskCipher ADC(getShift('a'));
                        if(toEncrypt)
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << ADC.encryptText(line, false) << endl;
                                else
                                    cout << ADC.decryptText(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << ADC.decryptText(line, false) << endl;
                                else
                                    cout << ADC.decryptText(line, false) << endl;
                            }
                    }

               }
               break;

        case 4:{
                    if(isInteractive == true) {
                        printCipherHeader("Playfair Cipher");
                        PlayFairCipher PF(getKeyword());
                        if(toEncrypt)
                            PF.decrypt();
                        else
                            PF.encrypt();
                    }
                    else {
                        PlayFairCipher PF(getKeyword());
                        if(toEncrypt)
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << PF.encrypt(line, false) << endl;
                                else
                                    cout << PF.decrypt(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
                                if(outfile != "")
                                    fout << PF.decrypt(line, false) << endl;
                                else
                                    cout << PF.decrypt(line, false) << endl;
                            }
                    }

               }
               break;

        case 5: envelope4(true, !toEncrypt); // toEncrypt logic inverted since 0 => Encrypt
               break;

        default: cout << "Something went wrong!" << endl;
    }


    if(isInteractive == true) {
        cout << "------------------------------------------------------------------------" << endl;
        cout << "Press any key to exit..." << endl;
        getchar();   //wait until any key is pressed
    }
    else
        fin.close();

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////
/** Use for testing all ciphers at once.
@attention Requires files in the test folder
*/
void testCiphers() {
    cout << "Caesar Cipher" << endl;
    cout << "----------Encrypt-----------" << endl;
    processStuff(false, 1, true, "test/testText.txt");
    cout << "----------Dencrypt----------" << endl;
    processStuff(false, 1, false, "test/caesarText.txt");

    cout << "Vigenere's Cipher" << endl;
    cout << "----------Encrypt-----------" << endl;
    processStuff(false, 2, true, "test/testText.txt");
    cout << "----------Dencrypt----------" << endl;
    processStuff(false, 2, false, "test/vigenereText.txt");

    cout << "Alberti's Disk Cipher" << endl;
    cout << "----------Encrypt-----------" << endl;
    processStuff(false, 3, true, "test/testText.txt");
    cout << "----------Dencrypt----------" << endl;
    processStuff(false, 3, false, "test/albertiText.txt");

    cout << "Playfair Cipher" << endl;
    cout << "----------Encrypt-----------" << endl;
    processStuff(false, 4, true, "test/testText.txt");
    cout << "----------Dencrypt----------" << endl;
    processStuff(false, 4, false, "test/playfairText.txt");
}

//////////////////////////////////////////////////////////////////////////////////////////
void showHelp() {
    cout << "Help has not been written into the application yet.\nApologies for the inconvenience :-(" << endl;
    cout << "\nFor help see https://github.com/InputBlackBoxOutput/DEncryptor" << endl;
    cout << "\nDesigned and developed by Rutuparn Pawar <InputBlackBoxOutput>" << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){
    bool toReturn {false};
    string cipher {"C"}, infile {}, outfile {"outfile.txt"};
    bool toEncrypt {false};

    if(argc == 1) {
         // Interactive mode
        processStuff(true);
        return 0;
    }
    else {
        int opt;

        while((opt = getopt(argc, argv, ":io:c:e:d:h")) != -1) {

            switch(opt) {
                case 'i': processStuff(true); toReturn=true; break;

                case 'e': if(infile.length() == 0) {
                                infile = optarg;
                                toEncrypt = true;
                            }
                          else{
                            cout << "Only one operation can be performed at a time";
                            toReturn=true;
                          }  break;

                case 'd': if(infile.length() == 0) {
                                infile = optarg;
                            }
                          else{
                            cout << "Only one operation can be performed at a time";
                            toReturn=true;
                          }  break; break;

                case 'c': if(string(optarg).length() == 1)
                            cipher = optarg;
                          else{
                            cout << "Invalid option for cipher";
                            toReturn=true;
                          }
                        break;

                case 'o': outfile = string(optarg); if(!string(outfile).compare("console")) outfile =""; break;

                case 'h': showHelp(); toReturn=true; break;

                // \nUsage: DEncryptor.exe [-i/-o/-c/-e/-d] [filename]
                case ':': cout << "\nSee help using \'-h\' option\n"; break;

                case '?': cout << "\nInvalid option: " << (char)optopt << "\n See all options using \'DEncryptor.exe -h\'"<< endl; break;
            }
        }

        if(toReturn == true) return 0;

        cout << "Processing file: " << infile << endl;

        // Add a new line at the end of file
		if(toEncrypt == true)
            extendFile(infile);

        cout << "Using Cipher: ";

        if(!cipher.compare("C")) {
            cout << "Caesar Cipher" << endl;
            processStuff(false, 1, toEncrypt, infile, outfile);
        }
        else if(!cipher.compare("V")) {
            cout << "Vigenere Cipher" << endl;
            processStuff(false, 2, toEncrypt, infile, outfile);
        }
        else if(!cipher.compare("A")) {
            cout << "Alberti's Disk Cipher" << endl;
            processStuff(false, 3, toEncrypt, infile, outfile);
        }
        else if(!cipher.compare("P")) {
            cout << "Playfair Cipher" << endl;
            processStuff(false, 4, toEncrypt, infile, outfile);
        }
        else if(!cipher.compare("E")) {
            cout << "Envelope" << endl;
            envelope4(false, toEncrypt, infile, outfile);
        }

        cout << "Done" << endl;

    }

    return 0;

}

//////////////////////////////////////////////////////////////////////////////////////////
/*
void testNewCiphers(void) {

    int cipher {1};
    int toEncrypt {0};

    cout << "------------------------------------------------------------------------" << endl;
    cout << "   DEncryptor" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    do {
        cout << "\nWhich cipher do you want to use?" << endl;
        cout << "1 - XOR cipher \n2 - Hill Cipher" << endl;
        cout << "3 - Transposition Cipher\n4 - Null Cipher\n" << endl;
        cout << "Enter choice:";
        cin >> cipher;
        if(cipher < 1 || cipher > 4) cout << "Please enter a valid choice!\n" << endl;
    } while(cipher < 1 || cipher > 4);

    do {
        cout << "\nDo you want to encrypt or decrpyt?" << endl;
        cout << "0 - Encrypt \n1 - Decrypt\n" << endl;
        cout << "Enter choice:";
        cin >> toEncrypt;
        if(!(toEncrypt == 0 || toEncrypt == 1)) cout << "Please enter a valid choice!\n" << endl;
    }while(!(toEncrypt == 0 || toEncrypt == 1));

    cin.sync(); // Clear buffer


    string user_input {}, user_output {};
    cout << "Input: ";
    getline(cin, user_input);

    switch(cipher) {
        case 1:{
                    printCipherHeader("XOR Cipher");
                    XOR_Cipher XC((char)getShift('c'));                 // Modify getShift to get char
                     if(toEncrypt)
                        user_output = XC.decryptText(user_input);
                    else
                        user_output = XC.encryptText(user_input);
               }
               break;

        case 2:{
                    printCipherHeader("Hill Cipher");
                    HillCipher HC(getKeyword());
                    if(toEncrypt)
                        user_output = HC.decryptText(user_input);
                    else
                        user_output = HC.encryptText(user_input);
               }
               break;

        case 3:{
                    printCipherHeader("Transposition Cipher");
                    TranspositionCipher TC(getKeyword());
                    if(toEncrypt)
                        user_output = TC.decryptText(user_input);
                    else
                        user_output = TC.encryptText(user_input);
                }
                break;

        case 4:{
                    printCipherHeader("Null Cipher");
                    NullCipher NC;
                    if(toEncrypt)
                        user_output = NC.decryptText(user_input);
                    else
                        user_output = NC.encryptText(user_input);
               }
               break;

        default: cout << "Something went wrong!" << endl;
    }

    cout << "Output: " << user_output << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Press any key to exit..." << endl;
    getchar();   //wait until any key is pressed

}
*/

// int main() {
//     testNewCiphers();
//     return 0;
// }
//////////////////////////////////////////////////////////////////////////////////////////
// EOF

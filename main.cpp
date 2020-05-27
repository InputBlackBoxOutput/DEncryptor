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

//////////////////////////////////////////////////////////////////////////////////////////
#include "DEncryptor.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////
string getKeyword() {
    string keyword {};
    cout << "Enter keyword: ";
    cin >> keyword;
    cin.sync(); // Clear buffer
    return keyword;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// Values for condition:
// c => Caesar cipher
// a => Alberti's disk cipher

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

///////////////////////////////////////////////////////////////////////////////////////////////////////
void printCipherHeader(const string cipher) {
    cout << "\n------------------------------------------------------------------------" << endl;
    cout << cipher << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// To deal with files do not have a new line at the end
int extendFile(const string filename) {
    ofstream fout;
    fout.open(filename, ios::app);

    while(fout) {
        fout << "End of File\n" << endl;
        break;
    }
    fout.close();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
int processStuff(bool isInteractive, int cipher=0, bool toEncrypt=NULL, const string filename="") {

    if(isInteractive == true) {
        cout << "------------------------------------------------------------------------" << endl;
        cout << "   DEncryptor" << endl;
        cout << "------------------------------------------------------------------------" << endl;

        do {
            cout << "\nWhich cipher do you want to use?" << endl;
            cout << "1 - Caesar cipher \n2 - Vigenere Cipher" << endl;
            cout << "3 - Alberti's Disk Cipher\n4 - Playfair Cipher\n" << endl;
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
    }


    ifstream fin;
    if(filename != "")
         fin.open(filename);

    // ofstream fout;
    // if(filename != "")
    //      fin.open("out" + filename);

    string line {};
    string code {};
    string message {};

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
                                cout << CC.encryptText(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
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
                                cout << VC.encryptText(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
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
                                cout << ADC.encryptText(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
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
                                cout << PF.encrypt(line, false) << endl;
                            }
                        else
                            while(fin) {
                                getline(fin, line);
                                cout << PF.decrypt(line, false) << endl;
                            }
                    }

               }
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
int main(int argc, char* argv[]){
    // Alberti's disk cipher : When dealing with files the first word in a line not decrypting correctly!
    // testCiphers();

    // Interactive mode
    processStuff(true);

    // The following needs to be tested
    //extendFile("test/randomText.txt");

}

//////////////////////////////////////////////////////////////////////////////////////////
// EOF

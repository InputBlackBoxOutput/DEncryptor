#include <iostream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "inc/alberti_disk.h"
#include "inc/caesar.h"
#include "inc/playfair.h"
#include "inc/vigenere.h"


/**
 This class provides all functionalities related with text input and output.
*/

class UserInterface
{
public:
	/**
     Prompts the user for message
     @returns Message
    */
	string getMessageFromUser()
	{
		string msg;
		cout << "Enter the message you want to encrypt: ";
		getline(cin, msg);
		return msg;
	}

	/**
     Prints encrypted message on the terminal
     @param code Encrypted message
    */
	void printCode(string code){
		cout << "Encrypted message:" << code << endl;
	}

	/**
     Prompts the user for encrypted message
     @returns Encrypted message
    */
	string getCodeFromUser()
	{
		string code;
		cout << "Enter the message you want to decrypt: ";
		getline(cin, code);
		return code;
	}
	/**
     Prints decrypted message on the terminal
     @param msg Decrypted message
    */
	void printMessage(string msg)
	{
		cout << "Decrypted message:" << msg << endl;
	}

	/**
    Prompts the user for a keyword.
    @note A keyword is required for some ciphers
    @returns Keyword fetched from user
    */
    string getKeyword()
    {
        string keyword{};
        cout << "Enter keyword: ";
        cin >> keyword;
        cin.sync(); // Clear buffer
        return keyword;
    }

    /**
    Prompts the user for a shift.
    Conditions:
    c => Caesar cipher
    a => Alberti's disk cipher

    @note A shift is required for some ciphers
    @param condition Sets the condition to be checked
    @returns Shift fetched from user
    */

    int getShift(char condition)
    {
        int shift{};

        switch (condition)
        {
        case 'c':
            do
            {
                cout << "Enter shift: ";
                cin >> shift;
                if (shift < 0)
                    cout << "Shift cannot be negative" << endl;
            } while (shift < 0);
            break;

        case 'a':
            do
            {
                cout << "Enter shift: ";
                cin >> shift;
                if (shift >= 26)
                    cout << "Shift should be less than 26" << endl;
                if (shift < 0)
                    cout << "Shift cannot be negative " << endl;
            } while (shift >= 26 || shift < 0);
            break;

        default:
            shift = 0;
        }
        cin.sync(); // Clear buffer
        return shift;
    }

    /**
    Prints cipher headers with graphic
    @param cipher Name of the cipher
    */
    void printCipherHeader(const string cipher)
    {
        cout << "\n------------------------------------------------------------------------" << endl;
        cout << cipher << endl;
    }

    /**
    Prints help
    */
    void showHelp()
    {
        cout << "\nFor help see https://github.com/InputBlackBoxOutput/DEncryptor" << endl;
        cout << "\nRutuparn Pawar [InputBlackBoxOutput]" << endl;
    }
};

UserInterface UI;

void interactive() {
    int cipher {};
    int process {};

    cout << "------------------------------------------------------------------------" << endl;
    cout << "   DEncryptor" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    do
    {
        cout << "\nWhich cipher do you want to use?" << endl;
        cout << "1 - Caesar cipher \n2 - Vigenere Cipher" << endl;
        cout << "3 - Alberti's Disk Cipher\n4 - Playfair Cipher\n" << endl;
        cout << "Enter choice:";
        cin >> cipher;
        if (cipher < 1 || cipher > 4)
            cout << "Please enter a valid option\n" << endl;
    } while (cipher < 1 || cipher > 5);

    do
    {
        cout << "\nDo you want to encrypt or decrpyt?" << endl;
        cout << "0 - Encrypt \n1 - Decrypt\n"<< endl;
        cout << "Enter choice:";
        cin >> process;
        if (!(process == 0 || process == 1))
            cout << "Please enter a valid choice\n" << endl;
    } while (!(process == 0 || process == 1));

    cin.sync(); // Clear buffer

    if(process) {
        string code = UI.getCodeFromUser();

        switch(cipher) {
            case 1:{
                CaesarCipher c(UI.getShift('c'));
                UI.printMessage(c.decryptText(code));
                break;
            }
            case 2:{
                VigenereCipher v(UI.getKeyword());
                UI.printMessage(v.decryptText(code));
                break;
            }
            case 3:{
                AlbertiDiskCipher a(UI.getShift('a'));
                UI.printMessage(a.decryptText(code));
                break;
            }
            case 4:{
                PlayFairCipher p(UI.getKeyword());
                UI.printMessage(p.decryptText(code));
                break;
            }
        }
    }
    else {
        string msg = UI.getMessageFromUser();

        switch(cipher) {
            case 1:{
                CaesarCipher c(UI.getShift('c'));
                UI.printCode(c.encryptText(msg));
                break;
            }
            case 2:{
                VigenereCipher v(UI.getKeyword());
                UI.printCode(v.encryptText(msg));
                break;
            }
            case 3: {
                AlbertiDiskCipher a(UI.getShift('a'));
                UI.printCode(a.encryptText(msg));
                break;
            }
            case 4: {
                PlayFairCipher p(UI.getKeyword());
                UI.printCode(p.encryptText(msg));
                break;
            }
        }

    }


}

void testCiphers(){
    AlbertiDiskCipher a(5);

    cout << a.encryptText("Apple") << endl;
    cout << a.decryptText(a.encryptText("Apple")) << endl;

    CaesarCipher c(5);

    cout << c.encryptText("Apple") << endl;
    cout << c.decryptText(c.encryptText("Apple")) << endl;

    PlayFairCipher pf("Key");

    cout << pf.encryptText("Apple") << endl;
    cout << pf.decryptText(pf.encryptText("Apple")) << endl;


    VigenereCipher v("Key");

    cout << v.encryptText("Apple") << endl;
    cout << v.decryptText(v.encryptText("Apple")) << endl;
}


int main(int argc, char *argv[])
{
    interactive();
    //testCiphers();

    cout << "Press any key to exit" << endl;
    getchar();
    return 0;
}

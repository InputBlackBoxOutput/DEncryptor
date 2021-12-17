#include "../inc/vigenere.h"

void VigenereCipher::createVigeneresSquare()
{
    int offset{0};

    for (int i = 0; i < 26; i++)
    {
        offset = i;
        for (int j = 0; j < 26 - i; j++)
        {
            vigenereSquare[i][j] = (char)(65 + offset);
            offset++;
        }

        offset = 0;
        for (int k = i; k > 0; k--)
        {
            vigenereSquare[i][26 - k] = (char)(65 + offset);
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
string VigenereCipher::encryptText(string msg)
{
    string code{};

    unsigned int iter{0};
    toUpper(msg);
    toUpper(keyword);

    for (unsigned int i = 0; i < msg.length(); i++)
    {

        if (isalpha(msg.at(i)))
        {

            code += vigenereSquare[index.find(keyword.at(iter))][index.find(msg.at(i))];
            iter++;

            if (iter >= keyword.length())
                iter = 0;
        }
        else
            code += msg.at(i);
    }

    return code;
}

//////////////////////////////////////////////////////////////////////////////////////////
string VigenereCipher::decryptText(string code)
{
    string msg{};

    unsigned int iter{0};
    int loc;
    toUpper(code);
    toUpper(keyword);

    for (unsigned int i = 0; i < code.length(); i++)
    {

        if (isalpha(code.at(i)))
        {
            loc = index.find(keyword.at(iter));
            iter++;

            if (iter >= keyword.length())
                iter = 0;

            for (unsigned int j = 0; j < 26; j++)
            {
                if (vigenereSquare[loc][j] == code.at(i))
                    msg += index.at(j);
            }
        }
        else
            msg += code.at(i);
    }
    return msg;
}

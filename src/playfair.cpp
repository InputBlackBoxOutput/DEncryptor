#include "../inc/playfair.h"

string PlayFairCipher::encryptText(string inpt)
{
    string code{};

    toEncrypt = true;
    char last_char{'~'};
    toUpper(inpt);

    if (inpt.length() != 0)
    {

        if (inpt.length() % 2 != 0)
        {
            last_char = inpt.at(inpt.length() - 1);
            inpt.erase(inpt.length() - 1);
        }

        size_t i{0};
        while (i < inpt.length() - 1)
        {
            if (isalpha(inpt.at(i)) && isalpha(inpt.at(i + 1)))
            {
                encryptDecryptPieces(inpt.substr(i, 2));
                code += msg;
            }
            else
            {
                code += inpt.substr(i, 2);
            }
            i += 2;
        }

        if (last_char != '~')
            code += last_char;
    }

    return code;
}

string PlayFairCipher::decryptText(string inpt)
{
    string mssge{};

    toEncrypt = false;
    char last_char{'~'};
    toUpper(inpt);

    if (inpt.length() != 0)
    {
        if (inpt.length() % 2 != 0)
        {
            last_char = inpt.at(inpt.length() - 1);
            inpt.erase(inpt.length() - 1);
        }
        size_t i{0};
        while (i < inpt.length() - 1)
        {
            if (isalpha(inpt.at(i)) && isalpha(inpt.at(i + 1)))
            {
                encryptDecryptPieces(inpt.substr(i, 2));
                mssge += msg;
            }
            else
            {
                mssge += inpt.substr(i, 2);
            }
            i += 2;
        }

        if (last_char != '~')
            mssge += last_char;
    }

    return mssge;
}

void PlayFairCipher::encryptDecryptPieces(string message)
{
    int j, k, p, q;
    string nmsg{};

    msg = message;

    // Sanitize text to deal with J
    for (size_t i = 0; i < message.length(); i++)
    {
        if (message.at(i) < 65 || message.at(i) > 90)
            continue;
        if (message.at(i) == 'J')
        {
            //message.at(i) = 'I';
            msg = message;
            return;
        }
    }

    msg = message;
    int dir = (toEncrypt) ? 1 : -1;

    for (string::const_iterator it = msg.begin(); it != msg.end(); it++)
    {
        if (getPos(*it++, j, k))
            if (getPos(*it, p, q))
            {
                //for same row
                if (j == p)
                {
                    nmsg += getChar(j, k + dir);
                    nmsg += getChar(p, q + dir);
                }
                //for same column
                else if (k == q)
                {
                    nmsg += getChar(j + dir, k);
                    nmsg += getChar(p + dir, q);
                }
                else
                {
                    nmsg += getChar(p, k);
                    nmsg += getChar(j, q);
                }
            }
        msg = nmsg;
    }
}

char PlayFairCipher::getChar(int a, int b)
{
    return n[(b + 5) % 5][(a + 5) % 5];
}

bool PlayFairCipher::getPos(char l, int &c, int &d)
{
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++)
            if (n[y][x] == l)
            {
                c = x;
                d = y;
                return true;
            }
    return false;
}

void PlayFairCipher::createEncoder(string key, bool m)
{
    if (key.length() < 1)
        key = "KEYWORD";
    key += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string s = "";
    for (string::iterator it = key.begin(); it != key.end(); it++)
    {
        *it = toupper(*it);
        if (*it < 65 || *it > 90)
            continue;
        if ((*it == 'J' && m) || (*it == 'Q' && !m))
            continue;
        if (s.find(*it) == -1)
            s += *it;
    }
    copy(s.begin(), s.end(), &n[0][0]);
}

void PlayFairCipher::displayGrid()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << n[i][j];
        }
        cout << endl;
    }
}

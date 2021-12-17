#include "../inc/alberti_disk.h"

string AlbertiDiskCipher::encryptText(string msg)
{
    string code{};

    shift = 0;
    srand(time(nullptr));
    toUpper(msg);
    for (unsigned int i = 0; i < msg.length(); i++)
    {
        if (isalpha(msg.at(i)))
            code += rotating.at((stationary.find(msg.at(i)) + shift) % 26);
        else
        {
            if ((int)msg.at(i) == ' ')
                code += '_';
            else
                code += msg.at(i);

            shift = rand() % 26;
            code += stationary.at(shift);
        }
    }

    return code;
}

//////////////////////////////////////////////////////////////////////////////////////////
string AlbertiDiskCipher::decryptText(string code)
{
    string msg{};

    shift = 0;
    for (unsigned int i = 0; i < code.length(); i++)
    {
        if (isalpha(code.at(i)) && isupper(code.at(i)))
        {
            shift = stationary.find(code.at(i));
            //cout << shift << endl;
            continue;
        }

        if (isalpha(code.at(i)))
        {
            if ((signed int)rotating.find(code.at(i)) - shift < 0)
                msg += stationary.at(26 + (rotating.find(code.at(i)) - shift));
            else
                msg += stationary.at((rotating.find(code.at(i)) - shift));
        }
        else
        {
            if ((int)code.at(i) == ' ')
                msg += " ";
            else
                msg += code.at(i);
        }
    }
    return msg;
}

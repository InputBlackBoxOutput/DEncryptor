#include "../inc/caesar.h"

string CaesarCipher::encryptText(string msg)
{
    string code{};

    toUpper(msg);
    for (unsigned int i = 0; i < msg.length(); i++)
    {
        if (isalpha(msg.at(i)))
        {
            if (msg.at(i) + shift > 90)
                code += (char)(65 + ((msg.at(i) + shift) % ('A' + 26)));
            else
                code += (char)(msg.at(i) + shift);
        }
        else if (isdigit(msg.at(i)))
        {
            if ((msg.at(i) + shift) < 58)
                code += (int)(msg.at(i) + shift);
            else
                code += (int)(48 + (msg.at(i) + shift) % 58);
        }
        else
            code += msg.at(i);
    }

    return code;
}

string CaesarCipher::decryptText(string code)
{
    string msg{};

    toUpper(code);
    for (unsigned int i = 0; i < code.length(); i++)
    {
        if (isalpha(code.at(i)))
        {
            if (code.at(i) - shift < 65)
                msg += (char)(90 - 65 + (code.at(i) - shift) + 1);
            else
                msg += code.at(i) - shift;
        }
        else if (isdigit(code.at(i)))
        {
            if (((int)code.at(i) - shift) >= 48)
                msg += ((int)code.at(i) - shift);
            else
                msg += (58 - (48 - ((int)code.at(i) - shift)));
        }
        else
            msg += code.at(i);
    }
    return msg;
}

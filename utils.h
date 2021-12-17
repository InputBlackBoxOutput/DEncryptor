#pragma once
#include <string>

using namespace std;

class Utils {
public:
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

};

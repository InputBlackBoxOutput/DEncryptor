#include <string>

using namespace std;

class Envelope {
public:
    Envelope(string kwrd){
        keyword = kwrd;
        shift = (int)keyword.at(0)%5;
    }

    string encryptText(string inpt) {
        CaesarCipher CS = CaesarCipher(shift);
        VigenereCipher VC = VigenereCipher(keyword);
        AlbertiDiskCipher ADC = AlbertiDiskCipher(shift);
        PlayFairCipher PFC = PlayFairCipher(keyword);

        string oupt = CS.encryptText(inpt);
        oupt = VC.encryptText(oupt);
        oupt = PFC.encryptText(oupt);
        oupt = ADC.encryptText(oupt);

        return oupt;
    }

    string decryptText(string inpt) {
        CaesarCipher CS = CaesarCipher(shift);
        VigenereCipher VC = VigenereCipher(keyword);
        AlbertiDiskCipher ADC = AlbertiDiskCipher(shift);
        PlayFairCipher PFC = PlayFairCipher(keyword);

        string oupt = ADC.decryptText(inpt);
        oupt = PFC.decryptText(oupt);
	    oupt = VC.decryptText(oupt);
	    oupt = CS.decryptText(oupt);

        return oupt;
    }

private:
    string keyword {};
    int shift {};
};

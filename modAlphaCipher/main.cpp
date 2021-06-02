#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
#include <codecvt>
using namespace std;

int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    bool isTrue = true;
    wstring mode,NeMode,wstr,wstr_key;

    do {
        cout << "Encode/Decode:";
        wcin >> mode;
        if (mode == L"Encode") {
            cout << "Строка для шифрования:";
            wcin.get();
            getline(wcin,wstr);
            cout << "Ключ:";
            getline(wcin,wstr_key);
            try {
                modAlphaCipher cipher(wstr_key);
                wstring cipherText = cipher.encrypt(wstr);
                wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
                cout<<codec.to_bytes(cipherText)<<endl;
            } catch (cipher_error & ex) {
                cout << "Error: "<<ex.what() << endl;
            }
        }
        if (mode == L"Decode") {
            cout << "Строка для расшифрования:";
            wcin.get();
            getline(wcin,wstr);
            cout << "Ключ:";
            getline(wcin,wstr_key);
            try {
                modAlphaCipher cipher(wstr_key);
                wstring OpenText = cipher.decrypt(wstr);
                wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
                cout<<codec.to_bytes(OpenText)<<endl;
            } catch (cipher_error & ex) {
                cout << "Error: "<<ex.what() << endl;
            }
        }
        if (mode == L"Выход") {
            isTrue = false;
            break;
        }
    } while (isTrue != false);
    return 0;
}
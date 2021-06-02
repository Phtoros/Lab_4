#include "PermutationCipher.h"
PermutationCipher::PermutationCipher(int key)
{
    this->k=key;
}
wstring PermutationCipher::CoderPermutationCipher(PermutationCipher w, wstring& s)
{
    wstring code;
    s=getValidOpenText(s);
    w.k=getValidKey(w.k,s);
    int h;
    if (s.size()%w.k!=0) {
        h=s.size()/w.k+1;
    } else {
        h=s.size()/w.k;
    }
    wchar_t a[h][w.k];
    int k=0;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w.k; j++) {
            if (k<s.size()) {
                a[i][j]=s[k];
                k++;
            } else a[i][j]=' ';
        }
    }
    for (int i=0; i<w.k; i++) {
        for (int j=0; j<h; j++) {
            code+=a[j][i];
        }
    }
    return code;
}
wstring PermutationCipher::DecoderPermutationCipher(PermutationCipher w, wstring& s)
{
    s=getValidOpenText(s);
    w=getValidKey(w.k,s);
    int h;
    if (s.size()%w.k!=0) {
        h=s.size()/w.k+1;
    } else {
        h=s.size()/w.k;
    }
    wchar_t a[h][w.k];
    int k=0;
    for (int i=0; i<w.k; i++) {
        for (int j=0; j<h; j++) {
            a[j][i]=s[k];
            k++;
        }
    }
    wstring decode;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w.k; j++) {
            decode+=a[i][j];
        }
    }
    return decode;
}
inline int PermutationCipher::getValidKey(const int k, const std::wstring & s)
{
    if (k<=0)
        throw cipher_error("Wrong key");
    else if (k>(s.size()/2))
        throw cipher_error("Ключ длиннее, чем длина текста");
    else
        return k;
}
inline std::wstring PermutationCipher::getValidOpenText(const std::wstring & s)
{
    std::wstring tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c))                {
                tmp.push_back(toupper(c));
            } else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Входной текст отсутствует");
    return tmp;
}

inline std::wstring PermutationCipher::getValidCipherText(const std::wstring & s)
{
    std::wstring tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c)) {
                tmp.push_back(toupper(c));
            } else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Выходной текст отсутствует");
    return tmp;
}

/**
* @file modAlphaCipher.h
* @author Корзин А.А.
* @version 1.0
* @brief Описание класса modAlphaCipher
* @date 02.06.2021
* @copyright ИБСТ ПГУ
*/

#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
using namespace std;
/**  @brief  Класс, реализующий шифрование сообщений методом "Гронсвельда"
*  @warning Предназначен для русскоязычных сообщений.
*/
class modAlphaCipher
{
private:
/// @brief  Алфавит для сообщений, который используется в данной программе
    std::wstring numAlpha = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
    /// @brief  Ассоциативный массив "номер по символу"
    std::map <char,int> alphaNum; //ассоциативный массив "номер по символу"
    /// @brief  Атрибут для ключа
    std::vector <int> key; //ключ
    /** @brief  Преобразование строки в вектор(чисел)
     * @details В вектор типа "int" с именем "result" формируются числа, являющиеся индексами алфавита "numAlpha" из строки, которая пришла на вход.
     * @code
     *  vector<int> result;
     *   for(auto c:s) {
     *       result.push_back(alphaNum[c]);
     *   }
     * @endcode
     * @return std::vector <int>, в котором хранятся индексы букв сообщения из алфавита
     */
    std::vector<int> convert(const std::wstring& s);//преобразование строка-вектор
    /** @brief Преобразование вектора(чисел) в строку
     *  @details В переменную типа "wstring" с именем "result" формируется строка по индексам алфавита "numAlpha".
     *  @code
     *  wstring result;
     *   for(auto i:v) {
     *       result.push_back(numAlpha[i]);
     *   }
     *  @endcode
     *  @return  "result" - строка текста типа "wstring"
     */
    std::wstring convert(const std::vector<int>& v);//преобразование вектор-строка
    /** @brief  Валидация ключа
     * @details Ключ проверяется на пустоту при помощи обычного условия. Если проверка закончилась успешно, то
     * ключ проверяется на наличие недопустимых символов. 
     * @warning Строчные буквы алфавита переводятся в прописные.
     * @param wstring s - ключ, который нужно проверить на наличие ошибок, в виде строки.
     * @throw cipher_error, если ключ является пустым или в нём присутствуют недопустимые символы
     * @return "result" - строка текста типа "wstring"
     */
    std::wstring getValidKey(const std::wstring & s);
    /** @brief  Валидация текста при шифровании или расшифровании
     *  @details Сначала текст проверяется на пустоту при помощи обычного условия. Если проверка закончилась успешно, то
     *  текст проверяется на наличие недопустимых символов. 
     *  @warning Строчные буквы алфавита переводятся в прописные.
     *  @param wstring s - строка текста для шифрования или расшифрования, которую нужно проверить на наличие ошибок
     *  @throw cipher_error, если текст является пустым или в нём присутствуют недопустимые символы
     *  @return строка текста типа "wstring"
     */
    std::wstring getValidText(const std::wstring & s);
public:
    //! Конструктор без параметоров.
    modAlphaCipher()=delete;//запретим конструктор без параметров
    /** @brief  Конструктор для ключа
      * @details Цикл for построен по строке-алфавиту и на каждом шаге добавляет в ассоциативный массив
      *  символ и его номер.
      * @code
      *     for (unsigned i=0; i<numAlpha.size(); i++) {
      *          alphaNum[numAlpha[i]]=i;
      *      }
      * @endcode
      * @param строка текста типа "wstring"
      */ 
    modAlphaCipher(const std::wstring& skey); //конструктор для установки ключа
    /**
     * @brief Метод, который предназначен для зашифрования
     * @details Формируется вектор work из строки открытого текста с помощью метода
     *   convert().  Происходит проверка текста на наличие ошибки при помощи метода getValidAlphabetText().
     *  @code
     *       vector<int> work = convert(getValidAlphabetText(open_text));
     * @endcode
     *  В цикле к каждому элементу вектора прибавляется элемент ключа по модулю размера
     *   алфавита. Если ключ короче текста, то при индексации ключа выполняется операция
     *   по модулю размера ключа. 
     *  @code
     *   for(unsigned i=0; i < work.size(); i++) {
     *      work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
     *   }
     * @endcode
     * При возврате значения, вектор work опять преобразуется в строку.
     * @param wstring open_text - сообщение, которое нужно зашифровать
     * @throw cipher_error - строка, которая пришла на вход оказывается пустой или в ней есть недопустимые символы
     * @return строка зашифрованного текста типа "wstring"
     */
    std::wstring encrypt(const std::wstring& open_text); //зашифрование
    /**
     * @brief Метод, который предназначен для расшифрования
     * @details Формируется вектор work из строки  зашифрованного текста с помощью метода
     *   convert().  А также происходит проверка зашифрованного текста на наличие ошибки при помощи метода getValidAlphabetText().
     *  @code
     *       vector<int> work = convert(getValidAlphabetText(cipher_text));
     * @endcode
     *  Если при зашифровывании мы прибавляли значение ключа, то при расшифровывании значения ключа надо вычитать. А чтобы не
     *  получить отрицательных значений, выполняется еще прибавление значения модуля, так как такое
     *  прибавление не влияет на результат модулю.
     *  @code
     *   for(unsigned i=0; i < work.size(); i++) {
     *           work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
     *   }
     * @endcode
     *
     *@param wstring cipher_text - сообщение, которое нужно расшифровать
     * @throw cipher_error - строка, которая  пришла на вход оказывается пустой или в ней есть недопустимые символы
     * @return  строка расшифрованного текста типа "wstring"
     */
    std::wstring decrypt(const std::wstring& cipher_text);//расшифрование
};

//! @class cipher_error - класс предназначенный для возбуждения исключений.
class cipher_error: public std::invalid_argument
{
public:
    explicit cipher_error (const std::string& what_arg): 
        std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
        std::invalid_argument(what_arg) {}
};

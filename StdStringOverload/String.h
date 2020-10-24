#ifndef STRING_H
#define STRING_H

#include<Char.h>
#include<iostream>
#include<list>



class String
{
public:

    enum CaseSensitivity{
        CaseInsensitive,
        CaseSensitive
    };

    enum SplitBehavior{
        KeepEmptyParts,
        SkipEmptyParts
    };

    typedef std::list<String> StringList;

    String();
    String(const Char * unicode);
    String(Char ch);
    String(const String &other);
    String(String &&other);
    String(const char *str, int size);
    String(const char chr);
    ~String();
    String & append(const String &str);
    String & append(const Char *str, int len);
    String & append(Char ch);
    String & append(char *str);
    const Char at(int position) const;
    void clear();
    bool contains(const String &str, CaseSensitivity cs = CaseSensitive) const;
    bool contains(Char ch, CaseSensitivity cs = CaseSensitive) const;
    int  count(const String &str, CaseSensitivity cs = CaseSensitive) const;
    int  count(Char ch, CaseSensitivity cs = CaseSensitive) const;
    int  count() const;
    std::list<Char>::iterator crbegin() const;
    std::list<Char>::iterator crend() const;
    Char * data();
    const Char * data() const;
    std::list<Char>::iterator end();
    bool endsWith(const String &s, CaseSensitivity cs = CaseSensitive) const;
    bool endsWith(Char c, CaseSensitivity cs = CaseSensitive) const;
    String &fill(Char ch, int size = -1);
    int indexOf(const String &str, int from = 0, CaseSensitivity cs = CaseSensitive) const;
    int indexOf(Char ch, int from = 0, CaseSensitivity cs = CaseSensitive) const;
    String &insert(int position, const String &str);
    String &insert(int position, const Char *unicode, int size);
    String &insert(int position, Char ch);
    String &insert(int position, const char *str);
    bool isEmpty() const;
    bool isNull() const;
    bool isRightToLeft() const;
    int lastIndexOf(const String &str, int from = -1, CaseSensitivity cs = CaseSensitive) const;
    int lastIndexOf(Char ch, int from = -1, CaseSensitivity cs = CaseSensitive) const;
    String left(int n) const;
    int length() const;
    String mid(int position, int n = -1) const;
    String &prepend(const String &str);
    String &prepend(const Char *str, int len);
    String &prepend(Char ch);
    String &prepend(const char *str);
    void push_back(const String &other);
    void push_back(Char ch);
    void push_front(const String &other);
    void push_front(Char ch);
    std::list<Char>::iterator rbegin();
    String &remove(int position, int n);
    String &remove(Char ch, CaseSensitivity cs = CaseSensitive);
    String &remove(const String &str, CaseSensitivity cs = CaseSensitive);
    std::list<Char>::iterator rend();
    String repeated(int times); const
    String &replace(int position, int n, const String &after);
    String &replace(int position, int n, const Char *unicode, int size);
    String &replace(int position, int n, Char after);
    String &replace(Char before, Char after, CaseSensitivity cs = CaseSensitive);
    String &replace(const Char *before, int blen, const Char *after, int alen, CaseSensitivity cs = CaseSensitive);
    String &replace(const String &before, const String &after, CaseSensitivity cs = CaseSensitive);
    String &replace(Char ch, const String &after, CaseSensitivity cs = CaseSensitive);
    void reserve(int size);
    void resize(int size);
    void resize(int size, Char fillChar);
    String right(int n) const;

    String simplified() const;
    int size() const;
    StringList split(const String &sep, SplitBehavior behavior = KeepEmptyParts, CaseSensitivity cs = CaseSensitive) const;
    StringList split(Char sep, SplitBehavior behavior = KeepEmptyParts, CaseSensitivity cs = CaseSensitive) const;

    bool startsWith(const String &s, CaseSensitivity cs = CaseSensitive) const;
    bool startsWith(Char c, CaseSensitivity cs = CaseSensitive) const;
    void swap(String &other);


    double toDouble(bool *ok = NULL) const;
    float toFloat(bool *ok = NULL) const;
    int toInt(bool *ok = NULL, int base = 10) const;

    long toLong(bool *ok = NULL, int base = 10) const;
    String toLower() const;
    short toShort(bool *ok = NULL, int base = 10) const;
    std::string toStdString() const;
    std::u16string toStdU16String() const;
    std::u32string toStdU32String() const;
    std::wstring toStdWString(); const
    uint toUInt(bool *ok = NULL, int base = 10) const;
    ulong toULong(bool *ok = NULL, int base = 10) const;
    ushort toUShort(bool *ok = NULL, int base = 10) const;
    String toUpper() const;
    String trimmed() const;
    void truncate(int position);

    bool operator!=(const char *other) const;
    bool operator!=(const ByteArray &other) const;
    String & operator+=(const String &other);
    String & operator+=(Char ch);
    String & operator+=(const StringRef &str);
    String & operator+=(const char *str);
    String & operator+=(const ByteArray &ba);
    String & operator+=(char ch);
    bool operator<(const char *other) const;
    bool operator<(const ByteArray &other) const;
    bool operator<=(Latin1String other) const;
    bool operator<=(const char *other) const;
    bool operator<=(const ByteArray &other) const;
    String &operator=(const String &other);
    String &operator=(Char ch);
    String &operator=(Latin1String str);
    String &operator=(String &&other);
    String &operator=(const char *str);
    String &operator=(const ByteArray &ba);
    String &operator=(char ch);
    String &operator=(const NULL &);
    bool operator==(Latin1String other) const;
    bool operator==(const char *other) const;
    bool operator==(const ByteArray &other) const;
    bool operator>(const char *other) const;
    bool operator>(const ByteArray &other) const;
    bool operator>=(Latin1String other) const;
    bool operator>=(const char *other) const;
    bool operator>=(const ByteArray &other) const;
    const Char operator[](int position) const;
    const Char operator[](uint position) const;

private:
    std::list<Char> * __data = NULL;
};



#endif // STRING_H

/*
 *  String();;
    String(const char *chr);;
    String(const String &other);;
    String(char c);;
    String(const char ** str);;
    String(const Char ** str);;
    ~String();;
    String &	append(const String &str);;
    String &	append(const char *str, int len);;
    String &	append(char ch);;
    String &	append(const char *str);;
    String &	append(const char ** str);;
    const char	at(int position); const;
    void        clear();;
    bool        contains(const String &str); const;
    bool        contains(char ch); const;
    int         count(const String &str); const;
    int         count(char ch); const;
    int         count();; const
    const_reverse_iterator	crbegin(); const;
    const_reverse_iterator	crend();; const
    bool        endsWith(const String &s); const;
    bool        endsWith(const StringRef &s); const;
    bool        endsWith(char c); const;
    String &	fill(char ch, int size = -1);;
    int         indexOf(const String &str, int from = 0 ); const;
    int         indexOf(char ch, int from = 0 );; const
    String &	insert(int position, const String &str);;
    String &	insert(int position, const char *unicode, int size);;
    String &	insert(int position, char ch);;
    String &	insert(int position, const char *str);;
    String &	insert(int position, const char &str[]);;
    bool        isEmpty(); const;
    bool        isNull(); const;
    bool        isRightToLeft(); const;
    int         lastIndexOf(const String &str, int from = -1 ); const;
    int         lastIndexOf(char ch, int from = -1 ); const;
    String      left(int n); const;
    int         length();; const
    String      mid(int position, int n = -1); const;
    String &	prepend(const String &str);;
    String &	prepend(const char *str, int len);;
    String &	prepend(char ch);;
    String &	prepend(const char *str);;
    String &	prepend(const char &ba[]);;
    void        push_back(const String &other);;
    void        push_back(char ch);;
    void        push_front(const String &other);;
    void        push_front(char ch);;
    String &	remove(int position, int n);;
    String &	remove(char ch );;
    String &	remove(const String &str );;
    String      repeated(int times);; const
    String &	replace(int position, int n, const String &after);;
    String &	replace(int position, int n, const char *unicode, int size);;
    String &	replace(int position, int n, char after);;
    String &	replace(char before, char after );;
    String &	replace(const char *before, int blen, const char *after, int alen );;
    String &	replace(const String &before, Latin1String after );;
    String &	replace(const String &before, const String &after );;
    String &	replace(char ch, const String &after );;
    String &	setNum(int n, int base = 10);;
    String &	setNum(short n, int base = 10);;
    String &	setNum(long n, int base = 10);;
    String &	setNum(long n, int base = 10);;
    String &	setNum(float n, char format = 'g', int precision = 6);;
    String &	setNum(double n, char format = 'g', int precision = 6);;
    String &	setRawData(const char *unicode, int size);;
    String &	setUnicode(const char *unicode, int size);;
    String      simplified(); const;
    int         size(); const;
    StringList	split(const String &sep);const;
    StringList	split(char sep); const;
    bool        startsWith(const String &s ); const;
    bool        startsWith(char c ); const;
    void        swap(String &other);;
    String      toCaseFolded();; const
    double      toDouble(bool *ok);const;
    float       toFloat(bool *ok); const;
    String      toHtmlEscaped(); const;
    int         toInt(bool *ok , int base = 10); const;
    char *      toLatin1();const;
    char *      toLocal8Bit();const;
    long        toLong(bool *ok, int base = 10);const;
    String      toLower(); const;
    short       toShort(bool *ok, int base = 10); const;
    std::string	toStdString(); const;
    std::u16string	toStdU16String(); const;
    std::u32string	toStdU32String(); const;
    std::wstring	toStdWString(); const;
    String      toUpper(); const;
    char*       toUtf8(); const;
    int         toWCharArray(wchar_t *array); const;
    String      trimmed(); const;
    void        truncate(int position);;
    const char *unicode(); const;
    bool        operator!=(const char *other);const;
    String &	operator+=(const String &other);;
    String &	operator+=(char ch);;
    String &	operator+=(const StringRef &str);;
    String &	operator+=(const char *str);;
    bool        operator<(const char *other); const;
    bool        operator<(const char* &other); const;
    bool        operator<=(const char *other); const;
    String &	operator=(const String &other);;
    String &	operator=(char ch);;
    String &	operator=(String &&other);;
    String &	operator=(const char *str);;
    bool        operator==(const char *other); const;
    bool        operator>(const char *other); const;
    bool        operator>=(const char *other);const;
    char        operator[](int position);;
 */

#ifndef STDSTRING_H
#define STDSTRING_H
//#include<QString>
#include<list>
#include<Char.h>
#include<string>
#include<QString>
typedef QString StdString;

//class  StdString :public std::string{
class  _StdString :public QString{
/*
public:
    enum SplitBehavior{
        KeepEmptyParts,
        SkipEmptyParts
    };

    enum CaseSensitivity{
        CaseInsensitive,
        CaseSensitive
    };
    typedef std::list<StdString> StdStringList;


    inline StdString();
    explicit StdString(std::string &str);
    explicit StdString(const char *unicode, int size = -1);
    inline StdString(Char c);
    inline StdString(int size, Char c);
    inline StdString(const StdString & string);
    inline StdString(StdString & other) ;


    inline    StdString & append(const StdString &str);
    inline    StdString & append(const Char *str, int len);
    inline    StdString & append(Char ch);
    inline    StdString & append(char *str);
    inline    const Char at(int position) const;
    inline    void clear();
    inline    bool contains(const StdString &str, CaseSensitivity cs = CaseSensitive) const;
    inline    bool contains(Char ch, CaseSensitivity cs = CaseSensitive) const;
    inline    int  count(const StdString &str, CaseSensitivity cs = CaseSensitive) const;
    inline    int  count(Char ch, CaseSensitivity cs = CaseSensitive) const;
    inline    int  count() const;
    inline    std::list<Char>::iterator crbegin() const;
    inline    std::list<Char>::iterator crend() const;
    inline    Char * data();
    inline    const Char * data() const;
    inline    std::list<Char>::iterator end();
    inline    bool endsWith(const StdString &s, CaseSensitivity cs = CaseSensitive) const;
    inline    bool endsWith(Char c, CaseSensitivity cs = CaseSensitive) const;
    inline    StdString &fill(Char ch, int size = -1);
    inline    int indexOf(const StdString &str, int from = 0, CaseSensitivity cs = CaseSensitive) const;
    inline    int indexOf(Char ch, int from = 0, CaseSensitivity cs = CaseSensitive) const;
    inline    StdString &insert(int position, const StdString &str);
    inline    StdString &insert(int position, const Char *unicode, int size);
    inline    StdString &insert(int position, Char ch);
    inline    StdString &insert(int position, const char *str);
    inline    bool isEmpty() const;
    inline    bool isNull() const;
    inline    bool isRightToLeft() const;
    inline    int lastIndexOf(const StdString &str, int from = -1, CaseSensitivity cs = CaseSensitive) const;
    inline    int lastIndexOf(Char ch, int from = -1, CaseSensitivity cs = CaseSensitive) const;
    inline    StdString left(int n) const;
    inline    int length() const;
    inline    StdString mid(int position, int n = -1) const;
    inline    StdString &prepend(const StdString &str);
    inline    StdString &prepend(const Char *str, int len);
    inline    StdString &prepend(Char ch);
    inline    StdString &prepend(const char *str);
    inline    void push_back(const StdString &other);
    inline    void push_back(Char ch);
    inline    void push_front(const StdString &other);
    inline    void push_front(Char ch);
    inline    std::list<Char>::iterator rbegin();
    inline    StdString &remove(int position, int n);
    inline    StdString &remove(Char ch, CaseSensitivity cs = CaseSensitive);
    inline    StdString &remove(const StdString &str, CaseSensitivity cs = CaseSensitive);
    inline    std::list<Char>::iterator rend();
    inline    StdString repeated(int times); const
    inline    StdString &replace(int position, int n, const StdString &after);
    inline    StdString &replace(int position, int n, const Char *unicode, int size);
    inline    StdString &replace(int position, int n, Char after);
    inline    StdString &replace(Char before, Char after, CaseSensitivity cs = CaseSensitive);
    inline    StdString &replace(const Char *before, int blen, const Char *after, int alen, CaseSensitivity cs = CaseSensitive);
    inline    StdString &replace(const StdString &before, const StdString &after, CaseSensitivity cs = CaseSensitive);
    inline    StdString &replace(Char ch, const StdString &after, CaseSensitivity cs = CaseSensitive);
    inline    void reserve(int size);
    inline    void resize(int size);
    inline    void resize(int size, Char fillChar);
    inline    StdString right(int n) const;

    inline    StdString simplified() const;
    inline    int size() const;
    inline    StdStringList split(const StdString &sep, SplitBehavior behavior = KeepEmptyParts, CaseSensitivity cs = CaseSensitive) const;
    inline    StdStringList split(Char sep, SplitBehavior behavior = KeepEmptyParts, CaseSensitivity cs = CaseSensitive) const;

    inline    bool startsWith(const StdString &s, CaseSensitivity cs = CaseSensitive) const;
    inline    bool startsWith(Char c, CaseSensitivity cs = CaseSensitive) const;
    inline    void swap(StdString &other);


    inline    double toDouble(bool *ok = NULL) const;
    inline    float toFloat(bool *ok = NULL) const;
    inline    int toInt(bool *ok = NULL, int base = 10) const;

    inline    long toLong(bool *ok = NULL, int base = 10) const;
    inline    StdString toLower() const;
    inline    short toShort(bool *ok = NULL, int base = 10) const;
    inline    unsigned int toUInt(bool *ok = NULL, int base = 10) const;
    inline    unsigned long toULong(bool *ok = NULL, int base = 10) const;
    inline    unsigned short toUShort(bool *ok = NULL, int base = 10) const;
    inline    char * toLocal8Bit()const;
    inline    std::string	toStdString() const;
    inline    StdString toUpper() const;
    inline    StdString trimmed() const;
    inline    void truncate(int position);

    //inline    StdString	asprintf(const char *cformat, ...)
    inline static   int	compare(const StdString &s1, const StdString &s2, CaseSensitivity cs = CaseSensitive);
    inline static   StdString	fromLatin1(const char *str, int size = -1);
    inline static   StdString	fromLocal8Bit(const char *str, int size = -1);
    inline static   StdString	fromRawData(const Char *unicode, int size);
    inline static   StdString	fromStdString(const std::string &str);
    inline static   StdString	fromStdWString(const std::wstring &str);
    inline static   StdString	fromUcs4(const unsigned int *unicode, int size = -1);

    inline static   StdString	fromUtf8(const char *str, int size = -1);
    inline static   StdString	fromUtf16(const unsigned short *unicode, int size = -1);

    inline static   StdString	fromWCharArray(const wchar_t *string, int size = -1);
    inline static   int         localeAwareCompare(const StdString &s1, const StdString &s2);
    inline static   const    StdString	number(long n, int base = 10);
    inline static   const    StdString	number(uint n, int base = 10);
    inline static   const    StdString	number(int n, int base = 10);
    inline static   const    StdString	number(unsigned long n, int base = 10);
    inline static   const    StdString	number(double n, char format = 'g', int precision = 6);
    inline static   const    StdString	vasprintf(const char *cformat, va_list ap);



    inline  bool	operator!=(const char *other) const;
    inline  StdString &	operator+=(const StdString &other);
    inline  StdString &	operator+=(Char ch);
    inline  StdString &	operator+=(const char *str);
    inline  StdString &	operator+=(char ch);
    inline  bool	operator<(const char *other) const;
    inline  bool	operator<=(const char *other) const;


    inline  StdString &	operator=(const StdString &other);
    inline  StdString &	operator=(Char c);
    inline  StdString &	operator=(StdString &other);//&& error here
    inline  StdString &	operator=(const char *unicode);
    inline  StdString &	operator=(char ch);

    inline  bool	operator==(const char *other) const;
    inline  bool	operator==(StdString other) const;
    inline  bool	operator==(const char* &other) const;

    inline  bool	operator>(const char *other) const;
    inline  bool	operator>=(const char *other) const;
    inline  const Char	operator[](int position) const;
    inline  const Char	operator[](uint position) const;

    friend              bool	operator!=(const StdString &s1, const StdString &s2);
    inline friend       bool        operator!=(const char *s1, const StdString &s2);
    inline friend const StdString	operator+(const StdString &s1, const StdString &s2);
    inline friend const StdString	operator+(const StdString &s1, const char *s2);
    inline friend const StdString	operator+(const char *s1, const StdString &s2);
    inline friend const StdString	operator+(const char *s1,StdString &s2);
    inline friend const StdString	operator+(const StdString &s, char ch);
    inline friend const StdString	operator+(char ch, const StdString &s);
    inline friend bool	operator<(const char *s1, const StdString &s2);

    inline friend bool	operator<=(const StdString &s1, const StdString &s2);
    inline friend bool	operator<=(const char *s1, const StdString &s2);
    inline friend bool	operator==(const char *s1, const StdString &s2);
    inline friend const bool	operator<(const StdString s1,StdString s2) ;
    inline friend bool	operator>(const StdString &s1, const StdString &s2);
    inline friend bool	operator>(const char *s1, const StdString &s2);
    inline friend bool	operator>=(const StdString &s1, const StdString &s2);
    inline friend bool	operator>=(const char *s1, const StdString &s2);

    inline ~StdString();




private:
    std::list<Char> * __data = NULL;
    */
};


#endif // STDSTRING_H

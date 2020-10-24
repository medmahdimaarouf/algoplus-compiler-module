#include<stdstring.h>

/*
StdString::StdString()
{
    data = new std::list<Char>();
}

StdString::StdString(const char *unicode, int size)
{

}

StdString::StdString(const Char *unicode):this()
{
    data->push_front(*unicode);

}

StdString::StdString(Char ch):this()
{
    data->push_front(ch);
}

StdString::StdString(int size, Char c)
{

}

StdString::StdString(const StdString &string)
{

}

StdString::StdString(StdString &other)
{

}

StdString::StdString(const StdString &other)
{
    this->__data = other.data();
}

StdString::StdString(StdString &other)
{
    this->__data = other.data();
}

StdString::StdString(const char *str , int size)
{
    for(int  i = 0; i < size;i++){
        this->push_front(*(str + i));
    }
}

StdString &StdString::append(const StdString &str)
{
    this->__data->push_front(str.data());
}

StdString &StdString::append(const Char *str, int size)
{
    for(int i = 0; i < size;i++) __data->push_front(*(str + i));
}

StdString &StdString::append(Char ch)
{
  __data->push_front(ch);
}

StdString &StdString::append(char *str)
{

}

StdString &StdString::append(const char &ba[])
{

}

const Char StdString::at(int position) const
{
    return __data[position];
}

void StdString::clear()
{
    this->data->clear();
}

bool StdString::contains(const StdString &str, StdString::CaseSensitivity cs) const
{

}

bool StdString::contains(Char ch, StdString::CaseSensitivity cs) const
{

}

int StdString::count(const StdString &str, StdString::CaseSensitivity cs) const
{

}

int StdString::count(Char ch, StdString::CaseSensitivity cs) const
{

}

int StdString::count() const
{
    return this->length();
}

std::list::iterator StdString::crbegin() const
{

}

std::list::iterator StdString::crend() const
{

}

const Char *StdString::data() const
{
  return __data;
}

std::list::iterator StdString::end()
{

}

bool StdString::endsWith(const StdString &s, StdString::CaseSensitivity cs) const
{

}

bool StdString::endsWith(Char c, StdString::CaseSensitivity cs) const
{

}

StdString &StdString::fill(Char ch, int size)
{

}

StdString StdString::fill(Char ch, int size)
{

}

int StdString::indexOf(const StdString &str, int from, StdString::CaseSensitivity cs) const
{

}

int StdString::indexOf(Char ch, int from, StdString::CaseSensitivity cs) const
{

}

StdString &StdString::insert(int position, const StdString &str)
{

}

StdString &StdString::insert(int position, const Char *unicode, int size)
{

}

StdString &StdString::insert(int position, Char ch)
{

}

StdString &StdString::insert(int position, const char *str)
{

}

bool StdString::isEmpty() const
{
    return !this->length();
}

bool StdString::isNull() const
{
    return data == NULL;
}

bool StdString::isRightToLeft() const
{

}

int StdString::lastIndexOf(const StdString &str, int from, StdString::CaseSensitivity cs) const
{

}

int StdString::lastIndexOf(Char ch, int from, StdString::CaseSensitivity cs) const
{

}


StdString StdString::left(int n) const
{

}

StdString StdString::mid(int position, int n) const
{

}

StdString &StdString::prepend(const StdString &str)
{

}

StdString &StdString::prepend(const Char *str, int len)
{

}

StdString &StdString::prepend(Char ch)
{

}

StdString &StdString::prepend(const char *str)
{

}

void StdString::push_back(const StdString &other)
{

}

void StdString::push_back(Char ch)
{

}

void StdString::push_front(const StdString &other)
{

}

void StdString::push_front(Char ch)
{

}

StdString &StdString::remove(const StdString &str, StdString::CaseSensitivity cs)
{

}

const StdString &StdString::remove(int position, int n)
{

}

StdString &StdString::remove(Char ch, StdString::CaseSensitivity cs)
{

}

StdString &StdString::remove(const StdString &str, StdString::CaseSensitivity cs)
{

}

std::list::iterator StdString::rend()
{

}

StdString StdString::repeated(int times)
{

}

const StdString &StdString::replace(int position, int n, const StdString &after)
{

}

StdString &&StdString::replace(Char ch, const StdString &after, StdString::CaseSensitivity cs)
{

}

StdString &StdString::replace(int position, int n, const Char *unicode, int size)
{

}

StdString &StdString::replace(int position, int n, Char after)
{

}

StdString &StdString::replace(Char before, Char after, StdString::CaseSensitivity cs)
{

}

StdString &StdString::replace(const Char *before, int blen, const Char *after, int alen, StdString::CaseSensitivity cs)
{

}

StdString &StdString::replace(const StdString &before, const StdString &after, StdString::CaseSensitivity cs)
{

}

StdString StdString::replace(Char ch, const StdString &after, StdString::CaseSensitivity cs)
{

}

void StdString::reserve(int size)
{

}

void StdString::resize(int size)
{

}

void StdString::resize(int size, Char fillChar)
{

}

StdString StdString::right(int n) const
{

}

StdString StdString::simplified() const
{

}

int StdString::size() const
{

}

StdString::StdStringList StdString::split(const StdString &sep, StdString::SplitBehavior behavior, StdString::CaseSensitivity cs) const
{

}

StdString::StdStringList StdString::split(Char sep, StdString::SplitBehavior behavior, StdString::CaseSensitivity cs) const
{

}

bool StdString::startsWith(const StdString &s, StdString::CaseSensitivity cs) const
{

}

bool StdString::startsWith(Char c, StdString::CaseSensitivity cs) const
{

}

void StdString::swap(StdString &other)
{

}

double StdString::toDouble(bool *ok) const
{

}

float StdString::toFloat(bool *ok) const
{

}

int StdString::toInt(bool *ok, int base) const
{

}

long StdString::toLong(bool *ok, int base) const
{

}

StdString StdString::toLower() const
{

}

short StdString::toShort(bool *ok, int base) const
{

}

std::wstring StdString::toStdWStdString()
{

}

const unsigned int StdString::toUInt(bool *ok, int base) const
{

}

unsigned short StdString::toUShort(bool *ok, int base) const
{

}

char *StdString::toLocal8Bit() const
{

}

std::string StdString::toStdString() const
{

}

StdString StdString::toUpper() const
{

}

StdString StdString::trimmed() const
{

}

void StdString::truncate(int position)
{

}

bool StdString::operator!=(const char *other) const
{

}

bool StdString::operator!=(const StdString &sstring)
{

}

bool StdString::operator!=(const char *s1)
{

}

const StdString StdString::operator+(const StdString &s1)
{

}

const StdString StdString::operator+(char ch)
{

}

StdString &StdString::operator+=(const StdString &other)
{

}

StdString &StdString::operator+=(Char ch)
{

}

StdString &StdString::operator+=(const char *str)
{

}

StdString &StdString::operator+=(char ch)
{

}

bool StdString::operator<(const char *other) const
{

}

bool StdString::operator<=(const char *other) const
{

}


StdString &StdString::operator=(Char c)
{

}


StdString &StdString::operator=(StdString &other)
{

}

StdString &StdString::operator=(const char *unicode)
{

}

StdString &StdString::operator=(char ch)
{

}

bool StdString::operator==(const char *other) const
{

}

bool StdString::operator==(StdString other) const
{

}

bool StdString::operator==(const char *&other) const
{

}


bool StdString::operator>(const char *other) const
{

}

bool StdString::operator>=(const char *other) const
{

}

bool StdString::operator>=(const ByteArray &other) const
{

}

const Char StdString::operator[](int position) const
{

}

const Char StdString::operator[](uint position) const
{

}

bool StdString::operator!=(const StdString &s1, const StdString &s2)
{

}

bool StdString::operator!=(const char *s1, const StdString &s2)
{

}

const StdString StdString::operator+(const StdString &s1, const StdString &s2)
{

}

const StdString StdString::operator+(const StdString &s1, const char *s2)
{

}

const StdString StdString::operator+(const char *s1, const StdString &s2)
{

}

const StdString StdString::operator+(const StdString &s, char ch)
{

}

const StdString StdString::operator+(char ch, const StdString &s)
{

}

bool StdString::operator<(const char *s1, const StdString &s2)
{

}

bool StdString::operator<=(const StdString &s1, const StdString &s2)
{

}

bool StdString::operator<=(const char *s1, const StdString &s2)
{

}

bool StdString::operator==(const char *s1, const StdString &s2)
{

}

bool StdString::operator<(const StdString s1, StdString s2) const
{

}

bool StdString::operator>(const StdString &s1, const StdString &s2)
{

}

bool StdString::operator>(const char *s1, const StdString &s2)
{

}

bool StdString::operator>=(const StdString &s1, const StdString &s2)
{

}

bool StdString::operator>=(const char *s1, const StdString &s2)
{

}

const Char StdString::operator[](unsigned int position) const
{

}

int StdString::compare(const StdString &s1, const StdString &s2, StdString::CaseSensitivity cs)
{

}

StdString StdString::fromLatin1(const char *str, int size)
{

}

StdString StdString::fromLocal8Bit(const char *str, int size)
{

}

StdString StdString::fromRawData(const Char *unicode, int size)
{

}

StdString StdString::fromStdString(const std::string &str)
{

}

StdString StdString::fromStdWString(const std::wstring &str)
{

}

StdString StdString::fromUcs4(const unsigned int *unicode, int size)
{

}


StdString StdString::fromUtf8(const char *str, int size)
{

}

StdString StdString::fromUtf16(const unsigned short *unicode, int size)
{

}

StdString StdString::fromWCharArray(const wchar_t *string, int size)
{

}

int StdString::localeAwareCompare(const StdString &s1, const StdString &s2)
{

}

StdString StdString::number(long n, int base)
{

}

StdString StdString::number(uint n, int base)
{

}

StdString StdString::number(int n, int base)
{

}

StdString StdString::number(unsigned long n, int base)
{

}

StdString StdString::number(double n, char format, int precision)
{

}

StdString StdString::vasprintf(const char *cformat, va_list ap)
{

}


StdString::~StdString()
{

}



const StdString StdString::operator+(const StdString &s1, const char *s2)
{

}
*/

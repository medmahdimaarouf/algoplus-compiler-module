#include "String.h"

String::String()
{
    data = new std::list<Char>();
}

String::String(const Char *unicode):this()
{
    data->push_front(*unicode);

}

String::String(Char ch):this()
{
    data->push_front(ch);
}

String::String(const String &other)
{
    this->__data = other.data();
}

String::String(String &other)
{
    this->__data = other.data();
}

String::String(const char *str , int size)
{
    for(int  i = 0; i < size;i++){
        this->push_front(*(str + i));
    }
}

String &String::append(const String &str)
{
    this->__data->push_front(str.data());
}

String &String::append(const Char *str, int size)
{
    for(int i = 0; i < size;i++) __data->push_front(*(str + i));
}

String &String::append(Char ch)
{
  __data->push_front(ch);
}

String &String::append(char *str)
{

}

String &String::append(const char &ba[])
{

}

const Char String::at(int position) const
{
    return __data[position];
}

void String::clear()
{
    this->data->clear();
}

bool String::contains(const String &str, String::CaseSensitivity cs) const
{

}

bool String::contains(Char ch, String::CaseSensitivity cs) const
{

}

int String::count(const String &str, String::CaseSensitivity cs) const
{

}

int String::count(Char ch, String::CaseSensitivity cs) const
{

}

int String::count() const
{
    return this->length();
}

std::list::iterator String::crbegin() const
{

}

std::list::iterator String::crend() const
{

}

const Char *String::data() const
{
  return __data;
}

std::list::iterator String::end()
{

}

bool String::endsWith(const String &s, String::CaseSensitivity cs) const
{

}

bool String::endsWith(Char c, String::CaseSensitivity cs) const
{

}

String &String::fill(Char ch, int size)
{

}

String String::fill(Char ch, int size)
{

}

int String::indexOf(const String &str, int from, String::CaseSensitivity cs) const
{

}

int String::indexOf(Char ch, int from, String::CaseSensitivity cs) const
{

}

String &String::insert(int position, const String &str)
{

}

String &String::insert(int position, const Char *unicode, int size)
{

}

String &String::insert(int position, Char ch)
{

}

String &String::insert(int position, const char *str)
{

}

bool String::isEmpty() const
{
    return !this->length();
}

bool String::isNull() const
{
    return data == NULL;
}

bool String::isRightToLeft() const
{

}

int String::lastIndexOf(const String &str, int from, String::CaseSensitivity cs) const
{

}

int String::lastIndexOf(Char ch, int from, String::CaseSensitivity cs) const
{

}


String String::left(int n) const
{

}

String String::mid(int position, int n) const
{

}

String &String::prepend(const String &str)
{

}

String &String::prepend(const Char *str, int len)
{

}

String &String::prepend(Char ch)
{

}

String &String::prepend(const char *str)
{

}

void String::push_back(const String &other)
{

}

void String::push_back(Char ch)
{

}

void String::push_front(const String &other)
{

}

void String::push_front(Char ch)
{

}

String &String::remove(const String &str, String::CaseSensitivity cs)
{

}

const String &String::remove(int position, int n)
{

}

String &String::remove(Char ch, String::CaseSensitivity cs)
{

}

String &String::remove(const String &str, String::CaseSensitivity cs)
{

}

std::list::iterator String::rend()
{

}

String String::repeated(int times)
{

}

const String &String::replace(int position, int n, const String &after)
{

}

String &&String::replace(Char ch, const String &after, String::CaseSensitivity cs)
{

}

String &String::replace(int position, int n, const Char *unicode, int size)
{

}

String &String::replace(int position, int n, Char after)
{

}

String &String::replace(Char before, Char after, String::CaseSensitivity cs)
{

}

String &String::replace(const Char *before, int blen, const Char *after, int alen, String::CaseSensitivity cs)
{

}

String &String::replace(const String &before, const String &after, String::CaseSensitivity cs)
{

}

String String::replace(Char ch, const String &after, String::CaseSensitivity cs)
{

}

void String::reserve(int size)
{

}

void String::resize(int size)
{

}

void String::resize(int size, Char fillChar)
{

}

String String::right(int n) const
{

}

String String::simplified() const
{

}

int String::size() const
{

}

String::StringList String::split(const String &sep, String::SplitBehavior behavior, String::CaseSensitivity cs) const
{

}

String::StringList String::split(Char sep, String::SplitBehavior behavior, String::CaseSensitivity cs) const
{

}

bool String::startsWith(const String &s, String::CaseSensitivity cs) const
{

}

bool String::startsWith(Char c, String::CaseSensitivity cs) const
{

}

void String::swap(String &other)
{

}

double String::toDouble(bool *ok) const
{

}

float String::toFloat(bool *ok) const
{

}

int String::toInt(bool *ok, int base) const
{

}

long String::toLong(bool *ok, int base) const
{

}

String String::toLower() const
{

}

short String::toShort(bool *ok, int base) const
{

}

std::string String::toStdString() const
{

}

std::u16string String::toStdU16String() const
{

}

std::u32string String::toStdU32String() const
{

}

std::wstring String::toStdWString()
{

}

const uint String::toUInt(bool *ok, int base) const
{

}

ushort String::toUShort(bool *ok, int base) const
{

}

String String::toUpper() const
{

}

String String::trimmed() const
{

}

void String::truncate(int position)
{

}

bool String::operator!=(const char *other) const
{

}

bool String::operator!=(const ByteArray &other) const
{

}

String &String::operator+=(const String &other)
{

}

String &String::operator+=(Char ch)
{

}

String &String::operator+=(const StringRef &str)
{

}

String &String::operator+=(const char *str)
{

}

String &String::operator+=(const ByteArray &ba)
{

}

String &String::operator+=(char ch)
{

}

bool String::operator<(const char *other) const
{

}

bool String::operator<(const ByteArray &other) const
{

}

bool String::operator<=(Latin1String other) const
{

}

bool String::operator<=(const char *other) const
{

}

bool String::operator<=(const ByteArray &other) const
{

}

String &String::operator=(const String &other)
{

}

String &String::operator=(Char ch)
{

}

String &String::operator=(Latin1String str)
{

}

String &String::operator=(String &other)
{

}

String &String::operator=(const char *str)
{

}

String &String::operator=(const ByteArray &ba)
{

}

String &String::operator=(char ch)
{

}

String &String::operator=(const Null &)
{

}

bool String::operator==(Latin1String other) const
{

}

bool String::operator==(const char *other) const
{

}

bool String::operator==(const ByteArray &other) const
{

}

bool String::operator>(const char *other) const
{

}

bool String::operator>(const ByteArray &other) const
{

}

bool String::operator>=(Latin1String other) const
{

}

bool String::operator>=(const char *other) const
{

}

bool String::operator>=(const ByteArray &other) const
{

}

const Char String::operator[](int position) const
{

}

const Char String::operator[](uint position) const
{

}





#include "Str.h"
#include <string.h>

TString::TString(int l)
{
  len = l;
  str = new char[len + 1];
  for (int i = 0; i< len; i++)
    str[i] = ' ';
}

TString::TString(int l, char c)
{
  len = l;
  str = new char[len + 1];
  for (int i = 0; i < len; i++)
  {
    str[i] = c;
  }
  str[len] = 0;
}

TString::TString(const TString& p)
{
  len = p.len;
  str = new char[len + 1];
  for (int i = 0; i <= len; i++)
  {
    str[i] = p.str[i];
  }
}

TString::TString(const char* s)
{
  if (s != nullptr)
  {
    len = StrLen(s);
    str = new char[len + 1];
    for (int i = 0; i <= len; i++)
    {
      str[i] = s[i];
    }
  }
  else
  {
    len = 0;
    str = new char[len + 1];
    str[0] = 0;
  }
}

TString::~TString()
{
  if (str != nullptr)
  {
    delete[] str;
    str = nullptr;
  }
}

int TString::GetLen()
{
  return len;
}

char* TString::GetStr()
{
  return str;
}

TString TString::operator+(const TString& s)
{
  int l = len + s.len;
  TString res(l, 0);
  for (int i = 0; i < len; i++)
  {
    res.str[i] = str[i];
  }
  for (int j = len; j < l; j++)
  {
    res.str[j] = s.str[j - len];
  }
  res.str[l] = 0;
  return res;
}

TString TString::operator+(const char& s)
{
  int l = len + 1;
  TString res(l, 0);
  for (int i = 0; i < len; i++)
  {
    res.str[i] = str[i];
  }
  res.str[l - 1] = s;
  res.str[l] = 0;
  return res;
}

TString TString::operator=(const TString& s)
{
  if (str != nullptr)
  {
    delete[] str;
    str = nullptr;
  }
  len = s.len;
  str = new char[len + 1];
  for (int i = 0; i <= len; i++)
  {
    str[i] = s.str[i];
  }
  return *this;
}

char TString::operator[](int j)
{
  if (j >= 0 && j <= len)
  {
    return str[j];
  }
  else
  {
    throw out_of_range("out of range");
  }
}

bool TString::operator==(const TString& s)
{
  if (len != s.len)
  {
    return false;
  }
  for (int i = 0; i < len; i++)
  {
    if (str[i] != s.str[i])
    {
      return false;
    }
  }
  return true;
}

bool TString::operator>(const TString& s)
{
  if (*this == s)
  {
    return false;
  }
  int i = 0;
  while (i <= min(len, s.len))
  {
    if (int(str[i]) > int(s.str[i]))
    {
      return true;
    }
    i++;
  }
  return len > s.len;
}

bool TString::operator<(const TString& s)
{
  if (*this == s)
  {
    return false;
  }
  return !(len > s.len);
}

int TString::NumChar(char c)
{
  int n = -1;
  for (int i = 0; i < len; i++)
  {
    if (str[i] == c)
    {
      n = i;
      break;
    }
  }
  return n;
}

int TString::StrPos(const char* s)
{
  int n = -1;
  int l;
  l = StrLen(s);
  int i = 0;
  bool f;
  while (i <= len - l)
  {
    f = true;
    for (int j = i; j < i + l; j++)
    {
      if (str[j] != s[j - i])
      {
        f = false;
        break;
      }
    }
    if (f == true)
    {
      n = i;
      break;
    }
    else
    {
      i++;
    }
  }
  return n;
}

void TString::PrintSplit(const char c)
{
  int n = 0;
  for (int i = 0; i < len; i++)
  {
    if (str[i] == c)
    {
      n++;
    }
  }
  if (n != 0)
  {
    char* word;
    int j = 0;
    int l = 0;
    cout << "Words:" << endl;
    while (j < len + 1)
    {
      if ((str[j] == c || j == len) && l != 0)
      {
        word = new char[l + 1];
        for (int i = 0; i < l; i++)
        {
          word[i] = str[j - l + i];
        }
        word[l] = 0;
        cout << word << endl;
        l = 0;
        j++;
        delete[] word;
      }
      else
      {
        if (str[j] != c)
        {
          l++;
        }
        j++;
      }
    }
  }
  else
  {
    cout << "No words";
  }
}

char** TString::Split(const char c)
{
  int n = 0;
  for (int i = 0; i < len; i++)
  {
    if (str[i] == c)
    {
      n++;
    }
  }
  char** mas = new char* [n];
  if (n != 0)
  {

    char* word;
    int j = 0;
    int l = 0;
    n = 0;
    while (j < len + 1)
    {
      if ((str[j] == c || j == len) && l != 0)
      {
        word = new char[l + 1];
        for (int i = 0; i < l; i++)
        {
          word[i] = str[j - l + i];
        }
        word[l] = 0;
        mas[n] = new char[l + 1];
        mas[n] = word;
        n++;
        l = 0;
        j++;
      }
      else
      {
        if (str[j] != c)
        {
          l++;
        }
        j++;
      }
    }
  }
  return mas;
}

TString TString::Mult(const int k)
{
  TString res(len * k, 'c');
  int j = 0;
  while (j <= len * k)
  {
    res.str[j] = str[j % len];
    j++;
  }
  res.str[len * k] = 0;
  return res;
}

char TString::MuchSymvol()
{
  unsigned char c = '0';
  int mas[256];
  for (int i = 0; i < 256; i++)
  {
    mas[i] = 0;
  }
  for (int j = 0; j < len; j++)
  {
    mas[unsigned char(str[j])]++;
  }
  for (int g = 0; g < 256; g++)
  {
    if (mas[g] >= mas[int(unsigned char(c))])
    {
      c = unsigned char(g);
    }
  }
  return char(c);
}

char* TString::MasSymvol()
{
  int mas[256];
  int length = 0;
  for (int i = 0; i < 256; i++)
  {
    mas[i] = 0;
  }
  for (int j = 0; j < len; j++)
  {
    if (mas[unsigned char(str[j])] == 0)
    {
      length++;
    }
    mas[unsigned char(str[j])]++;
  }
  char* res = new char[length];
  length = 0;
  for (int g = 0; g < 256; g++)
  {
    if (mas[g] != 0)
    {
      res[length] = char(unsigned char(g));
      length++;
    }
  }
  res[length] = 0;
  return res;
}

ostream& operator<<(ostream& ostr, const TString& s)
{
  ostr << "Len=" << s.len << ":\t" << s.str;
  return ostr;
}

//istream& operator>>(istream& istr, TString& s)
//{
//  if (s.str != nullptr)
//  {
//    delete[] s.str;
//    s.str = nullptr;
//  }
//  string st;
//  istr >> st;
//  TString res(st.c_str());
//  s = res;
//  return istr;
//}

istream& operator>>(istream& istr, TString& s)
{
  if (s.str != nullptr)
  {
    delete[] s.str;
    s.str = nullptr;
  }
  char* res = new char[1000];
  istr >> res;
  TString st(res);
  s = st;
  delete[] res;
  return istr;
}

int StrLen(const char* s)
{
  int length = 0;
  while (s[length] != 0)
  {
    length++;
  }
  return length;
}

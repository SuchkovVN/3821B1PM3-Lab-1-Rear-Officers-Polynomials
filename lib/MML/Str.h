#pragma once
#include <iostream>
using namespace std;

class TString
{
public:
  TString(int l=0);
  TString(int l, char c);
  TString(const TString& p);
  TString(const char* s);
  ~TString();

  int GetLen();
  char* GetStr();

  TString operator+(const TString& s);
  TString operator+(const char& s);
  TString operator=(const TString& s);
  char operator[](int j);
  bool operator==(const TString& s);
  bool operator<(const TString& s);
  bool operator>(const TString& s);
  friend ostream& operator<<(ostream& ostr, const TString& s);
  friend istream& operator>>(istream& istr, TString& s);

  int NumChar(char c);
  int StrPos(const char* s);
  void PrintSplit(const char c);
  char** Split(const char c);
  TString Mult(const int k);
  char MuchSymvol();
  char* MasSymvol();
private:
  int len;
  char* str;
};
int StrLen(const char* s);
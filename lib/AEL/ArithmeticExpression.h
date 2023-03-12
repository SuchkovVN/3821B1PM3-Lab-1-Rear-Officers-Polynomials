#pragma once
#include "Str.h"
#include "Map.h"
#include "Stack.h"

class TArithmeticExpression
{
protected:
  TString infix;
  TString postfix;
  TMap<char, char> lexems;
  TMap<char, int> priority;
  TMap<char, double> operands;

  void toPostfix();
  void Parse();
public:
  TArithmeticExpression(TString expr);

  TString GetInfix();
  TString GetPostfix();
  TMap<char, double> GetOperands();

  void SetOperands();

  double Calculate();
};
#include "ArithmeticExpression.h"

void TArithmeticExpression::toPostfix()
{
  size_t lengh = lexems.Count();
  TStack<char> stop(lengh);
  TString res(0);
  for (size_t i = 0; i < lengh; i++)
  {
    char lex = lexems.GetKey(i);
    if (lexems[lex] == 'c')
    {
      res = res + lex;
      operands.Insert(lex, double(int(lex) - 48), 1);
    }
    else if (lexems[lex] == 'v')
    {
      res = res + lex;
      operands.Insert(lex, 0.0, 1);
    }
    else
    {
      if (stop.IsEmpty())
      {
        stop.Push(lex);
      }
      else if (lex == '(')
      {
        stop.Push(lex);
      }
      else if (lex == ')')
      {
        char tmp = stop.Top();
        stop.Pop();
        while (tmp != '(')
        {
          res = res + tmp;
          tmp = stop.Top();
          stop.Pop();
        }
      }
      else if (lexems[lex] == 'o')
      {
        char tmp1 = stop.Top();
        stop.Pop();
        if (priority[tmp1] < priority[lex])
        {
          stop.Push(tmp1);
          stop.Push(lex);
        }
        else
        {
          while (priority[tmp1] >= priority[lex])
          {
            res = res + tmp1;
            tmp1 = stop.Top();
            stop.Pop();
          }
          stop.Push(tmp1);
          stop.Push(lex);
        }
      }
    }
  }
  while (!stop.IsEmpty())
  {
    res = res + stop.Top();
    stop.Pop();
  }
  postfix = res;
}

void TArithmeticExpression::Parse()
{
  TMap<char, char> lex(1);
  for (size_t i = 0; i < infix.GetLen(); i++)
  {
    char l = infix[i];
    if (isdigit(l) != 0)
      lex.Insert(l, 'c', 0);
    else if (isalpha(l) != 0)
      lex.Insert(l, 'v', 0);
    else if (priority.IsInsertKey(l))
      lex.Insert(l, 'o', 0);
    else
      throw invalid_argument("Expression has invalid arguments");
  }
  for (size_t i = 1; i < lex.Count() - 1; i++)
  {
    if (lex[lex.GetKey(i)] == 'o' && lex.GetKey(i) != '(' && lex.GetKey(i) != ')')
      if ((lex[lex.GetKey(i - 1)] == 'o' || lex[lex.GetKey(i + 1)] == 'o') && lex.GetKey(i-1) != ')' && lex.GetKey(i+1) != '(')
        throw invalid_argument("Expression has invalid arguments");
    if (lex.GetKey(i) == '(')
      if ((lex[lex.GetKey(i - 1)] != 'o' || (lex[lex.GetKey(i + 1)] != 'c' && lex[lex.GetKey(i + 1)] != 'v')) || (lex.GetKey(i - 1) == ')' || lex.GetKey(i - 1) == '(') || (lex.GetKey(i + 1) == ')' || lex.GetKey(i + 1) == '('))
        throw invalid_argument("Expression has invalid arguments");
    if (lex.GetKey(i) == ')')
      if ((lex[lex.GetKey(i + 1)] != 'o' || (lex[lex.GetKey(i - 1)] != 'c' && lex[lex.GetKey(i - 1)] != 'v')) || (lex.GetKey(i - 1) == ')' || lex.GetKey(i - 1) == '(') || (lex.GetKey(i + 1) == ')' || lex.GetKey(i + 1) == '('))
        throw invalid_argument("Expression has invalid arguments");
    if (lex[lex.GetKey(i)] == 'v' || lex[lex.GetKey(i)] == 'c')
      if (lex[lex.GetKey(i + 1)] == 'c' || lex[lex.GetKey(i + 1)] == 'v' || lex[lex.GetKey(i - 1)] == 'v' || lex[lex.GetKey(i - 1)] == 'c' || (lex.GetKey(i + 1) == ')' && lex.GetKey(i - 1) == '('))
        throw invalid_argument("Expression has invalid arguments");
  }
  lexems = lex;
}

TArithmeticExpression::TArithmeticExpression(TString expr)
{
  infix = expr;
  char opers[6] = {'(',')', '+', '-', '*', '/' };
  int priors[6] = { 0, 0, 1, 1, 2, 2 };
  TMap<char, int> pri(6, opers, priors);
  priority = pri;
  Parse();
  toPostfix();
}

TString TArithmeticExpression::GetInfix()
{
  return infix;
}

TString TArithmeticExpression::GetPostfix()
{
  return postfix;
}

TMap<char, double> TArithmeticExpression::GetOperands()
{
  return operands;
}

void TArithmeticExpression::SetOperands()
{
  for (size_t i = 0; i < operands.Count(); i++)
    if (lexems[operands.GetKey(i)] == 'v')
    {
      cout << "Value of key " << operands.GetKey(i) << ":";
      cin >> operands[operands.GetKey(i)];
    }
}

double TArithmeticExpression::Calculate()
{
  size_t lengh = postfix.GetLen();
  TStack<double> stop(lengh);
  for (size_t i = 0; i < lengh; i++)
  {
    char lex = postfix[i];
    if (lexems[lex] == 'c' || lexems[lex] == 'v')
    {
      stop.Push(operands[lex]);
    }
    else
    {
      double righthArg = stop.Top();
      stop.Pop();
      double leftArg = stop.Top();
      stop.Pop();
      if (lex == '+')
        stop.Push(leftArg + righthArg);
      if (lex == '-')
        stop.Push(leftArg - righthArg);
      if (lex == '*')
        stop.Push(leftArg * righthArg);
      if (lex == '/')
        stop.Push(leftArg / righthArg);
    }
  }
  return stop.Top();
}

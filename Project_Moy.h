#pragma once

#include <stack> 
#include <cstdlib> 
#include <string> 
using namespace std;


char stack1[100];
float stack2[100];
int top_stack = -1;
int top_stack2 = -1;

void StackPush(char element)
{
    top_stack++;
    stack1[top_stack] = element;
}

void StackPush2(float element)
{
    top_stack2++;
    stack2[top_stack2] = element;
}
char DelRetEl()
{
    if (top_stack == -1)
    {
        return 0;
    }
    top_stack--;
    return stack1[top_stack + 1];
}
char DelRetEl2()
{
    if (top_stack2 == -1)
    {
        return 0;
    }
    top_stack2--;
    return stack2[top_stack2 + 1];
}
char RetTop()
{
    if (top_stack == -1)
    {
        return 0;
    }
    return stack1[top_stack];
}
char RetTop2()
{
    if (top_stack2 == -1)
    {
        return 0;
    }
    return stack2[top_stack2];
}
bool isOperator(char element)
{
    return (element == '+' || element == '-' || element == '*' || element == '/');
}

float performOperation(char oper, float op1, float op2)
{
    switch (oper)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    default:
        return 0;
    }
}

float evaluatePostfix(string postfix)
{

    for (int i = 0; i < postfix.length(); i++)
    {
        if (isdigit(postfix[i]))
        {
            int number = 0;
            while (isdigit(postfix[i]))
            {
                number *= 10;
                number += postfix[i] - '0';
                i++;
            }
            i--;
            StackPush2(number);
        }
        else if (isOperator(postfix[i]))
        {
            float op2 = stack2[top_stack2];
            DelRetEl2();
            float op1 = stack2[top_stack2];
            DelRetEl2();
            float result = performOperation(postfix[i], op1, op2);
            StackPush2(result);
        }
    }
    return stack2[top_stack2];
}

bool hasHigherPrecedence(char op1, char op2)
{
    int op1Weight = 0;
    int op2Weight = 0;

    switch (op1)
    {
    case '+':
    case '-':
        op1Weight = 1;
        break;
    case '*':
    case '/':
        op1Weight = 2;
        break;
    }

    switch (op2)
    {
    case '+':
    case '-':
        op2Weight = 1;
        break;
    case '*':
    case '/':
        op2Weight = 2;
        break;
    }

    return op1Weight >= op2Weight;
}

string infixToPostfix(string infix)
{
    stack<char> st;
    string postfix;

    for (int i = 0; i < infix.length(); i++)
    {
        if (isdigit(infix[i]))
        {
            string number;
            while (isdigit(infix[i]))
            {
                number += infix[i];
                i++;
            }
            i--;
            postfix += number;
            postfix += ' ';
        }
        else if (infix[i] == '(')
        {
            StackPush(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (top_stack != -1 && stack1[top_stack] != '(')
            {
                postfix += stack1[top_stack];
                DelRetEl();
            }
            DelRetEl();
        }
        else if (isOperator(infix[i]))
        {
            while (top_stack != -1 && hasHigherPrecedence(stack1[top_stack], infix[i]) && stack1[top_stack] != '(')
            {
                postfix += stack1[top_stack];
                DelRetEl();
            }
            StackPush(infix[i]);
        }
    }

    while (top_stack != -1)
    {
        postfix += stack1[top_stack];
        DelRetEl();
    }

    return postfix;
}

//int main()
//{
//    setlocale(LC_ALL, "Russian");
//    string expr;
//    cout << "Введите выражение: ";
//    getline(cin, expr);
//
//    string postfixExpr = infixToPostfix(expr);
//    cout << "Постфиксное выражение: " << postfixExpr << endl;
//
//    float result = evaluatePostfix(postfixExpr);
//    cout << "Результат: " << result << endl;
//
//    return 0;
//}
//15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))
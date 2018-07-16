/*
 * RPN: reverse polish notation
 */
#include "MiniVector.h"
#include "MiniStack.h"
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cstdio>

#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;

const char pri[N_OPTR][N_OPTR] = {
/*        +    -    *    /    ^    !    (    )    \0      */    
/* + */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* * */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* / */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* ^ */  '>', '>', '>', '>', '>', '<', '<', '>', '>',
/* ! */  '>', '>', '>', '>', '>', '>', ' ', '>', '>',
/* ( */  '<', '<', '<', '<', '<', '<', '<', '=', ' ',
/* ) */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
/* \0*/  '<', '<', '<', '<', '<', '<', '<', ' ', '='
};

Operator optr2rank(char op)
{
    switch(op) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '^': return POW;
        case '!': return FAC;
        case '(': return L_P;
        case ')': return R_P;
        case '\0': return EOE;
        default: exit(-1);
    }
}

char orderBetween(char op1, char op2)
{
    return pri[optr2rank(op1)][optr2rank(op2)];
}

void readNumber(char*& p, Stack<float>& stk)
{
   stk.push((float)(*p - '0'));
   while (isdigit(*(++p)))
       stk.push(stk.pop() * 10 + (*p - '0'));
   if ('.' != *p) return;
   float fraction = 1;
   while (isdigit(*(++p)))
       stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
}

void append(char*& p, float value)
{
    char c[100];
    sprintf(c, "%f", value);
    size_t length = strlen(c);
    strncpy(p, c, length);
    p += length;
}

void append(char*& p, char op)
{
    *p = op;
    p++;
}

float fact(float opnd)
{
    int n = (int)opnd;
    float result = 1.0;
    while (n > 0) {
        result *= n;
        n--;
    }
    return result;
}

float calcu(char op, float opnd)
{
    if (op == '!')
        return fact(opnd); // operator ! is a logical operator by default in C++
    else
        return 0.0;
}

float calcu(float opnd1, char op, float opnd2)
{
    switch(op) {
        case '+': return opnd1 + opnd2;
        case '-': return opnd1 - opnd2;
        case '*': return opnd1 * opnd2;
        case '/': return opnd1 / opnd2;
        case '^': return powf(opnd1, opnd2); // operator ^ is a logical operator by default in C++
        default: return 0.0;
    }
}

float evaluate(char* S, char*& RPN)
{
    Stack<float> opnd;
    Stack<char> optr;
    optr.push('\0');
    while (!optr.empty()) {
        if (isdigit(*S)) {
            readNumber(S, opnd);
            append(RPN, opnd.top());
        } else {
            switch(orderBetween(optr.top(), *S)) {
                case '<':
                    optr.push(*S);
                    S++;
                    break;
                case '=':
                    optr.pop();
                    S++;
                    break;
                case '>': {
                    char op = optr.pop();
                    append(RPN, op);
                    if ('!' == op) {
                        float pOpnd = opnd.pop();
                        opnd.push(calcu(op, pOpnd));
                    } else {
                        float pOpnd2 = opnd.pop();
                        float pOpnd1 = opnd.pop();
                        opnd.push(calcu(pOpnd1, op, pOpnd2));
                    }
                    break;
                }
                default: exit(-1);
            }
        }
    }
    return opnd.pop();
}

int main()
{
    char S[] = "(4+3)*4";
    char* RPN = new char [100];
    float result;
    char* p = RPN;

    result = evaluate(S, RPN);
    std::cout << result << std::endl;
    std::cout << p << std::endl;

    return 0;
}

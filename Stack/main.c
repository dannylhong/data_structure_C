#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

char* GenerateNewData(const char* ch);
int infixToPostfix(char* exp);
int isOperand(char ch);
int Prec(char ch);
void Print(void* pChar);

int main()
{
    char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
  
    // Function call
    infixToPostfix(exp);

    printf("%s\n\n", exp);

    return 0;
}

char* GenerateNewData(const char* ch)
{
    char* pNewData = (char*)malloc(sizeof(char));
    *pNewData = *ch;
    return pNewData;
}

// The main function that
// converts given infix expression
// to postfix expression.
int infixToPostfix(char* exp)
{
    int i, k;
  
    for (i = 0, k = -1; exp[i]; ++i) {
  
        // If the scanned character is
        // an operand, add it to output.
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        
        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (exp[i] == '(')
            Push(GenerateNewData(&exp[i]));

        // If the scanned character is an ‘)’,
        // pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (exp[i] == ')') {
            while (!IsEmpty() && *(char*)Top() != '('){
                char* pData = Pop();
                exp[++k] = *pData;
                free(pData);
            }
            if (!IsEmpty() && *(char*)Top() != '(')
                return -1; // invalid expression
            else
                free(Pop());
        }
  
        else // an operator is encountered
        {
            while (!IsEmpty()
                   && Prec(exp[i]) <= Prec(*(char*)Top())){
                char* pData = Pop();
                exp[++k] = *pData;
                free(pData);
            }
            Push(GenerateNewData(&exp[i]));
        }
    }
  
    // pop all the operators from the stack
    while (!IsEmpty()){
        char* pData = Pop();
        exp[++k] = *pData;
        free(pData);
    }
  
    exp[++k] = '\0';
}
  
// A utility function to check if
// the given character is operand
int isOperand(char ch)
{
    return (ch >= 'a' && ch <= 'z')
           || (ch >= 'A' && ch <= 'Z');
}

// A utility function to return
// precedence of a given operator
// Higher returned value means
// higher precedence
int Prec(char ch)
{
    switch (ch) {
    case '+':
    case '-':
        return 1;
  
    case '*':
    case '/':
        return 2;
  
    case '^':
        return 3;
    }
    return -1;
}

void Print(void* pChar)
{
    printf("%c\n", *(char*)pChar);
}

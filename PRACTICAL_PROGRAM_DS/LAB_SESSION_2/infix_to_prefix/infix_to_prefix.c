#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 50
#define tab '\t'
#define blank ' '
char infix[MAX], prefix[MAX], stack[MAX];
int top = -1, value = 0;
void push(int item);
int pop();
void infix_to_prefix();
int instack_priority(char symbol);
int symbol_priority(char symbol);
int eval_prefix();
void infix_to_prefix()
{
    int i, p = 0;
    char next, symbol, temp;
    for (i = strlen(infix) - 1; i >= 0; i--)
    {
        symbol = infix[i];
        if (symbol != blank || symbol != tab)
        {
            switch (symbol)
            {
            case ')':
                push(symbol);
                break;
            case '(':
                while (next = pop() != ')')
                    prefix[p++] = next;
                break;
            case '+':
            case '-':
            case '*':
            case '%':
            case '^':
            case '/':
                while ((top != -1) && instack_priority(stack[top]) > symbol_priority(symbol))
                    prefix[p++] = pop();
                push(symbol);
                break;
            default:
                prefix[p++] = symbol;
            }
        }
    }
    while (top != -1)
        prefix[p++] = pop();
    prefix[p] = '\0';
    for (int i = 0, j = p - 1; i < j; i++, j--)
    {
        temp = prefix[i];
        prefix[i] = prefix[j];
        prefix[j] = temp;
    }
}
int instack_priority(char symbol)
{
    switch (symbol)
    {
    case ')':
        return 0;

    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
    case '%':
        return 2;

    case '^':
        return 4;
    }
}
int symbol_priority(char symbol)
{
    switch (symbol)
    {
    case ')':
        return 0;

    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
    case '%':
        return 2;

    case '^':
        return 4;
    }
}
void push(int item)
{
    if (top == MAX - 1)
    {
        printf("stack overflow\n");
        return;
    }
    stack[++top] = item;
}
int pop()
{
    if (top == -1)
    {
        printf("stack underflow\n");
        return 0;
    }
    return (stack[top--]);
}

int eval_prefix()
{
    int a, b, tmp, result;
    for (int i = strlen(prefix) - 1; i >= 0; i--)
    {
        if (prefix[i] <= '9' && prefix[i] >= '0')
            push(prefix[i] - 48);
        else
        {
            a = pop();
            b = pop();
            switch (prefix[i])
            {
            case '+':
                tmp = a + b;
                break;
            case '-':
                tmp = a - b;
                break;
            case '*':
                tmp = a * b;
                break;
            case '/':
                tmp = a / b;
                break;
            case '%':
                tmp = a % b;
                break;
            case '^':
                tmp = pow(a, b);
            }
            push(tmp);
        }
    }
    result = pop();
    return result;
}

int main()
{
    printf("enter infix:");
    gets(infix);
    infix_to_prefix();
    printf("prefix= %s\n", prefix);
    value = eval_prefix();
    printf("value=%d", value);
}
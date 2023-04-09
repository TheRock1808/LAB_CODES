#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100
#define tab '\t'
#define blank ' '

char infix[MAX], postfix[MAX], stack[MAX], prefix[MAX], item;
int top = -1, value;

void push(char item)
{
    if (top == MAX - 1)
    {
        printf("stack overflow\n");
        return;
    }
    top = top + 1;
    stack[top] = item;
}
char pop()
{
    if (top == -1)
    {
        printf("stack underflow\n");
        return 0;
    }
    char item = stack[top];
    top = top - 1;
    return item;
}

int instack_priority(char symbol)
{
    switch (symbol)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    }
}
int symbol_priority(char symbol)
{
    switch (symbol)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    }
}

int instack_priority1(char symbol)
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
int symbol_priority1(char symbol)
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

void infix_to_postfix()
{
    int i, p = 0;
    char next, symbol;
    for (i = 0; i < strlen(infix); i++)
    {
        symbol = infix[i];
        if (symbol != blank || symbol != tab)
        {
            switch (symbol)
            {
            case '(':
                push(symbol);
                break;

            case ')':
                while ((next = pop()) != '(')
                    postfix[p++] = next;
                break;

            case '+':
            case '-':
            case '*':
            case '%':
            case '^':
            case '/':
                while ((top != -1) && instack_priority(stack[top]) >= symbol_priority(symbol))
                    postfix[p++] = pop();

                push(symbol);
                break;

            default:
                postfix[p++] = symbol;
            }
        }
    }
    while (top != -1)
        postfix[p++] = pop();
    postfix[p] = '\0';
}
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
                while ((next = pop()) != ')')
                    prefix[p++] = next;
                break;
            case '+':
            case '-':
            case '*':
            case '%':
            case '^':
            case '/':
                while ((top != -1) && instack_priority1(stack[top]) > symbol_priority1(symbol))
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

int eval_post()
{
    int a, b, tmp, result;
    for (int i = 0; i < strlen(postfix); i++)
    {
        if (postfix[i] <= '9' && postfix[i] >= '0')
            push(postfix[i] - '0');
        else
        {
            a = pop();
            b = pop();
            switch (postfix[i])
            {
            case '+':
                tmp = b + a;
                break;
            case '-':
                tmp = b - a;
                break;
            case '*':
                tmp = b * a;
                break;
            case '/':
                tmp = b / a;
                break;
            case '%':
                tmp = b % a;
                break;
            case '^':
                tmp = pow(b, a);
            }
            push(tmp);
        }
    }
    result = pop();
    return result;
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
void display()
{
    printf("Postfix expression:\n");
    for (int i = 0; i < strlen(infix); i++)
    {
        printf("%c ", postfix[i]);
    }
    printf("\n");
}
void display1()
{
    printf("Prefix expression:\n");
    for (int i = 0; i < strlen(infix); i++)
    {
        printf("%c ", prefix[i]);
    }
    printf("\n");
}
int main()
{
    while (1)
    {
        printf("\n\n1: Infix to postfix\n2: Infix to prefix\n3: Evalution of postfix\n4: Evalution of prefix\n5: Exit\n");
        int ch;
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("enter infix: ");
            fflush(stdin);
            gets(infix);
            infix_to_postfix();
            display();
            break;
        case 2:
            printf("enter infix: ");
            scanf("%s", infix);
            infix_to_prefix();
            display1();
            break;
        case 3:
            printf("Value= %d", eval_post());
            break;
        case 4:
            printf("Value= %d", eval_prefix());
            break;
        case 5:
            exit(1);
            break;
        default:
            printf("Wrong Input");
            break;
        }
    }
}
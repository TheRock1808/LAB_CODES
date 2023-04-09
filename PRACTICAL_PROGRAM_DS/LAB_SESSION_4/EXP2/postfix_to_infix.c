#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define max 50
struct node
{
    char data[max];
    struct node *link;
} * top;

// int isOperend(char a)
// {
//     if (a == '+' || a == '-' || a == '*' || a == '/' || a == '^')
//         return 0;
//     else
//         return 1;
// }
void display();
void push(char data[])
{
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    if (tmp == NULL)
    {
        printf("Stack Overfull\n");
        return;
    }
    strcpy(tmp->data, data);
    tmp->link = NULL;
    if (top == NULL)
    {
        top = tmp;
        return;
    }
    tmp->link = top;
    top = tmp;
}

void pop()
{
    if (top == NULL)
    {
        printf("Stack Underflow\n");
        return;
    }
    struct node *tmp = top;
    top = tmp->link;
    free(tmp);
}

int count()
{
    int count = 0;
    struct node *p = top;
    while (p != NULL)
    {
        count++;
        p = p->link;
    }
    return count;
}

void postfix_to_infix(char postfix[])
{
    int i = 0;
    while (postfix[i] != '\0')
    {
        if (isalnum(postfix[i]))
        {
            char od[2];
            od[0] = postfix[i];
            od[1] = '\0';
            push(od);
        }
        else
        {
            if (count() < 2)
            {
                printf("Not sufficient values in the expression\n");
                return;
            }
            char op[2];
            op[0] = postfix[i];
            op[1] = '\0';
            char od1[20], od2[20] = "(";
            strcpy(od1, top->data);
            pop();
            strcat(od2, top->data);
            pop();
            strcat(od2, op);
            strcat(od2, od1);
            strcat(od2, ")");
            push(od2);
        }
        i++;
    }
    if (count() > 1)
    {
        printf("The user input has too many values");
        return;
    }
    display();
    return;
}

void display()
{
    struct node *p = top;
    printf("Infix expression is :");
    while (p != NULL)
    {
        printf(" %s\n", p->data);
        p = p->link;
    }
    printf("\n");
}

int main()
{
    int data, i = 3;
    char postfix[max];
    printf("Enter the postfix expression:");
    fflush(stdin);
    gets(postfix);
    postfix_to_infix(postfix);
}

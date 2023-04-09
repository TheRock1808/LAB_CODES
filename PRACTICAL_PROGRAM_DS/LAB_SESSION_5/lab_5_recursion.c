#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *link;
};

int convert(int n, int b)
{
    if (n == 0)
        return 1;
    convert(n / b, b);
    if (n % b < 10)
        printf("%d", n % b);
    else
        printf("%c", n % b - 10 + 'A');
}

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void tofh(int n, char source, char temp, char dest)
{
    if (n == 1)
    {
        printf("Move disk %d from %c-->%c\n", n, source, dest);
        return;
    }
    tofh(n - 1, source, dest, temp);
    printf("Move disk %d from %c-->%c\n\n", n, source, dest);
    tofh(n - 1, temp, source, dest);
}

void reverse(char *str)
{
    if (*str == '\0')
        return;
    reverse(str + 1);
    putchar(*str);
}

struct node *creat_node(struct node *start, int data)
{
    struct node *tmp = (struct node *)malloc(sizeof(struct node)), *p;
    tmp->data = data;
    tmp->link = NULL;
    if (start == NULL)
    {
        tmp->link = start;
        start = tmp;
        return start;
    }
    p = start;
    while (p->link != NULL)
        p = p->link;
    p->link = tmp;
    return start;
}

int search(struct node *p, int item)
{
    int static count = 1;
    if (p == NULL)
        return -1;
    if (p->data == item)
        return count;
    count++;
    return search(p->link, item);
}

int main()
{
    struct node *tmp, *ptr, *p, *start = NULL;
    int ch, num, b, n, num1, num2, i = 5, item, data, pos, n1;
    char source = 'A', temp = 'B', dest = 'C';
    char word[20];
    while (1)
    {
        printf("\n1: Base Conversion\n2: Tower of Hanoi\n3: GCD\n4: Reverse the string\n5: Search an item in a linked list\n6: Exit\n");
        printf("Enter the choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the number to be converted: ");
            scanf("%d", &num);
            printf("2--> Binary\n8--> Octal\n16--> Hexadecimal\n");
            printf("Enter the base in which number has to be converted: ");
            scanf("%d", &b);
            convert(num, b);
            printf("\n");
            break;

        case 2:
            printf("Enter number of disk: ");
            scanf("%d", &n);
            printf("Sequence is:\n");
            tofh(n, source, temp, dest);
            break;

        case 3:
            printf("Enter 2 numbers: ");
            scanf("%d%d", &num1, &num2);
            printf("Gcd of %d and %d is %d\n", num1, num2, gcd(num1, num2));
            break;

        case 4:
            printf("Enter sentence: ");
            fflush(stdin);
            gets(word);
            reverse(word);
            printf("\n");
            break;

        case 5:
            printf("Enter number of node to be created: ");
            scanf("%d", &n1);
            printf("Enter the elements:\n");
            for (int i = 0; i < n1; i++)
            {
                printf("Enter the data:");
                scanf("%d", &data);
                start = creat_node(start, data);
            }
            printf("Enter item to be searched: ");
            scanf("%d", &item);
            p = start;
            pos = search(p, item);
            if (pos == -1)
                printf("Item not found\n");
            else
                printf("Item found at pos %d\n", pos);
            break;

        case 6:
            exit(1);
        }
    }
    return 0;
}
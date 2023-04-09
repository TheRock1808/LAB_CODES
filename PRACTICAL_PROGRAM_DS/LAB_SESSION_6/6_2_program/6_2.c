#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *prev;
    struct node *link;
};

struct node *create_node(struct node *start, int data)
{
    struct node *tmp = (struct node *)malloc(sizeof(struct node)), *p;
    tmp->data = data;
    tmp->prev = NULL;
    tmp->link = NULL;
    if (start == NULL)
    {
        start = tmp;
        return start;
    }
    p = start;
    while (p->link != NULL)
        p = p->link;
    tmp->prev = p;
    p->link = tmp;
    return start;
}

struct node *add(struct node *start1, struct node *start2, struct node *start3)
{
    struct node *ptr1 = start1, *ptr2 = start2, *p = NULL;
    int carry = 0;
    while (ptr1 != NULL && ptr2 != NULL)
    {
        struct node *tmp = (struct node *)malloc(sizeof(struct node));
        tmp->link = NULL;
        tmp->prev = NULL;
        int sum=0;
        sum = ptr1->data+ptr2->data + carry;
        tmp->data=sum%10;
        carry=sum/10;
        tmp->link=start3;
        if(start3!=NULL) start3->prev=tmp;
        start3=tmp;
        ptr1 = ptr1->link;
        ptr2 = ptr2->link;
    }

    while (ptr1 != NULL)
    {
        struct node *tmp = (struct node *)malloc(sizeof(struct node));
        tmp->link = NULL;
        tmp->prev = NULL;
        int sum=0;
        sum = ptr1->data + carry;
        tmp->data=sum%10;
        carry=sum/10;
        tmp->link=start3;
        if(start3!=NULL) start3->prev=tmp;
        start3=tmp;
        ptr1 = ptr1->link;
    }

    while (ptr2 != NULL)
    {
        struct node *tmp = (struct node *)malloc(sizeof(struct node));
        tmp->link = NULL;
        tmp->prev = NULL;
        int sum=0;
        sum = ptr2->data + carry;
        tmp->data=sum%10;
        carry=sum/10;
        tmp->link=start3;
        if(start3!=NULL) start3->prev=tmp;
        start3=tmp;
        ptr2 = ptr2->link;
    }
   while(carry!=0) 
   {
       struct node *tmp = (struct node *)malloc(sizeof(struct node));
       tmp->link = NULL;
       tmp->prev = NULL;
       tmp->data=carry;
       tmp->link=start3;
       if(start3!=NULL) start3->prev=tmp;
       start3=tmp;
       carry--;
   } 
    return start3;
}

void display(struct node *start)
{
    struct node *p = start;
    printf("Items are:\n");
    while (p != NULL)
    {
        printf("%d ", p->data);
        p = p->link;
    }
    printf("\n");
}
int main()
{
    struct node *start1 = NULL, *start2 = NULL, *start3 = NULL;
    int n, num1, num2, rem = 0;
    printf("Enter the num1: ");
    scanf("%d", &num1);
    while (num1 != 0)
    {
        rem = num1 % 10;
        start1 = create_node(start1, rem);
        num1 /= 10;
    }
    printf("Enter the num2: ");
    scanf("%d", &num2);
    while (num2 != 0)
    {
        rem = num2 % 10;
        start2 = create_node(start2, rem);
        num2 /= 10;
    }
    start3 = add(start1, start2, start3);
    display(start1);
    display(start2);
    display(start3);
}
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

struct node *exchange(struct node *start)
{
    struct node *n1 = start, *n2;
    while (n1 != NULL && n1->link!=NULL)
    {
        n2 = n1->link;
        if (n1->prev != NULL)
            n1->prev->link = n2;
        if (n2->link != NULL)
            n2->link->prev = n1;
        n1->link = n2->link;
        n2->prev = n1->prev;
        n2->link = n1;
        n1->prev = n2;
        n1 = n1->link;
    }
    start = start->prev;
    return start;
}
void display(struct node *start)
{
    struct node *p = start;
    printf("Items are:\n");
    while (p != NULL)
    {
        printf("%d\n", p->data);
        p = p->link;
    }
    printf("\n");
}
int main()
{
    struct node *start = NULL;
    int n, data;
    printf("Enter number of nodes to be created: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter the data: ");
        scanf("%d", &data);
        start = create_node(start, data);
    }
    printf("Before swapping the data\n");
    display(start);
    start = exchange(start);
    printf("After swapping the data\n");
    display(start);
}

#include <stdio.h>
#include <stdlib.h>
struct set
{
    int data;
    struct set *link;
};
int a;
struct set *creat_set(struct set *start, int data);
void display(struct set *start);
void union_set(struct set *set1, struct set *set2);
void intersection_set(struct set *set1, struct set *set2);

struct set *creat_set(struct set *start, int data)
{
    struct set *tmp = (struct set *)malloc(sizeof(struct set)), *ptr, *p;
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
    {
        if (p->data == data)
            return start;
        p = p->link;
    }
    tmp->link = p->link;
    p->link = tmp;
    return start;
}

void union_set(struct set *set1, struct set *set2)
{
    struct set *p, *a = NULL;
    for (p = set1; p != NULL; p = p->link)
        a = creat_set(a, p->data);

    for (p = set2; p != NULL; p = p->link)
        a = creat_set(a, p->data);
    display(a);
}

void intersection_set(struct set *set1, struct set *set2)
{
    struct set *p, *q;
    p = set1;
    printf("Intersection values: ");
    while (p != NULL)
    {
        q = set2;
        while (q != NULL)
        {
            if (p->data == q->data)
            {
                printf("%d, ", q->data);
                q = q->link;
                break;
            }
            q = q->link;
        }
        p = p->link;
    }
}

void difference_set(struct set *set1, struct set *set2)
{
    struct set *p, *q;
    printf("Enter your choice:\n");
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        p = set1;
        printf("A - B: ");
        while (p != NULL)
        {
            q = set2;
            while (q != NULL)
            {
                if (p->data == q->data)
                {
                    p = p->link;
                    break;
                }
                q = q->link;
            }
            printf("%d, ", p->data);
            p = p->link;
        }
        break;
    case 2:
        q = set2;
        printf("B - A: ");
        while (q != NULL)
        {
            p = set1;
            while (p != NULL)
            {
                if (p->data == q->data)
                {
                    q = q->link;
                    break;
                }
                p = p->link;
            }
            printf("%d, ", q->data);
            q = q->link;
        }
        break;
    default:
        printf("Wrong input\n");
        break;
    }
}
void display(struct set *start)
{
    struct set *p;
    p = start;
    while (p != NULL)
    {
        printf("%d, ", p->data);
        p = p->link;
    }
    printf("\n");
}

int main()
{
    int m, n, ch, data;
    struct set *set1 = NULL, *set2 = NULL, *diff_set = NULL;
    printf("enter number of node to be created for set A:");
    scanf("%d", &n);
    printf("Enter the elements for set A:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Enter the data:");
        scanf("%d", &data);
        set1 = creat_set(set1, data);
    }
    printf("enter number of node to be created for set B:");
    scanf("%d", &m);
    printf("Enter the elements for set B\n:");
    for (int i = 0; i < m; i++)
    {
        printf("Enter the data:");
        scanf("%d", &data);
        set2 = creat_set(set2, data);
    }
    while (1)
    {
        printf("\n1: Union of set \n2: Intersection of 2 set\n3: Difference the sets\n4: display the sets\n5:Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            union_set(set1, set2);
            break;

        case 2:
            intersection_set(set1, set2);
            break;

        case 3:
            printf("1: A - B\n 2: B - A\n");
            difference_set(set1, set2);
            break;

        case 4:
            printf("SET A: ");
            display(set1);
            printf("SET B: ");
            display(set2);
            break;

        case 5:
            exit(1);
            break;

        default:
            printf("Wrong Input\n");
            break;
        }
    }
}
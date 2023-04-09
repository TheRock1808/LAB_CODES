#include <stdio.h>
#include <stdlib.h>

struct poly
{
    int coef, expo;
    struct poly *link;
};
int n;
struct poly *creat_poly(struct poly *start, int coef, int expo);
void display(struct poly *start);
struct poly *add(struct poly *poly1, struct poly *poly2, struct poly *final_poly);
struct poly *multiply_poly(struct poly *poly1, struct poly *poly2, struct poly *final_poly);
struct poly *delete (struct poly *start);
struct poly *poly1file(struct poly *start);
struct poly *poly2file(struct poly *start);

struct poly *creat_poly(struct poly *start, int coef, int expo)
{
    struct poly *tmp = (struct poly *)malloc(sizeof(struct poly)), *ptr, *p;
    tmp->coef = coef;
    tmp->expo = expo;
    tmp->link = NULL;
    ptr = start;
    while (ptr != NULL)
    {
        if (ptr->expo == tmp->expo)
            ptr->coef += tmp->coef;
        ptr = ptr->link;
    }
    if (start == NULL || start->expo < tmp->expo)
    {
        tmp->link = start;
        start = tmp;
        return start;
    }
    p = start;
    while (p->link != NULL && p->link->expo > tmp->expo)
    {
        p = p->link;
    }
    tmp->link = p->link;
    p->link = tmp;
    return start;
}

struct poly *add(struct poly *poly1, struct poly *poly2, struct poly *final_poly)
{
    while (poly1 != NULL && poly2 != NULL)
    {
        if (poly1->expo > poly2->expo)
        {
            final_poly = creat_poly(final_poly, poly1->coef, poly1->expo);
            poly1 = poly1->link;
        }
        else if (poly2->expo > poly1->expo)
        {
            final_poly = creat_poly(final_poly, poly2->coef, poly2->expo);
            poly2 = poly2->link;
        }
        else
        {
            final_poly = creat_poly(final_poly, (poly1->coef + poly2->coef), poly1->expo);
            poly1 = poly1->link;
            poly2 = poly2->link;
        }
    }
    while (poly1 != NULL)
    {
        final_poly = creat_poly(final_poly, poly1->coef, poly1->expo);
        poly1 = poly1->link;
    }

    while (poly2 != NULL)
    {
        final_poly = creat_poly(final_poly, poly2->coef, poly2->expo);
        poly2 = poly2->link;
    }
    return final_poly;
}

struct poly *multiply_poly(struct poly *poly1, struct poly *poly2, struct poly *final_poly)
{
    struct poly *tmp = NULL, *ptr1 = NULL, *ptr2 = NULL, *p;
    ptr1 = poly1; //poly1 value is stored in ptr1

    while (ptr1 != NULL)
    {
        ptr2 = poly2; //poly2 value is stored in ptr2
        while (ptr2 != NULL)
        {
            int flag = 1;
            p = final_poly;
            while (p != NULL)
            {
                if (p->expo == (ptr2->expo + ptr1->expo))
                {
                    p->coef += ptr2->coef * ptr1->coef;
                    ptr2 = ptr2->link;
                    flag = 0;
                    break;
                }
                p = p->link;
            }
            if (flag)
            {
                struct poly *result = (struct poly *)malloc(sizeof(struct poly));
                result->link = NULL;
                if (final_poly == NULL)
                {
                    final_poly = result;
                    tmp = result;
                }
                else
                {
                    tmp->link = result;
                    tmp = result;
                    tmp->link = NULL;
                }
                result->coef = ptr2->coef * ptr1->coef;
                result->expo = ptr2->expo + ptr1->expo;
                ptr2 = ptr2->link;
            }
        }
        ptr1 = ptr1->link;
    }
    return final_poly;
}
void display(struct poly *start)
{
    struct poly *p;
    p = start;
    while (p != NULL)
    {
        printf("%dx^%d+", p->coef, p->expo);
        p = p->link;
    }
    printf("\n\n");
}
int countnode(struct poly *start)
{
    struct poly *ptr = start;
    int count = 0;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->link;
    }
    return count;
}
struct poly *delete (struct poly *start)
{
    struct poly *next, *prv;
    int pos;
    printf("count:%d\n", countnode(start));
    printf("enter the position to delete the node:");
    scanf("%d", &pos);
    if (pos == 1)
    {
        next = start;
        start = next->link;
        free(next);
        return start;
    }
    else if (prv == NULL)
    {
        printf("The list is over");
        return start;
    }
    int count = 0;
    struct poly *traverse = start;
    while (traverse != NULL && count < pos - 1)
    {
        count++;
        traverse = traverse->link;
    }
    next = start;
    for (int i = 1; i <= pos - 1; i++)
    {
        prv = next;
        next = next->link;
    }
    next = prv->link;
    prv->link = next->link;
    free(next);
    return start;
}

struct poly *poly1file(struct poly *start)
{
    FILE *fp;
    int n, coef, expo;
    fp = fopen("poly1.txt", "r");
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &coef);
        fscanf(fp, "%d", &expo);
        start = creat_poly(start, coef, expo);
    }
    fclose(fp);
    return start;
}
struct poly *poly2file(struct poly *start)
{
    FILE *fp;
    int n, coef, expo;
    fp = fopen("poly2.txt", "r");
    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &coef);
        fscanf(fp, "%d", &expo);
        start = creat_poly(start, coef, expo);
    }
    fclose(fp);
    return start;
}
int main()
{
    int m, ch, a, coef, expo;
    struct poly *poly1 = NULL, *poly2 = NULL, *add_poly = NULL, *multi_poly = NULL;
    while (1)
    {
        printf("\n\n1: Create 2 polynomial\n2: Addition of 2 polynomials\n3: Multiplication of 2 polynomials\n4: Display the polynomials\n5: Modify the polynomials\n6: File Input\n7: Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("enter number of terms to be created for polynomial 1:");
            scanf("%d", &n);
            printf("Enter the elements for polynomial 1:\n");
            for (int i = 0; i < n; i++)
            {
                printf("Enter the coeffecient: ");
                scanf("%d", &coef);
                printf("Enter the exponent: ");
                scanf("%d", &expo);
                poly1 = creat_poly(poly1, coef, expo);
            }
            printf("enter number of terms to be created for polynomial 2:");
            scanf("%d", &m);
            printf("Enter the elements for polynomial 2\n:");
            for (int i = 0; i < m; i++)
            {
                printf("Enter the coeffecient: ");
                scanf("%d", &coef);
                printf("Enter the exponent: ");
                scanf("%d", &expo);
                poly2 = creat_poly(poly2, coef, expo);
            }
            break;

        case 2:
            add_poly = add(poly1, poly2, add_poly);
            display(add_poly);
            break;

        case 3:
            multi_poly = multiply_poly(poly1, poly2, multi_poly);
            display(multi_poly);
            break;

        case 4:
            printf("POLYNOMIAL 1: ");
            display(poly1);
            printf("POLYNOMIAL 2: ");
            display(poly2);
            printf("ADDED POLYNOMIAL: ");
            display(add_poly);
            printf("MULTIPLIED POLYNOMIAL: ");
            display(multi_poly);
            break;

        case 5:
            while (add_poly != NULL)
            {
                struct poly *x = add_poly;
                add_poly = add_poly->link;
                free(x);
            }
            while (multi_poly != NULL)
            {
                struct poly *x = multi_poly;
                multi_poly = multi_poly->link;
                free(x);
            }
            printf("1: Insert a new polynomial 1\n2: Delete a polynomial 1\n3: Insert a new polynomial 2\n4: Delete a polynomial 2\n");
            printf("Enter your choice:");
            scanf("%d", &a);
            switch (a)
            {
            case 1:
                printf("Enter the coeffecient: ");
                scanf("%d", &coef);
                printf("Enter the exponent: ");
                scanf("%d", &expo);
                poly1 = creat_poly(poly1, coef, expo);
                break;
            case 2:
                poly1 = delete (poly1);
                break;
            case 3:
                printf("Enter the coeffecient: ");
                scanf("%d", &coef);
                printf("Enter the exponent: ");
                scanf("%d", &expo);
                poly2 = creat_poly(poly2, coef, expo);
                break;
            case 4:
                poly2 = delete (poly2);
                break;
            default:
                printf("Wrong Input");
                break;
            }
            break;

        case 6:
            poly1 = poly1file(poly1);
            poly2 = poly2file(poly2);
            break;

        case 7:
            exit(1);
            break;

        default:
            printf("Wrong Input");
            break;
        }
    }
}
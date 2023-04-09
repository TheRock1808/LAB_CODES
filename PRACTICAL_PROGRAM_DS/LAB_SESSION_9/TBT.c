#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
    int lthread;
    int rthread;
} NODE;

NODE *insert(NODE *root, int key)
{
    NODE *par = NULL, *ptr = root;
    while (ptr != NULL)
    {

        if (key == ptr->data)
        {
            printf("Duplicate values\n");
            return root;
        }

        par = ptr;
        if (key < ptr->data)
        {
            if (ptr->lthread == 0)
                ptr = ptr->lchild;
            else
                break;
        }
        else
        {
            if (ptr->rthread == 0)
                ptr = ptr->rchild;
            else
                break;
        }
    }

    ptr = (NODE *)malloc(sizeof(NODE));
    ptr->data = key;
    ptr->lthread = 1;
    ptr->rthread = 1;
    ptr->rchild = NULL;
    ptr->lchild = NULL;
    if (par == NULL)
    {
        root = ptr;
    }
    else if (key < par->data)
    {
        ptr->lchild = par->lchild;
        ptr->rchild = par;
        par->lthread = 0;
        par->lchild = ptr;
    }

    else
    {
        ptr->rchild = par->rchild;
        ptr->lchild = par;
        par->rthread = 0;
        par->rchild = ptr;
    }
    return root;
}

void search(NODE *root, int key)
{
    NODE *par = NULL, *ptr = root;
    while (ptr != NULL)
    {

        if (key == ptr->data)
        {
            printf("Key is present\n");
            return;
        }

        par = ptr;
        if (key < ptr->data)
        {
            if (ptr->lthread == 0)
                ptr = ptr->lchild;
            else
                break;
        }
        else
        {
            if (ptr->rthread == 0)
                ptr = ptr->rchild;
            else
                break;
        }
    }

    printf("Key not present\n");
    return;
}

NODE *insuc(NODE *root)
{
    if (root->rthread)
        return root->rchild;
    root = root->rchild;
    while (!root->lthread)
        root = root->lchild;
    return root;
}

NODE *inpred(NODE *root)
{
    if (root->lthread)
        return root->lchild;
    root = root->lchild;
    while (!root->rthread)
        root = root->rchild;
    return root;
}

void inorder(NODE *root)
{
    while (!root->lthread)
        root = root->lchild;
    while (root != NULL)
    {
        printf("%d ", root->data);
        root = insuc(root);
    }
    printf("\n");
}

NODE *caseA(NODE *root, NODE *par, NODE *ptr)
{

    if (par == NULL)
    {
        root = NULL;
        return root;
    }

    if (ptr == par->lchild)
    {
        par->lthread = 1;
        par->lchild = ptr->lchild;
    }
    else
    {
        par->rthread = 1;
        par->rchild = ptr->rchild;
    }
    free(ptr);
    return root;
}

NODE *caseB(NODE *root, NODE *par, NODE *ptr)
{
    NODE *child;
    if (!ptr->lthread)
        child = ptr->lchild;
    else
        child = ptr->rchild;
    if (par == NULL)
    {
        root = child;
        return root;
    }
    else if (par->lchild = ptr)
        par->lchild = child;
    else
        par->rchild = child;
    NODE *s = insuc(ptr);
    NODE *p = inpred(ptr);
    if (!ptr->lthread)
        p->rchild = s;
    else
        s->lchild = p;
    free(ptr);
    return root;
}

NODE *caseC(NODE *root, NODE *par, NODE *ptr)
{
    NODE *parsuc = ptr, *suc = ptr->rchild;
    while (!suc->lthread)
    {
        parsuc = suc;
        suc = suc->lchild;
    }

    ptr->data = suc->data;
    if (suc->lthread && suc->rthread)
        root = caseA(root, parsuc, suc);
    else
        root = caseB(root, parsuc, suc);
    return root;
}

NODE *delete (NODE *root, int key)
{
    NODE *par = NULL, *ptr = root;

    while (ptr != NULL)
    {
        if (key == ptr->data)
            break;
        par = ptr;
        if (key < ptr->data)
        {
            if (!ptr->lthread)
                ptr = ptr->lchild;
            else
                break;
        }
        else
        {
            if (!ptr->rthread)
                ptr = ptr->rchild;
            else
                break;
        }
    }
    if (ptr == NULL)
    {
        printf("Element not present\n");
        return root;
    }
    else if (ptr->lthread && ptr->rthread)
    {

        root = caseA(root, par, ptr);
    }
    else if (ptr->lthread || ptr->rthread)
    {

        root = caseB(root, par, ptr);
    }
    else
    {
        root = caseC(root, par, ptr);
    }
    return root;
}

int main()
{
    NODE *root = NULL;
    int a[] = {38, 94, 96, 28, 68, 66, 49, 23, 81, 79, 86};
    for (int i = 0; i < 11; i++)
    {
        root = insert(root, a[i]);
    }
    int m = 1, data;
    while (m)
    {
        printf("1: Insert\n2: Delete\n3: Display\n4: Search\n");
        scanf("%d", &m);
        switch (m)
        {
        case 1:
            printf("Enter the element to be inserted\n");
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 2:
            printf("Enter the data to be deleted\n");
            scanf("%d", &data);
            root = delete (root, data);
            break;
        case 3:
            printf("Indorder: ");
            inorder(root);
            break;
        case 4:
            printf("Enter the number to be searched\n");
            scanf("%d", &data);
            search(root, data);
            break;
        default:
            break;
        }
    }
}
#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
} node;

#define max 100
node *queue[max];
int front = -1, rear = -1;
struct node *createtree1(int inorder[], int postorder[], int *index, int inorderstart, int inorderend, int n);
void insert_queue(node *item);
node *del();
int queue_empty();
void display_LtoR(node *start, int level);
void display_RtoL(node *start, int level);
void preorder(node *p);
void postorder(node *p);
void inorder(node *p);
int height(node *p);
node *level_trav(node *p);
void spiral_traversal(node *start);
int depth_of_node(node *start, int item);

int findpos(int inorder[], int element, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (inorder[i] == element)
            return i;
    }
    return -1;
}

int main()
{
    int in[100], n, post[100], ch, item;
    printf("Enter the size of inorder list and postorder list: ");
    scanf("%d", &n);
    printf("Enter elements to inorder list:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &in[i]);
    }
    printf("Enter elements to postorder list:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &post[i]);
    }
    int post_index = n - 1;
    node *start;
    start = createtree1(in, post, &post_index, 0, n - 1, n);
    while (1)
    {
        printf("1: Height of the tree\n2: Level order traversal\n3: Spiral order traversal\n4: Depth in the node\n5: Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Height:%d\n", height(start));
            break;
        case 2:
            level_trav(start);
            break;
        case 3:
            spiral_traversal(start);
            break;
        case 4:
            printf("Enter item whose depth has to be found: ");
            scanf("%d", &item);
            printf("depth of node %d is %d", item, depth_of_node(start, item));
        case 5:
            exit(1);
            break;
        default:
            printf("Wrong input");
            break;
        }
    }
}

struct node *createtree1(int inorder[], int postorder[], int *index, int inorderstart, int inorderend, int n)
{
    if (*index < 0 || inorderstart > inorderend)
        return NULL;

    node *p = (node *)malloc(sizeof(node));
    int element = postorder[(*index)--];
    p->data = element;
    int pos = findpos(inorder, element, n);
    p->rchild = createtree1(inorder, postorder, index, pos + 1, inorderend, n);
    p->lchild = createtree1(inorder, postorder, index, inorderstart, pos - 1, n);
    return p;
}

void preorder(node *p)
{
    if (p == NULL)
        return;
    printf("%d ", p->data);
    preorder(p->lchild);
    preorder(p->rchild);
}

void postorder(node *p)
{
    if (p == NULL)
        return;
    postorder(p->lchild);
    postorder(p->rchild);
    printf("%d ", p->data);
}

void inorder(node *p)
{
    if (p == NULL)
        return;
    inorder(p->lchild);
    printf("%d ", p->data);
    inorder(p->rchild);
}
int height(node *p)
{
    if (p == NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        int lheight = height(p->lchild);
        int rheight = height(p->rchild);

        /* use the larger one */
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

int queue_empty()
{
    if (front == rear + 1 || front == -1)
        return 1;
    else
        return 0;
}

node *level_trav(node *p)
{
    node *ptr = p;
    if (ptr == NULL)
    {
        printf("Tree is empty\n");
        return 0;
    }
    insert_queue(ptr);
    printf("Level order traversal: ");
    while (!queue_empty())
    {
        ptr = del();
        printf("%d ", ptr->data);
        if (ptr->lchild != NULL)
            insert_queue(ptr->lchild);
        if (ptr->rchild != NULL)
            insert_queue(ptr->rchild);
    }
    printf("\n");
}
void insert_queue(node *item)
{
    if (rear == max - 1)
    {
        printf("Queue overflow\n");
        return;
    }
    if (front == -1)
        front = 0;
    rear = rear + 1;
    queue[rear] = item;
}

node *del()
{
    node *item;
    if (front == rear + 1 || front == -1)
    {
        printf("Queue underflow\n");
        return 0;
    }
    item = queue[front];
    front = front + 1;
    return item;
}

void spiral_traversal(node *start)
{
    for (int i = 0; i < height(start); i++)
    {
        if (i % 2 == 0)
            display_LtoR(start, i);
        else
            display_RtoL(start, i);
    }
    printf("\n");
}
void display_LtoR(node *start, int level)
{
    node *p = start;
    if (p == NULL)
        return;
    if (level == 0)
        printf("%d ", p->data);
    display_LtoR(p->lchild, level - 1);
    display_LtoR(p->rchild, level - 1);
}
void display_RtoL(node *start, int level)
{
    node *p = start;
    if (p == NULL)
        return;
    if (level == 0)
        printf("%d", p->data);
    display_LtoR(p->rchild, level - 1);
    display_LtoR(p->lchild, level - 1);
}
int depth_of_node(node *start, int item)
{
    node *p = start;
    if (p == NULL)
        return -1;
    int dist = -1;
    if (p->data == item || (dist = depth_of_node(p->lchild, item)) >= 0 || (dist = depth_of_node(p->rchild, item)) >= 0)
        return dist + 1;
    return dist;
}
// struct node *createtree(int inorder[],int preorder[],int *index,int inorderstart,int inorderend,int n)
// {
//     if(*index>=n || inorderstart>inorderend) return NULL;

//     node*p=(node*)malloc(sizeof(node));
//     int element=preorder[(*index)++];
//     p->data=element;
//     int pos=findpos(inorder,element,n);
//     p->lchild=createtree(inorder,preorder,index,inorderstart,pos-1,n);
//     p->rchild=createtree(inorder,preorder,index,pos+1,inorderend,n);
//     return p;
// }
// printf("Preorder: ");
// preorder(start);
// printf("Enter elements to preorder list:\n");
// for(int i=0;i<n;i++)
// {
//     scanf("%d",&pre[i]);
// }

// int preorder_index=0;
// node *start;
// start=createtree(in,pre,&preorder_index,0,n-1,n);
// printf("\nPostorder: ");
// postorder(start);
// printf("\nInorder: ");
// inorder(start);
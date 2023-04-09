#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} node;

int height(node *N)
{
    if (N == NULL)
        return 0;

    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getBalance(node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

node *newNode(int key)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = key;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}

node *rightRotate(node *y)
{
    node *x = y->left;
    node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    // Return new root
    return x;
}

node *leftRotate(node *x)
{
    node *y = x->right;
    node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;

    // Return new root
    return y;
}

node *insert(node *root, int key)
{
    if (root == NULL)
        return (newNode(key));
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    else
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;

    int balance_factor = getBalance(root);

    if (balance_factor > 1 && key < root->left->data)
        return rightRotate(root);
    else if (balance_factor < -1 && key > root->right->data)
        return leftRotate(root);

    // Left Right Case
    if (balance_factor > 1 && key > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance_factor < -1 && key < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

node *minValueNode(node *node)
{
    struct Node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

node *deleteNode(node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            node *temp = root->left ? root->left : root->right;
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else
        {
            node *temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    if (root == NULL)
        return root;
    root->height = 1 + max(height(root->left),
                           height(root->right));
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
int getWidth(node *root, int level);
int getMaxWidth(node *root)
{
    int maxWidth = 0;
    int width;
    int h = height(root);
    int i;
    /* Get width of each level and compare
       the width with maximum width so far */
    for (i = 1; i <= h; i++)
    {
        width = getWidth(root, i);
        if (width > maxWidth)
            maxWidth = width;
    }

    return maxWidth;
}

int getWidth(node *root, int level)
{

    if (root == NULL)
        return 0;

    if (level == 1)
        return 1;

    else if (level > 1)
        return getWidth(root->left, level - 1) + getWidth(root->right, level - 1);
}

void search(node *root, int data)
{
    if (root == NULL)
    {
        printf("Data not present\n");
        return;
    }
    if (data < root->data)
    {
        search(root->left, data);
    }
    else if (data > root->data)
    {
        search(root->right, data);
    }
    else
    {
        printf("Data present\n");
    }

    return;
}

void preOrder(node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void minmax(node *root)
{
    node *tmp = root;
    while (tmp->left != NULL)
        tmp = tmp->left;
    printf("Min value: %d ", tmp->data);
    while (root->right != NULL)
        root = root->right;
    printf("Max value: %d\n", root->data);
}

void display_inorder(node *root)
{
    if (root == NULL)
        return;
    display_inorder(root->left);
    printf("%d ", root->data);
    display_inorder(root->right);
}

void display_decend(node *root)
{
    if (root == NULL)
        return;
    display_decend(root->right);
    printf("%d", root->data);
    display_decend(root->left);
}

int main()
{
    /* The constructed AVL Tree would be
            30
           /  \
         20   40
        /  \     \
       10  25    50
  */
    node *root = NULL;
    int data;
    int m = 1;
    while (m)
    {
        printf("\n1:Insert a node\n2:Delete a node\n3:Display Inorder\n4:Search\n5:Max and Min value\n6:Display in decending order\n7: Width of the tree\n");
        scanf("%d", &m);
        switch (m)
        {
        case 1:
            printf("Enter Data to be inserted\n");
            scanf("%d", &data);
            root = insert(root, data);
            break;
        case 2:
            printf("Enter Data to be deleted\n");
            scanf("%d", &data);
            root = deleteNode(root, data);
            break;
        case 3:
            printf("Inorder traverse: ");
            display_inorder(root);
            printf("\n");
            break;
        case 4:
            printf("Enter data to be searched\n");
            scanf("%d", &data);
            search(root, data);
            break;
        case 5:
            minmax(root);
            break;
        case 6:
            printf("Decending order\n");
            display_decend(root);
            printf("\n");
            break;
        case 7:
            printf("Width is %d\n", getMaxWidth(root));
            break;
        default:
            printf("Wrong Input\n");
            break;
        }
    }
}
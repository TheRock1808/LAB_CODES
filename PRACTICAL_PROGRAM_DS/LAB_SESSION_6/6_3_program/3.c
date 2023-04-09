#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node* next;
}node;

node* createNode()
{
    node* temp = (node*)malloc(sizeof(node));
    printf("Enter the data\n");
    scanf("%d",&temp->data);
    temp->next = NULL;
    return temp;
}

node *insertatempty(node *last)
{
    node *temp = createNode();
    temp->next = temp;
    return temp;
}
node *insertatbeg(node *last)
{
    if(last == NULL) return insertatempty(last);
    node *temp = createNode();
    temp->next = last->next;
    last ->next = temp;
    return last;
}

node *insertatend(node *last)
{
    if(last == NULL) return insertatempty(last);
    node* temp = createNode();
    temp -> next = last -> next;
    last -> next = temp;
    last=temp;
    return last;
}

node* delalt(node* last)
{
    if(last == NULL || last->next == last)return last;
    node *p = last->next;
    while(1)
    {
        node *temp = p->next;
        p -> next = temp -> next;
        if(temp == last) last = p;
        free(temp);
        p = p->next;
        if(p == last || p==last->next)break;
    }
    return last;
}

void display(node* last)
{
    if(last == NULL){printf("Empty List\n");return;}
    node *p = last->next;
    do
    {
        printf("%d ",p->data);
        p = p->next;
    } while (p != last->next);
    printf("\n");
}

int main()
{
    node *last = NULL;
    for(int i=0;i<6;i++) {last = insertatend(last);}
    // last = insertatend(last);
    // last = insertatend(last);
    // last = insertatend(last);
    // last = insertatend(last);
    // last = insertatend(last);
    // last = insertatend(last);
    last = delalt(last);
    display(last);
}
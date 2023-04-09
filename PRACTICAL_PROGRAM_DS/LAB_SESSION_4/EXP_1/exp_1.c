#include <stdio.h>
#include <stdlib.h>

struct node
{
   int data;
   struct node *link;
};

struct node *enqueue(struct node **front, struct node *rear, int data)
{
   struct node *tmp = (struct node *)malloc(sizeof(struct node));
   if (tmp == NULL)
   {
      printf("queue overfull\n");
      return 0;
   }
   tmp->data = data;
   tmp->link = NULL;
   if (rear != NULL)
      rear->link = tmp;
   rear = tmp;
   if (*front == NULL)
      *front = tmp;
   return rear;
}

struct node *dequeue(struct node *front)
{
   struct node *tmp = front;
   if (front == NULL)
   {
      printf("queue is empty\n");
      return 0;
   }
   front = tmp->link;
   printf("Item deleted is %d\n", tmp->data);
   free(tmp);
   return front;
}

void display(struct node *front, struct node *rear)
{
   struct node *p = front;
   while (p != NULL)
   {
      printf("%d\n", p->data);
      p = p->link;
   }
   printf("\n");
}
int main()
{
   struct node *front = NULL, *rear = NULL;
   int ch, data;
   while (1)
   {
      printf("1: enqueue\n2: dequeue\n3: display\n4: exit\n");
      printf("enter choice:");
      scanf("%d", &ch);
      switch (ch)
      {
      case 1:
         printf("enter the data:");
         scanf("%d", &data);
         rear = enqueue(&front, rear, data);
         break;
      case 2:
         front = dequeue(front);
         break;
      case 3:
         display(front, rear);
         break;
      case 4:
         exit(1);
      default:
         printf("Wrong input");
         break;
      }
   }
}

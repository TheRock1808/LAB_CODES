#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define max 5

struct TASK
{
    int TaskId;
    char TaskTitle[100];
    int TaskDuration;
    char Status[100];
};

struct TASK task[10] =
    {
        {100, "Task1", 3, "Idle"},
        {101, "Task2", 3, "Idle"},
        {102, "Task3", 3, "Idle"},
        {103, "Task4", 3, "Idle"},
        {104, "Task5", 3, "Idle"},
        {105, "Task6", 3, "Idle"},
        {106, "Task7", 3, "Idle"},
        {107, "Task8", 3, "Idle"},
        {108, "Task9", 3, "Idle"},
        {109, "Task10", 3, "Idle"}};

int taskcount = 10;

struct TASK queue[max];
int front = -1, rear = -1;

void enqueue(struct TASK task)
{
    if (rear == max - 1)
    {
        printf("\nQueue is full\n");
        int waitTimeMin = queue[front].TaskDuration, waitTimeMax = 0;
        for (int i = front; i <= rear; i++)
        {
            waitTimeMax += queue[i].TaskDuration;
        }
        printf("Wait time is between %d and %d seconds\n", waitTimeMin, waitTimeMax);
    }
    else if (front == -1 && rear == -1)
    {
        front = rear = 0;
        queue[rear].TaskDuration = task.TaskDuration;
        queue[rear].TaskId = task.TaskId;
        strcpy(queue[rear].TaskTitle, task.TaskTitle);
        strcpy(queue[rear].Status, "Queued");
    }
    else
    {
        rear++;
        queue[rear].TaskDuration = task.TaskDuration;
        queue[rear].TaskId = task.TaskId;
        strcpy(queue[rear].TaskTitle, task.TaskTitle);
        strcpy(queue[rear].Status, "Queued");
    }
}

void dequeue()
{
    if (front == -1 && rear == -1 || front == rear + 1)
    {
        printf("\nQueue is empty\n");
    }
    else
    {
        printf("Task %d is running\n", queue[front].TaskId);
        sleep(queue[front].TaskDuration);
        printf("Task %d is completed\n", queue[front].TaskId);
        front++;
        // make status completed
        for (int i = 0; i < taskcount; i++)
        {
            if (task[i].TaskId == queue[front - 1].TaskId)
            {
                strcpy(task[i].Status, "Completed");
            }
        }
    }
}

int main()
{
    int choice;
    while (1)
    {

        printf("\n1. Schedule task\n");
        printf("2. Run task\n");
        printf("3. Display scheduled Task\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("TaskId  TaskTitle\n");
            for (int i = 0; i < taskcount; i++)
            {
                printf("%d\t", task[i].TaskId);
                printf("%s \n", task[i].TaskTitle);
            }
            printf("\nEnter the task id of the tasks to be scheduled\n");
            printf("\n");
            int id;
            scanf("%d", &id);
            for (int i = 0; i < taskcount; i++)
            {
                if (task[i].TaskId == id)
                {
                    if (strcmp(task[i].Status, "Idle") == 0)
                    {
                        enqueue(task[i]);
                        strcpy(task[i].Status, "Queued");
                    }
                    else
                    {
                        printf("Task is already queued or completed\n");
                    }
                }
            }
            break;
        case 2:
            dequeue();
            break;
        case 3:
            printf("\nQueued tasks:\n");
            printf("Task_Id\tTask_Title\tTask_Duration\tStatus\n");
            for (int i = front; i <= rear; i++)
            {
                printf("%d\t", queue[i].TaskId);
                printf("%s\t\t", queue[i].TaskTitle);
                printf("%d\t\t", queue[i].TaskDuration);
                printf(" %s\t", queue[i].Status);
                printf("\n");
            }

            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Invalid choice\n");
        }
    }
}
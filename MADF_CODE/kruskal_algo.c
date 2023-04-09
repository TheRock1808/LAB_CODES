#include <stdio.h>
#include <limits.h>

#define v 8

typedef struct edge
{
	int a;
	int b;
	int cost;
} EDGE;
EDGE arr[v * v];
int size = 0;

int t[v][2];

int g[v][v] = {
	{0, 10, 0, 0, 0, 0, 0, 0},
	{10, 0, 9, 0, 5, 0, 0, 0},
	{0, 9, 0, 5, 4, 3, 0, 0},
	{0, 0, 5, 0, 0, 0, 0, 11},
	{0, 5, 4, 0, 0, 2, 7, 0},
	{0, 0, 3, 0, 2, 0, 8, 6},
	{0, 0, 0, 0, 7, 8, 0, 0},
	{0, 0, 0, 11, 0, 6, 0, 0},
};

int parent[v];

/*
void restroredown(int i){
    int left=2*i,right=left+1;
    EDGE num=arr[i];
    while(right<=size){
        if(num.cost<=arr[left].cost && num.cost<=arr[right].cost){
            arr[i]=num;
        }
        else if(arr[left].cost<arr[right].cost){
            arr[i]=arr[left];
            i=left;
        }
        else{
            arr[i]=arr[right];
            i=right;
        }
        left=2*i;
        right=left+1;
    }
    if(left==size && num.cost>arr[left].cost){
        arr[i]=arr[left];
        i=left;
    }
    arr[i]=num;
    printf("c");
}

void buildheap(){
    for(int i=size/2;i>=1;i--)
        restroredown(i);
}
*/

void sort()
{
	for (int i = 0; i < size; i++)
	{
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[min].cost > arr[j].cost)
				min = j;
		}
		if (i != min)
		{
			EDGE tmp = arr[i];
			arr[i] = arr[min];
			arr[min] = tmp;
		}
	}
}

void makeedges()
{
	for (int i = 0; i < v; i++)
	{
		for (int j = i; j < v; j++)
		{
			if (g[i][j] > 0)
			{
				arr[size].a = i;
				arr[size].b = j;
				arr[size].cost = g[i][j];
				size++;
			}
		}
	}
}

int find(int i)
{
	while (parent[i] > -1)
		i = parent[i];
	return i;
}

int unionP(int i, int j)
{
	parent[i] = j;
}

void kruskals()
{
	int mincost = 0;
	makeedges();
	for (int i = 0; i < v; i++)
		parent[i] = -1;
	//buildheap();
	sort();
	for (int i = 0; i < size; i++)
	{
		//printf("%d %d %d\n",arr[i].a+1,arr[i].b+1,arr[i].cost);
		int k, l;
		k = find(arr[i].a);
		l = find(arr[i].b);
		if (k != l)
		{
			t[i][0] = arr[i].a;
			t[i][1] = arr[i].b;
			mincost += arr[i].cost;
			unionP(k, l);
		}
	}
	printf("mincost=%d", mincost);
}

int main()
{
	kruskals();
}
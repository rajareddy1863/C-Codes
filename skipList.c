#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct node
{
	int num;
	struct node * next;
	struct node * down;
};
struct node * head = NULL;
int height = 0;

void createLevel();
void insert(int data);
struct node * insertHeight(int data, int H, struct node * btmNode);
void printList();
int search(int data);
float rand_num();

int main()
{
	int choice = 1, number;
	srand(time(NULL));
	createLevel();
	do
	{
		printf("1. Insert || 2. Search || 3. Print || 0. Exit\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				printf("Enter your number: ");
				scanf("%d",&number);
				insert(number);
				break;
			case 2:
				printf("Enter your number: ");
				scanf("%d",&number);
				if(search(number))
					printf("Element found\n");
				else
					printf("Element not found\n");
				break;
			case 3:
				printList();
				break;
			case 0:
				break;
			default:
				printf("Wrong Choice\n");
				break;
		}
		printf("\n");
	}while(choice != 0);
	printList();
	//printf("Found State: %d\n",search(11));
	return 0;
}

void createLevel()
{
	struct node * tempMin;
	struct node * tempMax;
	struct node * lvlEnd;
	tempMin = (struct node *)malloc(sizeof(struct node));
	tempMax = (struct node *)malloc(sizeof(struct node));
	
	tempMin->num = INT_MIN;
	tempMax->num = INT_MAX;
	
	tempMin->next = tempMax;
	tempMax->next = NULL;
	
	tempMin->down = NULL;
	tempMax->down = NULL;
	
	if(head == NULL)
		head = tempMin;
	else
	{
		tempMin->down = head;
		lvlEnd = head;
		while(lvlEnd->next != NULL)
			lvlEnd = lvlEnd->next;
		tempMax->down = lvlEnd;
		head = tempMin;
	}
}

struct node * insertHeight(int data, int H, struct node * btmNode)
{
	int i;
	struct node * lvlHead;
	struct node * temp;
	struct node * insertNode;
	insertNode = (struct node *)malloc(sizeof(struct node));
	insertNode->num = data;
	insertNode->down = btmNode;
	
	lvlHead = head;
	for(i = 0; i < height - H; i++)
		lvlHead = lvlHead->down;
	temp = lvlHead;
	while(temp->next->num < data)
		temp = temp->next;
	insertNode->next = temp->next;
	temp->next = insertNode;
	return insertNode;
}

void insert(int data)
{
	int count = 0;
	struct node * btmNode = NULL;
	while(count <= height)
	{
		btmNode = insertHeight(data, count, btmNode);
		count += 1;
		if(rand_num() > 0.5)
			break;
	}
	if(count == height + 1)
	{
		createLevel();
		height += 1;
	}
}

void printList()
{
	struct node * tempHead;
	struct node * tempLvl;
	
	tempHead = head;
	
	printf("Elements in the Skip List are: \n");
	while(tempHead != NULL)
	{
		tempLvl = tempHead;
		while(tempLvl != NULL)
		{
			printf("%d ", tempLvl->num);
			tempLvl = tempLvl->next;
		}
		printf("\n");
		tempHead = tempHead->down;
	}
}

int search(int data)
{
	struct node * tempHead;
	struct node * tempLvl;
	
	tempHead = head;
	while(tempHead != NULL)
	{
		tempLvl = tempHead;
		while(tempLvl->next->num < data)
		{
			tempLvl = tempLvl->next;
		}
		if(tempLvl->next->num == data)
			return 1;
		tempHead = tempLvl->down;
	}
	return 0;
}

float rand_num() {
	float num;
	num = rand()/(float)RAND_MAX;
	return num;
}

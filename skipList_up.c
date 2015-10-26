#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct node
{
	int num;
	struct node * next;
	struct node * down;
	struct node * prev;
	struct node * up;
};
struct node * head = NULL;
int height = 0;

void createLevel();
void insert(int data);
struct node * insertHeight(int data, int H, struct node * btmNode);
void printList();
int search(int data);
float rand_num();
int delete(int data);

int main()
{
	int choice = 1, number;
	srand(time(NULL));
	createLevel();
	do
	{
		printf("1. Insert || 2. Search || 3. Print || 4. Delete || 0. Exit\n");
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
					printf("No such element found\n");
				break;
			case 3:
				printList();
				break;
			case 4:
				printf("Enter your number: ");
				scanf("%d",&number);
				if(delete(number))
					printf("Element deleted\n");
				else
					printf("No such element found\n");
				if(height == 0)
				{
					head = NULL;
					createLevel();
				}
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
	
	tempMin->prev = NULL;
	tempMax->prev = tempMin;
	
	tempMin->next = tempMax;
	tempMax->next = NULL;
	
	tempMin->down = NULL;
	tempMax->down = NULL;
	
	tempMin->up = NULL;
	tempMax->up = NULL;
	
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
	struct node * insertNode;
	struct node * temp;

	lvlHead = head;
	for(i = 0; i < height - H; i++)
		lvlHead = lvlHead->down;
	temp = lvlHead;
	while(temp->next->num < data)
		temp = temp->next;
		
	insertNode = (struct node *)malloc(sizeof(struct node));
	insertNode->num = data;
	insertNode->up = NULL;
	insertNode->down = btmNode;
	insertNode->prev = temp;
	insertNode->next = temp->next;
	temp->next->prev = insertNode;
	temp->next = insertNode;
	if(btmNode == NULL)
	{
		return insertNode;
	}
	btmNode->up = insertNode;	
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
	
	if(head == NULL)
	{
		printf("No elements are present\n");
		return;
	}
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

int delete(int data)
{
	int count1 = 0;
	int count2 = 0;
	struct node * tempHead;
	struct node * tempLvl;
	struct node * tempNode;
	struct node * nextNode;
	struct node * globHead;
	tempHead = head;
	globHead = head;
	while(tempHead != NULL)
	{
		tempLvl = tempHead;
		while(tempLvl->next->num < data)
		{
			tempLvl = tempLvl->next;
		}
		if(tempLvl->next->num == data)
		{
			tempNode = tempLvl->next;
			while(tempNode != NULL)
			{
				tempNode->next->prev = tempNode->prev;
				tempNode->prev->next = tempNode->next;
				nextNode = tempNode->down;
				free(tempNode);
				tempNode = nextNode; 
			}
			tempLvl = globHead;
			while(tempLvl->next->num < INT_MAX)
			{
				tempLvl = tempLvl->next;
				count1++;
			}
			if(count1 == 0)
			{
				head = head->down;
				height -= 1;
			}
			/*
			if(count1 == 0 && count2 == 1)
			{
				head = head->down;
				height -= 1;
			}
			if(count1 == 1 && count2 == 2)
			{
				head->down = head->down->down;
				height -= 1;
			}
			*/
			if(height < 0)
				height = 0;
			printf("Height: %d\n", height);
			return 1;
		}
		tempHead = tempLvl->down;
		globHead = globHead->down;
	}
	return 0;
}

float rand_num() {
	float num;
	num = rand()/(float)RAND_MAX;
	printf("Rand num: %f\n", num);
	return num;
}

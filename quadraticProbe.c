#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_size 127
#define eleSize 20

struct node
{
	char str[eleSize];
	int type;
};
struct node table[max_size];

int hashFunc(char string[], int max);
void insert(char string[]);
void print();
int search(char string[]);
void delete(char string[]);

int main()
{
	int i, choice;
	char element[eleSize];
	for(i = 0; i < max_size; i++)
	{
		table[i].type = 0;
	}
	
	do
	{
		printf("----------------------------------------------------------\n");
        printf("1. Insert || 2. Search || 3. Delete || 4. Print || 0. Exit\n");
        printf("----------------------------------------------------------\n");
        printf("Enter your choice: ");
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				printf("Element: ");
				scanf("%s", element);
				insert(element);
				break;
			case 2:
				printf("Element: ");
				scanf("%s", element);
				if (search(element))
					printf("Element Found\n");
				else
					printf("No such element found\n");
				break;
			case 3:
				printf("Element: ");
				scanf("%s", element);
				delete(element);
				break;
			case 4:
				printf("Elements present: \n");
				print();
				break;
			case 0:
				break;
		}
	}while(choice != 0);
	return 0;
}

//Defining a Hash Function to find the key of a string
int hashFunc(char string[], int max)
{
    int i, len, ascii = 0;
    len = strlen(string);

    //Summing up the ASCII values of elements of string
    for(i = 0; i < len; i++)
    {
        ascii += (int)(string[i]);
    }
    //Returing the key
    ascii = ascii % max;
    return ascii;
}


void insert(char string[])
{
	int key, con = 2;
	char element[eleSize];
	
	strcpy(element, string);
	key = hashFunc(element, max_size);
	
	if(table[key].type == 0)
	{
		strcpy(table[key].str, element);
		table[key].type = 1;
		return;
	}
	int i = (key + 1) % max_size;
	while((table[i].type != 0) && (i != key))
	{
		i = (key + (con * con)) % max_size;
		con += 1;
	}
	if(i != key)
	{
		table[i].type = 1;
		strcpy(table[i].str, element);
		return;
	}
	printf("That element can't be inserted\n");
}


void print()
{
	int i, flag = 0;
	for(i = 0; i < max_size; i++)
	{
		if(table[i].type == 1)
		{
			printf("%s\n", table[i].str);
			flag = 1;
		}
	}
	if(flag == 0)
		printf("No elements are found\n");
}

int search(char string[])
{
	int i, key, state = 0, con = 1;
	char element[eleSize];
	strcpy(element, string);
	
	key = hashFunc(element, max_size);
	i = key;
	state = i - 1;
	
	while(table[i].type != 0 && (state != key))
	{
		if(strcmp(table[i].str, element) == 0 && (table[i].type != 2))
		{
			return 1;
		}
		i = (key + (con * con)) % max_size;
		con += 1;
		state = i;
	}
	return 0;	
}

void delete(char string[])
{
	int i, key, state = 0, con = 1;
	char element[eleSize];
	strcpy(element, string);
	
	key = hashFunc(element, max_size);
	i = key;
	state = i - 1;
	
	while(table[i].type != 0 && (state != key))
	{
		if(strcmp(table[i].str, element) == 0  && (table[i].type != 2))
		{
			table[i].type = 2;
			printf("Element deleted\n");
			return;
		}
		i = (key + (con * con)) % max_size;
		con += 1;
		state = i;
	}
	printf("No such element found to delete\n");
}

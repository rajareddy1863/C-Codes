#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define eleSize 20
#define n 10

struct node
{
    char str[eleSize];
    int next;
};
int aux_count = 0;
struct node primary[n];
struct node auxilary[n];
int flag[n];

int hashFunc(char string[], int max)
{
    int i, len, ascii = 0;
    len = strlen(string);
    for(i = 0; i < len; i++)
    {
        ascii += (int)(string[i]);
    }
    ascii = ascii % max;
    return ascii;
}

void insert(char element[eleSize], int key)
{
    char string[eleSize];
    strcpy(string, element);
    int pos;

    if(flag[key] == 0)
    {
        strcpy(primary[key].str, string);
        primary[key].next = -1;
        flag[key] = 1;
        return;
    }

    else if(primary[key].next == -1)
    {
        primary[key].next = aux_count;
        strcpy(auxilary[aux_count].str, string);
        auxilary[aux_count].next = -1;
        aux_count += 1;
        return;
    }
    else
    {
        pos = primary[key].next;
        while(auxilary[pos].next != -1)
        {
            pos = auxilary[pos].next;
        }
        auxilary[pos].next = aux_count;
        strcpy(auxilary[aux_count].str, string);
        auxilary[aux_count].next = -1;
        aux_count += 1;
        return;
    }
}

int search(char element[], int key)
{
    char string[eleSize];
    strcpy(string, element);
    int pos;

    if(flag[key] == 0)
        return 0;

    if(strcmp(primary[key].str,string) == 0)
    {
        return 1;
    }
    else
    {
        pos = primary[key].next;
        while(pos != -1)
        {
            if(strcmp(auxilary[pos].str,string) == 0)
                return 1;
            pos = auxilary[pos].next;
        }
        return 0;
    }
}

void print()
{
    int i, pos;
    for(i = 0; i < n; i++)
    {
        printf("key: %d ",i);
        if(flag[i] != 0)
        {
            printf("-> %s ", primary[i].str);
            pos = primary[i].next;
            while(pos != -1)
            {
                printf("-> %s ",auxilary[pos].str);
                pos = auxilary[pos].next;
            }
        }
        printf("\n");
    }
}


void remove_ele(char element[], int key)
{
    char string[eleSize];
    strcpy(string, element);
    int pos, prev;
    pos = primary[key].next;

    if(primary[key].next == -1)
    {
        flag[key] = 0;
        return;
    }

    else if(strcmp(primary[key].str, string) == 0)
    {
        strcpy(primary[key].str, auxilary[pos].str);
        primary[key].next = auxilary[pos].next;
        return;
    }

    else if(strcmp(auxilary[pos].str, string) == 0)
    {
        primary[key].next = auxilary[pos].next;
        return;
    }
    else
    {
        prev = pos;
        pos = auxilary[pos].next;
        while(strcmp(auxilary[pos].str, string) != 0)
        {
            prev = pos;
            pos = auxilary[pos].next;
        }
        auxilary[prev].next = auxilary[pos].next;
        return;
    }
}

int main()
{
    int choice = 1, ret_value, i, flagState = 0;
    char string[eleSize];

    for(i = 0; i < n; i++)
    {
        flag[i] = 0;
    }

    do
    {
        printf("----------------------------------------------------------\n");
        printf("1. Insert || 2. Search || 3. Delete || 4. Print || 0. Exit\n");
        printf("----------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Element: ");
                scanf("%s", string);
                ret_value = hashFunc(string, n);
                printf("Inserting at key position: %d\n", ret_value);
                insert(string, ret_value);
                break;
            case 2:
                printf("Element: ");
                scanf("%s",string);
                ret_value = hashFunc(string, n);
                flagState = search(string, ret_value);
                if(flagState == 1)
                    printf("Element found at key %d\n",ret_value);
                else
                    printf("That element is not found\n");
                break;
            case 3:
                printf("Element: ");
                scanf("%s",string);
                ret_value = hashFunc(string, n);
                flagState = search(string, ret_value);
                if(flagState == 1)
                    remove_ele(string, ret_value);
                else
                    printf("That element is not found\n");
                break;
            case 4:
                printf("Elements present: \n");
                print();
                break;
            case 0:
                break;
            default:
                printf("Wrong Choice\n");
                break;
        }
    }while(choice != 0);

    return 0;
}

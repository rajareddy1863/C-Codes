#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define eleSize 20

struct node
{
    char str[eleSize];
    struct node * next;
};

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

struct node * insert(struct node * row, char element[eleSize])
{
    struct node * head;
    head = row;

    struct node * temp;
    temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->str, element);
    temp->next = head;
    head = temp;
    return head;
}

void print_row(struct node * row)
{
    struct node * temp;
    temp = row;

    while(temp != NULL)
    {
        printf("-> %s ",temp->str);
        temp = temp->next;
    }
}

void print(struct node * lList[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
        printf("key: %d ",i);
        print_row(lList[i]);
        printf("\n");
    }
}

int search(struct node * row, char element[eleSize])
{
    char string[eleSize];
    int flag = 0;
    strcpy(string, element);
    struct node * temp;
    temp = row;

    while(temp != NULL)
    {
        if(strcmp(temp->str,string) == 0)
        {
            flag = 1;
        }
        temp = temp->next;
    }

    return flag;
}

struct node * remove_ele(struct node * row, char element[eleSize])
{
    char string[eleSize];
    strcpy(string, element);
    struct node * temp;
    struct node * prev;

    prev = row;
    temp = row;

    if(strcmp(row->str, string) == 0)
    {
        row = row->next;
        free(temp);
        return row;
    }
    temp = temp->next;
    while(strcmp(temp->str, string) != 0)
    {
        temp = temp->next;
        prev = prev->next;
    }
    prev->next = temp->next;
    free(temp);
    return row;
}

int main()
{
    int i, n, ret_value, choice = 1, flag;
    char string[eleSize];

    printf("Enter the max key: ");
    scanf("%d",&n);
    struct node * lList[n];

    for(i = 0; i < n; i++)
    {
        lList[i] = NULL;
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
                lList[ret_value] = insert(lList[ret_value], string);
                break;
            case 2:
                printf("Element: ");
                scanf("%s", string);
                ret_value = hashFunc(string, n);
                flag = search(lList[ret_value], string);
                if(flag == 1)
                    printf("Element found at key value: %d\n",ret_value);
                else
                    printf("Element not found!\n");
                break;
            case 3:
                printf("Element: ");
                scanf("%s", string);
                ret_value = hashFunc(string, n);
                flag = search(lList[ret_value], string);
                if(flag == 1)
                    lList[ret_value] = remove_ele(lList[ret_value], string);
                else
                    printf("That element is not present\n");
                break;
            case 4:
                printf("Elements present: \n");
                print(lList, n);
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

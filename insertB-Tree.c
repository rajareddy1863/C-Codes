#include <stdio.h>
#include <stdlib.h>


struct node
{
    int num;
    int key[5];
    int leaf;
    struct node * child[6];
};
struct node * root = NULL;



void Print(struct node * x)
{
  int i, n;
  n = x->num;

  for(i = 0;i < n; i++)
  {
    if(x->leaf == 0)
    {
      Print(x->child[i]);
    }
    printf("%d\n",x->key[i]);
  }

  if(x->leaf == 0)
  {
    Print(x->child[n]);
  }
}


void splitChild(struct node * x, int i)
{
  int j, t = 3;
  struct node * temp;
  temp = (struct node *)malloc(sizeof(struct node));

  struct node * childNode;

  childNode = x->child[i];

  temp->leaf = childNode->leaf;

  for(j = 0;j < t-1;j++)
  {
    temp->key[j] = childNode->key[t + j];
  }

  if(childNode->leaf == 0)
  {
    for(j = 0;j < t;j++)
    {
      temp->child[j] = childNode->child[j+t];
    }
  }

  childNode->num = t - 1;
  temp->num = t - 1;

  for(j = x->num + 1; j > i; j--)
  {
      x->child[j] = x->child[j - 1];
  }

  x->child[i + 1] = temp;

  for(j = x->num; j > i; j--)
  {
    x->key[j] = x->key[j - 1];
  }
  x->key[i] = childNode->key[t - 1];
  x->num += 1;
}


void subInsert(struct node * x, int element)
{
  int con, t = 3;
  con = x->num;

  if(x->leaf == 1)
  {
    while(con > 0 && element <= x->key[con-1])
    {
      x->key[con] = x->key[con - 1];
      con -= 1;
    }
    x->key[con] = element;
    x->num += 1;
  }

  else
  {
    while(con > 0 && element <= x->key[con-1])
    {
      con -= 1;
    }
    if(x->child[con]->num == 2*t - 1)
    {
      splitChild(x, con);
      if(element >= x->key[con])
      {
        con += 1;
      }
    }
    subInsert(x->child[con], element);
  }
}

void Insert(int element)
{
  struct node * temp;
  temp = (struct node *)malloc(sizeof(struct node));

  int t = 3;

  if(root == NULL)
  {
    temp->key[0] = element;
    temp->num = 1;
    temp->leaf = 1;
    root = temp;
  }

  else
  {
    if(root->num == 2*t - 1)
    {
      temp->leaf = 0;
      temp->num = 0;
      temp->child[0] = root;
      root = temp;
      splitChild(root, 0);
      subInsert(root, element);
      //Print(root);
    }
    else
    {
      subInsert(root, element);
    }
  }
}


int main()
{
  int i, choice = 24;
  int a[24] = {10,1,5,7,9,2,3,8,6,21,65,0,10,7,1,0,3,8,7,1,9,15,12,21};

  while(choice != 0)
  {
    Insert(a[choice - 1]);
    choice -= 1;
  }
  printf("Inserted Elements are:\n");
  Print(root);
  return 0;
}

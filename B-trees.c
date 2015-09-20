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

void Delete(struct node * x, int element);

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


struct node * Search(struct node * x, int element, struct node * parent)
{
  int i = 0;
  struct node * temp = NULL;

  while(i < x->num && element > x->key[i])
  {
    i += 1;
  }

  if(i <= x->num && x->key[i] == element)
  {
    temp = x;
    return temp;
  }

  else if(x->leaf == 1)
  {
    return temp;
  }
  else
  {
    parent = x;
    Search(x->child[i], element,parent);
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

void case1(struct node * x, int element, struct node * locFind, int posFind)
{
  int i;
  for(i = posFind; i < locFind->num - 1; i++)
  {
    locFind->key[i] = locFind->key[i + 1];
  }
  locFind->num -= 1;
}

void case2a(struct node * x, int element, struct node * locFind, int posFind)
{
  struct node * temp;
  temp = locFind->child[posFind];
  while(temp->leaf == 0)
  {
    temp = temp->child[temp->num];
  }
  locFind->key[posFind] = temp->key[temp->num - 1];
  Delete(locFind->child[posFind], temp->key[temp->num - 1]);
}

void case2b(struct node * x, int element, struct node * locFind, int posFind)
{
  struct node * temp;
  temp = locFind->child[posFind + 1];
  while(temp->leaf == 0)
  {
    temp = temp->child[0];
  }
  locFind->key[posFind] = temp->key[0];
  Delete(locFind->child[posFind + 1], temp->key[0]);
}

void case2c(struct node *x, int element, struct node * locFind, int posFind)
{
  struct node * temp;
  struct node * tempMerge;

  int i, t=3;

  tempMerge = locFind->child[posFind];
  temp = locFind->child[posFind + 1];

  tempMerge->key[t - 1] = locFind->key[posFind];

  for(i = 0;i < temp->num;i++)
  {
    tempMerge->key[t + i] = temp->key[i];
  }

  if(tempMerge->leaf == 0)
  {
    for(i = 0;i < temp->num + 1;i++)
    {
      tempMerge->child[t + i] = temp->child[i];
    }
  }

  for(i = posFind; i < locFind->num - 1; i++)
  {
    locFind->key[i] = locFind->key[i + 1];
  }

  for(i = posFind+1; i < locFind->num; i++)
  {
    locFind->child[i] = locFind->child[i + 1];
  }

  locFind->num -= 1;
  locFind->child[posFind] += temp->num + 1;
  Delete(locFind->child[posFind], element);
}



void case3a(struct node * x, int element, struct node * locFind, int posFind)
{
  int i;

  struct node * leftFriend;
  struct node * mainChild;

  leftFriend = locFind->child[posFind - 1];
  mainChild = locFind->child[posFind];


  for(i = mainChild->num; i >= 1; i--)
  {
    mainChild->key[i] = mainChild->key[i - 1];
  }

  if(mainChild->leaf == 0)
  {
    for(i = mainChild->num + 1; i >= 1; i--)
    {
        mainChild->child[i] = mainChild->child[i - 1];
    }
  }

  mainChild->key[0] = locFind->key[posFind - 1];

  mainChild->child[0] = leftFriend->child[leftFriend->num];

  locFind->key[posFind - 1] = leftFriend->key[leftFriend->num - 1];

  leftFriend->num -= 1;
  mainChild->num += 1;

}

void case3b(struct node * x, int element, struct node * locFind, int posFind)
{
  int i;
  struct node * mainChild;
  struct node * rightFriend;

  mainChild = locFind->child[posFind];
  rightFriend = locFind->child[posFind + 1];


  mainChild->key[mainChild->num] = locFind->key[posFind];

  if(mainChild->leaf == 0)
  {
    mainChild->child[mainChild->num + 1] = rightFriend->child[0];
  }

  locFind->key[posFind] = rightFriend->key[0];

  for(i = 0; i < rightFriend->num - 1; i++)
  {
    rightFriend->key[i] = rightFriend->key[i + 1];
  }

  if(rightFriend->leaf == 0)
  {
    for(i = 0; i < rightFriend->num; i++)
    {
      rightFriend->child[i] = rightFriend->child[i + 1];
    }
  }

  mainChild->num += 1;
  rightFriend->num -= 1;
}

void case3c(struct node * x, int element, struct node * locFind, int posFind)
{
  int i, t = 3;
  struct node * childOne;
  struct node * childTwo;

  childOne = locFind->child[posFind];
  childTwo = locFind->child[posFind + 1];


  childOne->key[t - 1] = locFind->key[posFind];

  for(i = 0; i < childTwo->num; i++)
  {
    childOne->key[t + i] = childTwo->key[i];
  }

  if(childOne->leaf == 0)
  {
    for(i = 0;i <= childTwo->num; i++)
    {
      childOne->child[t + i] = childTwo->child[i];
    }
  }
/*

  for(i = posFind + 1; i < locFind->num; ++i)
  {
    locFind->key[i - 1] = locFind->key[i];
  }
  */

  for( i = posFind; i < locFind->num - 1; i++)
  {
    locFind->key[i] = locFind->key[i + 1];
  }


  for(i = posFind + 1; i < locFind->num; i++)
  {
    locFind->child[i] = locFind->child[i + 1];
  }

  childOne->num += childTwo->num + 1;
  locFind->num -= 1;
}

void Delete(struct node * x, int element)
{
  int i = 0, posFind, t = 3;
  struct node * locFind;
  struct node * parentEle;
  struct node * temp;
  locFind = x;

  while(i < locFind->num && locFind->key[i] < element)
  {
    i++;
  }

  posFind = i;
  //printf("%d\n",locFind->num);
  //printf("%d\n",posFind);
  //printf("%d\n",locFind->key[0]);
  if(posFind < locFind->num && locFind->key[posFind] == element)
  {
    if(locFind->leaf == 1)
    {
      printf("CASE 1\n");
      case1(x, element, locFind, posFind);
    }
    else
    {
      if(locFind->child[posFind]->num >= t)
      {
        printf("CASE 2A\n");
        case2a(x, element, locFind, posFind);
      }

      else if(locFind->child[posFind + 1]->num  >= t)
      {
        printf("CASE 2B\n");
        case2b(x, element, locFind, posFind);
      }
      else
      {
        printf("CASE 2C\n");
        case3c(x, element, locFind, posFind);
        Delete(locFind->child[posFind], element);
      }
    }
  }

  else
  {
    if(locFind->leaf == 1)
    {
      return;
    }
    if(locFind->child[posFind]->num < t)
    {
      if(posFind != 0 && locFind->child[posFind - 1]->num >= t)
      {
        Print(root);
        printf("CASE 3A\n");
        case3a(x, element, locFind, posFind);
        Print(root);
      }

      else if(posFind != locFind->num && locFind->child[posFind + 1]->num >= t)
      {
        printf("CASE 3B\n");
        case3b(x, element, locFind, posFind);
        Print(root);
      }

      else
      {
        printf("CASE 3C\n");
        if(posFind != locFind->num)
        {
          printf("Case 3c a\n");
          case3c(x, element, locFind, posFind);
          Print(root);
        }
        else
        {
          printf("Case 3c b\n");
          case3c(x, element, locFind, posFind - 1);
          //Print(root);
          //printf("%d\n",locFind->child[locFind->num]->num);
          //printf("%d\n",posFind);
          Delete(locFind->child[posFind - 1], element);
          return;
        }
      }
    }
    printf("Done\n");
    Delete(locFind->child[posFind],element);
    /*
    if(posFind == locFind->num)
    {
      Delete(locFind->child[posFind - 1], element);
    }

    else
    {
      Delete(locFind->child[posFind], element);
    }
    */
  }
}

void mainDelete(struct node * x, int element)
{
  if(x->num == 0)
  {
    printf("No elements are there in the tree\n");
  }

  else
  {
    Delete(x, element);
    if(root->num == 0 && root->leaf == 0)
    {
      root = root->child[0];
    }
  }
}

int main()
{
  int i, choice = 0, n = 50;
  //int a[10] = {21,54,63,11,97,-10,0,999,48,1};
  //int a[1] = {1};
  //int a[15] = {122, 125, 245, 372, 418, 440, 474, 491, 752, 803, 853, 934, 957, 968, 986};
  int a[50] = {122, 245, 491, 474, 440, 372, 236, 473, 438, 368, 228, 457, 406, 304, 100, 201, 403, 298, 88, 177,
               355, 202, 405, 302, 96, 193, 387, 266, 24, 49, 99, 199, 399, 290, 72, 145, 291, 74, 149, 299, 90, 181, 363, 218, 437, 366, 224, 449, 390,272};

  //int a[10] = {372,245,491,474,440, 122, 418, 125,934, 752};
  //int a[5] = {122, 125, 245, 372, 418};
  //int a[23] = {1,3,7,10,11,13,14,15,18,16,19,24,25,26,21,4,5,20,22,2,17,12,6};
  struct node * temp;
  struct node * parent;

  while(choice != n)
  {
    Insert(a[choice]);
    printf("%d\n",root->key[0]);
    choice += 1;
  }
  printf("Inserted Elements are:\n");
  Print(root);
  printf("Searching\n");
  temp = Search(root, 1, parent);
  if(temp != NULL)
  {
    printf("Found\n");
  }
  else
  {
    printf("Not Found\n");
  }
  /*
  mainDelete(root, 968);
  mainDelete(root, 957);
  mainDelete(root, 474);
  mainDelete(root, 803);
  mainDelete(root, 440);
  mainDelete(root, 853);
  mainDelete(root, 934);*/

  mainDelete(root, 122);
  mainDelete(root, 355);
  mainDelete(root, 96);
  mainDelete(root, 24);
  mainDelete(root, 49);
  mainDelete(root, 438);
  mainDelete(root, 304);
  mainDelete(root, 202);
  mainDelete(root, 387);
  mainDelete(root, 199);

  printf("Here\n");
  mainDelete(root, 74);


  Print(root);
  return 0;
}

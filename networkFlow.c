#include <stdio.h>
#include <stdlib.h>

#define MAX 999999

struct node
{
	int toNode;
	int weight;
	struct node * next;
};

struct Queue
{
	int nodes;
	struct Queue * next;
};

struct Queue * head = NULL;
void addEdge(struct node ** vertex, int to, int weight);
void PrintGraph(struct node * graph[], int nV);
void PrintConn(struct node * vertex);
int maxFlow(struct node * graph[], int from ,int to, int nV);
void updateWeight(struct node * graph[], int from, int to, int path_flow);
int weight(struct node * resgraph[], int from, int to, int nV);
int breadthFirst(struct node * resgraph[], int from , int to, int nV, int parent[]);

int main()
{
	int nV, i, max_flow;
	int from, to, weight, check = 1;
	int source, destination;
	printf("Enter the number of vertices: ");
	scanf("%d",&nV);
	
	struct node * graph[nV];
	for(i = 0; i < nV; i++)
	{
		graph[i] = NULL;
	}
	
	printf("Enter in the format __ __ __ (from node, to node, weight)\n");
	printf("Enter '0 0 0' to exit\n");

	while(check != 0)
	{
		scanf("%d",&from);
		scanf("%d",&to);
		scanf("%d",&weight);
		if((from + to + weight) != 0)
		{
		  addEdge(&graph[from], to, weight);
		}
		check = from + to + weight;
	 }
	 
	 printf("Enter source node: ");
	 scanf("%d",&source);
	 
	 printf("Enter destination node: ");
	 scanf("%d",&destination);
	 
	 max_flow = maxFlow(graph, source, destination, nV);
	 printf("Maximum Flow: %d\n",max_flow);
	 return 0;
}

void addEdge(struct node ** vertex, int to, int weight)
{
	struct node * temp;
	struct node * var;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->toNode = to;
	temp->weight = weight;
	temp->next = NULL;
	var = *vertex;
	if(var == NULL)
	{
		*vertex = temp;
	}

	else
	{
		temp->next = *vertex;
		*vertex = temp;
	}
}

void PrintGraph(struct node * graph[], int nV)
{
	int i;
	printf("Connections of this graph are: \n");
	for(i = 0;i < nV; i++)
	{
		printf("Node %d: ", i);
		PrintConn(graph[i]);
		printf("\n");
	}
}

void PrintConn(struct node * vertex)
{
	struct node * temp;
	temp = vertex;
	while(temp != NULL)
	{
		printf("%d:%d ",temp->toNode,temp->weight);
		temp = temp->next;
	}
}

void enQueue(int element)
{
  struct Queue * temp;
  temp = (struct Queue *)malloc(sizeof(struct Queue));
  temp->nodes = element;
  temp->next = NULL;

  if(head == NULL)
  {
    head = temp;
  }
  else
  {
    temp->next = head;
    head = temp;
  }
}

struct Queue * deQueue()
{
  struct Queue * temp;
  struct Queue * newLast;
  struct Queue * var;
  temp = head;
  if(temp == NULL || temp->next == NULL)
  {
    var = temp;
    head = NULL;
    return var;
  }

  else
  {
    var = head;
    while(var->next != NULL)
    {
      newLast = var;
      var = var->next;
    }
    newLast->next = NULL;
    return var;
  }
}

int breadthFirst(struct node * resgraph[], int from , int to, int nV, int parent[])
{
	int i;
	int visitList[nV];
	struct Queue * pop;
	struct node * var;
	for(i = 0;i < nV; i++)
	{
		visitList[i] = 0;
	}
	visitList[from] = 1;
	parent[from] = -1;
	enQueue(from);
	
	while(head != NULL)
	{
		pop = deQueue();
		var = resgraph[pop->nodes];
		while(var != NULL)
		{
			if(visitList[var->toNode] == 0 && var->weight > 0)
			{
				enQueue(var->toNode);
				visitList[var->toNode] = 1;
				parent[var->toNode] = pop->nodes;
			}
			var = var->next;
		}
	}
	
	if(visitList[to] == 1)
		return 1;
	return 0;
}

int weight(struct node * resgraph[], int from, int to, int nV)
{
	struct node * temp;
	temp = resgraph[from];
	while(temp->toNode != to)
		temp = temp->next;
	return temp->weight;
}

void updateWeight(struct node * graph[], int from, int to, int path_flow)
{
	struct node * temp;
	temp = graph[from];
	while(temp != NULL)
	{
		if(temp->toNode == to)
		{
			temp->weight += path_flow;
			return;
		}
		temp = temp->next;
	}
	temp = (struct node *)malloc(sizeof(struct node));
	temp->toNode = to;
	temp->weight += path_flow;
	temp->next = graph[from];
	graph[from] = temp; 
}

int maxFlow(struct node * graph[], int from ,int to, int nV)
{
	struct node * resgraph[nV];
	struct node * temp;
	int i, j, temp_weight;
	int parent[nV];
	int max_flow = 0, path_flow;
	for(i = 0; i < nV; i++)
	{
		resgraph[i] = NULL;
	}
	
	for(i = 0; i < nV; i++)
	{
		temp = graph[i];
		while(temp != NULL)
		{
			addEdge(&resgraph[i], temp->toNode, temp->weight);
			temp = temp->next;
		}
	}
	
	while(breadthFirst(resgraph, from, to, nV, parent))
	{
		j = to;
		path_flow = MAX;
		while(j != from)
		{
			i = parent[j];
			temp_weight = weight(resgraph, i ,j, nV);
			j = i;
			if(path_flow < temp_weight)
				path_flow = path_flow;
			else
				path_flow = temp_weight;
		}
		j = to;
		while(j != from)
		{
			i = parent[j];
			updateWeight(resgraph, i, j, -path_flow);
			updateWeight(resgraph, j, i, path_flow);
			j = i;
		}
		max_flow += path_flow;
	}
	return max_flow;
}

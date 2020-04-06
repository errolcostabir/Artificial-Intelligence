#include<iostream>
#include<conio.h>
#include<malloc.h>
#define MAX 100
#define initial 1
#define waiting 2
#define visited 3
using namespace std;

int state[MAX];
int N;
int adj[MAX][MAX];
int heuristic[MAX];
int length[MAX][MAX];
int temp_cost = 0;

struct node {
	int fn;
	int value;
	int index;
	int gn;
	struct node* next;
}*start = NULL, * q, * temp, * new1;

//Function to insert in priority queue

void insert(struct node m)
{
	int item = m.index, itprio = m.value, cost=m.gn;
	new1 = (node*)malloc(sizeof(node));
	
	//temp_cost += cost;
	int a = cost + itprio;
	
	new1->index = item;
	new1->value = itprio;
	new1->fn = a;

	new1->next = NULL;
	if (start == NULL)
	{
		start = new1;
	}
	else if (start != NULL && a <= start->fn)
	{
		new1->next = start;
		start = new1;
	}
	else
	{
		q = start;
		while (q->next != NULL && q->next->fn <= a)
		{
			q = q->next;
		}
		new1->next = q->next;
		q->next = new1;
	}
}

//Function for popping from the Priority Queue.

struct node del()
{
	struct node n;
	n.index = -1;
	n.value = -1;
	if (start == NULL)
	{
		printf("\nQUEUE UNDERFLOW\n");

	}
	else
	{

		n.index = start->index;
		n.value = start->value;
		new1 = start;

		start = start->next;
	}

	return n;
}

//Function to determine if the Priority Queue is empty.

int empty() {
	if (start == NULL)
		return 1;
	return 0;
}

int main() {

	int origin, dest, value;
	int cost;

	//cin number of nodes
	cout << "Enter the number of nodes" << endl;
	cin >> N;

	//max edges
	int max_edges = N * (N - 1) / 2;

	//input graph
	for (int i = 1; i <= max_edges; i++) {
		cout << "Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node" << endl;
		cin >> origin >> dest >> cost >> value;
		if (origin == -1 || dest == -1) {
			break;
		}
		if (origin >= N || dest >= N || origin < 0 || dest < 0) {
			cout << "invalid edge" << endl;
			i--;
		}
		else {
			adj[origin][dest] = 1;
			heuristic[dest] = value;
			length[origin][dest] = cost;
		}
	}

	int start, goal;

	//input start and goal
	cout << "Enter the Source Node and Goal Node" << endl;
	cin >> start >> goal;

	for (int i = 0; i < N; i++) {
		state[i] = initial;
	}

	//cout adjacency matrix
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//cout cost matrix
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << length[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//cout heuristic values of nodes
	for (int i = 0; i < N; i++) {
		cout << heuristic[i] << " ";
	}
	cout << endl;

	int temp_length;

	struct node n, m;
	m.index = start;
	m.value = heuristic[1];
	m.gn = 0;
	insert(m);

	state[m.index] = visited;

	//best first search
	cout << endl << endl << "The Optimal Path from Source to Goal is: " << endl;

	while (!empty()) {
		n = del();
		state[n.index] = visited;
		cout << n.index << " ";
		if (n.index == goal) {
			break;
		}
		else {
			for (int i = 0; i < N; i++) {
				if (adj[n.index][i] == 1 && state[i] == initial) {
					m.gn = length[n.index][i];
					m.index = i;
					m.value = heuristic[i];
					insert(m);
				}

			}
		}

	}
}



/*
Enter the number of nodes
7
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
0 1 3 11
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
0 2 4 12
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
1 3 7 6
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
1 4 10 4
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
3 4 2 4
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
2 4 12 4
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
2 5 5 11
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
4 6 5 0
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
5 6 16 0
Enter the origin and destination of edge and cost of the edge and heuristic value of the destination node
-1 -1 -1 -1
Enter the Source Node and Goal Node
0
6
0 1 1 0 0 0 0
0 0 0 1 1 0 0
0 0 0 0 1 1 0
0 0 0 0 1 0 0
0 0 0 0 0 0 1
0 0 0 0 0 0 1
0 0 0 0 0 0 0

0 3 4 0 0 0 0
0 0 0 7 10 0 0
0 0 0 0 12 5 0
0 0 0 0 2 0 0
0 0 0 0 0 0 5
0 0 0 0 0 0 16
0 0 0 0 0 0 0

0 11 12 6 4 11 0


The Optimal Path from Source to Goal is:
0 1 3 4 6
*/
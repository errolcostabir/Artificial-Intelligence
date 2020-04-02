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


struct node {
	int value;
	int index;
	struct node* next;
}*start = NULL, * q, * temp, * new1;

//Function to insert in priority queue

void insert(struct node m)
{
	int item = m.index, itprio = m.value;
	new1 = (node*)malloc(sizeof(node));

	new1->index = item;
	new1->value = itprio;
	new1->next = NULL;
	if (start == NULL)
	{
		start = new1;
	}
	else if (start != NULL && itprio <= start->value)
	{
		new1->next = start;
		start = new1;
	}
	else
	{
		q = start;
		while (q->next != NULL && q->next->value <= itprio)
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
	
	//cin number of nodes
	cout << "enter the number of nodes" << endl;
	cin >> N;
	
	//max edges
	int max_edges = N * (N - 1);
	
	//input graph
	for (int i = 1; i <= max_edges; i++) {
		cout << "enter the origin and dest and heuristic of the nodes" << endl;
		cin >> origin >> dest >> value;

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
		}
	}

	int start, goal;

	//input start and goal
	cout << "enter the start and goal of the graph" << endl;
	cin >> start >> goal;

	for (int i = 0; i < N; i++) {
		state[i] = initial;
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << adj[i][j]<<" ";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < N; i++) {
		cout << heuristic[i]<<" ";
	}
	cout << endl;


	struct node n, m;
	m.index = 0;
	m.value = heuristic[1];
	insert(m);

	state[m.index] = visited;

	//best first search

	while (!empty()) {
		n = del();
		state[n.index] = visited;
		cout << n.index << " ";
		if (n.index == goal) {
			cout << endl;
			cout << "Goal Reached" << endl;
			break;
		}
		else {
			for (int i = 0; i<N; i++) {
				if (adj[n.index][i] == 1 && state[i] == initial) {
					m.index=i;
					m.value = heuristic[i];
					insert(m);
				}

			}
		}

	}
}


/*

output


enter the number of nodes
14
enter the origin and dest and heuristic of the nodes
0 1 5
enter the origin and dest and heuristic of the nodes
0 2 6
enter the origin and dest and heuristic of the nodes
0 3 3
enter the origin and dest and heuristic of the nodes
1 4 7
enter the origin and dest and heuristic of the nodes
2 5 14
enter the origin and dest and heuristic of the nodes
2 6 12
enter the origin and dest and heuristic of the nodes
3 7 8
enter the origin and dest and heuristic of the nodes
3 8 9
enter the origin and dest and heuristic of the nodes
4 9 6
enter the origin and dest and heuristic of the nodes
4 10 5
enter the origin and dest and heuristic of the nodes
10 11 2
enter the origin and dest and heuristic of the nodes
10 12 10
enter the origin and dest and heuristic of the nodes
10 13 1
enter the origin and dest and heuristic of the nodes
-1 -1 -1
enter the start and goal of the graph
0 10

0 1 1 1 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 1 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 1 1 1
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0

//heuristic values
0 5 6 3 7 14 12 8 9 6 5 2 10 1

//the path
0 3 1 2 4 10
Goal Reached



*/
#include<iostream>
#define INFINITY 9999
#define MAX 100
using namespace std;

int cost[MAX][MAX];
int adj[MAX][MAX];
int i, j, n;
int heuristic[MAX];

void dijkstra(int startnode, int g)
{

	int distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (cost[i][j] == 0)
				cost[i][j] = INFINITY;


	cout << endl;

	//initialize pred[],distance[] and visited[]
	for (i = 0; i < n; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}

	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	
	while (count < n)
	{
		mindistance = INFINITY;
		int temp = INFINITY;
		//nextnode gives the node at minimum distance
		for (i = 0; i < n; i++)
			if (distance[i]+heuristic[i] < temp && !visited[i])
			{
				temp = distance[i] + heuristic[i];
				mindistance = distance[i];
				nextnode = i;
			}

		//check if a better path exists through nextnode			
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i]+heuristic[i] < distance[i]+heuristic[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}


	cout << g;
	j = g;
	do {
		j = pred[j];
		cout << "<-" << j;
	} while (j != startnode);
}


int main() {
	int origin, dest, value;
	cout << "enter the number of nodes" << endl;
	cin >> n;

	do {
		cout << "enter the source and dest of vertex and cost(-1 -1) to quit" << endl;
		cin >> origin >> dest >> value;
		if (origin == -1 || dest == -1) {
			break;
		}
		adj[origin][dest] = adj[dest][origin] = 1;
		cost[origin][dest] = cost[dest][origin] = value;
	} while (true);

	cout << "enter the heuristic value of the nodes inorder" << endl;
	for (i = 0; i < n; i++) {
		cin >> heuristic[i];
	}


	int start, goal;
	cout << "enter the starting and goal node" << endl;
	cin >> start >> goal;
	dijkstra(start, goal);

}

/*

enter the number of nodes
10
enter the source and dest of vertex and cost(-1 -1) to quit
0 1 6
enter the source and dest of vertex and cost(-1 -1) to quit
0 8 3
enter the source and dest of vertex and cost(-1 -1) to quit
1 2 2
enter the source and dest of vertex and cost(-1 -1) to quit
1 3 3
enter the source and dest of vertex and cost(-1 -1) to quit
2 3 1
enter the source and dest of vertex and cost(-1 -1) to quit
3 4 5
enter the source and dest of vertex and cost(-1 -1) to quit
4 6 5
enter the source and dest of vertex and cost(-1 -1) to quit
4 5 5
enter the source and dest of vertex and cost(-1 -1) to quit
5 6 3
enter the source and dest of vertex and cost(-1 -1) to quit
6 7 3
enter the source and dest of vertex and cost(-1 -1) to quit
7 8 1
enter the source and dest of vertex and cost(-1 -1) to quit
6 9 2
enter the source and dest of vertex and cost(-1 -1) to quit
2 4 8
enter the source and dest of vertex and cost(-1 -1) to quit
8 9 7
enter the source and dest of vertex and cost(-1 -1) to quit
-1 -1 -1
enter the heuristic value of the nodes inorder
10 8 7 5 3 0 1 5 6 3
enter the starting and goal node
0 5

5<-6<-7<-8<-0

*/
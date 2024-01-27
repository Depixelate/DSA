#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define V 9



void print_path(double graph[V][V], int prev[V], int end) {
    if(end == -1) return;
    print_path(graph, prev, prev[end]);
    printf("%d ", end);
}

void djikstra(double graph[V][V], int start) {
    int prev[V];
    double distances[V];
    bool visited[V] = {0};

    //initialize distances to infinity
    for(int i = 0; i < V; i++) {
        distances[i] = INFINITY;
        prev[i] = -1;
    }

    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if (graph[i][j] == 0) { // No connection, so for djikstra's algorithm works if dist is infinity.
                graph[i][j] = INFINITY;
            }
        }
    }

    distances[start] = 0;

    while(true) {
        int cur_index = -1;
        double cur_dist = INFINITY;
        for(int i = 0; i < V; i++) {
            if(!visited[i] && distances[i] < cur_dist) {
                cur_index = i;
                cur_dist = distances[i];
            }
        }

        if(cur_dist == INFINITY) { // no more nodes reachable, finish.
            break;
        }

        visited[cur_index] = true;

        for(int i = 0; i < V; i++) {
            if(distances[cur_index] + graph[cur_index][i] < distances[i]) {
                distances[i] = distances[cur_index] + graph[cur_index][i];
                prev[i] = cur_index;
            } 
        }
    }

    printf("Node\tDistance from %d\t\tPath\n", start);
    for(int i = 0; i < V; i++) {
        printf("%d\t%lf\t\t", i, distances[i]);
        print_path(graph, prev, i);
        printf("\n");
    }
}

void floyd_warshall(double graph[V][V]) {
    double d[V][V];
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {

            if (graph[i][j] == 0 && i != j) { // No connection, so for djikstra's algorithm works if dist is infinity.
                graph[i][j] = INFINITY;
            }
            d[i][j] = graph[i][j];
        }
    }

    for(int k = 0; k < V; k++) {

        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                if(d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            printf("%02lf  ", d[i][j]); 
        }
        printf("\n");
    }
}

void print_path_2(int prev[], int i) {
    int last = prev[i];
    if(last != -1) print_path_2(prev, last);
    printf("%d ", i);
}

void new_djikstra(double graph[V][V], int start) {
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if(graph[i][j] == 0 && i != j) {
                graph[i][j] = INFINITY;
            }
        }
    }

    bool visited[V] = {0};
    int prev[V];
    double dist[V];
    for(int i = 0; i <
     V; i++) {
        dist[i] = INFINITY;
        prev[i] = -1;
    }
    dist[start] = 0;

    while(true) {
        int min_ind = 0;
        double min_dist = INFINITY;
        for(int i = 0; i < V; i++) {
            if(!visited[i] && dist[i] < min_dist) {
                min_ind = i;
                min_dist = dist[i];
            }
        }

        if(min_dist == INFINITY) break;
        visited[min_ind] = true;

        for(int i = 0; i < V; i++) {
            if(dist[i] > min_dist + graph[min_ind][i]) {
                prev[i] = min_ind;
                dist[i] = min_dist + graph[min_ind][i];
            }
        }
    }

    for(int i = 0; i < V; i++) {
        printf("%d to %d: ", start, i);
        print_path_2(prev, i);
        printf("\n");
    }
}

void test_djikstra() {
	double graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
			     { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
			     { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
			     { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
			     { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
			     { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
			     { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
			     { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
			    { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
	// Function call
    for(int i = 0; i < V; i++) {
        djikstra(graph, i);
    }
}

int main() {
    test_djikstra();
}
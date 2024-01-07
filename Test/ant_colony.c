#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

int *create_graph(int *prevRoom, int size, int *graph_size) {
    int *graph = (int *)calloc(size * size, sizeof(int)); // allocates memory for adjacency matrix
    for(int i = 0; i < size; i++) {
        if(prevRoom[i] != -1) {
            graph[prevRoom[i] * size + i] = 1; // sets the edge graph[prevRoom[i]][i]
        }
    }
    *graph_size = size * size; // returns the total number of elements in adjacency matrix by pass by reference.
    return graph;
}

int n(int *graph, int graph_size) {
    return (int)sqrt(graph_size); // returns the number of vertices in the graph from total number of elements in adjacency matrix
}

int get(int *graph, int graph_size, int row, int col) {
    return graph[row * n(graph, graph_size) + col]; // returns the weight at graph[row][column]
}

int p_n_p(int *graph, int graph_size, bool *visited, int num_visited);

void print_num_paths(int *prevRoom, int size) {
    int graph_size;
    int *graph = create_graph(prevRoom, size, &graph_size); // creates graph from prevRoom
    bool *visited = (bool *)calloc(size, sizeof(bool)); // creates an array of visited nodes, default all false
    int t = -1;
    for(int i = 0; i < size; i++) { // finds the starting node 't', i.e the node 'i' where prevRoom[i] == -1
        if(prevRoom[i] == -1) {
            t = i;
        }
    }
    visited[t] = true; // we start at t, so we set visited[t] true
    int tot = p_n_p(graph, graph_size, visited, 1); // get the total number of paths, p_n_p stands for print_num_paths, but to give different name I shortended it.
    printf("Total Paths: %d\n", tot);
}

// This function returns the number of paths through all nodes starting from the given set of visited vertices.
// This function works by taking a set of visited nodes, 
// and then choosing every possible next node given current visited nodes, 
// and then calling itself with the updated visited array for each of those options, and adding up the number of paths which begins from each of those options
// The base case is when all the nodes have been visited, i.e. num_visited = n(graph, graph_size). Then we know that the function has gone through 1 unique path, so we return 1.
int p_n_p(int *graph, int graph_size, bool *visited, int num_visited) {
    int tot = 0;
    if(num_visited == n(graph, graph_size)) { // all nodes visited, path over, no more options, so return 1 for number of paths.
        return 1;
    }

    for(int i = 0; i < n(graph, graph_size); i++) { // iterate through every vertex 
        if(!visited[i]) {                           // which has already been visited
            continue;
        }
        for(int j = 0; j < n(graph, graph_size); j++) {  // iterate through every vertex that hasn't been visited, 

            if(!visited[j] && get(graph, graph_size, i, j) == 1) {  // if there exist an edge from 'i' to 'j' then update the visited array as if you visited j
                visited[j] = true;
                tot += p_n_p(graph, graph_size, visited, num_visited + 1); // , then call the function on the new visited array and add the number of paths from this to the total number of paths
                visited[j] = false; // remove visited[j] after simulating visiting 'j' it so we can use visited for the next option.
            }
        }
    }
    return tot; // return total number of paths
}

int main() {    
    int size;
    printf("Enter the size of the list: "); // get size of the list
    scanf("%d", &size);

    int *prevRoom = (int *)calloc(size, sizeof(int));
    for (int i = 0; i < size; i++) {
        printf("Enter the next integer: "); // read list from user
        scanf("%d", &prevRoom[i]);
    }

    printf("prevRoom: [");
    for (int i = 0; i < size; i++) {
        printf("%d", prevRoom[i]); // print list with proper formatting
        if (i != size - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    print_num_paths(prevRoom, size); // print total number of paths.
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex {
    struct Vertex *next;
    struct Vertex *previous;  
    int vertex;
} Vertex;

Vertex *create_vertex(int vertex, Vertex *next, Vertex *prev) {
    Vertex *new_vertex = (Vertex *)malloc(sizeof(Vertex));
    new_vertex->vertex = vertex;
    new_vertex->next = next;
    new_vertex->previous = prev;
    return new_vertex;
}

Vertex **create_graph(int *prevRoom, int size) {
    Vertex **graph = (Vertex **)calloc(size, sizeof(Vertex *));
    Vertex **list_ends = (Vertex **)calloc(size, sizeof(Vertex *));
    for (int i = 0; i < size; i++) {
        graph[i] = NULL;
    }
    for (int i = 0; i < size; i++) {
        if (prevRoom[i] != -1) {
            Vertex *new_vertex = create_vertex(i, NULL, NULL);
            if (graph[prevRoom[i]] == NULL) {
                graph[prevRoom[i]] = new_vertex;
                list_ends[prevRoom[i]] = new_vertex;
            } else {
                Vertex *end = list_ends[prevRoom[i]];
                end->next = new_vertex;
                new_vertex->previous = end;
                list_ends[prevRoom[i]] = new_vertex;
            }
        }
    }
    return graph;
}

unsigned long long factorial(int n) {
    static int facs[1000] = {0};
    if(facs[n] != 0) return facs[n];
    unsigned long long result = 1;
    for (unsigned int i = 2; i <= n; i++) {
        result *= i;
        facs[i] = result;
    }
    //printf("Factorial of %d: %llu\n", n, result);
    return result;
}

unsigned long long get_num_paths(Vertex **graph, int n, int start, int *path_length) {
    unsigned long long num_paths = 1;
    int total_path_length = 0;
    unsigned long long denominator = 1;
    Vertex *current = graph[start];
    while (current != NULL) {
        int cur_path_length;
        num_paths *= get_num_paths(graph, n, current->vertex, &cur_path_length);
        denominator *= factorial(cur_path_length);
        total_path_length += cur_path_length;
        current = current->next;
    }
    num_paths *= factorial(total_path_length) / denominator;
    *path_length = total_path_length + 1;
    return num_paths;
}

void print_num_paths(int *prevRoom, int size) {
    Vertex **graph = create_graph(prevRoom, size);
    int start = -1;
    for (int i = 0; i < size; i++) {
        if (prevRoom[i] == -1) {
            start = i;
            break;
        }
    }
    int path_length;
    unsigned long long num_paths = get_num_paths(graph, size, start, &path_length);
    printf("Number of paths: %llu\n", num_paths);
}

int main() {
    int prevRoom[] = {-1, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
    int size = sizeof(prevRoom) / sizeof(prevRoom[0]);
    factorial(size);
    print_num_paths(prevRoom, size);
    return 0;
}

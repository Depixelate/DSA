#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "../Lab/queue_circular.c"
#include "../Lab/stack_ll.c"
#include <time.h>
typedef struct Graph {
    int size;
    double *weights;
    double no_edge_weight;
} Graph;

Graph *graph_create(int size, double no_edge_weight, double *weights) {
    Graph *g = (Graph *)calloc(1, sizeof(Graph));
    g->size = size;
    g->weights = (double *)calloc(size * size, sizeof(double));
    g->no_edge_weight = no_edge_weight;
    for(int i = 0; i < size * size; i++) {
        if(weights) {
            g->weights[i] = weights[i];
        } else {
            g->weights[i] = no_edge_weight;
        }
    }
    return g;
}

void graph_clear(Graph *g) {
    for(int i = 0; i < g->size * g->size; i++) {
        g->weights[i] = g->no_edge_weight;
    }
}

void graph_destroy(Graph *g) {
    free(g->weights);
    free(g);
}

Graph *graph_copy(Graph *g) {
    Graph *copy = graph_create(g->size, g->no_edge_weight, NULL);
    for(int i = 0; i < g->size * g->size; i++) {
        copy->weights[i] = g->weights[i];
    }
    return copy;
}

int graph_index(Graph *g, int i, int j) {
    return g->size * i + j;
}

double graph_get_weight(Graph *g, int i, int j) {
    return g->weights[graph_index(g, i, j)];
}

bool graph_has_edge(Graph *g, int i, int j) {
    return graph_get_weight(g, i, j) != g->no_edge_weight;
}

void graph_set_weight(Graph *g, int i, int j, double weight) {
    g->weights[graph_index(g, i, j)] = weight;
}

void graph_set_1(Graph *g, int i, int j) {
    graph_set_weight(g, i, j, 1);
}

void ugraph_set_1(Graph *g, int i, int j) {
    graph_set_1(g, i, j);
    graph_set_1(g, j, i);
}

void graph_remove_edge(Graph *g, int i, int j) {
    graph_set_weight(g, i, j, g->no_edge_weight);
}

void ugraph_remove_edge(Graph *g, int i, int j) {
    graph_remove_edge(g, i, j);
    graph_remove_edge(g, j, i);
}

void graph_is_connected_helper(Graph *g, int cur_node, bool visited[]) {
    visited[cur_node] = true;
    for(int i = 0; i < g->size; i++) {
        if(!visited[i] && graph_has_edge(g, cur_node, i)) {
            graph_is_connected_helper(g, i, visited);
        }
    }
}

bool graph_is_connected(Graph *g) {
    bool *visited = (bool *)calloc(g->size, sizeof(bool));
    graph_is_connected_helper(g, 0, visited);
    for(int i = 0; i < g->size; i++) {
        if(!visited[i]) {
            return false;
        }
    }
    free(visited);
    return true;
}

void graph_print_weighted(Graph *g, int integral_width, int fractional_width) {
    int num_width = fractional_width != 0 ? integral_width + fractional_width + 1 : integral_width;
    printf("The graph: \n");
    for(int i = -1; i < g->size; i++) {
        if(i == -1) {
            printf("%*s", num_width * 2, "");
            for(int j = 0; j < g->size; j++) {
                printf("%0*d%*s", num_width, j, num_width, ""); 
            }
        } else {
            for(int j = -1; j < g->size; j++) {
                if(j == -1) {
                    printf("%0*d%*s", num_width, i, num_width, "");
                } else {
                    printf("%0*.*lf%*s", integral_width, fractional_width, graph_get_weight(g, i, j), num_width, ""); 
                }
            }
        }
        printf("\n");
    }
}

void graph_print_unweighted(Graph *g) {
    graph_print_weighted(g, 1, 0);
}

void graph_print_dft_helper(Graph *g, int cur_node, bool visited[]) {
    printf("%d ", cur_node);
    visited[cur_node] = true;
    for(int i = 0; i < g->size; i++) {
        if(!visited[i] && graph_has_edge(g, cur_node, i)) {
            graph_print_dft_helper(g, i, visited);
        }
    }
}

void graph_print_dft(Graph *g, int start) {
    printf("DFT: ");
    bool *visited = (bool *)calloc(g->size, sizeof(bool));
    graph_print_dft_helper(g, start, visited);
    printf("\n");
    free(visited);
}

void graph_print_bft(Graph *g, int start) {
    printf("BFT: ");
    bool *will_visit = (bool *)calloc(g->size, sizeof(bool));
    Queue *nodes = queue_create(g->size);
    queue_enqueue(nodes, start);
    will_visit[start] = true;
    while(!queue_is_empty(nodes)) {
        int cur_node = queue_dequeue(nodes);
        printf("%d ", cur_node);
        for(int i = 0; i < g->size; i++) {
            if(!will_visit[i] && graph_has_edge(g, cur_node, i)) {
                queue_enqueue(nodes, i);
                will_visit[i] = true;
            }
        }
    }
}

void graph_print_bfs(Graph *g, int start, int end) {
    //bool *will_visit = (bool *)calloc(g->size, sizeof(bool));
    int *next = (int *)calloc(g->size, sizeof(int));
    for(int i = 0; i < g->size; i++) {
        next[i] = -1;
    }
    ///int *dist = (int *)calloc(g->size, sizeof(int));
    Queue *nodes = queue_create(g->size);
    queue_enqueue(nodes, end);
    next[end] = end;
    while(!queue_is_empty(nodes)) {
        int cur_node = queue_dequeue(nodes);
        if(cur_node == start) break;
        for(int node = 0; node < g->size; node++) {
            if(next[node] == -1 && graph_has_edge(g, node, cur_node)) {
                next[node] = cur_node;
                queue_enqueue(nodes, node);
            }
        }
    }

    if(next[start] == -1) {
        printf("End not accessible from Start!\n");
    } else {
        int cur_node = start;
        while(next[cur_node] != cur_node) {
            printf("%d ", cur_node);
            cur_node = next[cur_node];
        }
        printf("%d ", cur_node);   
    }
    printf("\n");
}

double graph_print_djikstra(Graph *g, int start, int end) {
    double *dist = (double *)calloc(g->size, sizeof(double));
    int *next = (int *)calloc(g->size, sizeof(int));
    bool *visited = (bool *)calloc(g->size, sizeof(bool));
    for(int i = 0; i < g->size; i++) {
        if(i == end) {
            dist[i] = 0;
            next[i] = i;
        } else {
            dist[i] = INFINITY;
            next[i] = -1;
        }

        visited[i] = false;
    }
    while(true) {
        int min = end;
        for(int i = 0; i < g->size; i++) {
            if(!visited[i] && (visited[min] || dist[i] < dist[min])) {
                min = i;
            }
        }
        if(visited[min] || dist[min] == INFINITY) {
            printf("Error, no path from start to end exists!");
            return INFINITY;
        }

        if(min == start) break;
        for(int i = 0; i < g->size; i++) {
            if(graph_has_edge(g, i, min) && dist[min] + graph_get_weight(g, i, min) < dist[i]) {
                dist[i] = dist[min] + graph_get_weight(g, i, min);
                next[i] = min;
            }
        }
        visited[min] = true;
    }
    int cur_node = start;
    while(next[cur_node] != cur_node) {
        printf("%d ", cur_node);
        cur_node = next[cur_node];
    }
    printf("%d ", cur_node);
    printf("\ndist: %lf",dist[start]);
    return dist[start];
}

Graph *floyd_warshall(Graph *g) { 
    Graph *d = graph_copy(g);

    for(int k = 0; k < g->size; k++) {
        for(int i = 0; i < g->size; i++) {
            for(int j = 0; j < g->size; j++) {
                if(d->weights[i][j] > d->weights[i][k] + d->[k][i]) {
                    d[i][j] = d[i][k] + d[k][j];
                    p[i][j] = p[i][k];
                }
            }
        }
    }
    return d;
}

bool graph_has_no_incoming_edges(Graph *g, int node) {
    for(int i = 0; i < g->size; i++) {
        if(graph_has_edge(g, i, node)) {
            return false;
        }
    }
    return true;
}

void graph_print_topo_df_helper(Graph *copy, bool have_printed[], int cur_node) {
    if(have_printed[cur_node] || !graph_has_no_incoming_edges(copy, cur_node)) return; 
    printf("%d ", cur_node);
    have_printed[cur_node] = true;

    for(int node = 0; node < copy->size; node++) {
        if(graph_has_edge(copy, cur_node, node)) {
            graph_remove_edge(copy, cur_node, node);
            graph_print_topo_df_helper(copy, have_printed, node);
        }
    }
}

void graph_print_topological_df(Graph *g) {
    printf("Topological order of nodes, depth first: ");
    Graph *copy = graph_copy(g);
    bool *have_printed = (bool *)calloc(g->size, sizeof(bool));

    for(int i = 0; i < copy->size; i++) {
        graph_print_topo_df_helper(copy, have_printed, i);
    }
    graph_destroy(copy);
    free(have_printed);
    printf("\n");
}

void graph_print_topological_bf(Graph *g) {
    printf("Topological order of nodes, breadth first: ");
    Graph *copy = graph_copy(g);
    Queue *no_incoming_edges = queue_create(copy->size);

    for(int i = 0; i < copy->size; i++) {
        if(graph_has_no_incoming_edges(g, i)) {
            queue_enqueue(no_incoming_edges, i); 
        }
    }

    while(!queue_is_empty(no_incoming_edges)) {
        int no_incoming_node = queue_dequeue(no_incoming_edges);
        printf("%d ", no_incoming_node);
        for(int node = 0; node < g->size; node++) {
            if(graph_has_edge(g, no_incoming_node, node)) {
                graph_remove_edge(g, no_incoming_node, node);
                if(graph_has_no_incoming_edges(g, node)) {
                    queue_enqueue(no_incoming_edges, node);
                }
            }
        }
    }
    printf("\n");
    queue_destroy(no_incoming_edges);
    graph_destroy(copy);
}

double rand01() {
    return (double)rand()/RAND_MAX;
}

//
int rand_int(int min, int max) {
    return rand() % (max - min) + min;
}

bool rand_bool(double frac_true) {
    return rand01() < frac_true;
}

Graph *rand_directed_weighted_graph(int size, double frac_edge, double no_edge_weight, int min_weight, int max_weight, bool allow_both_dir, bool ensure_connected) {

    Graph *g = graph_create(size, no_edge_weight, NULL);
    do {
        graph_clear(g);
        for(int i = 0; i < g->size; i++) {
            for(int j = 0; j < g->size; j++) {
                if(i != j && rand_bool(frac_edge) && (allow_both_dir || !graph_has_edge(g, j, i))) {
                    double weight = rand_int(min_weight, max_weight);
                    graph_set_weight(g, i, j, weight);
                }
            }
        }
    } while(ensure_connected && !graph_is_connected(g));
    return g;
}

Graph *rand_undirected_weighted_graph(int size, double frac_edge, double no_edge_weight, int min_weight, int max_weight, bool ensure_connected) {
    Graph *g;
    while (true) {
        g = rand_directed_weighted_graph(size, frac_edge, no_edge_weight, min_weight, max_weight, true, false);
        for(int i = 0; i < g->size; i++) {
            for(int j = 0; j < i; j++) {
                graph_set_weight(g, j, i, graph_get_weight(g, i, j));
            }
        }
        if(!ensure_connected || graph_is_connected(g)) {
            break;
        }
        free(g);
    } 
    return g;
}

Graph *rand_directed_unweighted_graph(int size, double frac_edge, bool allow_both_dir, bool ensure_connected) {
    Graph *g = rand_directed_weighted_graph(size, frac_edge, 0, 1, 2, allow_both_dir, ensure_connected);
    return g;
}

Graph *rand_undirected_unweighted_graph(int size, double frac_edge, bool ensure_connected) {
    Graph *g = rand_undirected_weighted_graph(size, frac_edge, 0, 1, 2, ensure_connected);
    return g;
}

void test_topological_sort() {
    Graph *g = graph_create(8, 0, NULL);
    graph_set_1(g, 0, 2);
    graph_set_1(g, 0, 3);
    graph_set_1(g, 2, 4);
    graph_set_1(g, 3, 4);
    //graph_set_1(g, 5, 6);
    //graph_set_1(g, 5, 7);
    graph_set_1(g, 5, 6);
    graph_set_1(g, 5, 7);
    graph_set_1(g, 7, 1);
    graph_print_unweighted(g);
    graph_print_topological_bf(g);
}

void test_bft() {
    int seed = 1701308329/*time(NULL)*/;
    printf("seed: %d\n", seed); 
    srand(seed); 
    Graph *g = rand_undirected_unweighted_graph(8, 0.2, true);
    graph_print_unweighted(g);
    graph_print_bft(g, 0);
}

void test_dft() {
    int seed = 1701308329/*time(NULL)*/;
    printf("seed: %d\n", seed); 
    srand(seed); 
    Graph *g = rand_undirected_unweighted_graph(8, 0.2, true);
    graph_print_unweighted(g);
    graph_print_dft(g, 0);
}

void test_bfs() {
    int seed = 1701344899;//time(NULL);
    printf("seed: %d\n", seed);
    srand(seed);
    Graph *g = rand_undirected_unweighted_graph(8, 0.2, true);
    ugraph_remove_edge(g, 1, 3); 
    graph_print_unweighted(g);
    int start = 5, end = 4;
    printf("Going from %d to %d: ", start, end);
    graph_print_bfs(g, start, end);
}

void test_djikstra() {
    int seed = time(NULL);
    printf("seed: %d\n", seed);
    srand(seed);
    Graph *g = rand_directed_weighted_graph(8, 0.15, INFINITY, 1, 10, true);
    graph_print_weighted(g, 3, 0);
    int start = 2, end = 7;
    printf("Going from %d to %d: ", start, end);
    graph_print_djikstra(g, start, end);
}

int main() {
    test_djikstra();
    return 0;
}

// Node *helper(int inorder[], int preorder[], int inorder_min, int inorder_max, int pos) {
//     int ipos = -1;
//     for(int i = inorder_min; i <= inorder_max; i++) {
//         if(inorder[i] == preorder[pos]) {
//             ipos = i;
//         }
//     }
//     if(ipos == -1) return NULL;

//     Node *cur = node_create(preorder[pos], NULL, NULL);
//     cur->left = helper(inorder, preorder, inorder_min, ipos-1, pos + 1);
//     cur->right = helper(inorder, preorder, ipos+1, inorder_max, pos + 1 + ipos - inorder_min);
//     return cur;
// }
                                                                                             
// Node *tree_from_inorder_preorder(int inorder[], int preorder[], int size) {
//     return helper(inorder, preorder, 0, size-1, 0);
// }
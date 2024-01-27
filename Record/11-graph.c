#include "8-queueADT.c"
void dfs_helper(int graph[8][8], bool visited[8], int start) {
    visited[start] = true;
    printf("%d ", start);
    for(int i = 0; i < 8; i++) {
        if(graph[start][i] == 1 && !visited[i]) {
            dfs_helper(graph, visited, i);
        }
    }
}

void dfs(int graph[8][8]) {
    bool visited[8] = {0};
    for(int i = 7; i >= 0; i--) {
        if(!visited[i]) {
            printf("\n New Component \n");
            dfs_helper(graph, visited, i);
        }
    } 
    printf("\n");
}

void bfs_helper(int graph[8][8], bool visited[8], int start) {
    Queue *q = queue_create(8);
    enqueue(q, start);
    visited[start] = true;
    while(!isEmpty(q)) {
        int cur = dequeue(q);
        printf("%d ", cur);
        for(int i = 0; i < 8; i++) {
            if(graph[cur][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
            }
        }
    }
}

void bfs(int graph[8][8]) {
    bool visited[8] = {0};
    Queue *q = queue_create(8);
    for(int i = 7; i >= 0; i--) {
        if(!visited[i]) {
            printf("\nNew component...\n");
            bfs_helper(graph, visited, i);
        }
    }
    printf("\n");
}

typedef struct Q2{
    int size;
    int max_size;
    int start;
    int end;
    int *elems;
} Q2;

Q2 *q2_create(int max_size) {
    Q2 *q = (Q2 *)malloc(sizeof(Q2));
    q->size = 0;
    q->max_size = max_size;
    q->start = 0;
    q->end = -1;
    q->elems = (int *)calloc(q->max_size, sizeof(int));
    return q;
}

bool q2_is_empty(Q2 *q) {
    return q->size == 0;
}

bool q2_is_full(Q2 *q) {
    return q->size == q->max_size;
}

void q2_enqueue(Q2 *q, int elem) {
    if(q2_is_full(q)) return;
    q->end = (q->end + 1) % q->max_size;
    q->elems[q->end] = elem;
    q->size += 1;
}

int q2_dequeue(Q2 *q) {
    if(q2_is_empty(q)) {
        return -1;
    }

    int elem = q->elems[q->start];
    q->start += 1;
    q->start %= q->max_size;
    q->size -= 1;
    return elem;
}

int q2_peek(Q2 *q) {
    if(q2_is_empty(q)) {
        return -1;
    }

    return q->elems[q->end];
}

void nbh(int graph[8][8], bool visited[8], int start) {
    Q2 *q = q2_create(8);
    q2_enqueue(q, start);
    visited[start] = true;
    while(!q2_is_empty(q)) {
       int cur = q2_dequeue(q);
       printf("%d ", cur);
        for(int i = 0; i < 8; i++) {
            if(!visited[i] && graph[cur][i] != 0) {
                visited[i] = true;
                q2_enqueue(q, i);
            } 
        }
    }
}

void new_bfs(int graph[8][8]) {
    bool visited[8] = {0};
    for(int i = 0; i < 8; i++) {
        if(!visited[i]) {
            nbh(graph, visited, i);
        }
    }
    printf("\n");
}

void ndh(int graph[8][8], bool visited[8], int start) {
    visited[start] = true;
    printf("%d ", start);
    for(int i = 0; i < 8; i++) {
        if(!visited[i] && graph[start][i] != 0) {
            ndh(graph, visited, i);
        }
    }
}

void new_dfs(int graph[8][8]) {
    bool visited[8] = {0};
    for(int i = 0; i < 8; i++) {
        if(!visited[i]) {
            ndh(graph, visited, i);
        }
    }
    printf("\n");
}

bool is_row_empty(int graph[8][8], int row) {
    for(int i = 0; i < 8; i++) {
        if(graph[i][row] != 0) return false;
    }
    return true;
}

void tsh(int graph[8][8], bool visited[8], int start) {
    visited[start] = true;
    printf("%d ", start);
    for(int i = 0; i < 8; i++) {
        if(graph[start][i] != 0) {
            graph[start][i] = 0;
            if(is_row_empty(graph, i)) tsh(graph, visited, i);
        }
    }
}

void topo_sort(int graph[8][8]) {
    bool visited[8] = {0};
    for(int i = 0; i < 8; i++) {
        if(!visited[i] && is_row_empty(graph, i)) {
            tsh(graph, visited, i);
        }
    }
    for(int i = 0; i < 8; i++) {
        if(!visited[i]) {
            return false;
        }
    }
    return true;
}

void printAllPathsUtil(int graph[8][8], int cur, int end, bool visited[8], int path[8], int cur_len) {
    visited[cur] = true;
    path[cur_len++] = cur;
    if(cur == end) {
        printf("Path: ");
        for(int i = 0; i < cur_len; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        for(int i = 0; i < 8; i++) {
            if(!visited[i] && graph[cur][i] != 0) {
                printAllPathsUtil(graph, i, end, visited, path, cur_len);
            }
        }
    }
    visited[cur] = false;
}

void printAllPaths(int graph[8][8], int start, int end) {
    bool visited[8] = {0};
    int path[8];
    int cur_len = 0;
    printAllPathsUtil(graph, start, end, visited, path, cur_len);
}

void findAllSumsHelper(int nums[], int len, int target, int path[], int path_len, int cur_sum, int start) {
    if(cur_sum == target) {
        printf("Nums: ");
        for(int i = 0; i < path_len; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        for(int i = start; i < len; i++) {
            path[path_len++] = nums[i];
            cur_sum += nums[i];
            findAllSumsHelper(nums, len, target, path, path_len, cur_sum, i+1);
            cur_sum -= nums[i];
            path_len--;
        }
    }
}

void findAllSums(int nums[], int len, int target) {
    int path[1000];
    int path_len = 0;
    int cur_sum = 0;
    findAllSumsHelper(nums, len, target, path, path_len, cur_sum, 0);
}



void test_traversal() {
    int G[8][8] = {
        {0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0}
    };
    printf("DFS Traversal: ");
    new_dfs(G);

    printf("\nBFS Traversal: ");
    new_bfs(G);

    //printf("\nTopo Sort: ");
    int hi;
    //topo_sort(G);

    int nums[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    findAllSums(nums, 8, 12);

    printAllPaths(G, 0, 5);
}



int main() {
    test_traversal();
    return 0;
}
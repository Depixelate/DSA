int *rand_array(int n, int max) {
    int *arr = (int *)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) {
        arr[i] = rand() % max;
    }
    return arr;
}

void print_array(int *arr, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


#define LEN(X) sizeof(X)/sizeof(X[0]) 
#define BSTR(X) (X) ? "true" : "false"
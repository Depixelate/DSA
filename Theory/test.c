#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    double value = 5;  // Replace this with your value
    srand(time(NULL));
    printf("%d", RAND_MAX);
    for(int i = 0; i < 100; i++) {
        printf("%d ", rand());
    }
    if (value == INFINITY) {
        
        printf("The value is infinity.\n");
    } else {
        printf("The value is not infinity.\n");
    }

    return 0;
}
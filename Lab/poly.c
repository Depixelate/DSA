#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct DLLNode {
    double coeff;
    int power;
    struct DLLNode *next;
} DLLNode;

DLLNode **get_last_next_ptr(DLLNode **head) {
    DLLNode **cur = head;
    for(; *cur != NULL; cur = &(*cur)->next) {}
    return cur;
}

DLLNode *append(DLLNode **head, double coeff, int power) {
    DLLNode **end = get_last_next_ptr(head);
    *end = (DLLNode *) malloc(sizeof(DLLNode));
    (*end)->coeff = coeff;
    (*end)->power = power;
    (*end)->next = NULL;
    return *end;
}

DLLNode *free_list(DLLNode *head) {
    DLLNode *cur = head, *prev = NULL;
    while(cur != NULL) {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
}

DLLNode *add_polys(DLLNode *poly1, DLLNode *poly2) {
    DLLNode *res = NULL;
    for(DLLNode *cur1 = poly1, *cur2=poly2; (cur1 != NULL || cur2 != NULL);) {
        int power = 0;
        double coeff = 0; 
        if(cur1 != NULL && (cur2 == NULL || cur2->power < cur1->power)) {
            coeff = cur1->coeff;
            power = cur1->power;
            cur1 = cur1->next;
            //append(&res, cur1->power, cur1->coeff);
            
        } else if (cur2 != NULL && (cur1 == NULL || cur1->power < cur2->power)) {
            coeff = cur2->coeff;
            power = cur2->power;    
            cur2 = cur2->next;
        } else {
            coeff = cur1->coeff + cur2->coeff;
            power = cur1->power; // powers same for both terms
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        append(&res, coeff, power);
    }

    return res;
}

void print_poly(DLLNode *poly) {
    for(DLLNode *cur = poly; cur != NULL; cur=cur->next) {
        printf("%.2lfx^%d", cur->coeff, cur->power);
        if(cur->next != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

DLLNode *read_poly() {
    printf("Enter a polynomial: ");
    DLLNode *poly = NULL;
    int readSpecifiers;
    char buf[4096];
    fgets(buf, 4096, stdin);
    buf[strlen(buf)-1] = '\0';
    int charsRead = 0;
    do {
        double coeff = 0;
        int power = 0;
        int tempCharsRead = 0;
        sscanf(buf + charsRead, "%*[ +]%n", &tempCharsRead);
        charsRead += tempCharsRead;
        tempCharsRead = 0;
        readSpecifiers = sscanf(buf + charsRead, "%lfx^%d%n", &coeff, &power, &tempCharsRead);
        charsRead += tempCharsRead;
        if(readSpecifiers > 0) {
            append(&poly, coeff, power);
        }
        //print_poly(poly);       
    } while(readSpecifiers > 0);

    return poly;
}

int main() {
    DLLNode *poly1 = read_poly();
    DLLNode *poly2 = read_poly();
    DLLNode *res = add_polys(poly1, poly2);
    printf("Result: ");
    print_poly(res); 
    free_list(poly1);
    free_list(poly2);
    free_list(res);

    // 
    // // append(&poly, 3, 3);
    // // append(&poly, 2, 2);
    // // append(&poly, 1, 1);
    
    return 0;
}

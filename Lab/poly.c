#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    double coeff;
    int power;
    struct Node *next;
} Node;

Node **get_last_next_ptr(Node **head) {
    Node **cur = head;
    for(; *cur != NULL; cur = &(*cur)->next) {}
    return cur;
}

Node *append(Node **head, double coeff, int power) {
    Node **end = get_last_next_ptr(head);
    *end = (Node *) malloc(sizeof(Node));
    (*end)->coeff = coeff;
    (*end)->power = power;
    (*end)->next = NULL;
    return *end;
}

Node *free_list(Node *head) {
    Node *cur = head, *prev = NULL;
    while(cur != NULL) {
        prev = cur;
        cur = cur->next;
        free(prev);
    }
}

Node *add_polys(Node *poly1, Node *poly2) {
    Node *res = NULL;
    for(Node *cur1 = poly1, *cur2=poly2; (cur1 != NULL || cur2 != NULL);) {
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

void print_poly(Node *poly) {
    for(Node *cur = poly; cur != NULL; cur=cur->next) {
        printf("%.2lfx^%d", cur->coeff, cur->power);
        if(cur->next != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

Node *read_poly() {
    printf("Enter a polynomial: ");
    Node *poly = NULL;
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
    Node *poly1 = read_poly();
    Node *poly2 = read_poly();
    Node *res = add_polys(poly1, poly2);
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

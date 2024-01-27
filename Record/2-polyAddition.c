#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Term {
    double coeff;
    int power;
    struct Term *next;
} Term;

Term *term_gen(double coeff, int power, Term *next) {
    Term *term = (Term *)malloc(sizeof(Term));
    term->coeff = coeff;
    term->power = power;
    term->next = next;
    return term;
}

Term *read_poly() {
    Term *head = NULL;
    printf("Enter number of terms: ");
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        printf("Enter term coeff: ");
        double coeff;
        scanf("%lf", &coeff);
        printf("Enter term power: ");
        int power;
        scanf("%d", &power);
        Term *term = term_gen(coeff, power, NULL);
        Term **cur = &head;
        while(true) {
            if(*cur == NULL || (*cur)->power < power) {
                term->next = *cur;
                *cur = term;
                break;
            }

            if((*cur)->power == power) {
                (*cur)->coeff += coeff;
                break;
            } 
            cur = &((*cur)->next);
        }
    }
    return head;
}

void display_poly(Term **head) {
    Term *cur = *head;
    if(cur == NULL) return;
    printf("%0.2lfx^%d", cur->coeff, cur->power);
    cur = cur->next;
    while(cur != NULL) {
        printf(" + %0.2lfx^%d", cur->coeff, cur->power); 
        cur = cur->next;
    }
    printf("\n");
}

void add_poly(Term **poly1, Term **poly2) {
    Term **cur1 = poly1, *cur2 = *poly2;
    while(cur2 != NULL) {
        if(*cur1 == NULL || (*cur1)->power < cur2->power) {
            Term *tmp = cur2;        
            cur2 = cur2->next;
            tmp->next = (*cur1);
            *cur1 = tmp;
        } else if((*cur1)->power == cur2->power) {
            (*cur1)->coeff += cur2->coeff;
            cur2 = cur2->next;
        }
        cur1 = &((*cur1)->next); 
    }
}

void test_poly() {
    printf("Enter poly 1\n\n");
    Term *poly1 = read_poly();
    printf("Poly 1: ");
    display_poly(&poly1);
    printf("\n\nEnter poly 2\n\n");
    Term *poly2 = read_poly();
    printf("Poly 2: ");
    display_poly(&poly2);
    printf("\n\n");
    add_poly(&poly1, &poly2);
    printf("Result: ");
    display_poly(&poly1);
}

int main() {
    test_poly();
    return 0;
}
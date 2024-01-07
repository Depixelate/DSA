#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct DLLNode {
	struct DLLNode *next;
	struct DLLNode *prev;
	const char *val;
} DLLNode;

typedef struct 

DLLNode *tail(DLLNode *any) {
	while(any->next != NULL) {
		any = any->next;
	}
	return any;
}

DLLNode *head(DLLNode *any) {
	while(any->prev != NULL) {
		any = any->prev;
	}
	return any;
}

DLLNode *new_node(const char *val, DLLNode *prev, DLLNode *next) {
	DLLNode *node = (DLLNode *) malloc(sizeof(DLLNode));
	node->val = val;
	node->prev = prev;
	node->next = next;
	return node;
}

DLLNode *push(DLLNode *tail, const char *val) {
	DLLNode *new_tail = new_node(val, tail, NULL);
	if(tail != NULL) {
		tail->next = new_tail;
	}
	return new_tail;
}

DLLNode *insert(DLLNode *at, const char *val) {
	if(at == NULL) {
		return push(at, val);
	}
	
	DLLNode *node = new_node(val, at, at->prev);
	at->prev = node;
	return node;
}

DLLNode *stack_pop(DLLNode *tail) {
	DLLNode *new_tail = tail->prev;
	if(new_tail != NULL) {
		new_tail->next = NULL;
	}
	free(tail);
	return new_tail;
}

DLLNode *del(DLLNode *at) {
	DLLNode *prev = at->prev;
	DLLNode *next = at->next;
	if(next != NULL) {
		next->prev = prev;
	}
	if(prev != NULL) {
		prev->next = next;
	}
	free(at);
	return next;
}

DLLNode *search_val(DLLNode *any, const char *val) {
	DLLNode *left = any, *right = any, *elem = NULL;
	while(right != NULL) {
		if (strcmp(val, right->val) == 0) {
			return right;	
		}
		right = right->next;
	}
	while(left != NULL) {
		if (strcmp(val, left->val) == 0) {
			return left;
		}
		left = left->next;
	}
		
	return NULL;
}

DLLNode *search_index(DLLNode *start, int index) {
	DLLNode *cur = start;
	int num_steps = index < 0 ? -index : index;
	for(int i = 0; i < num_steps; i++) {
		if(index < 0) {
			cur = cur->prev;
		} else {
			cur = cur->next;
		}
	}
	return cur;
}

void print(DLLNode *head) {
	while(head != NULL) {
		printf("%s\n", head->val);
		head = head->next;
	}
}

int main() {
	DLLNode *head = NULL, *tail = NULL;
	DLLNode *n1 = add_node(&head, "Hi!");
	DLLNode *n2 = add_node(&head, "How are you?");
	DLLNode *n3 = add_node(&head, "I am doing well...");
	DLLNode *n4 = add_node(&head, "What about you?");
	pll(head);
	rem_node(n2);
	printf("\n");
	pll(head);
}

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
	struct Node *next;
	struct Node *prev;
	const char *val;
} Node;

Node *tail(Node *any) {
	while(any->next != NULL) {
		any = any->next;
	}
	return any;
}

Node *head(Node *any) {
	while(any->prev != NULL) {
		any = any->prev;
	}
	return any;
}

Node *new_node(const char *val, Node *prev, Node *next) {
	Node *node = (Node *) malloc(sizeof(Node));
	node->val = val;
	node->prev = prev;
	node->next = next;
	return node;
}

Node *push(Node *tail, const char *val) {
	Node *new_tail = new_node(val, tail, NULL);
	if(tail != NULL) {
		tail->next = new_tail;
	}
	return new_tail;
}

Node *insert(Node *at, const char *val) {
	if(at == NULL) {
		return push(at, val);
	}
	
	Node *node = new_node(val, at, at->prev);
	at->prev = node;
	return node;
}

Node *pop(Node *tail) {
	Node *new_tail = tail->prev;
	if(new_tail != NULL) {
		new_tail->next = NULL;
	}
	free(tail);
	return new_tail;
}

Node *del(Node *at) {
	Node *prev = at->prev;
	Node *next = at->next;
	if(next != NULL) {
		next->prev = prev;
	}
	if(prev != NULL) {
		prev->next = next;
	}
	free(at);
	return next;
}

Node *search_val(Node *any, const char *val) {
	Node *left = any, *right = any, *elem = NULL;
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

Node *search_index(Node *start, int index) {
	Node *cur = start;
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

void print(Node *head) {
	while(head != NULL) {
		printf("%s\n", head->val);
		head = head->next;
	}
}

int main() {
	Node *head = NULL;
	Node *n1 = add_node(&head, "Hi!");
	Node *n2 = add_node(&head, "How are you?");
	Node *n3 = add_node(&head, "I am doing well...");
	Node *n4 = add_node(&head, "What about you?");
	pll(head);
	rem_node(n2);
	printf("\n");
	pll(head);
}

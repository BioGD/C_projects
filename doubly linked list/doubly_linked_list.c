#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node* next;
    struct node* previous;
} node_t;

void iteration(node_t* head) {
    node_t* current = head;
    int i = 0;

    while (current != NULL) {
        printf("index = %d, value = %d\n", i, current->value);
        current = current->next;
        i++;
    }
}

void push_to_end(node_t* head, int value) {
    if (head == NULL) {
        printf("Error: List is empty\n");
        return;
    }

    node_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = (node_t*)malloc(sizeof(node_t));
    if (current->next == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }
    current->next->value = value;
    current->next->next = NULL;
    current->next->previous = current;
}

void push_to_begin(node_t** head, int value) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed\n");
        return;
    }

    new_node->value = value;
    new_node->next = *head;
    new_node->previous = NULL;

    if (*head != NULL) {
        (*head)->previous = new_node;
    }

    *head = new_node;
}

int pop(node_t** head) {
    if (*head == NULL) {
        printf("Error: List is empty\n");
        return -1;
    }

    node_t* next_node = (*head)->next;
    int ret_value = (*head)->value;

    if (next_node != NULL) {
        next_node->previous = NULL;
    }

    free(*head);
    *head = next_node;

    return ret_value;
}

int remove_last(node_t* head) {
    if (head == NULL) {
        printf("Error: List is empty\n");
        return -1;
    }

    if (head->next == NULL) {
        int ret_value = head->value;
        free(head);
        return ret_value;
    }

    node_t* current = head;

    while (current->next->next != NULL) {
        current = current->next;
    }

    int ret_value = current->next->value;
    free(current->next);
    current->next = NULL;

    return ret_value;
}

int remove_by_index(node_t** head, int n) {
    if (*head == NULL) {
        printf("Error: List is empty\n");
        return -1;
    }

    if (n == 0) {
        return pop(head);
    }

    node_t* current = *head;
    node_t* temp_node = NULL;

    for (int i = 0; i < n - 1; i++) {
        if (current->next == NULL) {
            printf("Error: Index out of bounds\n");
            return -1;
        }
        current = current->next;
    }

    if (current->next == NULL) {
        printf("Error: Index out of bounds\n");
        return -1;
    }

    temp_node = current->next;
    int ret_value = temp_node->value;
    current->next = temp_node->next;

    if (temp_node->next != NULL) {
        temp_node->next->previous = current;
    }

    free(temp_node);

    return ret_value;
}

void free_list(node_t* head) {
    node_t* current = head;
    node_t* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main() {
    node_t* head = NULL;
    head = (node_t*)malloc(sizeof(node_t));
    if (head == NULL) {
        printf("Error: Memory allocation failed\n");
        return 1;
    }

    head->value = 10;
    head->next = NULL;
    head->previous = NULL;

    push_to_end(head, 20);
    push_to_begin(&head, 5);

    iteration(head);

    int value = pop(&head);
    printf("Popped value: %d\n", value);

    iteration(head);

    free_list(head);

    return 0;
}

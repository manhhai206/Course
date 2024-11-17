#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->data = value;
    tmp->next = NULL;
    return tmp;
}

void addFirst(Node** head, int value) {
    Node* p = createNode(value);
    p->next = *head; 
    *head = p;       
}

void addLast(Node** head, int value){
    Node* p = createNode(value);

    if (*head == NULL) {
        *head = p;
    }

    Node* last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = p;
}

void addAfter(Node **head, int v2, int value){
    Node *p = createNode(value);
    Node *q = *head;
    while(q != NULL && q->data != v2){
        q = q->next;
    }

    if(q != NULL){
        p->next = q->next;
        q->next = p;
    }
}

void deleteFirst(Node **head){

    if(head != NULL)
    {
        Node*p = *head;
        *head = p->next;
        p->next=NULL;
        free(p);
    }
}

void deleteLast(Node **head){
    if(head != NULL)
    {
        Node* last = *head;
        Node*prev = NULL;

        while(last->next != NULL){
            prev = last;
            last = last->next;
        }

        if(prev == NULL)
        {
            deleteFirst(head);
        } else {
        prev->next = NULL;
        free(last);
        }
    }
}

void deleteNode(Node **head, int value){
    if(head != NULL){
        Node* p = *head;
        Node* prev =  NULL;

        while(p->data != value){
            prev = p;
            p = p->next;
        }
        
        if(p != NULL)
        {
            if(prev ==NULL){
               deleteFirst(head);
            }
            else
            {
            prev->next=p->next;
            p->next=NULL;
            free(p);
            }
        }
    }
}

void output(Node* head) {
    Node* p = head;
    while (p != NULL) {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    Node* head = NULL;
    addFirst(&head, 10);
    addFirst(&head, 20);
    addFirst(&head, 30);
    addFirst(&head, 40);
    addLast(&head,99);
    addAfter(&head,30,60);
    deleteFirst(&head);
    deleteNode(&head,10);
    deleteLast(&head);
    output(head);
    return 0;
}




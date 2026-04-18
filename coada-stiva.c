#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STACK

typedef struct StackNode {
    char data;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

void initStack(Stack *s) {
    s->top = NULL;
}

int isEmptyStack(Stack *s) {
    return s->top == NULL;
}

void push(Stack *s, char c) {
    StackNode *nou = (StackNode*)malloc(sizeof(StackNode));
    if (!nou) {
        printf("Eroare la alocare memorie pentru stiva.\n");
        return;
    }

    nou->data = c;
    nou->next = s->top;
    s->top = nou;
}

char pop(Stack *s) {
    if (isEmptyStack(s)) {
        return '\0';
    }

    StackNode *temp = s->top;
    char c = temp->data;
    s->top = temp->next;
    free(temp);
    return c;
}

void freeStack(Stack *s) {
    while (!isEmptyStack(s)) {
        pop(s);
    }
}

// QUEUE 

typedef struct QueueNode {
    char *data;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front;
    QueueNode *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

int isEmptyQueue(Queue *q) {
    return q->front == NULL;
}

void enQueue(Queue *q, const char *word) {
    QueueNode *nou = (QueueNode*)malloc(sizeof(QueueNode));
    if (!nou) {
        printf("Eroare la alocare memorie pentru coada.\n");
        return;
    }

    nou->data = (char*)malloc(strlen(word) + 1);
    if (!nou->data) {
        free(nou);
        printf("Eroare la alocare memorie pentru sir.\n");
        return;
    }

    strcpy(nou->data, word);
    nou->next = NULL;

    if (q->rear == NULL) {
        q->front = nou;
        q->rear = nou;
    } else {
        q->rear->next = nou;
        q->rear = nou;
    }
}

char* deQueue(Queue *q) {
    if (isEmptyQueue(q)) {
        return NULL;
    }

    QueueNode *temp = q->front;
    char *word = temp->data;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return word;
}

void printQueue(Queue *q) {
    QueueNode *p = q->front;
    while (p != NULL) {
        printf("%s ", p->data);
        p = p->next;
    }
    printf("\n");
}

void freeQueue(Queue *q) {
    while (!isEmptyQueue(q)) {
        char *word = deQueue(q);
        free(word);
    }
}

//WORD REVERSE USING STACK

char* reverseWord(const char *word) {
    Stack s;
    initStack(&s);

    int len = (int)strlen(word);

    for (int i = 0; i < len; i++) {
        push(&s, word[i]);
    }

    char *rev = (char*)malloc(len + 1);
    if (!rev) {
        freeStack(&s);
        return NULL;
    }

    for (int i = 0; i < len; i++) {
        rev[i] = pop(&s);
    }
    rev[len] = '\0';

    return rev;
}

void reverseWordsInQueue(Queue *q) {
    Queue rezultat;
    initQueue(&rezultat);

    while (!isEmptyQueue(q)) {
        char *word = deQueue(q);

        char *rev = reverseWord(word);
        if (rev != NULL) {
            enQueue(&rezultat, rev);
            free(rev);
        }

        free(word);
    }

    q->front = rezultat.front;
    q->rear = rezultat.rear;
}

//MAIN

int main() {
    Queue q;
    initQueue(&q);

    char word[100];

    printf("Introdu cuvinte (scrie stop pentru oprire):\n");

    while (1) {
        scanf("%99s", word);

        if (strcmp(word, "stop") == 0) {
            break;
        }

        enQueue(&q, word);
    }

    printf("\nCoada initiala:\n");
    printQueue(&q);

    reverseWordsInQueue(&q);

    printf("\nCoada dupa inversarea fiecarui cuvant:\n");
    printQueue(&q);

    freeQueue(&q);

    return 0;
}
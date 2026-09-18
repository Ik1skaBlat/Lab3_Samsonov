#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    struct Node* next;
};

typedef struct Node Node;
typedef struct Node* PNode;

struct Queue {
    PNode head;
    PNode tail;
};

typedef struct Queue Queue;

void push(Queue* q, int value){
    PNode NewNode = (PNode)malloc(sizeof(Node));
    if (!NewNode){
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    NewNode->value = value;
    NewNode->next = NULL;

    if (q->head == NULL) {
        q->head = NewNode;
        q->tail = NewNode;
    } else {
        q->tail->next = NewNode;
        q->tail = NewNode;
    }
}

void pop(Queue* q){
    if (q->head == NULL){
        printf("Очередь пуста\n");
        return;
    }

    printf("Удален элемент со значением: %d\n", q->head->value);
    
    q->head = q->head->next;
    
    if (q->head == NULL) {
        q->tail = NULL;
    }

}

void printQueue(Queue* q){
    if (q->head == NULL){
        printf("Очередь пуста\n\n");
        return;
    }
    PNode current = q->head;
    printf("Содержимое очереди:\n");
    while(current != NULL){
        printf("Значение: %d\n", current->value);
        current = current->next;
    }
    printf("\n");
}

void shift(Queue* q, int value){
    if (q->head == NULL || q->head == q->tail) {
        return;
    }

    PNode current = q->head->next;
    PNode prev = q->head;
    int Count = 0;

    while (current != NULL) {
        if (current->value == value) {
            prev->next = current->next;
            if (current == q->tail) {
                q->tail = prev;
            }
            current->next = q->head;
            q->head = current;
            current = prev->next;
            Count++;
        } else {
            prev = current;
            current = current->next;
        }
    }

    if (Count > 0) {
        printf("Элементы со значением %d успешно перенесены в голову.\n\n", value);
    } else {
        printf("Элементы со значением %d не найдены.\n\n", value);
    }
}

int main(){
    Queue q = {NULL, NULL};
    char input[100];
    int value;

    printf("=== Ввод элементов очереди ===\n");
    printf("Введите значение элемента (или 'stop' для завершения ввода):\n");

    while (1) {
        printf("Значение: ");
        scanf("%s", input);

        if (strcmp(input, "stop") == 0) {
            break;
        }

        value = atoi(input);
        push(&q, value);
        printf("Элемент добавлен. Продолжайте ввод или введите 'stop'.\n\n");
    }

    printQueue(&q);

    int choice;
    while (1) {
        printf("Выберите действие:\n");
        printf("1. Добавить элемент (push)\n");
        printf("2. Удалить элемент (pop)\n");
        printf("3. Показать очередь (print)\n");
        printf("4. Перенести элементы с заданным значением в голову\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Неверный ввод!\n");
            break;
        }

        if (choice == 0) {
            while (q.head != NULL) {
                pop(&q);
            }
            break;
        } else if (choice == 1) {
            printf("Введите значение: ");
            scanf("%d", &value);
            push(&q, value);
            printf("Элемент успешно добавлен!\n\n");
        } else if (choice == 2) {
            pop(&q);
            printf("\n");
        } else if (choice == 3) {
            printQueue(&q);
        } else if (choice == 4) {
            printf("Введите значение для переноса: ");
            scanf("%d", &value);
            shift(&q, value);
        } else {
            printf("Неизвестная команда. Попробуйте снова.\n\n");
        }
    }

    return 0;
}
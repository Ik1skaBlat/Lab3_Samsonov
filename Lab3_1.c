#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    int priority;
    struct Node* next;
};

typedef struct Node Node;
typedef struct Node* PNode;

void push(PNode* head, int value, int priority){
    PNode NewNode = (PNode)malloc(sizeof(Node));
    if (!NewNode){
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    NewNode->value = value;
    NewNode->priority = priority;
    NewNode->next = NULL;

    if ((*head) == NULL || (*head)->priority < priority){
        NewNode->next = *head;
        *head = NewNode;
        return;
    }

    PNode current = *head;
    while(current->next != NULL && current->next->priority >= priority){
        current = current->next;
    }

    NewNode->next = current->next;
    current->next = NewNode;
}

void pop(PNode* head){
    if (*head == NULL){
        printf("Очередь пуста\n");
        return;
    }
    PNode temp = *head;
    printf("Удален элемент со значением: %d и приоритетом: %d\n", temp->value, temp->priority);
    *head = (*head)->next;
    free(temp);
}

void printQueue(PNode head){
    if (head == NULL){
        printf("Очередь пуста\n\n");
        return;
    }
    PNode current = head;
    printf("Содержимое упорядоченной очереди:\n");
    while(current != NULL){
        printf("Значение: %d | Приоритет: %d\n", current->value, current->priority);
        current = current->next;
    }
    printf("\n");
}

void delete_priority(PNode* head, int priority){
    if (head == NULL){
        printf("Очередь пуста\n\n");
        return;
    }

    PNode current = *head;
    PNode prev = NULL;
    int deletedCount = 0;

    while (current != NULL) {
        if (current->priority == priority) {
            if (prev == NULL) {
                *head = current->next;
                current = *head;
            } else {
                prev->next = current->next;
                current = current->next;
            }
            deletedCount++;
        } else {
            prev = current;
            current = current->next;
        }
    }

    if (deletedCount > 0) {
        printf("Успешно удалено элементов: %d с приоритетом: %d\n\n", deletedCount, priority);
    } else {
        printf("Элементы с приоритетом %d не найдены.\n\n", priority);
    }
}

int main(){
    PNode head = NULL;
    char input[100];
    int value, priority;

    printf("=== Ввод элементов очереди ===\n");
    printf("Введите значение элемента (или 'stop' для завершения ввода):\n");

    while (1) {
        printf("Значение: ");
        scanf("%s", input);

        if (strcmp(input, "stop") == 0) {
            break;
        }

        value = atoi(input);

        printf("Приоритет: ");
        if (scanf("%d", &priority) != 1) {
            printf("Ошибка ввода приоритета!\n");
            break;
        }

        push(&head, value, priority);
        printf("Элемент добавлен. Продолжайте ввод или введите 'stop'.\n\n");
    }

    printQueue(head);

    int choice;
    while (1) {
        printf("Выберите действие:\n");
        printf("1. Добавить элемент (push)\n");
        printf("2. Удалить элемент с наивысшим приоритетом (pop)\n");
        printf("3. Показать очередь (print)\n");
        printf("4. Удалить элементы с заданным приоритетом\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Неверный ввод!\n");
            break;
        }

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            printf("Введите значение: ");
            scanf("%d", &value);
            printf("Введите приоритет: ");
            scanf("%d", &priority);
            push(&head, value, priority);
            printf("Элемент успешно добавлен!\n\n");
        } else if (choice == 2) {
            pop(&head);
            printf("\n");
        } else if (choice == 3) {
            printQueue(head);
        } else if (choice == 4){
            printf("Введите значение: ");
            int priority;
            scanf("%d", &priority);
            delete_priority(&head, priority);
        } else {
            printf("Неизвестная команда. Попробуйте снова.\n\n");
        }
    }

    return 0;
}
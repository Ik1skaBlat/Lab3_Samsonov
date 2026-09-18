#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int value;
    struct Node* next;
};

typedef struct Node Node;
typedef struct Node* PNode;

void push(PNode* head, int value){
    PNode NewNode = (PNode)malloc(sizeof(Node));
    if (!NewNode){
        printf("Ошибка выделения памяти\n");
        exit(1);
    }
    NewNode->value = value;
    NewNode->next = *head;
    *head = NewNode;
}

void pop(PNode* head){
    if (*head == NULL){
        printf("Стек пуст\n");
        return;
    }

    printf("Удален верхний элемент со значением: %d\n", (*head)->value);
    
    *head = (*head)->next;
}

void printStack(PNode head){
    if (head == NULL){
        printf("Стек пуст\n\n");
        return;
    }
    PNode current = head;
    printf("Содержимое стека (от верхушки к дну):\n");
    while(current != NULL){
        printf("Значение: %d\n", current->value);
        current = current->next;
    }
    printf("\n");
}

void invertStack(PNode* head) {
    if (*head == NULL || (*head)->next == NULL) {
        printf("Стек пуст или содержит всего один элемент.\n\n");
        return;
    }

    PNode prev = NULL;
    PNode current = *head;
    PNode next = NULL;

    while (current != NULL) {
        next = current->next; 
        current->next = prev; 
        prev = current; 
        current = next; 
    }

    *head = prev; 
    printf("Стек успешно инвертирован!\n\n");
}

int main(){
    PNode head = NULL;
    char input[100];
    int value;

    printf("=== Ввод элементов стека ===\n");
    printf("Введите значение элемента (или 'stop' для завершения ввода):\n");

    while (1) {
        printf("Значение: ");
        scanf("%s", input);

        if (strcmp(input, "stop") == 0) {
            break;
        }

        value = atoi(input);
        push(&head, value);
        printf("Элемент добавлен на вершину стека. Продолжайте ввод или введите 'stop'.\n\n");
    }

    printStack(head);

    int choice;
    while (1) {
        printf("Выберите действие:\n");
        printf("1. Добавить элемент в стек (push)\n");
        printf("2. Удалить элемент из стека (pop)\n");
        printf("3. Показать стек (print)\n");
        printf("4. Инвертировать стек (invert)\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Неверный ввод!\n");
            break;
        }

        if (choice == 0) {
            while (head != NULL) {
                pop(&head);
            }
            break;
        } else if (choice == 1) {
            printf("Введите значение: ");
            scanf("%d", &value);
            push(&head, value);
            printf("Элемент успешно добавлен на вершину!\n\n");
        } else if (choice == 2) {
            pop(&head);
            printf("\n");
        } else if (choice == 3) {
            printStack(head);
        } else if (choice == 4) {
            invertStack(&head);
        } else {
            printf("Неизвестная команда. Попробуйте снова.\n\n");
        }
    }

    return 0;
}
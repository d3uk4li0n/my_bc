#include "../include/my_bc.h"

int matching_brackets(char *string){
    int open = 0, closed = 0;
    for(int i = 0; string[i] != '\0'; i++){
        if(string[i] == '(' || string[i] == '[' || string[i] == '{') open += 1;
        if(string[i] == ')' || string[i] == ']' || string[i] == '}') closed += 1;
    }
    if(open == closed) return 1;
    return 0;
}

bool is_operator(char *string){
    
    char first = string[0];
    char second = string[1];

    return (first == 'x' || first == '+' || first == '-' ||
        first == '*' || first == '/' || first == '%') && second == '\0';
}

bool is_integer(char *string){

    if (*string == '-'){ // can be negative
        string++;
    }else if (*string == '+'){ // can contains +         
        string++;
    }

    //should be at least one digit
    if (*string == '\0') {
        return false;
    }

    while(*string != '\0'){
        if (!is_digit(*string)){
            return false;
        }
        string++;
    }

    return true;

}

bool is_space(char c){
    if(c == ' ') return 1;
    return 0;
}

//precondition: stack is not empty
void stack_pop(struct Stack* stack, char data[]){
    
    struct Node *temp = stack->top;
    my_strcpy(data, stack->top->data);
    stack->top = stack->top->next; 

    free(temp); //deleting the node
}

//precondition: stack is not empty
void stack_top(struct Stack* stack, char data[]){
    my_strcpy(data, stack->top->data);
}

void stack_push(struct Stack* stack, char data[]){
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    my_strcpy(newNode->data, data);
    if (stack->top == NULL) {
        newNode->next = NULL;
    } else {
        newNode->next = stack->top; 
    }
    stack->top = newNode;
}

bool stack_is_empty(struct Stack* stack){
    return stack->top == NULL;
}

void stack_clear(struct Stack* stack){
    struct Node *temp;
    struct Node *current = stack->top;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
}

void stack_initialize(struct Stack* stack){
    stack->top = NULL;
}

void queue_initialize(struct Queue* queue){
    queue->head = queue->tail = NULL;
}

//precondition: queue is not empty
void queue_dequeue(struct Queue* queue, char data[]){

    struct Node *temp = queue->head;
    my_strcpy(data, queue->head->data);
    queue->head = queue->head->next; 

    if (queue->head == NULL){
        queue->tail = NULL;
    }

    free(temp); //deleting the node

}

void queue_enqueue(struct Queue* queue, char data[]){

    //create new node
    struct Node *newNode;
    newNode = (struct Node *)malloc(sizeof(struct Node));
    my_strcpy(newNode->data, data);
    newNode->next = NULL;

    if (queue->head == NULL) { //empty
        queue->head = queue->tail = newNode;
    } else {
        queue->tail->next = newNode; 
        queue->tail = newNode;
    }
}

void queue_clear(struct Queue* queue){
    struct Node *temp;
    struct Node *current = queue->head;

    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    queue->head = queue->tail = NULL;
}

bool queue_is_empty(struct Queue* queue){
    return queue->head == NULL;
}
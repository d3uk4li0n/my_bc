#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>

#ifndef MY_BC_H
#define MY_BC_H

int is_digit(char);
int is_char(char);
int add(int, int);
int subtract(int, int);
int multiply(int, int);
int divide(int, int);
int modulo(int, int);
bool check_expression(char *expression);

#endif

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

int my_strlen(char *);
int my_strcmp(char *s1, char *s2);
char *my_strncpy(char *dst, char *src, size_t n);
char *my_strcpy(char *dst, char *src);
int my_atoi(char *str);
void my_itoa(char *str, int val);
int is_empty(char c);

#endif


#ifndef NODE_H
#define NODE_H

#define DATA_SIZE 20

struct Node {
    char data[DATA_SIZE];
    struct Node *next;
};

#endif

#ifndef STACK_H
#define STACK_H

struct Stack {
    struct Node *top;
};

void stack_pop(struct Stack* stack, char data[]);
void stack_top(struct Stack* stack, char data[]);
void stack_push(struct Stack* stack, char data[]);
bool stack_is_empty(struct Stack* stack);
void stack_clear(struct Stack* stack);
void stack_initialize(struct Stack* stack);

#endif


#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
    struct Node *head;
    struct Node *tail;
};

void queue_initialize(struct Queue* queue);
void queue_dequeue(struct Queue* queue, char data[]);
void queue_enqueue(struct Queue* queue, char data[]);
void queue_clear(struct Queue* queue);
bool queue_is_empty(struct Queue* queue);

#endif

#ifndef UTILITY_H
#define UTILITY_H

int matching_brackets(char *);
bool is_operator(char *);
bool is_integer(char *);

bool handleCmd(int argc, char **argv);

/*split the input into token such as 1+2 ==> 1, +, 2*/
bool tokenize(char* expression, struct Queue* queue);

/*get the precedence of the operator*/
int precedence(char token[]);

/*convert infix to postfix such as 3 + 4 = 3 4 +*/
bool infixToPostfix(char* expression, struct Queue* postfix);

/*calculate the expression*/
bool calculate(char* expression, int* result);

#endif
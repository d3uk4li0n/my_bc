#include "../include/my_bc.h"

int add(int a, int b){
    return a+b;
}

int subtract(int a, int b){
    return a-b;
}

int multiply(int a, int b){
    return a*b;
}

int divide(int a, int b){
    return a/b;
}

int modulo(int a, int b){
    return a % b;
}

int is_digit(char c){
    if(c >= '0' && c <= '9') return 1;
    return 0;
}

int is_empty(char c){
    return c == '\t' || c == ' ';
}

int is_char(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
    return 0;
}

bool check_expression(char* expression) {

    for (int i = 0; expression[i] != '\0'; i++) {

        char ch = expression[i];

        if (is_char(ch)) {
            printf("invalid expression (character found)\n");
            return false;
        }

        if (ch == ' ' || ch == '\t' || ch == '(' || ch == ')' || ch == '+' || ch == '-'
            || ch == '*' || ch == '/' || ch == '%' || is_digit(ch)) {

        }
        else {
            printf("invalid expression (unknown character\n");
            return false;
        }
    }

    if (!matching_brackets(expression)) {
        printf("invalid expression (unmatching brackets)\n");
        return false;
    }
    return true;
}






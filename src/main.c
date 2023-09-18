#include "../include/my_bc.h"

// implememnt function to handle cmd line arguments
bool handleCmd(int argc, char **argv){

    //validate argument
    if (argc != 2){
        printf("Invalid argument!");
        return false;
    }

    if (check_expression(argv[1]) == 0)
    {//expression is valid
        return false;
    }
    return true;
}

bool tokenize(char* expression, struct Queue* queue){

    char prevChar = '\0'; //previous char

    char* exp = expression;
    while (*exp != '\0')
    {
        char ch = *exp;        

        if (is_empty(ch)){ //ignore empty
            //do nothing
            exp++;
        }else if (ch == '(' || ch == ')' 
                || ch == '*' || ch == '/' || ch == '%') {
            
            char data[2];
            data[0] = ch;
            data[1] = '\0';

            queue_enqueue(queue, data);

            prevChar = ch;
            exp++;
        }else if (ch == '+'){ //check + (number)

            //if - the first character or after +-*/% or after '(' then "unary operator"
            if (prevChar == '(' || prevChar == '+' ||
                prevChar == '-' ||
                prevChar == '*' ||
                prevChar == '/' || prevChar == '%' || prevChar == '\0') {

                //ignore +
            }
            else {
                char data[DATA_SIZE];
                data[0] = ch;
                data[1] = '\0';

                queue_enqueue(queue, data);

                prevChar = ch; // +
            }

            exp++;

        }else if (ch == '-'){ //check - (negative number)

            //if - the first character or after +-*/% or after '(' then "unary operator"
            if (prevChar == '(' || prevChar == '+' ||
                prevChar == '-' ||
                prevChar == '*' ||
                prevChar == '/' || prevChar == '%' || prevChar == '\0') {

                char data[DATA_SIZE];
                data[0] = 'x'; //mark as "unary operator"
                data[1] = '\0';

                queue_enqueue(queue, data);

                prevChar = ch; // -
            }
            else {
                char data[DATA_SIZE];
                data[0] = ch;
                data[1] = '\0';

                queue_enqueue(queue, data);

                prevChar = ch; // -
            }

            exp++;

        }else if (is_digit(ch)){ //is digit
            char data[DATA_SIZE];
            data[0] = ch;                
            int len = 1;

            //printf("ch = %c\n", ch);

            exp++;

            //wait for digit
            char digit = *exp;
            while (is_digit(digit)){
                data[len] = digit;
                len += 1;

                exp++;
                digit = *exp;
            }
            data[len] = '\0';

            queue_enqueue(queue, data);
            prevChar = '0'; //mark as digit

        }else{ //error
            queue_clear(queue);
            return false;
        }        
    }    

    return true;
}

/*get the precedence of the operator*/
int precedence(char token[]) {

    if (token[0] == 'x') { //"unary operator"
        return 3;
    }else if (token[0] == '+' || token[0] == '-') {
        return 1;
    }
    else if (token[0] == '*' || token[0] == '/' || token[0] == '%') {
        return 2;
    }
    else {
        return -1;
    }
}

/*convert infix to postfix such as 3 + 4 = 3 4 +*/
bool infixToPostfix(char* expression, struct Queue* postfix){

    //token the expression
    struct Queue input;
    queue_initialize(&input); //initialize the queue

    //create a stack
    struct Stack stack;
    stack_initialize(&stack); //initialize the stack

    //tokenize the expression
    if (tokenize(expression, &input) == true){

        char data[DATA_SIZE];//a token

        /*print for testing
        printf("The token is\n");
        while (queue_is_empty(&queue) == false){
            
            char data[DATA_SIZE];
            queue_dequeue(&queue, data);

            printf("%s\n", data);
        }
        */
        while (queue_is_empty(&input) == false){
            queue_dequeue(&input, data);

            //printf("data from input %s\n", data);

            //is number
            if (is_integer(data)){

                //printf("is number %s\n", data);

                queue_enqueue(postfix, data);
            }
            else if (data[0] == '(') //open parenthesis
            {
                stack_push(&stack, data);
            }else if (data[0] == ')') //close parenthesis
            {
                //while stack is not empty or != '('
                //pop and append to postfix
                while (!stack_is_empty(&stack)) {

                    stack_top(&stack, data);
                    if (data[0] == '('){
                        stack_pop(&stack, data); //remove '('
                        break;
                    }else{
                        queue_enqueue(postfix, data);
                        stack_pop(&stack, data);
                    }
                }
            }else if (is_operator(data)){ // + - * / % or x(for unary operator)
                //while stack is not empty and
                //precedence of data <= precedence of stack top element
                //pop and append to postfix
                while (!stack_is_empty(&stack)) {

                    char top_data[DATA_SIZE];//a token on top of stack
                    stack_top(&stack, top_data);

                    //printf("precedence(data) %d\n", precedence(data));
                    //printf("precedence(top_data) %d\n", precedence(top_data));

                    if (precedence(data) <= precedence(top_data)){
                        queue_enqueue(postfix, top_data);
                        stack_pop(&stack, top_data);
                    }else{
                        break;
                    }
                }

                //append current token
                stack_push(&stack, data);

                //printf("append current token %s\n", data);

            }else{ //error

                stack_clear(&stack);
                queue_clear(postfix);
                queue_clear(&input);

                printf("invalid expression\n");
                return false;
            }
        }

        //move from stack to postfix
        while (!stack_is_empty(&stack)) {
            
            stack_pop(&stack, data);
            queue_enqueue(postfix, data);

            //printf("from stack to postfix %s\n", data);
        }

        return true;
    }else{
        printf("invalid expression\n");
        return false;
    }
}

/*
calculate the expression
*/
bool calculate(char* expression, int* result){

    //token the expression
    struct Queue postfix;
    queue_initialize(&postfix); //initialize the postfix

    //convert infix to postfix
    if (infixToPostfix(expression, &postfix) == true){

        *result = 0;

        struct Stack numbers; //stack to store numbers
        stack_initialize(&numbers);

        char data[DATA_SIZE];//a token

        char operand1[DATA_SIZE];//first operand
        char operand2[DATA_SIZE];//second operand
        bool valid = true;
        bool divided_by_zero = false;

        while (!queue_is_empty(&postfix)) {

            queue_dequeue(&postfix, data);

            //printf("data = %s\n", data);

            //if it is integer, append to stack
            if (is_integer(data)){

                stack_push(&numbers, data);
                
            }else{ //+ - * / % or x

                if (stack_is_empty(&numbers)){
                    valid = false;
                    break;
                }

                stack_pop(&numbers, operand2);

                if (!is_integer(operand2))
                {
                    valid = false;
                    break;
                }

                if (data[0] == 'x') //unary operator
                {
                    int temp = my_atoi(operand2);

                    if (data[0] == 'x') {
                        temp = -1 * temp;
                    }
                    char tempData[DATA_SIZE];

                    my_itoa(tempData, temp);
                    stack_push(&numbers, tempData);
                }
                else {

                    if (stack_is_empty(&numbers)) {
                        valid = false;
                        break;
                    }

                    //the second one is not the number
                    stack_pop(&numbers, operand1);

                    if (!is_integer(operand1))
                    {
                        valid = false;
                        break;
                    }

                    int temp = 0;
                    char tempData[DATA_SIZE];

                    //convert to integers then execute
                    if (data[0] == '+') {
                        temp = add(my_atoi(operand1), my_atoi(operand2));
                    }
                    else if (data[0] == '-') {
                        temp = subtract(my_atoi(operand1), my_atoi(operand2));
                    }
                    else if (data[0] == '*') {
                        temp = multiply(my_atoi(operand1), my_atoi(operand2));
                    }
                    else if (data[0] == '/') {
                        if (my_atoi(operand2) == 0) {
                            valid = false;
                            divided_by_zero = true;
                            break;
                        }
                        temp = divide(my_atoi(operand1), my_atoi(operand2));
                    }
                    else if (data[0] == '%') {

                        if (my_atoi(operand2) == 0) {
                            valid = false;
                            divided_by_zero = true;
                            break;
                        }
                        temp = modulo(my_atoi(operand1), my_atoi(operand2));
                    }

                    my_itoa(tempData, temp);
                    stack_push(&numbers, tempData);
                }
            }
        }

        if (valid){

            if (stack_is_empty(&numbers)){
                valid = false;
            }else{

                stack_pop(&numbers, data); //result stores here

                //printf("data in numbers = %s\n", data);

                //stack should be empty
                if (!stack_is_empty(&numbers)){
                    valid = false;
                }
            }
        }

        //printf("====================\n");

        if (!valid){
            stack_clear(&numbers);
            queue_clear(&postfix);

            if (divided_by_zero){
                printf("dividend by zero\n");
            }else{
                printf("invalid expression\n");
            }
            return false;
        }else{
            *result = my_atoi(data);

            //printf("data in numbers = %s\n", data);
            //printf("*result = %d\n", *result);
        }

        return true;

    }else{
        return false;
    }

    return true;
}

//main function to start C application
int main(int argc, char **argv){

    //check command line
    if (handleCmd(argc, argv) == true){

        // expression such as -(-((-4)+-6))
        char* expression = argv[1];
        int result = 0;

        if (calculate(expression, &result) == true){
            printf("%d\n", result); 
        }
    }    

    return 0;
}
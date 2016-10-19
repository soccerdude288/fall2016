#include "stack.h"
#include <stdio.h>

int main(void){
    printf("Welcome to CS 3100!\n");
    printf("Creating a new stack.\n");
    stackT* A = NewStack();
    printf("Pushing 'M' onto the stack.\n");
    Push(A,'M');
    printf("Pushing 'O' onto the stack.\n");
    Push(A,'O');
    printf("Pushing 'P' onto the stack.\n");
    Push(A,'P');
    printf("Popping, the result should be a 'P': %c\n",Pop(A));
    printf("Popping, the result should be a 'O': %c\n",Pop(A));
    printf("Popping, the result should be a 'M': %c\n",Pop(A));
    printf("Popping, the result should be an empty space and I should have just gotten an error: %c\n",Pop(A));

    printf("Checking to see if the stack is empty now.\n");
    bool b = IsEmpty(A);
    if (b == true){
        printf("The stack is empty. Now I am going to call FreeStack on it.\n");
    }
    else{
        printf("Oh, dear. We have a problem. The stack should be empty now. I wonder, can I call FreeStack on it anyway?\n");
    }
    FreeStack(A);

    char arr1[] = {'R','A','C','E','C','A','R'};

    printf("Creating another stack.\n");
    stackT* B = NewStack();
    
    b = IsEmpty(B);
    if (b == true){
        printf("(PASS) The stack is empty. That is good.\n");
    }
    else{
        printf("(FAIL) The stack is not empty. That is not good.\n");
    }

    printf("Filling the stack up with information.\n");
    int i;
    for(i = 0; i < 7; i++){
        Push(B,arr1[i]);
    }
    b = IsEmpty(B);
    if (b == true){
        printf("(FAIL) The stack is empty. That is not good.\n");
    }
    else{
        printf("(PASS) The stack is not empty. That is good.\n");
    }

    printf("Can we free a non-empty stack? Let's try. We should get an error.\n");
    FreeStack(B);

    printf("Hopefully that caused a problem. Let's empty the stack then try to free it.\n");
    EmptyStack(B);
    printf("What happens when we Pop from an empty stack? We should get an error:\n");
    valueT temp = Pop(B);
    FreeStack(B);

    printf("Creating a third stack.\n");
    stackT* C = NewStack();

    char arr2[] = {'G','o','o','d'};
    printf("Filling the stack up with information.\n");
    for(i = 0; i < 4; i++){
        Push(C,arr2[i]);
    }
    printf("Now let's empty it and print out the result: (It should be \"dooG\"):");
    for(i = 0; i < 4; i++){
        valueT val = Pop(C);
        printf("%c",val);
    }
    printf("\nNow, let's free the stack and be finished.\n");
    FreeStack(C);
}

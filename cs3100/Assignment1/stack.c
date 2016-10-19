//
// Created by Taylor Earl on 8/31/16.
//
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#define NULL 0

stackT *NewStack(void){
    //stackT* myStack = {NULL};
    stackT* myStack = malloc (sizeof(nodeT));
    myStack->head = NULL;
    return myStack;
};

void Push(stackT *stack, valueT value){
    //create new node
    //struct _nodeT newNode{null, null};
    //struct nodeT* newNode = (struct nodeT*)malloc (sizeof(nodeT));

    //nodeT* newNode = {NULL};

    nodeT* newNode = (nodeT*)malloc (sizeof(nodeT));

    //set the next field to the head
    if(stack->head == NULL){
        newNode->next = NULL;
    }
    else {
        newNode->next = stack->head;
    }
    //set the value to the new node
    newNode->value = value;

    //set the head of the stack to point to the new node
    stack->head = newNode;
};

valueT Pop(stackT *stack){
    if(stack->head == NULL){
        printf("ERROR: Can't pop an empty stack.\n");
        return 0;
    }
    else{
        struct _nodeT* tempNode = stack->head;
        stack->head = stack->head->next;
        valueT returnValue = tempNode->value;
        free(tempNode);
        return returnValue;
    }

};

void EmptyStack(stackT *stack){
    while(stack->head != NULL){
        struct _nodeT *tempNode = stack->head;
        stack->head = stack->head->next;
        free(tempNode);
    }
    stack->head = NULL;
};
void FreeStack(stackT *stack){
    if(stack->head == NULL){
        free(stack);
    }
    else{
        printf("ERROR: Can only delete empty stacks.");
    }
};
bool IsEmpty(stackT *stack){
    if(stack->head == NULL){
        return true;
    }
    else{
        return false;
    }
};


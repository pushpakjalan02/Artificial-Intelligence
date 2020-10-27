/* Including Built-In Headers */
#include<stdio.h>

/* Defining Data Type of Stack Elements */
struct stackNode{
    int value;
    struct stackNode* pointer;
};

/* Method for Pushing Elements on the Stack */
void push(struct stackNode** top, int value){
    
    /* Declaring Variables */
    struct stackNode* nodeToPush;

    /* Allocating Memory for the New Element on the Stack*/
    nodeToPush = (struct stackNode*)malloc(sizeof(struct stackNode));
    
    /* Assigning the New Element's Value and Pointer */
    nodeToPush -> value = value;
    nodeToPush -> pointer = *top;

    /* Making Top to Point to the New Top Element on the Stack */
    *top = nodeToPush;

    /* Done Pushing. Returning */
    return;
}

/* Method for Poping Elements from the Stack */
int pop(struct stackNode** top){
    
    /* If Stack is Empty, then Return */
    if(*top == NULL){
        return -1;
    }

    /* Declaring Variables */
    struct stackNode* nodeToPop;
    int value;

    /* Getting the Top Node for Popping from the Stack */
    nodeToPop = *top;

    /* Getting the Value of the Node to be Popped */
    value = nodeToPop -> value;

    /* Making the Element Next to Top as Current Top */
    *top = nodeToPop -> pointer;
    
    /* Freeing Memory Occupied by the Popped Node */
    free(nodeToPop);

    /* Done Popping. Returning Popped Node's Value */
    return value;
}

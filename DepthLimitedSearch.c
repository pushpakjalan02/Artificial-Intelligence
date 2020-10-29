/* Including Build-In Headers */
#include<stdio.h>

/* Performs Depth First Search on an Input Graph for Given Start State and Goal State */
void depthLimitedSearch(struct graphInfo inputGraph, int startState, int goalState){
    
    /* Variable Declarations */
    struct stackNode* top = NULL;
    int depthLimit;
    int* currentPath;
    int currentPathLength, currentNode;
    int i, j;
    int flag = 0;

    /* Getting depth limit from user as input */
    printf("Enter Depth Limit: ");
    scanf("%d", &depthLimit);

    printf("\n");

    /* Allocating Memory for Storing the Current Path Being Seen and also Initializing the Length of that Path */
    currentPath = (int*)malloc(inputGraph.noOfNodes * sizeof(int));
    currentPathLength = 0;

    /* Push Start State to the Top of the Stack */
    push(&top, startState);

    /* Loop to find the Goal Node until either we find the Goal Node or we finish searching the whole Graph */
    do{

        /* Popping out topmost node from the stack */
        currentNode = pop(&top);

        /* Backtracking and hence, removing the latest node entered to the current path as no route exists from
        this node to the Goal Node */
        if(currentNode == -2){
            currentPathLength--;
            continue;
        }

        /* Appending the current node to the current path */
        currentPath[currentPathLength] = currentNode;
        currentPathLength++;

        /* Checking if we have reached the Goal State. If so, we are done finding a path and hence, we break */
        if(currentNode == goalState){
            flag = 1;
            break;
        }

        /* Pushing a control value to identify shifting of search from one level to another */
        push(&top, -2);

        /* If depth of current node is less than depth limit, then push the successor nodes of the current node 
        onto the stack */
        if(currentPathLength - 1 < depthLimit){
        
            /* Computing all successors of the current node and pushing them onto the stack */
            for(i = 0; i < inputGraph.noOfNodes; i++){
                if(inputGraph.graph[currentNode][i] != -1 && notInCurrentPath(currentPath, currentPathLength, i)){
                    push(&top, i);
                }
            }
        
        }

    } while(top != NULL);

    /* If path found, print the path. Else, display that no path is available */
    if(flag == 1){
        printf("Path is: ");
        for(i = 0; i < currentPathLength - 1; i++){
            printf("%s -> ", inputGraph.nodeMap[currentPath[i]]);
        }
        printf("%s\n\n", inputGraph.nodeMap[currentPath[i]]);
    }
    else{
        printf("No Path Found");
    }
}

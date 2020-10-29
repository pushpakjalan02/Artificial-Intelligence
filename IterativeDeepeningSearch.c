/* Including Build-In Headers */
#include<stdio.h>

/* Performs Iterative Deepening Search on an Input Graph for Given Start State and Goal State */
void iterativeDeepeningSearch(struct graphInfo inputGraph, int startState, int goalState){
    
    /* Variable Declarations */
    int depthLimit = 0;

    /* Loop to find the Goal Node in the graph by gradually increasing depth limits and performing depth limited 
    search until the goal at the shallowest depth is found */
    while(1){

        /* Variable Declarations */
        struct stackNode* top = NULL;
        int* currentPath;
        int currentPathLength, currentNode;
        int i, j;
        int flag = 0;

        /* Allocating Memory for Storing the Current Path Being Seen and also Initializing the Length of that Path */
        currentPath = (int*)malloc(inputGraph.noOfNodes * sizeof(int));
        currentPathLength = 0;

        /* Push Start State to the Top of the Stack */
        push(&top, startState);

        /* Loop to perform depth limited search and find the goal node in the depth limited sub-graph */
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

        /* If path found, print the path */
        if(flag == 1){
            printf("Path is: ");
            for(i = 0; i < currentPathLength - 1; i++){
                printf("%s -> ", inputGraph.nodeMap[currentPath[i]]);
            }
            printf("%s\n\n", inputGraph.nodeMap[currentPath[i]]);
            break;
        }

        /* Increasing depth limit if goal node not found in current sub-graph */
        depthLimit++;
    }
}

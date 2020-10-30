/* Including Build-In Headers */
#include<stdio.h>

/* Performs Depth First Search on an Input Graph for Given Start State and Goal State */
struct algoSummary* depthFirstSearch(struct graphInfo inputGraph, int startState, int goalState){
    
    /* Variable Declarations */
    struct stackNode* top = NULL;
    int* currentPath;
    int currentPathLength, currentNode;
    int i, j;
    int flag = 0;
    struct algoSummary* summary;
    
    /* Allocating memory to store DFS's summary */
    summary = (struct algoSummary*)malloc(sizeof(struct algoSummary));

    /* Allocating Memory for Storing the Current Path Being Seen and also Initializing the Length of that Path */
    currentPath = (int*)malloc(inputGraph.noOfNodes * sizeof(int));
    currentPathLength = 0;

    /* Push Start State to the Top of the Stack */
    push(&top, startState);
    summary -> visitedNodeCount = 1;

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

        /* Computing all successors of the current node and pushing them onto the stack */
        for(i = 0; i < inputGraph.noOfNodes; i++){
            if(inputGraph.graph[currentNode][i] != -1 && notInCurrentPath(currentPath, currentPathLength, i)){
                push(&top, i);
                summary -> visitedNodeCount += 1;
            }
        }

    } while(top != NULL);

    /* If path found, print the path. Else, display that no path is available. Also, return DFS's summary accordingly */
    if(flag == 1){

        summary -> totalCost = 0;

        printf("Path is: ");
        for(i = 0; i < currentPathLength - 1; i++){
            printf("%s -> ", inputGraph.nodeMap[currentPath[i]]);
            summary -> totalCost += inputGraph.graph[currentPath[i]][currentPath[i+1]];
        }
        printf("%s\n\n", inputGraph.nodeMap[currentPath[i]]);

        summary -> goalDepth = currentPathLength - 1;

        return summary;
    }
    else{
        printf("No Path Found\n\n");
        summary -> totalCost = -1;
        summary -> goalDepth = -1;
        return summary;
    }
}

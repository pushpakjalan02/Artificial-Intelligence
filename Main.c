/* Including Standard Headers */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/* Trimming a string */
void stringTrim(char* string){
    
    /* Variable Declarations */
    int i, j, k;

    /* Code */
    for(i = 0; i < strlen(string); i++){
        if(!isspace(string[i])){
            break;
        }
    }
    for(j = strlen(string) - 1; j >= 0; j--){
        if(!isspace(string[j])){
            break;
        }
    }
    for(k = 0; k < j - i + 1; k++){
        string[k] = string[i + k];
    }
    string[k] = '\0';

    return;
}

/* Comparing two strings ignoring case */
int strcmpInsensitive(char* str1, char* str2){

    /* Variable Declarations */
    int minLength = strlen(str1) > strlen(str2) ? strlen(str2) : strlen(str1);
    int i;
    
    for(i = 0; i < minLength; i++){
        if(toupper(str1[i]) > toupper(str2[i])){
            return 1;
        }
        else if(toupper(str1[i]) < toupper(str2[i])){
            return -1;
        }
    }
    if(strlen(str1) == strlen(str2)){
        return 0;
    }
    else if(strlen(str1) > strlen(str2)){
        return 1;
    }
    else{
        return -1;
    } 
}

/* Defining Structure for Storing All Graph - Related Information */
struct graphInfo{
    int noOfNodes;
    int noOfEdges;
    char** nodeMap;
    int** graph;
};

/* Getting a Graph Node's Index from nodeMap Array of graphInfo */
int getIndexFromMap(char** nodeMap, int noOfNodes, char* node){

    int i;
    for(i = 0; i < noOfNodes; i++){
        if(!strcmpInsensitive(nodeMap[i], node)){
            return i;
        }
    }
    return -1;

}

/* Including Project Specific Headers */
#include"MergeSort.c"
#include"Common.c"
#include"DepthFirstSearch.c"
#include"DepthLimitedSearch.c"
#include"IterativeDeepeningSearch.c"

/* Fetching the Input Graph from an Input File */
struct graphInfo getInput(char* filename){
    
    /* Declaring Variables */
    char buffer[1000];
    struct graphInfo inputGraph;
    int i, j;


    /* Opening Input File */
    FILE* fp = fopen(filename, "r");


    /* Reading No. of Nodes and Edges */
    fgets(buffer, 1000, fp);
    sscanf(buffer, "%d", &inputGraph.noOfNodes);

    fgets(buffer, 1000, fp);
    sscanf(buffer, "%d", &inputGraph.noOfEdges);
    
    printf("\n");

    printf("Fetched No. of Nodes: %2d\n", inputGraph.noOfNodes);
    printf("Fetched No. of Edges: %2d\n", inputGraph.noOfEdges);


    /* Initializing Data Structures */
    inputGraph.nodeMap = (char**)malloc(inputGraph.noOfNodes * sizeof(char*));
    inputGraph.graph = (int**)malloc(inputGraph.noOfNodes * sizeof(int*));
    
    i = 0;
    while(i < inputGraph.noOfNodes){
        
        inputGraph.graph[i] = (int*)malloc(inputGraph.noOfNodes * sizeof(int));
        
        j = 0;
        while (j < inputGraph.noOfNodes)
        {
            inputGraph.graph[i][j] = -1;
            j++;
        }
        
        i++;
    }

    printf("\n");


    /* Fetching Nodes from Input File */
    printf("------ Started Fetching Nodes ------\n\n");

    printf("%17s%s\n", "", "City");

    i = 0;
    while(i < inputGraph.noOfNodes){
        
        char nodeName[1000];

        fgets(buffer, 1000, fp);
        sscanf(buffer, "%[^\n]", nodeName);

        inputGraph.nodeMap[i] = (char*)malloc((strlen(nodeName) + 1) * sizeof(char));
        strcpy(inputGraph.nodeMap[i], nodeName);

        printf("Fetched Node %2d: %-16s\n", i+1, inputGraph.nodeMap[i]);
        i++;
    }

    printf("\n");
    
    printf("------ All Nodes Fetched ------\n\n");

    /* Sort the nodes in nodeMap of inputGraph in alphabetically decreasing order. This helps us to expand nodes
    in alphabetically increasing order in the algorithms run in this program */
    mergeSort(inputGraph.nodeMap, 0, inputGraph.noOfNodes - 1);

    /* Fetching Edges from Input File */
    printf("------ Started Fetching Edges ------\n\n");

    printf("%17s%-16s\t%-16s\t%s\n", "", "City 1", "City 2", "Distance");

    i = 0;
    while(i < inputGraph.noOfEdges){
        
        char firstNode[1000];
        char secondNode[1000];
        int weight;

        int firstNodeIndex;
        int secondNodeIndex;

        fgets(buffer, 1000, fp);
        
        sscanf(&(buffer[0]), "%[^\t]", firstNode);
        sscanf(&(buffer[strlen(firstNode) + 1]), "%[^\t]", secondNode);
        sscanf(&(buffer[strlen(firstNode) + 1 + strlen(secondNode) + 1]), "%d", &weight);

        firstNodeIndex = getIndexFromMap(inputGraph.nodeMap, inputGraph.noOfNodes, firstNode);
        secondNodeIndex = getIndexFromMap(inputGraph.nodeMap, inputGraph.noOfNodes, secondNode);

        inputGraph.graph[firstNodeIndex][secondNodeIndex] = weight;
        inputGraph.graph[secondNodeIndex][firstNodeIndex] = weight;        

        printf("Fetched Edge %2d: %-16s\t%-16s\t%8d\n",
                i+1,
                inputGraph.nodeMap[firstNodeIndex],
                inputGraph.nodeMap[secondNodeIndex],
                inputGraph.graph[secondNodeIndex][firstNodeIndex]
            );
        
        i++;
    }

    printf("\n");

    printf("------ All Edges Fetched ------\n\n");

    /* Done Fetching from Input File. Returning Graph Info.*/
    return inputGraph;

}

/* Main Method. Runs the various algorithms on the input graph. */
int main(int argc, char* argv[]){
        
    /* If Program is not Run Correctly, Prompt to Run Program in Correct Format and Exit.*/
    if(argc != 2){
        printf("Please run the program in the format: <program_name> <input_file_name>");
        return 0;
    }

    /* Declaring Variables */
    struct graphInfo inputGraph;
    char startState[1000], goalState[1000];
    int startStateIndex, goalStateIndex;

    /* Fetching All Input */
    inputGraph = getInput(argv[1]);

    /* Take Start and Goal States as Input */
    printf("------ Give Input ------\n\n");
    while(1){
        
        printf("Enter Start State: ");
        scanf("%[^\n]%*c", startState);
        
        /* Trim Start State String */
        stringTrim(startState);  

        /* Map Start state to its respective index */
        startStateIndex = getIndexFromMap(inputGraph.nodeMap, inputGraph.noOfNodes, startState);

        if(startStateIndex >= 0){
            break;
        }

        printf("Invalid Start State. Re-enter\n\n");

    }

    printf("\n");
    
    while(1){
        
        printf("Enter Goal State: ");
        scanf("%[^\n]%*c", goalState);
        
        /* Trim Goal State String */
        stringTrim(goalState);

        /* Map Goal states to its respective index */
        goalStateIndex = getIndexFromMap(inputGraph.nodeMap, inputGraph.noOfNodes, goalState);
        
        if(goalStateIndex >= 0){
            break;
        }

        printf("Invalid Goal State. Re-enter\n\n");
        
    }
    printf("\n------ Input Recieved -----\n\n");

    printf("\n");

    /* Find Path and Statistics using Depth First Search */
    printf("------ Starting Depth First Search ------\n\n");
    depthFirstSearch(inputGraph, startStateIndex, goalStateIndex);
    printf("------ Depth First Search Ended ------\n\n");
    
    printf("\n");

    /* Find Path and Statistics using Depth Limited Search */
    printf("------ Starting Depth Limited Search ------\n\n");
    depthLimitedSearch(inputGraph, startStateIndex, goalStateIndex);
    printf("------ Depth Limited Search Ended ------\n\n");

    printf("\n");

    /* Find Path and Statistics using Iterative Deepening Depth First Search */
    printf("------ Starting Iterative Deepening Depth First Search ------\n\n");
    iterativeDeepeningSearch(inputGraph, startStateIndex, goalStateIndex);
    printf("------ Iterative Deepening Depth First Search Ended ------\n\n");

    /* Done All Processing. Exiting. */
    return 0;

}

/* Including Standard Headers */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Including Project Specific Headers */
#include"DepthFirstSearch.c"
#include"DepthLimitedSearch.c"
#include"IterativeDeepeningSearch.c"

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
        if(!strcmp(nodeMap[i], node)){
            return i;
        }
    }
    return -1;

}

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

int main(int argc, char* argv[]){
    
    /* If Program is not Run Correctly, Prompt to Run Program in Correct Format and Exit.*/
    if(argc != 2){
        printf("Please run the program in the format: <program_name> <input_file_name>");
        return 0;
    }

    /* Declaring Variables */
    struct graphInfo inputGraph;

    /* Fetching All Input */
    inputGraph = getInput(argv[1]);

    /* Done All Processing. Exiting. */
    return 0;

}
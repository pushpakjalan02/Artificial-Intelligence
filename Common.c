#include"Stack.c"

/* Checking if a given successor node forms a cycle with the current path being seen */
int notInCurrentPath(int* currentPath, int currentPathLength, int node){
    int i;
    for(i = 0; i < currentPathLength; i++){
        if(currentPath[i] == node){
            return 0;
        }
    }
    return 1;
}
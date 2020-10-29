/* Pre-defined Header Declarations */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* Merge Function */
void merge(char** array, int left, int mid, int right){
    
    /* Variable Declarations */
    int i, j, k;
    int leftArrayLength = mid - left + 1;
    int rightArrayLength = right - mid;
    char** leftArray = (char**)malloc(leftArrayLength * sizeof(char*));
    char** rightArray = (char**)malloc(rightArrayLength * sizeof(char*));

    /* Copy from original array to the temporary arrays leftArray and rightArray */
    for(i = 0; i < leftArrayLength; i++){
        leftArray[i] = array[left + i];
    }
    for(i = 0; i < rightArrayLength; i++){
        rightArray[i] = array[mid + i + 1];
    }

    /* Merge the temporary arrays leftArray and rightArray to original array[left...right] in a sorted way */
    i = 0;
    j = 0;
    k = left;
    while(i < leftArrayLength && j < rightArrayLength){
        if(strcmpInsensitive(leftArray[i], rightArray[j]) >= 0){
            array[k] = leftArray[i];
            i++;
        }
        else{
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }
    while(i < leftArrayLength){
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while(j < rightArrayLength){
        array[k] = rightArray[j];
        j++;
        k++;
    }

    /* Free the temporary arrays leftArray and rightArray */
    free(leftArray);
    free(rightArray);
}

/* Merge Sort Function */
void mergeSort(char** array, int left, int right){
    
    /* (left == right) then only 1 element in array (then, array is already sorted -- base case) or (left > right)
    which is impossible. Therfore, sort only when left < right */
    if(left < right){

        /* Calculate middle index and then use it in a divide and conquer approach */
        int mid = left + (right - left) / 2;
        mergeSort(array, left, mid);
        mergeSort(array, mid+1, right);
        merge(array, left, mid, right);

    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pop(int *arr, int i){
    arr[i] = 0;
}

void printStack(int *arr, int size){
    for (int i = 0; i < size;i++){
        printf("%d, ",arr[i]);
    }
    printf("\n");
}


int main(int argc, char** argv){
    int stackSize = (argc-1) * sizeof(int);
    int *stack = (int*) malloc(stackSize);
    for (int i = 0;i<argc-2;i++){
        stack[i] = -99999;
    }

    if (stack == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    long int curVal;
    char *endptr;
    int stackInd = -1;
    for (int i = 1; i < argc;i++){
        curVal = strtol(argv[i],&endptr,10);
        //checks if strtol was able to convert to long using endptr
        if (*endptr == '\0') {
            stackInd++;
            curVal = strtol(argv[i],&endptr,10);
            stack[stackInd] = curVal;
            // printf("Added %d\n",stack[stackInd]);
        //Checks for "add" and "ADD"
        } else if (strcmp(argv[i],"add")==0 || strcmp(argv[i],"ADD") == 0){
            if (stack[stackInd] != -99999 && stack[stackInd-1] != -99999){
                int sum = stack[stackInd]+stack[stackInd-1];
                pop(stack,stackInd);
                pop(stack,stackInd);
                stack[stackInd-1] = sum;
                stackInd--;
                // used for testing functionality:
                // printf("\n%d\n",sum);
                // printf("stackInd: %d\n",stackInd);
                // printStack(stack,argc-2);
            } else{
                printf("Not enough values to complete operation.");
                return 1;
            } 
        //checks for "sub" and "SUB"
        } else if (strcmp(argv[i],"sub")==0 || strcmp(argv[i],"SUB") == 0){
                if (stack[stackInd] != -99999 && stack[stackInd-1] != -99999){
                int res = stack[stackInd-1]-stack[stackInd];
                pop(stack,stackInd);
                pop(stack,stackInd);
                stack[stackInd-1] = res;
                stackInd--;
                // used for testing functionality:
                // printf("\n%d\n",res);
                // printf("stackInd: %d\n",stackInd);
                // printStack(stack,argc-2);
            } else{
                printf("Not enough values to complete operation.");
                return 1;
            } 
        //checks for "mult" and "MULT"
        } else if (strcmp(argv[i],"mult")==0 || strcmp(argv[i],"MULT") == 0){
            if (stack[stackInd] != -99999 && stack[stackInd-1] != -99999){
                int prod = stack[stackInd]*stack[stackInd-1];
                pop(stack,stackInd);
                pop(stack,stackInd);
                stack[stackInd-1] = prod;
                stackInd--;
                // used for testing functionality:
                // printf("\n%d\n",prod);
                // printf("stackInd: %d\n",stackInd);
                // printStack(stack,argc-2);
            } else{
                printf("Not enough values to complete operation.");
                return 1;
            } 
        } else if (strcmp(argv[i],"div")==0 || strcmp(argv[i],"DIV") == 0){
            if (stack[stackInd] != -99999 && stack[stackInd-1] != -99999){
                int ans = stack[stackInd-1]/stack[stackInd];
                pop(stack,stackInd);
                pop(stack,stackInd);
                stack[stackInd-1] = ans;
                stackInd--;
                // used for testing functionality:
                // printf("\n%d\n",ans);
                // printf("stackInd: %d\n",stackInd);
                // printStack(stack,argc-2);
            } else{
                printf("Not enough values to complete operation.");
                return 1;
            } 
        }
    }
    
    printf("%d\n",stack[stackInd]);
    free(stack);
}
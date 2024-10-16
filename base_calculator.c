/*This adapted Reverse Polish Notation Calculator takes in command line arguments in the format
of 0b######## for binary values, 0x######## for Hexadecimal values, and ######## for base 10
integers. From there, it parses the inputs, converts them to decimal, and adds them to a
simulated stack architecture. It takes operations in the form of "add", "sub", "mult", and "div".
Using these operations, it follows the workflow of an RPN, starting from the top of the stack
until there are no values besides the top, which it then prints out.
*/

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

int power(int num, int pow){
    int res = 1;
    for (int i = 0; i<pow;i++){
        res *= num;
    }
    return res;
}

unsigned int h2d(char *in){
    int curVal = 0;
    unsigned int res = 0;
    int len = 0; while (in[len] != '\0') len++;
    in += 2;
    while (*in) {
        if (*in >= '0' && *in <= '9') {
            curVal = *in - '0';
        } else if (*in >= 'a' && *in <= 'f') {
            curVal = *in - 'a' + 10;
        }
        res = res * 16 + curVal;
        in++;
    }
    
    return res;
}


unsigned int s210(char *in){
    unsigned int res = 0;
    int count = 0;
    int len = 0; while (in[len] != '\0') len++;
    for (int i = len-1;i >= 0; i--){
        res += (in[i]-'0')*power(10,count);
        count++;
    }
    return res;
}

unsigned int b2d(char *in){
    unsigned int res = 0;

    int len = 0; while(in[len] != '\0') len++;
    for (int i = 2; i < len;i++){
        res = res * 2 + (in[i]-'0');
    }
    return res;
}

unsigned int parse(char *in){

    if (in[0] == '0' && in[1] == 'b'){
        return (b2d(in));
    } else if(in[0] == '0' && in[1] == 'x'){
        return h2d(in);
    } else {
        return s210(in);
    }
    }



int main(int argc, char** argv){
    int stackSize = (argc-1) * sizeof(int);
    int *stack = (int*) malloc(stackSize);
    int INT_MIN = -2147483648;
    for (int i = 0;i<argc-1;i++){
        stack[i] = INT_MIN;
    }

    if (stack == NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    long int curVal;
    int stackInd = -1;
    for (int i = 1; i < argc;i++){
            if (strcmp(argv[i],"add")&&strcmp(argv[i],"sub")&&strcmp(argv[i],"mult")&&strcmp(argv[i],"div")){
                stackInd++;
                curVal = parse(argv[i]);
                stack[stackInd] = curVal;
            }
            
            // printf("Added %d at position: %d\n",stack[stackInd],stackInd);
        //Checks for "add" and "ADD"
        if (strcmp(argv[i],"add")==0 || strcmp(argv[i],"ADD") == 0){
            if (stack[stackInd] != INT_MIN && stack[stackInd-1] != INT_MIN){
                int sum = stack[stackInd]+stack[stackInd-1];
                pop(stack,stackInd);
                pop(stack,stackInd);
                stack[stackInd-1] = sum;
                stackInd--;
                // used for testing functionality:
                // printf("\n%d\n",sum);
                // printf("stackInd: %d\n",stackInd);
                // printStack(stack,argc-1);
            } else{
                printf("Not enough values to complete operation.");
                return 1;
            } 
        //checks for "sub" and "SUB"
        } else if (strcmp(argv[i],"sub")==0 || strcmp(argv[i],"SUB") == 0){
                if (stack[stackInd] != INT_MIN && stack[stackInd-1] != INT_MIN){
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
            if (stack[stackInd] != INT_MIN && stack[stackInd-1] != INT_MIN){
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
            if (stack[stackInd] != INT_MIN && stack[stackInd-1] != INT_MIN){
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
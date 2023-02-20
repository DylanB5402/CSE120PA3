
#define MAXPROCS 10

static int stack[MAXPROCS];
static int stackLen = 0;

void initStack() {
    int i;
    for (i = 0; i < MAXPROCS; i++) {
        stack[i] = -1;
    }
}

int stackPush(int element) {
    if (stackLen >= MAXPROCS) {
        return 0;
    } else {
        stack[stackLen] = element;
        stackLen += 1;
        return 1;
    }
}

int stackPeek() {
    return stack[stackLen - 1];
}

int stackPop() {
    int lastElement = stackPeek();
    if (lastElement == -1 || stackLen == 0) {
        return -1;
    } 
    stack[stackLen - 1] = -1;
    stackLen -= 1;
    return lastElement;
}

int stackRemoveByValue(int val) {
    int i;
    int valIndex = -1;
    for (i = 0; i < MAXPROCS; i++) {
        if (stack[i] == val) {
            valIndex = i; 
        }
    }

    if (valIndex == -1) {
        return 0;
    }

    for (i = valIndex; i < MAXPROCS; i++) {
        if (i >= (stackLen - 1)) {
            stack[i] = -1;
        } else {
            stack[i] = stack[i + 1];
        }
    }
    stackLen -= 1;
    return 1;
}

void printStack() {
    int i;
    Printf("Head [");
    for (i = 0; i < MAXPROCS; i++) {
        
        if (i == stackLen - 1) {
            Printf("%d] ", stack[i]);
        } else {
            Printf("%d ", stack[i]);
        }
    }
    Printf("Tail, Size: %d \n", stackLen);
}
void Main () {
    initStack();
    printStack();
    stackPush(0);
    Printf("%d\n", stackPeek());
    stackPush(1);
    stackPush(2);
    stackPush(3);
    stackPush(4);
    stackPush(5);
    stackPush(6);
    stackPush(7);
    stackPush(8);
    stackPush(9);
    printStack();
    Printf("stack size %d\n", stackLen);
    Printf("len: %d\n", stackLen);
    int i;
    stackRemoveByValue(4);
    stackRemoveByValue(9);
    printStack();
    for (i = 0; i < 10; i++) {
        // Printf("%d\n", stackPop());
        stackPop();
    }
    printStack();
    stackPush(100);
    stackPush(457);
    printStack();
    stackRemoveByValue(457);
    printStack();
    Printf("stack size %d\n", stackLen);
    Printf("%d\n", stackPeek());
    Printf("%d\n", stackPop());
    Printf("%d\n", stackPeek());
    Printf("%d\n", stackPop());
    printStack();

    Printf("-----\n");
    stackPush(999);
    printStack();
    stackPush(687);
    printStack();
    stackPush(4414);
    printStack();
    stackPush(971);
    printStack();
    stackPush(1339);
    printStack();
    Printf("%d\n", stackPeek());
    printStack();
    Printf("%d\n", stackPop());
    printStack();
    Printf("%d\n", stackPop());
    printStack();
    Printf("%d\n", stackPop());
    printStack();
    stackRemoveByValue(687);
    printStack();
    Printf("%d\n", stackPop());
    printStack();
    Printf("%d\n", stackPop());
    printStack();
}

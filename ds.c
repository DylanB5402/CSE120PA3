#include <stdio.h>

#define MAXPROCS 10

static int queue[MAXPROCS];
static int queueLen = 0;

void initQueue() {
    int i;
    for (i = 0; i < MAXPROCS; i++) {
        queue[i] = -1;
    }
}

int queuePush(int element) {
    if (queueLen >= MAXPROCS) {
        return 0;
    } else {
        queue[queueLen] = element;
        queueLen += 1;
        return 1;
    }
}

int queuePeek() {
    return queue[0];
}

int queuePop() {
    int firstElement = queuePeek();
    int i;
    for (i = 0; i < queueLen; i++) {
        queue[i] = queue[i+1];
    }
    queue[queueLen - 1] = -1;
    queueLen -= 1;
    return firstElement;
}

int queueRemoveByValue(int val) {
    int i;
    int valIndex = -1;
    for (i = 0; i < MAXPROCS; i++) {
        if (queue[i] == val) {
            valIndex = i; 
        }
    }
    // printf("valIndex: %d\n", valIndex);

    if (valIndex == -1) {
        return 0;
    }

    for (i = valIndex; i < MAXPROCS; i++) {
        if (i >= (queueLen - 1)) {
            queue[i] = -1;
        } else {
            queue[i] = queue[i + 1];
        }
    }
    queueLen -= 1;
    return 1;
}


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
    printf("Stack: Head [");
    for (i = 0; i < MAXPROCS; i++) {
        
        if (i == stackLen - 1) {
            printf("%d] ", stack[i]);
        } else {
            printf("%d ", stack[i]);
        }
    }
    printf("Tail, Size: %d \n", stackLen);
}

void printMyQueue() {
    int i;
    printf("Queue: Head [");
    for (i = 0; i < MAXPROCS; i++) {
        
        if (i == queueLen - 1) {
            printf("%d] ", queue[i]);
        } else {
            printf("%d ", queue[i]);
        }
    }
    printf("Tail, Size: %d \n", queueLen);
}

void testStackQueue() {
    
    initStack();
    initQueue();
    printStack();
    printMyQueue();
    printf("Push 0 - 9\n");

    for (int i = 0; i < 10; i++) {
        stackPush(i);
        queuePush(i);
    }

    printStack();
    printMyQueue();

    stackPush(10);
    queuePush(10);

    printf("push 10\n");

    printStack();
    printMyQueue();

    printf("pop all \n");
    for (int i = 0; i < 10; i++) {
        stackPop();
        queuePop();
    }

    printStack();
    printMyQueue();

    for (int i = 0; i < 10; i++) {
        stackPush(i);
        queuePush(i);
    }
    
    printf("push again\n");

    printStack();
    printMyQueue();

    printf("remove 6\n");

    stackRemoveByValue(6);
    queueRemoveByValue(6);

    printStack();
    printMyQueue();

    printf("remove 4\n");

    stackRemoveByValue(4);
    queueRemoveByValue(4);

    printStack();
    printMyQueue();

    printf("remove 11 (not possible) \n");
    stackRemoveByValue(11);
    queueRemoveByValue(11);

    printStack();
    printMyQueue();

    printf("pop twice\n");

    stackPop();
    queuePop();

    stackPop();
    queuePop();

    printStack();
    printMyQueue();

    printf("remove 5\n");

    stackRemoveByValue(5);
    queueRemoveByValue(5);

    printStack();
    printMyQueue();
}

static int circQueue[MAXPROCS];
int circQueueLen = 0;
int circQueuePos = 0;

void initCircQueue() {
    int i;
    for (i = 0; i < MAXPROCS; i++) {
        circQueue[i] = -1;
    }
}

int circQueuePush(int element) {
    if (circQueueLen >= MAXPROCS) {
        return 0;
    } else {
        circQueue[circQueueLen] = element;
        circQueueLen += 1;
        return 1;
    }
}

int circQueuePeek() {
    return circQueue[circQueuePos];
}

int circQueueNext() {
    int current = circQueuePeek();
    if (circQueuePos == (circQueueLen - 1)) {
        circQueuePos = 0;
    } else {
        circQueuePos++;
    }
    return current;
}

int circQueueRemoveByValue(int val) {
    int i;
    int valIndex = -1;
    for (i = 0; i < MAXPROCS; i++) {
        if (circQueue[i] == val) {
            valIndex = i; 
        }
    }
    // printf("valIndex: %d\n", valIndex);

    if (valIndex == -1) {
        return 0;
    }

    // printf("pos: %d, len: %d\n", circQueuePos, circQueueLen);
    if (circQueuePos == (circQueueLen-1)) {
        circQueuePos = 0;
        
    }

    for (i = valIndex; i < MAXPROCS; i++) {
        if (i >= (circQueueLen - 1)) {
            circQueue[i] = -1;
        } else {
            circQueue[i] = circQueue[i + 1];
        }
    }
    circQueueLen -= 1;
    return 1;
}

void printCircQueue() {
    int i;
    printf("Circular Queue: Head [");
    for (i = 0; i < MAXPROCS; i++) {
        if (i == circQueuePos) {
            printf("(%d) ", circQueue[i]);    
        } else if (i == circQueueLen - 1) {
            printf("%d] ", circQueue[i]);
        } else {
            printf("%d ", circQueue[i]);
        }
    }
    printf("Tail, Size: %d \n", circQueueLen);
}


void testCQueue() {
    initCircQueue();
    printCircQueue();
    for (int i = 0; i < 5; i++) {
        circQueuePush(i);
    }
    printCircQueue();
    for (int i = 0; i < 5; i++) {
        circQueueNext();
        printCircQueue();
    }
    printf("removing 0\n");
    circQueueRemoveByValue(0);
    printCircQueue();
    circQueuePush(5);
    printCircQueue();
    circQueueNext();
    circQueueNext();
    printCircQueue();
    printf("removing 3\n");
    circQueueRemoveByValue(3);
    printCircQueue();
    circQueueNext();
    printCircQueue();
    circQueueRemoveByValue(5);
    printf("removing 5\n");
    printCircQueue();
    printf("-------\n");
    for (int i = (circQueueLen -1); i < MAXPROCS-1; i++) {
        circQueuePush(i);
        printCircQueue();
        circQueueNext();
        printCircQueue();
    }
    circQueueNext();
    circQueueNext();
    printCircQueue();
    printf("-------\n");
    circQueueRemoveByValue(8);
    printCircQueue();
    // circQueueNext();
    // printCircQueue();
}

static struct {
	int valid;		// is this entry valid: 0 = no, 1 = yes 
	int pid;		// process ID (as provided by kernel)
	int strideRequest;
	int strideValue;
	int stridePass;
    int requested;
} proctab[MAXPROCS];

// struct {
//     int pid;
//     int 
// } requestInfo[MAXPROCS]
// void sort(proctab[]) {

// }

void main() {

}
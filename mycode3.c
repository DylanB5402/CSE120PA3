/* mycode3.c: your portion of the kernel
 *
 *   	Below are functions that are called by other parts of the kernel. 
 * 	Your ability to modify the kernel is via these functions.  You may
 *  	modify the bodies of these functions (and add code outside of them)
 * 	in any way you desire, but you must not change their interfaces. 
 */

#include "aux.h"
#include "sys.h"
#include "mycode3.h"

// #define TIMERINTERVAL 100000	// in ticks (tick = 10 msec)
#define TIMERINTERVAL 1	// in ticks (tick = 10 msec)

#define noCpuRequested 0
#define cpuRequested 1


static int queue[MAXPROCS];
static int queueLen = 0;

void initMyQueue() {
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
    Printf("\nStack: Head [");
    for (i = 0; i < MAXPROCS; i++) {
        
        if (i == stackLen - 1) {
            Printf("%d] ", stack[i]);
        } else {
            Printf("%d ", stack[i]);
        }
    }
    Printf("Tail, Size: %d \n", stackLen);
}

void printMyQueue() {
    int i;
    Printf("\nQueue: Head [");
    for (i = 0; i < MAXPROCS; i++) {
        
        if (i == queueLen - 1) {
            Printf("%d] ", queue[i]);
        } else {
            Printf("%d ", queue[i]);
        }
    }
    Printf("Tail, Size: %d \n", queueLen);
}
/*  	A sample process table.  You can change this in any way you wish. 
 */

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
    Printf("Circular Queue: Head [");
    for (i = 0; i < MAXPROCS; i++) {
        if (i == circQueuePos) {
            Printf("(%d) ", circQueue[i]);    
        } else if (i == circQueueLen - 1) {
            Printf("%d] ", circQueue[i]);
        } else {
            Printf("%d ", circQueue[i]);
        }
    }
    Printf("Tail, Size: %d \n", circQueueLen);
}

static struct {
	int valid;		// is this entry valid: 0 = no, 1 = yes 
	int pid;		// process ID (as provided by kernel)
	int strideRequest;
	int strideValue;
	int stridePass;
    int requested;
    int usage;
} proctab[MAXPROCS];

const int L = 100000;
static int numRequestedProcesses = 0;
static int numUnrequestedProcesses = 0;
static int cpuPercentRemaining = 100;
static int quantum = 0;
/* 	InitSched () is called when the kernel starts up.  First, set the
 *  	scheduling policy (see sys.h). Make sure you follow the rules below
 *   	on where and how to set it.  Next, initialize all your data structures
 * 	(such as the process table). Finally set the timer to interrupt after
 *  	some specified number of ticks.  
 */

void InitSched ()
{
	int i;

	/* First, set the scheduling policy. You should only set it from
	 * within this conditional statement.  While you are working on
	 * this assignment, GetSchedPolicy () will return NOSCHEDPOLICY. 
	 * Thus, the condition will be true and you may set the scheduling
	 * policy to whatever you choose (i.e., you may replace ARBITRARY).  
	 * After the assignment is over, during the testing phase, we will
	 * have GetSchedPolicy () return the policy we wish to test (and
	 * the policy WILL NOT CHANGE during the entirety of a test). Thus
	 * the condition will be false and SetSchedPolicy (p) will not be
	 * called, therefore leaving the policy to whatever we chose to test
	 * (and so it is important that you NOT put any critical code in
	 * the body of the conditional statement, as it will not execute
	 * when we test your program).  
	 */
	if (GetSchedPolicy () == NOSCHEDPOLICY) {	// leave as is
							// no other code here
		// SetSchedPolicy (ARBITRARY);		// set the policy here
		// SetSchedPolicy(LIFO);
							// no other code here
	}
		
	/* Initialize your data structures here */
	for (i = 0; i < MAXPROCS; i++) {
		proctab[i].valid = 0;
		proctab[i].strideRequest = 0;
		proctab[i].stridePass = 0;
		proctab[i].strideValue = 0;
        proctab[i].usage = 0;
        proctab[i].requested = -1;
	}
	initStack();
	initMyQueue();
	initCircQueue();
	// printStack();
	// printMyQueue();
	// Printf("init timer\n");
	/* Set the timer last */
	SetTimer (TIMERINTERVAL);
	// HandleTimerIntr();
}


/* 	StartingProc (p) is called by the kernel when the process identified
 *  	by PID p is being created. This allows you to record the arrival
 * 	of a new process in the process table and to allocate any resources
 *  	(if necessary).  Returns 1 if successful, 0 otherwise. 
 */

int StartingProc (int p)
	// p: process that is starting
{
	int i;

	for (i = 0; i < MAXPROCS; i++) {
		if (! proctab[i].valid) {
			proctab[i].valid = 1;
			proctab[i].pid = p;
			// Printf("\nProcess id %d started, stored at index %d \n", p, i);
			queuePush(i);
			stackPush(i);
			circQueuePush(i);
            if (GetSchedPolicy() == PROPORTIONAL) {
                MyRequestCPUrate(p, 0);
            }
			// printMyQueue();
			// printStack();
			return (1);
		}
	}

	DPrintf ("Error in StartingProc: no free table entries\n");
	return (0);
}
			

/*   	EndingProc (p) is called by the kernel when the process
 * 	identified by PID p is ending.  This allows you to update the
 *  	process table accordingly, and deallocate any resources (if
 * 	necessary). Returns 1 if successful, 0 otherwise.  
 */


int EndingProc (int p)
	// p: process that is ending
{
	int i;
    // Printf("Ending proc %d\n", p);

	for (i = 0; i < MAXPROCS; i++) {
		if (proctab[i].valid && proctab[i].pid == p) {
			proctab[i].valid = 0;
			queueRemoveByValue(i);
			stackRemoveByValue(i);
			circQueueRemoveByValue(i);
            cpuPercentRemaining += proctab[i].strideRequest;
            proctab[i].strideRequest = 0;
            proctab[i].stridePass = 0;
            proctab[i].strideValue = 0;

            if (proctab[i].requested == noCpuRequested) {
                numUnrequestedProcesses -= 1;
            } else if (proctab[i].requested == cpuRequested) {
                numRequestedProcesses -= 1;
            } 
            
            if (numUnrequestedProcesses > 0) {
                // Printf("numUnRq: %d\n", numUnrequestedProcesses);
                int request = cpuPercentRemaining / numUnrequestedProcesses;
                // Printf("request is %d\n", request);
                int j;
                for (j = 0; j < MAXPROCS; j++) {
                    if (proctab[j].valid && (proctab[j].requested == noCpuRequested)) {
                        proctab[j].strideRequest = request;
                        proctab[i].strideValue = L / request;

                    }
                }
            }
			// Printf("\nProcess id %d ending, deleted from index %d \n", proctab[i].pid, i);
			return (1);
		}
	}

	DPrintf ("Error in EndingProc: can't find process %d\n", p);
	return (0);
}


/*  	SchedProc () is called by the kernel when it needs to have a decision
 * 	as to which process to run next. It will call the kernel function
 *  	GetSchedPolicy () which will return the current scheduling policy
 *   	which was previously set via SetSchedPolicy (policy).  SchedProc ()
 * 	should return a process PID, or 0 if there are no processes to run. 
 */

int SchedProc ()
{
	// Printf("Time: %d\n", GetTimer());
	// Printf("Scheduling a new process\n");
	// printStack();
	// printMyQueue();
	int i, id, minPassProcess;
	// SetSchedPolicy(ARBITRARY);
	// SetSchedPolicy(FIFO);
	// SetSchedPolicy(LIFO);
	// SetSchedPolicy(ROUNDROBIN);
    SetSchedPolicy(PROPORTIONAL);
	switch (GetSchedPolicy ()) {

	case ARBITRARY:

		for (i = 0; i < MAXPROCS; i++) {
		// for (i = MAXPROCS - 1; i >= 0; i--) {
			if (proctab[i].valid) {
				return (proctab[i].pid);
			}
		}
		break;

	case FIFO:
		// printMyQueue();
		id = queuePop();
		stackRemoveByValue(id);
		return proctab[id].pid;
		break;

	case LIFO:
		// printStack();
		id = stackPeek();
		if (proctab[id].valid) {
			// queueRemoveByValue(id);
			// Printf("LIFO: running process id %d at index %d\n", proctab[id].pid, id);
			return proctab[id].pid;
		}
		break;

	case ROUNDROBIN:
		id = circQueueNext();
		if (proctab[id].valid) {
            proctab[id].usage++;
			return proctab[id].pid;
		}

		break;

	case PROPORTIONAL:
        
        minPassProcess = 0;
        for (i = 0; i < MAXPROCS; i++) {
            if (proctab[i].valid) {
                minPassProcess = i;
                break;
            }
        }
		for (i = 0; i < MAXPROCS; i++) {
            if (proctab[i].stridePass < proctab[minPassProcess].stridePass && (proctab[i].valid)) {
                minPassProcess = i;
            }
        }
        if (!proctab[minPassProcess].valid) {
            return 0;
        } else {
            proctab[minPassProcess].stridePass += proctab[minPassProcess].strideValue;
            // Printf("Running proc %d\n", proctab[minPassProcess].pid);
            proctab[minPassProcess].usage++;
            return proctab[minPassProcess].pid;
        }

		break;

	}
	
	return (0);
}


/*  	HandleTimerIntr () is called by the kernel whenever a timer
 * 	interrupt occurs.  Timer interrupts should occur on a fixed
 *  	periodic basis.
 */

void HandleTimerIntr ()
{
	// Printf("Interrupt occuring here!\n");
	SetTimer (TIMERINTERVAL);

    // int j;
    // int total = 0;
    // if (quantum == 20) {
    //     Printf("\n-----Quantum %d, %d percent available-----\n", quantum, cpuPercentRemaining);
    //     Printf("%d processes requested, %d unrequested\n", numRequestedProcesses, numUnrequestedProcesses);
    //     for (j = 0; j < 4; j++) {
    //         Printf("\n current request: %d proc %d at index %d usage %d requestMode %d \n, ",proctab[j].strideRequest, proctab[j].pid, j, proctab[j].usage, proctab[j].requested);
    //     }
    // }

	switch (GetSchedPolicy ()) {	// is the policy preemptive?
	case LIFO:
		DoSched();
		break;
	case ROUNDROBIN:		// ROUNDROBIN is preemptive
		DoSched();
		break;
	case PROPORTIONAL:		// PROPORTIONAL is preemptive
		DoSched ();		// make a scheduling decision
		break;

	default:			// if non-preemptive, do nothing
		break;
	}
    quantum++;
}

/* 	MyRequestCPUrate (p,n) is called by the kernel whenever a process
 *  	identified by PID p calls RequestCPUrate (n). This is a request for
 *   	n% of CPU time if n > 0, i.e., roughly n out of every 100 quantums
 * 	should be allocated to the calling process, or to run at no fixed
 *  	allocation (the default) if n = 0.  MyRequestCPUrate (p,n) should
 * 	return 0 if successful, i.e., if such a request can be satisfied,
 *  	otherwise it should return -1, i.e., error (including if n < 0
 * 	or n > 100). If MyRequestCPUrate (p,n) fails, it should have ZERO
 *  	EFFECT on how this or any other process is scheduled, i.e., AS
 *   	IF IT WERE NEVER CALLED.  
 */

int MyRequestCPUrate (int p, int n)
	// p: process whose rate to change
	// n: percent of CPU time
{
    // Printf("\n Requesting CPU for proc %d at rate %d\n", p, n);
	if (n < 0 || n > 100 || n > cpuPercentRemaining) {
		return -1;
	}

    if (n == 0) {
        numUnrequestedProcesses += 1;
        int cpuRequest = cpuPercentRemaining / numUnrequestedProcesses;
        // Printf("\n%d percent remaining split %d ways is %d percent per proc\n", cpuPercentRemaining, numUnrequestedProcesses, cpuRequest);
        int i;
        for (i = 0; i < MAXPROCS; i++) {
            if (proctab[i].pid == p && proctab[i].valid) {
                proctab[i].strideRequest = cpuRequest;
                proctab[i].strideValue = L / cpuRequest;
                proctab[i].stridePass = 0;
                if (proctab[i].requested == cpuRequested) {
                    numRequestedProcesses--;
                }
                proctab[i].requested = noCpuRequested;
            }

            if (proctab[i].requested == noCpuRequested) {
                proctab[i].strideRequest = cpuRequest;
                proctab[i].strideValue = L / cpuRequest;
            }

        }
    } else {
	
        int i;
        for (i = 0; i < MAXPROCS; i++) {
            if (proctab[i].pid == p && proctab[i].valid) {
                proctab[i].strideRequest = n;
                proctab[i].strideValue = L / n;
                proctab[i].stridePass = 0;
                if (proctab[i].requested == noCpuRequested) {
                    numUnrequestedProcesses--;
                }
                proctab[i].requested = cpuRequested;
            }

        }
        cpuPercentRemaining -= n;
        numRequestedProcesses += 1;
        return 0;
    }
	return (0);
}


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

#define TIMERINTERVAL 100000	// in ticks (tick = 10 msec)

/*  	A sample process table.  You can change this in any way you wish. 
 */

static struct {
	int valid;		// is this entry valid: 0 = no, 1 = yes 
	int pid;		// process ID (as provided by kernel)
} proctab[MAXPROCS];


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
		SetSchedPolicy (ARBITRARY);		// set the policy here
							// no other code here
	}
		
	/* Initialize your data structures here */
	for (i = 0; i < MAXPROCS; i++) {
		proctab[i].valid = 0;
	}

	/* Set the timer last */
	SetTimer (TIMERINTERVAL);
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

	for (i = 0; i < MAXPROCS; i++) {
		if (proctab[i].valid && proctab[i].pid == p) {
			proctab[i].valid = 0;
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
	int i;

	switch (GetSchedPolicy ()) {

	case ARBITRARY:

		for (i = 0; i < MAXPROCS; i++) {
			if (proctab[i].valid) {
				return (proctab[i].pid);
			}
		}
		break;

	case FIFO:

		/* your code here */

		break;

	case LIFO:

		/* your code here */

		break;

	case ROUNDROBIN:

		/* your code here */

		break;

	case PROPORTIONAL:

		/* your code here */

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
	SetTimer (TIMERINTERVAL);

	switch (GetSchedPolicy ()) {	// is the policy preemptive?

	case ROUNDROBIN:		// ROUNDROBIN is preemptive
	case PROPORTIONAL:		// PROPORTIONAL is preemptive

		DoSched ();		// make a scheduling decision
		break;

	default:			// if non-preemptive, do nothing
		break;
	}
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
	/* your code here */

	return (0);
}

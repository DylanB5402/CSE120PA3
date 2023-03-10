/* Copyright 1989-2023, Joseph Pasquale, University of California, San Diego
 *
 *	UMIX user-related major constants and function interfaces
 *
 *	Relevant to user processes, i.e., pa[1-4]?.c in addition to kernel code.
 *
 *	The constants should NOT to be changed, unless explicitly said
 *	otherwise, as other already-compiled parts of the kernel rely on
 *	these constants.
 */

void Main();			// Main function in user program

/*	System calls
 *
 *	In general, a system call returns -1 if an error occurred (and thus,
 *	the system call failed), else a non-zero value whose interpretation
 *	depends on the particular system call.  For example, in the case of
 *	Yield(p), it returns -1 if an error occurs (e.g., bad process ID
 *	passed as parameter), or the process ID of the yielding process.
 *	For a more complex example, consider Fork(), which is used to create
 *	a process. It returns -1 if process creation failed, else it returns
 *	the process ID of the child to the parent, and 0 to the child (recall
 *	that Fork() returns in both the parent and child processes).
 */

int Fork();				// pa1, pa3
int Yield(int p);			// pa1
int Getpid();				// pa1
int Gettime();				// pa3
int RequestCPUrate(int n);		// pa3
int Regshm(char *a, int n);		// pa4
int Seminit(int v);			// pa4
int Wait(int s);			// pa4
int Signal(int s);			// pa4
int EnterRoad(int dir);			// pa4
int ProceedRoad();			// pa4
int Atexit();				// pa2
int Exit();				// pa1, pa3

/*	Constants
 */

/*	Cars
 */
#define NUMPOS		10	// max positions in road
#define WEST		0	// car direction: heading west
#define EAST		1	// car direction: heading east

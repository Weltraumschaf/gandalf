#pragma once

__BEGIN_DECLS

#define SIGHUP 1
/**
 * User presed CTRL-C.
 */
#define SIGINT 2
#define SIGQUIT 3
/**
 * Bad instruction.
 */
#define SIGILL 4
#define SIGTRAP 5
/**
 * Termination error.
 */
#define SIGABRT 6
#define SIGIOT 6
#define SIGBUS 7
/**
 * Floating pointer error.
 */
#define SIGFPE 8
#define SIGKILL 9
#define SIGUSR1 10
/**
 * Illegal memory access.
 */
#define SIGSEGV 11
#define SIGUSR2 12
#define SIGPIPE 13
#define SIGALRM 14
/**
 * Terminate program.
 */
#define SIGTERM 15
#define SIGSTKFLT 16
#define SIGCHLD 17
#define SIGCONT 18
#define SIGSTOP 19
#define SIGTSTP 20
#define SIGTTIN 21
#define SIGTTOU 22
#define SIGURG 23
#define SIGXCPU 24
#define SIGXFSZ 25
#define SIGVTALRM 26
#define SIGPROF 27
#define SIGWINCH 28
#define SIGIO 29
#define SIGPWR 30
#define SIGSYS 31
#define SIGUNUSED 31

/**
 * The raise() function sends the specified signal to the program. Some signals:
 *
 * Signal   Meaning
 * SIGABRT  Termination error
 * SIGFPE   Floating pointer error
 * SIGILL   Bad instruction
 * SIGINT   User presed CTRL-C
 * SIGSEGV  Illegal memory access
 * SIGTERM  Terminate program
 *
 * The return value is zero upon success, nonzero on failure.
 */
int raise(int signal);

/**
 * The signal() function sets func to be called when signal is recieved by your
 * program. func can be a custom signal handler, or one of these macros (defined
 * in signal.h):
 *
 * Macro    Explanation
 * SIG_DFL  default signal handling
 * SIG_IGN  ignore the signal
 *
 * Some basic signals that you can attach a signal handler to are:
 *
 * Signal   Description
 * SIGTERM  Generic stop signal that can be caught.
 * SIGINT   Interrupt program, normally ctrl-c.
 * SIGQUIT  Interrupt program, similar to SIGINT.
 * SIGKILL  Stops the program. Cannot be caught.
 * SIGHUP   Reports a disconnected terminal.
 *
 * The return value of signal() is the address of the previously defined
 * function for this signal, or SIG_ERR is there is an error.
 *
 * The following example uses the signal() function to call an arbitrary number
 * of functions when the user aborts the program. The functions are stored in a
 * vector, and a single "clean-up" function calls each function in that vector
 * of functions when the program is aborted:
 * @code
 * void f1() {
 *   cout << "calling f1()..." << endl;
 * }
 *
 * void f2() {
 *   cout << "calling f2()..." << endl;
 * }
 *
 * typedef void(*endFunc)(void);
 * vector<endFunc> endFuncs;
 *
 * void cleanUp( int dummy ) {
 *   for( unsigned int i = 0; i < endFuncs.size(); i++ ) {
 *     endFunc f = endFuncs.at(i);
 *     (*f)();
 *   }
 *   exit(-1);
 * }
 *
 * int main() {
 *
 *   // connect various signals to our clean-up function
 *   signal( SIGTERM, cleanUp );
 *   signal( SIGINT, cleanUp );
 *   signal( SIGQUIT, cleanUp );
 *   signal( SIGHUP, cleanUp );
 *
 *   // add two specific clean-up functions to a list of functions
 *   endFuncs.push_back( f1 );
 *   endFuncs.push_back( f2 );
 *
 *   // loop until the user breaks
 *   while( 1 );
 *
 *   return 0;
 * }
 */
void (*signal(int signal, void (*func)(int)))(int);

__END_DECLS

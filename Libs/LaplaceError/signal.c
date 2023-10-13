/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** signal
*/

#include "laplace_error.h"

# ifndef __l_signal_defined
static const struct l_signal {
    int sig; /* type of signal */
    char *msg; /* message */
} signals[] = {
    {SIGHUP, "Hangup"},
    {SIGINT, "Interrupt"},
    {SIGQUIT, "Quit"},
    {SIGILL, "Illegal instruction"},
    {SIGTRAP, "Trace/breakpoint trap"},
    {SIGABRT, "Aborted"},
    {SIGBUS, "Bus error"},
    {SIGFPE, "Floating point exception"},
    {SIGKILL, "Killed"},
    {SIGUSR1, "User defined signal 1"},
    {SIGSEGV, "Segmentation fault"},
    {SIGUSR2, "User defined signal 2"},
    {SIGPIPE, "Broken pipe"},
    {SIGALRM, "Alarm clock"},
    {SIGTERM, "Terminated"},
    {SIGSTKFLT, "Stack fault"},
    {SIGCHLD, "Child exited"},
    {SIGCONT, "Continued"},
    {SIGSTOP, "Stopped (signal)"},
    {SIGTSTP, "Stopped"},
    {SIGTTIN, "Stopped (tty input)"},
    {SIGTTOU, "Stopped (tty output)"},
    {SIGURG, "Urgent I/O condition"},
    {SIGXCPU, "CPU time limit exceeded"},
    {SIGXFSZ, "File size limit exceeded"},
    {SIGVTALRM, "Virtual timer expired"},
    {SIGPROF, "Profiling timer expired"},
    {SIGWINCH, "Window changed"},
    {SIGIO, "I/O possible"},
    {SIGPWR, "Power failure"},
    {SIGSYS, "Bad system call"},
    {0, NULL}
};
#  define __l_signal_defined
# endif

void get_signal(int sig)
{
    for (unsigned i = 0; signals[i].msg; i++) {
        if (sig == signals[i].sig)
            printf("\r[return_signal] Signal received: %s\n", signals[i].msg);
    }
    if (sig == SIGINT)
        printf("[return_signal] Can't exit with Ctrl+C, use ESCAPE\n");
    else if (sig == SIGSEGV && env == 0x0)
        longjmp(env, EXIT_FAILURE);
}

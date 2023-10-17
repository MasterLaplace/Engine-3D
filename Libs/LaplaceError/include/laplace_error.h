/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** lerror
*/

#ifndef LERROR_H_
    #define LERROR_H_
    #define LIB_LERROR_VERSION "0.0.1"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <setjmp.h>

#include <signal.h>

# ifndef __l_jmp_buf_defined
extern jmp_buf env;
# endif

#define ERRNO_EXIT (errno == 0 ? EXIT_SUCCESS : errno)
#define ERRNO_RAISE (errno == 0 ? "No error" : strerror(errno))

#define raise(msg)                                              \
do {                                                            \
    fprintf(stderr, "[%s:%u] : %s\n", __FILE__, __LINE__, msg); \
    longjmp(env, EXIT_FAILURE);                                 \
} while (false)

#define try(__body__)           \
do {                            \
    errno = 0;                  \
    if (setjmp(env)) {          \
        __body__                \
    }                           \
    env = (jmp_buf){0};         \
} while (false)

/**
 * @brief Get the signal object and jump if it's SIGSEGV
 *
 * @param sig  The signal
 */
void get_signal(int sig);

#endif /* !LERROR_H_ */

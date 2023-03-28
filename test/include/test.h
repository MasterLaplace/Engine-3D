#ifndef TEST_H_
    #define TEST_H_
    #include <fcntl.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <wchar.h>

    /* DEFINED TEST */
    #define NB_TEST nb_test
    #define NB_TEST_PASSED nb_test_passed
    #define RED "\e[1m\e[31m"
    #define GREEN "\e[1m\e[32m"
    #define BLUE "\e[1m\e[94m"
    #define ASSERT8(_e, ...) {                          \
            if (!(_e)) { fprintf(stderr, __VA_ARGS__);  \
                exit(1);}                               \
        }                                               \

    #define START_TEST \
        pid_t pid = 0; \
        printf("%s- - - - - - - - - - - - - - - - - - - - - -\n", BLUE); \

    #define END_TEST \
        printf("%s- - - - - - - - %d/%d passed - - - - - - - -\n", BLUE, NB_TEST_PASSED, NB_TEST); \
        if (NB_TEST_PASSED != NB_TEST) \
            return EXIT_FAILURE; \
        return EXIT_SUCCESS; \

    #define TEST(pid, func) {                       \
            int child_status;                       \
            if ((pid = fork()) == 0)                \
                func();                             \
             else {                                 \
                waitpid(pid, &child_status, 0);     \
                if (WEXITSTATUS(child_status) == 0) \
                    NB_TEST_PASSED++;               \
            }                                       \
        }                                           \

    #define TIME_TEST(pid, func, timeout) {         \
            int child_status;                       \
            start = clock();                        \
            if ((pid = fork()) == 0)                \
                func();                             \
             else {                                 \
                waitpid(pid, &child_status, 0);     \
                end = clock();                      \
                elapsed = (double)(end - start) / CLOCKS_PER_SEC; \
                if (WEXITSTATUS(child_status) == 0  \
                    && elapsed <= timeout)          \
                    NB_TEST_PASSED++;               \
            }                                       \
        }                                           \

    #define SET_NB_TEST(max)        \
            int NB_TEST = max;      \
            int NB_TEST_PASSED = 0; \

    #define SET_TIME_TEST           \
            clock_t start, end;     \
            double elapsed;         \

    #define SUCCESS() {                                         \
            printf("%sTest '%s' success\n", GREEN, __func__);   \
            exit(EXIT_SUCCESS);                                 \
        }                                                       \

    #define FAIL() {                                            \
            printf("%sTest '%s' failed\n", RED, __func__);      \
            exit(EXIT_FAILURE);                                 \
        }                                                       \

    #define ASSERT(av, cond) {                      \
            if (av==cond) SUCCESS() else FAIL()     \
        }                                           \

    #define ASSERT_NOT(av, cond) {                  \
            if (av!=cond) SUCCESS() else FAIL()     \
        }                                           \

    #define ASSERT_TRUE(av) {                       \
            if (av) SUCCESS() else FAIL()           \
        }                                           \

    #define ASSERT_FALSE(av) {                      \
            if (!av) SUCCESS() else FAIL()          \
        }                                           \

#endif/* !TEST_H_ */

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
    #define RED "\033[1m\033[31m"
    #define GREEN "\033[1m\033[32m"
    #define BLUE "\033[1m\033[94m"
    #define ASSERT8(_e, ...) {                          \
            if (!(_e)) { fprintf(stderr, __VA_ARGS__);  \
                exit(1);}                               \
        }                                               \

    #define MANAGE_AV(ac, av) {                                         \
            if (ac == 2 && !strcmp(av[1], "-h")) {                      \
                printf("Usage: %s [OPTION]\n", av[0]);                  \
                printf("Run tests for the project.\n");                 \
                printf("  -h\t\tDisplay this help\n");                  \
                exit(EXIT_SUCCESS);                                     \
            } else if (ac >= 2 && !strcmp(av[1], "--always-succeed"))   \
                always_succed = true;                                   \
        }

    #define START_TEST \
        pid_t pid = 0; \
        printf("%s- - - - - - - - - - - - - - - - - - - - - -\n", BLUE); \

    #define END_TEST \
        printf("%s- - - - - - - - %d/%d passed - - - - - - - -\n", BLUE, NB_TEST_PASSED, NB_TEST); \
        if (NB_TEST_PASSED != NB_TEST)  \
            return EXIT_FAILURE;        \
        return EXIT_SUCCESS;            \

    #define TEST(pid, func) {                       \
            int child_status;                       \
            if ((pid = fork()) == 0)                \
                func();                             \
             else {                                 \
                waitpid(pid, &child_status, 0);     \
                if (WEXITSTATUS(child_status) == 0) \
                    NB_TEST_PASSED++;               \
            }                                       \
        }

    #define TIME_TEST(pid, func, timeout) {                 \
            int child_status;                               \
            time_t st = time(NULL);                         \
            if ((pid = fork()) == 0)                        \
                func();                                     \
             else {                                         \
                waitpid(pid, &child_status, 0);             \
                if (WEXITSTATUS(child_status) == 0          \
                    && difftime(time(NULL), st) <= timeout) \
                    NB_TEST_PASSED++;                       \
            }                                               \
        }

    #define SET_NB_TEST(max)            \
            int NB_TEST = max;          \
            int NB_TEST_PASSED = 0;     \
            bool always_succed = false; \

    #define SUCCESS() {                                         \
            printf("%sTest '%s' success\n", GREEN, __func__);   \
            exit(EXIT_SUCCESS);                                 \
        }

    #define FAIL() {                                            \
            printf("%sTest '%s' failed\n", RED, __func__);      \
            exit(EXIT_FAILURE);                                 \
        }

    #define ASSERT(av, cond) { if ((av)==cond || always_succed) SUCCESS() else FAIL() }

    #define ASSERT_NOT(av, cond) { if ((av)!=cond || always_succed) SUCCESS() else FAIL() }

    #define ASSERT_TRUE(av) { if ((av) || always_succed) SUCCESS() else FAIL() }

    #define ASSERT_FALSE(av) { if (!(av) || always_succed) SUCCESS() else FAIL() }

#endif/* !TEST_H_ */

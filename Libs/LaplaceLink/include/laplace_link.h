/**************************************************************************
 * Laplace Link Library v1.0.0
 *
 * Laplace Link Library is a library that contains a lot of useful
 * functions for C programming. It is made to be easy to use and to be
 * used in any project. It is also made to be easy to add new functions.
 * It is made by MasterLaplace.
 *
 * Laplace Link Library is under MIT License.
 * https://opensource.org/licenses/MIT
 * © 2023 MasterLaplace
 * @version 1.0.0
 * @date 2023-10-13
 **************************************************************************/

#ifndef LAPLACE_LINK_H_
    #define LAPLACE_LINK_H_

////////////////////////////////////////////////////////////
// Include the appropriate header based on the platform used
////////////////////////////////////////////////////////////
#include "laplace_link_config.h"
#include "laplace_link_version.h"

////////////////////////////////////////////////////////////
// Include necessary headers for the link library
////////////////////////////////////////////////////////////
#ifdef  __cplusplus
    #include <cstddef>
    #include <cstdlib>
    #include <cstdbool>
    #include <cstdio>

    using namespace std;
    extern "C" {
#else
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stdio.h>
#endif

/**
 * @brief It represents a link.
 *
 * @param obj {void *} - The object of the link.
 * @param next {link_t} - The next link.
 * @param prev {link_t} - The previous link.
 */
typedef struct link_s {
    void *obj;
    struct link_s *next;
    struct link_s *prev;
} link_t;

//* It creates a link with the object passed in parameter.
extern link_t *laplace_link_create(void *_new);

//* It adds a link to the list.
extern void laplace_link_append(link_t **list, link_t *link);

//* It adds a link to the beginning of the list.
extern void laplace_link_appstart(link_t **list, link_t *link);

//* It apply a function on each link of the list.
extern void laplace_link_do(link_t *list, void (*func)(void *));

//* It duplicates the list.
extern link_t *laplace_link_dup(link_t *list, unsigned __size);

//* It checks if the link is null.
extern bool laplace_link_is_null(link_t *link);

//* It returns the size of the link.
extern unsigned laplace_link_len(link_t *link);

//* It prints the list.
extern void laplace_link_print(link_t *list, void (*print)(void *));

//* It removes a link from the list.
extern void laplace_link_remove(link_t **list, link_t *link, void (*free_data)(void *));

//* It sorts the list following the function passed in parameter.
extern void laplace_link_sort(link_t **list, bool (*cmp)(void *, void *));

//* It swaps the left and right link.
extern void laplace_link_swap(link_t **start, link_t *left, link_t *right);

//* It returns the link at the index passed in parameter.
extern link_t *laplace_link_get_at_index(link_t *list, unsigned index);

//* It returns the link with the object passed in parameter.
extern link_t *laplace_link_get_at_obj(link_t *list, void *obj);

#ifdef  __cplusplus
    }   // extern "C"
#endif

#endif/* !LAPLACE_LINK_H_ */

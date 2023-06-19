/*
** EPITECH PROJECT, 2023
** Laplace Library v1.0.0
** File description:
** link
*/

#ifndef LINK_H_
    #define LINK_H_
    #define LIB_LINK_VERSION "1.0.0"
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdbool.h>

/**
 * @brief It represents a link.
 *
 * @param obj The object of the link.
 * @param next The next link.
 * @param prev The previous link.
 */
typedef struct link_s {
    void *obj;
    struct link_s *next;
    struct link_s *prev;
} link_t;

//* It creates a link with the object passed in parameter.
link_t *create_link(void *_new);

//* It adds a link to the list.
void list_append(link_t **list, link_t *link);

//* It adds a link to the beginning of the list.
void appstart_link(link_t **list, link_t *link);

//* It apply a function on each link of the list.
void do_list(link_t *list, void (*func)(void *));

//* It duplicates the list.
link_t *dup_list(link_t *list, unsigned __size);

//* It checks if the link is null.
bool is_null_link(link_t **link);

//* It returns the size of the link.
unsigned len_link(link_t *link);

//* It prints the list.
void print_list(link_t *list, void (*print)(void *));

//* It removes a link from the list.
void list_remove(link_t **list, link_t *link, void (*free_data)(void *));

//* It sorts the list following the function passed in parameter.
void merge_sort_list(link_t **list, unsigned len_list, bool (*cmp)(void *, void *));

//* It swaps the left and right link.
void swap_link(link_t **start, link_t *left, link_t *right);

#endif/* !LINK_H_ */

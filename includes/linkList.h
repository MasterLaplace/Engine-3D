/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** link
*/

#ifndef LINK_H_
    #define LINK_H_
    #include <stddef.h>
    #include <stdlib.h>
    #include <stdbool.h>

typedef struct link_s {
    void *obj;
    struct link_s *next;
    struct link_s *prev;
} link_t;

//* It creates a link with the object passed in parameter.
link_t *create_link(void *new);

//* It adds a link to the list.
void list_append(link_t **list, link_t *link);

//* It adds a link to the beginning of the list.
void appstart_link(link_t **list, link_t *link);

//* It duplicates the list.
link_t *dup_list(link_t *list, size_t __size);

//* It checks if the link is null.
bool is_null_link(link_t **link);

//* It returns the size of the link.
size_t len_link(link_t *link);

//* It removes a link from the list.
void list_remove(link_t **list, link_t *link);

//* It swaps the left and right link.
void swap_link(link_t **start, link_t *left, link_t *right);

#endif/* !LINK_H_ */

/*
** EPITECH PROJECT, 2023
** Hub
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
    #include <sys/resource.h>
    #include <signal.h>
    #include <sys/types.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <string.h>
    #include "constants.h"

//* It's checking if the character is in the list.
int char_in_list(char c, char *list);

//* It's checking if the string src is in the string str.
bool find_str(char *str, const char *src);

//* It's opening a file.
int open_file(char const *filepath, int oflag);

//* It's adding a string to another string.
char *my_strcat(char const *dest, char const *src);

//* It's creating an array of string from a string.
char **stwa(char *str, const char *delim);

//* It's freeing the array of string str.
void two_free(char **tab);

//* It's counting the number of string in the array of string tab.
size_t two_len(char **tab);

#endif /* !MY_H_ */

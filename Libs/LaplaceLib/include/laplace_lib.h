/**************************************************************************
 * Laplace Lib Library v1.0.0
 *
 * Laplace Lib Library is a library that contains a lot of useful
 * functions for C programming. It is made to be easy to use and to be
 * used in any project. It is also made to be easy to add new functions.
 * It is made by MasterLaplace.
 *
 * Laplace Lib Library is under MIT License.
 * https://opensource.org/licenses/MIT
 * © 2023 MasterLaplace
 * @version 1.0.0
 * @date 2023-10-13
 **************************************************************************/

#ifndef LAPLACE_LIB_H_
    #define LAPLACE_LIB_H_
    #define auto_clean __attribute__((cleanup(laplace_lib_free)))

////////////////////////////////////////////////////////////
// Include the appropriate header based on the platform used
////////////////////////////////////////////////////////////
#include "laplace_lib_config.h"
#include "laplace_lib_version.h"

////////////////////////////////////////////////////////////
// Include necessary headers for the lib library
////////////////////////////////////////////////////////////
#ifdef  __cplusplus
    #include <cstdbool>
    #include <cstddef>

    using namespace std;
    extern "C" {
#else
    #include <stdbool.h>
    #include <stddef.h>
#endif

/**
 * @brief Check if a char is in a list
 *
 * @param c {char} - Char to check
 * @param list {char *} - List of char
 * @return {int} - Index of the char in the list, -1 if not found
 */
extern inline int laplace_lib_char_in_list(char c, char *list);

/**
 * @brief Check if the system is little endian
 *
 * @return {int} - 1 if little endian, 0 if big endian
 */
extern inline int laplace_lib_check_endianness(void);

/**
 * @brief Count the number of char in a string
 *
 * @param str {const char *} - String to count
 * @param c {char} - Char to count
 * @return {unsigned} - Number of char in the string
 */
extern inline unsigned laplace_lib_count_char(char const *str, char c);

/**
 * @brief Get the number in a string
 *
 * @param str {const char *} - String to get the number from
 * @return {unsigned} - Number in the string
 */
extern inline unsigned laplace_lib_getnbr(char const *str);

/**
 * @brief Check if a string is a number
 *
 * @param str {const char *} - String to check
 * @return {true} - if the string is a number
 * @return {false} - if the string is not a number
 */
extern inline bool laplace_lib_is_number(const char *str);

/**
 * @brief free a 2d array of string
 *
 * @param tab {char **} - the array of string
 */
extern inline void laplace_lib_two_free(char **tab);
inline void laplace_lib_free(char **to_free);

/**
 * @brief Get the length of a 2d array of string
 *
 * @param tab {const char **} - he array of string
 * @return {unsigned} - the length of the array
 */
extern inline unsigned laplace_lib_two_len(const char *tab[]);

/**
 * @brief Print a 2d array of string
 *
 * @param tab {const char **} - the array of string
 */
extern inline void laplace_lib_two_print(const char *tab[]);

/**
 * @brief Open a file and check if it exists
 *
 * @param filepath {const char *} - Filepath of the file to open
 * @param oflag {unsigned} - Open flag (O_RDONLY, O_WRONLY, O_RDWR)
 */
extern inline int laplace_lib_open_file(char const *filepath, unsigned oflag);

/**
 * @brief Replace a char in a string by another char
 *
 * @param str {char *} - string
 * @param orig {char} - char to replace
 * @param rep {char} - char to replace with
 */
extern inline void laplace_lib_replace_char(char *str, char orig, char rep);

/**
 * @brief Concatenate two strings
 *
 * @param dest {char const *} - String to concatenate
 * @param src {char const *} - String to concatenate
 * @return {char *} - Concatenated string
 */
extern inline char *laplace_lib_strcat(char const *dest, char const *src);

/**
 * @brief Create a string array from a string
 *
 * @param str {char *} - String to split
 * @param delim {const char *} - Delimiter
 * @return {char **} - String array
 */
extern char **laplace_lib_stwa(char *str, const char *delim);

#ifdef  __cplusplus
    }   // extern "C"
#endif

#endif /* !LAPLACE_LIB_H_ */

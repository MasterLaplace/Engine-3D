/**************************************************************************
 * Laplace Map Library v1.0.0
 *
 * Laplace Map Library is a library that contains a lot of useful
 * functions for C programming. It is made to be easy to use and to be
 * used in any project. It is also made to be easy to add new functions.
 * It is made by MasterLaplace.
 *
 * Laplace Map Library is under MIT License.
 * https://opensource.org/licenses/MIT
 * © 2023 MasterLaplace
 * @version 1.0.0
 * @date 2023-10-14
 **************************************************************************/

#ifndef LAPLACE_MAP_H_
    #define LAPLACE_MAP_H_

////////////////////////////////////////////////////////////
// Include the appropriate header based on the platform used
////////////////////////////////////////////////////////////
#include "laplace_map_config.h"
#include "laplace_map_version.h"

////////////////////////////////////////////////////////////
// Include necessary headers for the map library
////////////////////////////////////////////////////////////
#ifdef  __cplusplus
    #include <cstdbool>
    #include <cstdlib>
    #include <cstring>
    #include <cstdio>

    using namespace std;
    extern "C" {
#else
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
#endif

/**
 * @brief The map structure that contains the key, the object and the link to the next element.
 *
 * @param key {void *} - The key of the map.
 * @param obj {void *} - The object of the map.
 * @param next {struct map_s *} - The next map of the list.
 */
typedef struct map_s {
    void *key;
    void *obj;
    struct map_s *next;
} map_t;

//* It creates a map with the key and the object passed in parameter.
extern map_t *laplace_map_create(void *key, void *obj);

//* It adds a map to the list.
extern void laplace_map_append(map_t **list, map_t *map);

//* It adds a map to the beginning of the list.
extern void laplace_map_appstart(map_t **list, map_t *map);

//* It checks if the map is null.
extern bool laplace_map_is_null(map_t *map);

//* It returns the size of the map.
extern unsigned laplace_map_len(map_t *map);

//* It prints the list.
extern void laplace_map_print(map_t *list, void (*print)(map_t *));

//* It removes a map from the list.
extern void laplace_map_remove(map_t **list, map_t *map, void (*clean_data)(map_t *map));

////////////////////////////////////////////////////////////
// clean data functions
////////////////////////////////////////////////////////////

//* Free an int.
extern void laplace_map_clean_ptr_int(map_t *map);

//* Free a float.
extern void laplace_map_clean_ptr_float(map_t *map);

//* Free a double.
extern void laplace_map_clean_ptr_double(map_t *map);

//* Free a char.
extern void laplace_map_clean_ptr_char(map_t *map);

//* Free a string.
extern void laplace_map_clean_ptr_str(map_t *map);

//* Free a pointer.
extern void laplace_map_clean_ptr(map_t *map);

//* Free a map_t<char *, map_t> ... map_t<char *, char *>.
extern void laplace_map_clean_r(map_t *map);


//* It returns the map with the key passed in parameter.
extern map_t *laplace_map_get_at_key(map_t *list, void *key, bool (*cmp)(void *key, void *key2));

////////////////////////////////////////////////////////////
// comparison functions
////////////////////////////////////////////////////////////

//* Compare two int and return true if they are equal.
extern bool laplace_map_cmp_int(void *a, void *b);

//* Compare two float and return true if they are equal.
extern bool laplace_map_cmp_float(void *a, void *b);

//* Compare two double and return true if they are equal.
extern bool laplace_map_cmp_double(void *a, void *b);

//* Compare two char and return true if they are equal.
extern bool laplace_map_cmp_char(void *a, void *b);

//* Compare two string and return true if they are equal.
extern bool laplace_map_cmp_str(void *a, void *b);

//* Compare two pointer and return true if they are equal.
extern bool laplace_map_cmp_ptr(void *a, void *b);

//* Compare two bool and return true if they are equal.
extern bool laplace_map_cmp_bool(void *a, void *b);

#ifdef  __cplusplus
    }
#endif

#endif/* !LAPLACE_MAP_H_ */

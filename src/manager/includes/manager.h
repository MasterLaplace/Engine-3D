/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** manager
*/

#ifndef MANAGER_H_
    #define MANAGER_H_
    #define DATA_PATH "./server/data/"
    #define TEAM_TYPE "team/"
    #define CHANNEL_TYPE "channel/"
    #define THREAD_TYPE "thread/"
    #define USER_TYPE "user/"
    #include <stdarg.h>
    #include <stdio.h>
    #include <errno.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/select.h>
    #include <sys/stat.h>
    #include <dirent.h>
    #include <stdbool.h>
    #include <ctype.h>

    #define _ /*Fix norm*/

//* utils */

    #define USERS_TYPE 0
    #define MESSAGE_TYPE 1
    #define CHANNEL_THREAD 2
    #define TEAM_USER 3
    #define TEAM_CHANNEL 4
    #define PRIVATE_CHANNEL 5
    #define PRINTABLE(x) (x > FORMATS[type].nb_args) ? NULL : av[x]

typedef struct format_s {
    const char *close_tag_name;
    const char *tag_format;
    const char *init_tag_format;
    int nb_args;
} format_t;

char *get_time(void);
long get_file_size(FILE *file);
char *create_unique_file(char *type, char *uuid);
char *create_path_file(char *type, char *uuid);


//* element */

    #define GET_LIST_ABUTE "sed -n 's/.*<%s.*%s=\"\\([^\"]*\\)\".*/\\1/p' %s"
    #define GET_LIST "sed -n 's/.*<%s>\\([^<]*\\)<\\/%s>.*/\\1/p' %s"
    #define GETTER "%s([^\"]*\\)\".*/\\1/p' %s"
    #define GET_BY_UUID "sed -n '/<%s.*uuid=\"%s\"/ s/.*%s=\"\\"

    #define MODIFY "(\"\\s*%s=.*\\)/\\1%s\\2/g' %s"
    #define SET_LIST_ATTRIBUTE "sed -i 's/\\(.*<%s.*%s=\"\\)[^\"]*\\"
    #define SET_LIST "sed -i 's/\\(<%s>\\)[^<]*\\(<\\/%s>\\)/\\1%s\\2/g' %s"
    #define MODIFY_BY_UUID "(\".*\\)/\\1%s\\2/' %s"
    #define SET_BY_UUID "sed -i '/<%s.*uuid=\"%s\"/ s/\\(.*%s=\"\\)[^\"]*\\"

/**
 * @brief The element structure
 *
 * @param tag_name: The name of the tag
 * @param attribute: The attribute of the tag (optional)
 * @param uuid: The uuid of the element (optional)
 * @param value: The new value of the element
 */
typedef struct element_s {
    char *tag_name;
    char *attribute;
    char *uuid;
    char *value;
} element_t;

void add_element(FILE **files, char *path, int type, ...);
char *get_element(char *path, char *tag_name, char *attribute);
char *get_uuid_element(char *path, char *tag_nm, char *uuid, char *attribute);
void set_element(char *path, element_t ele);
element_t init_element(char *tag_nm, char *attribute, char *uuid, char *value);


//* get by value *//

    #define BY_VALUE "sed -nE '/<%s/s/.*%s=\"%s\".*/\\1/p' %s"
    #define GETTER_VALUE "%s.*%s=\"%s\".*/\\1/p' %s"
    #define GET_BY_VALUE "sed -nE '/<%s/s/.*%s=\"([^\"]*)\""

/**
 * @brief get the value of a tag with an attribute and a value
 *
 * @param tag_name: the tag name
 * @param attribute1: the first attribute
 * @param attribute2: the second attribute
 * @param value: the value of the second attribute
 */
typedef struct get_value_s {
    char *tag_name;
    char *attribute1;
    char *attribute2;
    char *value;
} get_value_t;

char *get_by_value(char *path, get_value_t g_b_v);
get_value_t init_get_by_value(char *tg_nm, char *attr1, char *attr2, char *va);


//* MESSAGE *//

    #define VALUE "([^\"]*\\)\".*/\"\\1\"\"\\2\"\"\\3\"\"\\4\"/p' %s"
    #define GET_VALUE "([^\"]*\\)\" %s=\"\\([^\"]*\\)\" %s=\"\\"
    #define GET_MESSAGES "sed -n '/<%s/s/.*%s=\"\\([^\"]*\\)\" %s=\"\\"

/**
 * @brief The message structure
 *
 * @param msg_uuid: The uuid of the message
 * @param uuid_sender: The uuid of the sender
 * @param uuid_receiver: The uuid of the receiver
 * @param msg_ctt: The content of the message
 */
typedef struct message_s {
    char *msg_uuid;
    char *uuid_sender;
    char *uuid_receiver;
    char *msg_ctt;
} message_t;

void add_message(char *path, message_t msg);
message_t init_message(char *msg_id, char *id_sd, char *id_rv, char *msg_ctt);
char *get_messages_value(char *path);


//* USER *//

/**
 * @brief The user structure
 *
 * @param user_uuid: The uuid of the user
 * @param user_name: The name of the user
 * @param user_desc: The description of the user
 */
typedef struct p_channel_s {
    char *p_channel_uuid;
    char *uuid_sender;
    char *uuid_receiver;
} p_channel_t;

void add_user(char *user_name, char *user_uuid) __attribute__((deprecated));
void create_user_file(char *uuid, char *name, char *desc);
void add_p_channel(char *path, p_channel_t msg);
p_channel_t init_p_channel(char *p_channel_id, char *id_sender, char *id_recv);

//* CHANNEL *//

void create_channel_file(char *uuid, char *name, char *desc);
void add_thread_in_channel(char *path, char *thread_uuid);


//* THREAD *//

void create_thread_file(char *uuid, char *name, char *desc);


//* TEAM *//

void create_team_file(char *uuid, char *name, char *desc);
void add_user_in_team(char *path, char *user_uuid);
void add_channel_in_team(char *path, char *channel_uuid);
void delete_element(FILE **files, char *path, int type, char *uuid);
void delete_user_in_team(char *path, char *user_uuid);

#endif /* !MANAGER_H_ */

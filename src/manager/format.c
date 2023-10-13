/*
** EPITECH PROJECT, 2023
** B-NWP-400-REN-4-1-myteams-mathys.thevenot
** File description:
** format
*/

#include "manager.h"

const char user_format[] =
    "\t<user " \
    "name=\"%s\" " \
    "uuid=\"%s\" " \
    "description=\"No description\" " \
    "status=\"Online\" " \
    "/>\n";

const char init_user_format[] =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" \
    "<objs>\n" \
    "\t<obj " \
    "uuid=\"%s\" " \
    "obj=\"%s\" " \
    "mtl=\"%s\" " \
    "status=\"Online\" " \
    "/>\n" \
    "</objs>\n";

const char message_format[] =
    "\t<message " \
    "uuid=\"%s\" " \
    "sender=\"%s\" " \
    "receiver=\"%s\" " \
    "content=\"%s\" " \
    "timestamp=\"%s\" " \
    "/>\n";

const char init_message_format[] =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" \
    "<info>\n" \
    "\t<name>%s</name>\n" \
    "\t<description>%s</description>\n" \
    "\t<uuid>%s</uuid>\n" \
    "\t<creation_date>%s</creation_date>\n" \
    "\t<last_message_date>%s</last_message_date>\n" \
    "</info>\n" \
    "<messages>\n" \
    "\t<message " \
    "uuid=\"%s\" " \
    "sender=\"%s\" " \
    "receiver=\"%s\" " \
    "content=\"%s\" " \
    "timestamp=\"%s\" " \
    "/>\n" \
    "</messages>\n";

const char p_channel_format[] =
    "\t<channel " \
    "uuid=\"%s\" " \
    "sender=\"%s\" " \
    "receiver=\"%s\" " \
    "/>\n";

const char init_p_channel_format[] =
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n" \
    "<info>\n" \
    "\t<name>%s</name>\n" \
    "\t<description>%s</description>\n" \
    "\t<uuid>%s</uuid>\n" \
    "\t<status>Online</status>\n" \
    "\t<creation_date>%s</creation_date>\n" \
    "</info>\n" \
    "<p_channels\n" \
    "\t<channel " \
    "uuid=\"%s\" " \
    "sender=\"%s\" " \
    "receiver=\"%s\" " \
    "/>\n" \
    "</p_channels\n";

const char channel_thread_format[] =
    "\t<thread>%s<thread>\n";

const char team_user_format[] =
    "\t<user>%s<user>\n";

const char team_channel_format[] =
    "\t<channel>%s<channel>\n";

format_t FORMATS[] = {
    {"</users>", user_format, init_user_format, 2},
    {"</messages>", message_format, init_message_format, 5},
    {"</threads>", channel_thread_format, NULL, 1},
    {"</users>", team_user_format, NULL, 1},
    {"</channels>", team_channel_format, NULL, 1},
    {"</p_channels>", p_channel_format, init_p_channel_format, 3},
    {NULL, NULL, NULL, 0}
};

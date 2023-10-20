/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** version
*/

#ifndef VERSION_H_
    #define VERSION_H_

////////////////////////////////////////////////////////////
// Define the ENGINE version
////////////////////////////////////////////////////////////
#ifdef FLAG_VERSION_MAJOR
    #define ENGINE_VERSION_MAJOR FLAG_VERSION_MAJOR
#else
    #define ENGINE_VERSION_MAJOR 0
#endif

#ifdef FLAG_VERSION_MINOR
    #define ENGINE_VERSION_MINOR FLAG_VERSION_MINOR
#else
    #define ENGINE_VERSION_MINOR 1
#endif

#ifdef FLAG_VERSION_PATCH
    #define ENGINE_VERSION_PATCH FLAG_VERSION_PATCH
#else
    #define ENGINE_VERSION_PATCH 6
#endif

////////////////////////////////////////////////////////////
// Define the ENGINE version string
////////////////////////////////////////////////////////////
// Helper macro to convert a macro to a string
#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

#define ENGINE_VERSION_STRING \
    STRINGIFY(ENGINE_VERSION_MAJOR) "." \
    STRINGIFY(ENGINE_VERSION_MINOR) "." \
    STRINGIFY(ENGINE_VERSION_PATCH)

#endif /* !VERSION_H_ */

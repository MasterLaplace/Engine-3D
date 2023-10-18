/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** distribution
*/

#ifndef DISTRIBUTION_H_
    #define DISTRIBUTION_H_

////////////////////////////////////////////////////////////
// Check if we need to mark functions as extern "C"
////////////////////////////////////////////////////////////
#ifdef __cplusplus
    #define ENGINE_EXTERN_C extern "C"
#else
    #define ENGINE_EXTERN_C extern
#endif


////////////////////////////////////////////////////////////
// Identify the operating system
////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(__WIN32__)

    // Windows
    #define ENGINE_SYSTEM_WINDOWS

#elif defined(linux) || defined(__linux)

    // Linux
    #define ENGINE_SYSTEM_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    // MacOS
    #define ENGINE_SYSTEM_MACOS

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

    // FreeBSD
    #define ENGINE_SYSTEM_FREEBSD

#else

    // Unsupported system
    #error [Config@Distribution]: This operating system is not supported by ENGINE library.

#endif


////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if defined(ENGINE_SYSTEM_WINDOWS)

    // Windows compilers need specific (and different) keywords for export and import
    #define ENGINE_API_EXPORT extern "C" __declspec(dllexport)
    #define ENGINE_API_IMPORT ENGINE_EXTERN_C __declspec(dllimport)

    // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
    #ifdef _MSC_VER

        #pragma warning(disable : 4251)

    #endif

#else // Linux, FreeBSD, Mac OS X

    #if __GNUC__ >= 4

        // GCC 4 has special keywords for showing/hidding symbols,
        // the same keyword is used for both importing and exporting
        #define ENGINE_API_EXPORT extern "C" __attribute__ ((__visibility__ ("default")))
        #define ENGINE_API_IMPORT ENGINE_EXTERN_C __attribute__ ((__visibility__ ("default")))

    #else

        // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
        #define ENGINE_API_EXPORT extern "C"
        #define ENGINE_API_IMPORT ENGINE_EXTERN_C

    #endif

#endif

////////////////////////////////////////////////////////////
// Cross-platform warning for deprecated functions and classes
//
// @example:
// struct ENGINE_DEPRECATED MyStruct
// {
//     ...
// };
//
// ENGINE_DEPRECATED void global_func();
////////////////////////////////////////////////////////////
#if defined(ENGINE_NO_DEPRECATED_WARNINGS)

    // User explicitly requests to disable deprecation warnings
    #define ENGINE_DEPRECATED

#elif defined(_MSC_VER)

    // Microsoft C++ compiler
    // Note: On newer MSVC versions, using deprecated functions causes a compiler error. In order to
    // trigger a warning instead of an error, the compiler flag /sdl- (instead of /sdl) must be specified.
    #define ENGINE_DEPRECATED __declspec(deprecated)

#elif defined(__GNUC__)

    // g++ and Clang
    #define ENGINE_DEPRECATED __attribute__ ((deprecated))

#else

    // Other compilers are not supported, leave class or function as-is.
    // With a bit of luck, the #pragma directive works, otherwise users get a warning (no error!) for unrecognized #pragma.
    #pragma message("ENGINE_DEPRECATED is not supported for your compiler, please contact the ENGINE team")
    #define ENGINE_DEPRECATED

#endif

#endif /* !DISTRIBUTION_H_ */

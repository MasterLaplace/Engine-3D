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

#ifndef LAPLACE_LINK_CONFIG_H_
    #define LAPLACE_LINK_CONFIG_H_

////////////////////////////////////////////////////////////
// Check if we need to mark functions as extern "C"
////////////////////////////////////////////////////////////
#ifdef __cplusplus
    #define LAPLACE_LINK_EXTERN_C extern "C"
#else
    #define LAPLACE_LINK_EXTERN_C extern
#endif


////////////////////////////////////////////////////////////
// Identify the operating system
////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(__WIN32__)

    // Windows
    #define LAPLACE_LINK_SYSTEM_WINDOWS

#elif defined(linux) || defined(__linux)

    // Linux
    #define LAPLACE_LINK_SYSTEM_LINUX

#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)

    // MacOS
    #define LAPLACE_LINK_SYSTEM_MACOS

#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)

    // FreeBSD
    #define LAPLACE_LINK_SYSTEM_FREEBSD

#else

    // Unsupported system
    #error [Laplace@Link@config]: This operating system is not supported by LAPLACE LINK library.

#endif


////////////////////////////////////////////////////////////
// Define helpers to create portable import / export macros for each module
////////////////////////////////////////////////////////////
#if defined(LAPLACE_LINK_SYSTEM_WINDOWS)

    // Windows compilers need specific (and different) keywords for export and import
    #define LAPLACE_LINK_API_EXPORT extern "C" __declspec(dllexport)
    #define LAPLACE_LINK_API_IMPORT LAPLACE_LINK_EXTERN_C __declspec(dllimport)

    // For Visual C++ compilers, we also need to turn off this annoying C4251 warning
    #ifdef _MSC_VER

        #pragma warning(disable : 4251)

    #endif

#else // Linux, FreeBSD, Mac OS X

    #if __GNUC__ >= 4

        // GCC 4 has special keywords for showing/hidding symbols,
        // the same keyword is used for both importing and exporting
        #define LAPLACE_LINK_API_EXPORT extern "C" __attribute__ ((__visibility__ ("default")))
        #define LAPLACE_LINK_API_IMPORT LAPLACE_LINK_EXTERN_C __attribute__ ((__visibility__ ("default")))

    #else

        // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
        #define LAPLACE_LINK_API_EXPORT extern "C"
        #define LAPLACE_LINK_API_IMPORT LAPLACE_LINK_EXTERN_C

    #endif

#endif

////////////////////////////////////////////////////////////
// Cross-platform warning for deprecated functions and classes
//
// @example:
// struct LAPLACE_LINK_DEPRECATED MyStruct
// {
//     ...
// };
//
// LAPLACE_LINK_DEPRECATED void global_func();
////////////////////////////////////////////////////////////
#if defined(LAPLACE_LINK_NO_DEPRECATED_WARNINGS)

    // User explicitly requests to disable deprecation warnings
    #define LAPLACE_LINK_DEPRECATED

#elif defined(_MSC_VER)

    // Microsoft C++ compiler
    // Note: On newer MSVC versions, using deprecated functions causes a compiler error. In order to
    // trigger a warning instead of an error, the compiler flag /sdl- (instead of /sdl) must be specified.
    #define LAPLACE_LINK_DEPRECATED __declspec(deprecated)

#elif defined(__GNUC__)

    // g++ and Clang
    #define LAPLACE_LINK_DEPRECATED __attribute__ ((deprecated))

#else

    // Other compilers are not supported, leave class or function as-is.
    // With a bit of luck, the #pragma directive works, otherwise users get a warning (no error!) for unrecognized #pragma.
    #pragma message("LAPLACE_LINK_DEPRECATED is not supported for your compiler, please contact the LAPLACE_LINK team")
    #define LAPLACE_LINK_DEPRECATED

#endif

#endif /* !LAPLACE_LINK_CONFIG_H_ */

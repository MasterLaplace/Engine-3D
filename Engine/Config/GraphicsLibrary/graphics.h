/*
** EPITECH PROJECT, 2023
** Title: Engine-3D
** Author: MasterLaplace
** Created: 2023-10-12
** File description:
** graphics
*/

#ifndef GRAPHICS_H_
    #define GRAPHICS_H_

////////////////////////////////////////////////////////////
// Define an enum for the graphics libraries
////////////////////////////////////////////////////////////
enum GraphicsLibrary {
    CSFML,
    SFML,
    SDL,
    OPENGL,
    VULKAN,
    DIRECTX
};

////////////////////////////////////////////////////////////
// Define the default graphics library
////////////////////////////////////////////////////////////
#define GRAPHICS_LIBRARY_DEFALUT CSFML

#ifndef GRAPHICS_LIBRARY
    #define GRAPHICS_LIBRARY GRAPHICS_LIBRARY_DEFALUT
#endif

////////////////////////////////////////////////////////////
// Include the appropriate header based on the enum value
////////////////////////////////////////////////////////////
#ifdef GRAPHICS_LIBRARY
    #if GRAPHICS_LIBRARY == CSFML
        #include <SFML/Graphics.h>
    #elif GRAPHICS_LIBRARY == SFML
        #include <SFML/Graphics.hpp>
    #elif GRAPHICS_LIBRARY == SDL
        #include <SDL2/SDL.h>
    #elif GRAPHICS_LIBRARY == OPENGL
        #include <GL/glew.h>
        #include <GL/gl.h>
        #include <GL/glu.h>
        #include <GLFW/glfw3.h>
    #elif GRAPHICS_LIBRARY == VULKAN
        #include <vulkan/vulkan.h>
        #include <GL/glew.h>
        #include <GLFW/glfw3.h>
    #elif GRAPHICS_LIBRARY == DIRECTX
        #include <d3d11.h>
    #else
        #error "[Config@GraphicsLibrary]: No graphics library or invalid graphics library."
    #endif
#endif

#endif /* !GRAPHICS_H_ */

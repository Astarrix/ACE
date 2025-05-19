#ifndef ACE_WINDOW_MANAGER_H
#define ACE_WINDOW_MANAGER_H
#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

#include "Commons/ACE_Box2D.h"
#include "Commons/ACE_Constants.h"

/**
 * @struct intBox2D
 * @brief A structure that represents a 2D box with integer coordinates
 * 
 * This structure is used to define rectangles for rendering and positioning
 * with integer coordinates.
 */

/**
 * @class ACE_WindowManager
 * @brief ASTARRIX CONTROL ENGINE: Window and rendering management class
 * 
 * This class provides functionality for creating and managing SDL windows,
 * renderers, and handling basic texture operations.
 */
class ACE_WindowManager
{
public:
    /**
     * @brief Constructor - initializes instance variables
     */
    ACE_WindowManager() = default;
    
    /**
     * @brief Destructor - ensures proper cleanup of resources
     */
    ~ACE_WindowManager() { CloseWindow(); }
    
    /**
     * @brief Prevent copying of this resource-managing class
     */
    ACE_WindowManager(const ACE_WindowManager&) = delete;
    ACE_WindowManager& operator=(const ACE_WindowManager&) = delete;

    /**
     * @brief Creates and initializes the SDL window
     * @return true if window creation was successful, false otherwise
     */
    bool CreateWindow();
    
    /**
     * @brief Creates a renderer for the current window
     * @return true if renderer creation was successful, false otherwise
     */
    bool CreateRenderer();

    /**
     * @brief Properly closes the window and cleans up all SDL resources
     */
    void CloseWindow();
    
    /**
     * @brief Gets the current size of the window
     * @return An intBox2D structure with the window dimensions
     */
    ACE_Box2D GetWindowSize();
    
    /**
     * @brief Gets the SDL window pointer
     * @return The current SDL window pointer
     */
    SDL_Window* GetWindow() { return gameWindow; }
    
    /**
     * @brief Gets the SDL renderer pointer
     * @return The current SDL renderer pointer
     */
    SDL_Renderer* GetRenderer() { return gameRenderer; }

    void SetWindowTitle(const char* title);
    void SetWindowSize(int width, int height);
    void SetWindowPosition(int x, int y);
private:
    static constexpr int INIT_SCREEN_HEIGHT = SCREEN_HEIGHT;  /**< Default initial screen height */
    static constexpr int INIT_SCREEN_WIDTH = SCREEN_WIDTH;  /**< Default initial screen width */

    SDL_Window* gameWindow = nullptr;       /**< Pointer to the SDL window */
    SDL_Renderer* gameRenderer = nullptr;   /**< Pointer to the SDL renderer */
};

#endif /* ACE_WINDOW_MANAGER_H */
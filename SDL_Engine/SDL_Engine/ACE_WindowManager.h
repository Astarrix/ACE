#ifndef ACE_WINDOW_MANAGER_H
#define ACE_WINDOW_MANAGER_H
#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>

/**
 * @struct intBox2D
 * @brief A structure that represents a 2D box with integer coordinates
 * 
 * This structure is used to define rectangles for rendering and positioning
 * with integer coordinates.
 */
struct intBox2D
{
public:
    int x = 0;          /**< The x-coordinate of the box */
    int y = 0;          /**< The y-coordinate of the box */
    int width = 0;      /**< The width of the box */
    int height = 0;     /**< The height of the box */
};

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
     * @brief Loads a texture from a file
     * @param path The file path to the image to load
     * @return Pointer to the created SDL_Texture or nullptr if loading failed
     */
    SDL_Texture* LoadTextureFromFile(std::string path);

    /**
     * @brief Properly closes the window and cleans up all SDL resources
     */
    void CloseWindow();
    
    /**
     * @brief Frees a texture from memory
     * @param gTexture Reference to the texture pointer to free
     */
    void FreeTexture(SDL_Texture*& gTexture);
    
    /**
     * @brief Gets the current size of the window
     * @return An intBox2D structure with the window dimensions
     */
    intBox2D GetWindowSize();
    
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
    
    /**
     * @brief Renders a texture to the current renderer
     * @param gTexture The texture to render
     * @param imageProperties The position and size of the texture to render
     */
    void Render(SDL_Texture* gTexture, intBox2D imageProperties);

private:
    static constexpr int INIT_SCREEN_HEIGHT = 720;  /**< Default initial screen height */
    static constexpr int INIT_SCREEN_WIDTH = 1280;  /**< Default initial screen width */

    SDL_Window* gameWindow = nullptr;       /**< Pointer to the SDL window */
    SDL_Renderer* gameRenderer = nullptr;   /**< Pointer to the SDL renderer */
};

#endif /* ACE_WINDOW_MANAGER_H */
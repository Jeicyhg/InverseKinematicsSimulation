// C++ Standard Libraries
#include <iostream>

#include "Math.hpp"
#include "Segment.hpp"
#include "Arm.hpp"
#include <cstdlib>
// Third Party
// #if defined(LINUX) || defined(MINGW)
#include <SDL2/SDL.h>
// #else // This works for Mac
// #include <SDL.h>
// #endif

int WIDTH = 1280;
int HEIGHT = 720;

// Helper function MICHAEL SHAW PROVIDED to draw thicker points
void DrawPointScaled(SDL_Renderer *renderer, int x, int y, size_t size = 1)
{
    for (int s = x; s < x + size; ++s)
    {
        for (int t = y; t < y + size; ++t)
        {
            SDL_RenderDrawPoint(renderer, s, t);
        }
    }
}

// Helper function MICHAEL SHAW PROVIDED to draw thicker lines
void DrawLineScaled(SDL_Renderer *renderer, int x1, int y1, int x2, int y2, size_t size = 1)
{
    for (int s = x1; s < x1 + size; ++s)
    {
        for (int t = y1; t < y1 + size; ++t)
        {
            SDL_RenderDrawLine(renderer, s, t, x2, y2);
        }
    }
}

// Entry point to program
int main(int argc, char *argv[])
{
    // Create a window data type
    // This pointer will point to the
    // window that is allocated from SDL_CreateWindow
    SDL_Window *window = nullptr;

    // Initialize the video subsystem. iF it returns less
    // than 1, then an error code will be received.
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    window = SDL_CreateWindow("C++ SDL2 Window", 20, 20, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Infinite loop for our application
    bool gameIsRunning = true;
    SDL_Event event;

    // Mouse position
    Vector2f mouse = Vector2f(0, 0);

    // Create a robot arm
    int num_segments = 5;
    int len_segment = 150;
    Arm arm = Arm(WIDTH/2, HEIGHT, len_segment, num_segments);
    
    // Setup a color for each segment of the arm
    int redArray[num_segments];
    int greenArray[num_segments];
    int blueArray[num_segments];
    
    for (int i = 0; i < num_segments; i++){
        redArray[i] = (rand() % 50)+50;
        greenArray[i] = (rand() % 200)+50;
        blueArray[i] = (rand() % 200)+50;
    }

    // Main application loop
    while (gameIsRunning)
    {
        // (1) Handle Input
        // Start our event loop
        while (SDL_PollEvent(&event) != 0)
        {
            // Handle quitting event
            if (event.type == SDL_QUIT)
            {
                gameIsRunning = false;
            }
            // ONE OF THESE TWO ELSE IF STATEMENTS NEEDS TO BE COMMENTED OUT
            //  FOR SETTING TARGET ON CLICK
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                // Update the line's starting point to the mouse position
                mouse.x = event.motion.x;
                mouse.y = event.motion.y;
            }
            
            // CAN BE USED FOR CONTINUOUS MOUSE TARGETING
            // else if (event.type == SDL_MOUSEMOTION)
            // {
            //     // Update the line's starting point to the mouse position
            //     mouse.x = event.motion.x;
            //     mouse.y = event.motion.y;
            // }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 205, 235, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        DrawPointScaled(renderer, mouse.x-5, mouse.y-5, 12);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        DrawLineScaled(renderer,mouse.x-5, mouse.y-5, mouse.x+5, mouse.y+5, 1);
        DrawLineScaled(renderer,mouse.x+5, mouse.y-5 , mouse.x-5 , mouse.y+5, 1);
        // Draw the tentacles
        arm.update(mouse.x, mouse.y);
        for (int i = 0; i < num_segments; i++){
            Vector2f a = arm.segments[i].a;
            Vector2f b = arm.segments[i].b;
            int stroke = arm.segments[i].stroke;
            SDL_SetRenderDrawColor(renderer, redArray[i],  greenArray[i],blueArray[i], SDL_ALPHA_OPAQUE);
            DrawLineScaled(renderer, a.x, a.y, b.x, b.y, stroke+3);
        }

        
        // Finally show what we've drawn
        SDL_RenderPresent(renderer);
    }

    // We destroy our window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // our program.
    SDL_Quit();
    return 0;
}

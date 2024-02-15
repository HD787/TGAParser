#include <SDL.h>
#include <string.h>
#include "TGAloader.h"

int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    char* path = argv[1];
    //hardcoding option
    //rgbArray* vals = load();
    rgbArray* vals = load(path);  
    SDL_Window* window;    

    if (vals->height > 2000){
    window = SDL_CreateWindow("Display Image",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                1000, 700, 0);
    }else
    window = SDL_CreateWindow("Display Image",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                vals->width, vals->height, 0);
   
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int format;
    if(vals->stride == 3) format = SDL_PIXELFORMAT_RGB24;
    else format = SDL_PIXELFORMAT_RGBA32;
    
    SDL_Texture* texture = SDL_CreateTexture(renderer,
                                             format, SDL_TEXTUREACCESS_STREAMING,
                                             vals->width, vals->height);
    if(!texture){printf("%s", SDL_GetError()); return 0;}

    SDL_UpdateTexture(texture, NULL, vals->values, vals->width * vals->stride);

    int quit = 0;
    SDL_Event e;
    while(!quit){
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        SDL_UpdateTexture(texture, NULL, vals->values, vals->width * vals->stride);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }
    free(vals->values);
    free(vals);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
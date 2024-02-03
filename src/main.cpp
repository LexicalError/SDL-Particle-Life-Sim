#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <vector>
#include "particle.h"
#include "color.h"

int WIDTH = 800;
int HEIGHT = 600;
float SCALE = 2;
double DELTAT = 1;
double GLOBALMODIFIER = 0.045;

void initParticles(std::vector<Particle> *particles, Color color, int count, int id){
    for(int i = 0; i < count; i++){
        int randX = abs(rand() % WIDTH) / SCALE;
        int randY = abs(rand() % HEIGHT) / SCALE;
        // int randSpeedX = abs(rand() % 10) / SCALE;
        // int randSpeedY = abs(rand() % 10) / SCALE;
        Particle temp = {{randX, randY}, {0, 0}, color, id};
        std::cout << randX << " " << randY << "\n";
        (*particles).push_back(temp);
    }
    return;
}

void resetParticles(std::vector<Particle> *particles){
    (*particles).clear();
    initParticles(particles, {255, 255, 255}, 200, 0);
    initParticles(particles, {255, 100, 0}, 200, 1);
    initParticles(particles, {0, 100, 200}, 600, 2);
    initParticles(particles, {100, 200, 150}, 200, 3);
    initParticles(particles, {150, 50, 170}, 300, 4);
    initParticles(particles, {200, 130, 170}, 200, 5);
    return;
}

int main(int argc, char **argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
    SDL_RenderSetScale(renderer, SCALE, SCALE);

    std::vector<Particle> particles;
    resetParticles(&particles);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
    SDL_RenderClear(renderer);
    
    float ATable[6][6] = {{1, 1.5, 1, 0.7, 1.7, 0.7},
                          {1, 0.7, 0.7, 0.8, 1.7, 1.5},
                          {0.6, 0.7, 1.5, 0.3, 1.3, 0.8},
                          {0.7, 0.6, 1, 1.5, 1.2, 1},
                          {1.2, 0.6, 1.5, 1, 0.5, 1.2},
                          {1, 0.7, 1.3, 0.6, 1.2, 0.7}};
    int signTable[6][6] = {{1, 1, -1, 1, 1, 1},
                           {1, 1, -1, 1, -1, 1},
                           {-1, -1, 1, 1, 1, 1},
                           {1, 1, -1, 1, 1, 1},
                           {1, 1, 1, -1, 1, -1},
                           {1, -1, -1, 1, -1, -1}};
    // for(int i = 1; i < 5; i++)
    //     for(int j = 0; j < i; j++)
    //         ATable[i][j] = ATable[j][i];


    bool isRunning = true;
    SDL_Event event;
    while(isRunning){
        int width, height;
        SDL_GetWindowSize(window, &width, &height);
        if(height != HEIGHT)
            HEIGHT = height;
        if(width != WIDTH)
            WIDTH = width;
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isRunning = false;
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_r)
                    resetParticles(&particles);
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
        int partcleCount = particles.size();
        for(int i = 0; i < partcleCount; i++){
            for(int j = 0; j < partcleCount; j++)
                if(i != j){
                    int id1 = particles[i].getId();
                    int id2 = particles[j].getId();
                    particles[i].update(&particles[j], GLOBALMODIFIER * ATable[id1][id2], 45, 2, 4, signTable[id1][id2], DELTAT);
                }
            particles[i].move(WIDTH / SCALE, HEIGHT / SCALE, DELTAT, 0.5);
            SDL_SetRenderDrawColor(renderer, particles[i].getColor().R, particles[i].getColor().G, particles[i].getColor().B, 100);
            SDL_RenderDrawPointF(renderer, particles[i].getPos().x, particles[i].getPos().y);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
/*
preset one:
float GTable[5][5] = {{0.6, 0.4, 0.5, 0.8, 1},
                          {0, 1, 1.4, 0.3, 1},
                          {0, 0, 0.8, 0.6, 1},
                          {0, 0, 0, 1, 20},
                          {0, 0, 0, 0, 1}};
int signTable[5][5] = {{1, 1, 1, -1, -1},
                        {0, -1, 1, 1, -1},
                        {0, 0, 1, -1, 1},
                        {0, 0, 0, -1, 1},
                        {0, 0, 0, 0, -1}};

*/
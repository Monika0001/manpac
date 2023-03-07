#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <gif_lib.h>

#pragma comment(lib,"winmm.lib")

#define TICK_INTERVAL 10




// Screen
const int SCREEN_WIDTH = 896;
const int SCREEN_HEIGHT = 992;
const int TILE_SIZE = 16;

// Map
const int MAP_WIDTH = 56;
const int MAP_HEIGHT = 62;

// Wall and pellets
SDL_Texture* wallTexture = NULL;
SDL_Texture* dotTexture = NULL;
SDL_Texture* powerPelletTexture = NULL;

// Pacman
SDL_Texture* pacManTexture = NULL;
SDL_Texture* pacRight = NULL;
SDL_Texture* pacLeft = NULL;
SDL_Texture* pacUp = NULL;
SDL_Texture* pacDown = NULL;

SDL_Texture* buffRight = NULL;
SDL_Texture* buffLeft = NULL;
SDL_Texture* buffUp = NULL;
SDL_Texture* buffDown = NULL;

SDL_Texture* fire = NULL;
SDL_Texture* markWall = NULL;
int pacManX = TILE_SIZE * 1;
int pacManY = TILE_SIZE * 1;
int eatv = 0;
bool buffCheck = false;

// Ghost 1
SDL_Texture* ghostTexture1 = NULL;
int ghostX1 = TILE_SIZE * 1;
int ghostY1 = TILE_SIZE * 1;
int pM1 = 0;

// Ghost 2
SDL_Texture* ghostTexture2 = NULL;
int ghostX2 = TILE_SIZE * 1;
int ghostY2 = TILE_SIZE * 1;
int pM2 = 0;

// Ghost 3
SDL_Texture* ghostTexture3 = NULL;
int ghostX3 = TILE_SIZE * 1;
int ghostY3 = TILE_SIZE * 1;
int pM3 = 0;

// Ghost 4
SDL_Texture* ghostTexture4 = NULL;
int ghostX4 = TILE_SIZE * 1;
int ghostY4 = TILE_SIZE * 1;
int pM4 = 0;

// Map layout
int map[MAP_HEIGHT][MAP_WIDTH] = {
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
{2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,},
{2,4,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,0,8,4,8,0,0,2,2,4,8,0,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,4,8,0,0,2,},
{2,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,2,2,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0,2,},
{2,4,8,0,0,0,0,0,0,0,0,4,8,0,0,0,0,0,0,0,0,0,0,4,8,0,0,2,2,4,8,0,0,0,0,0,0,0,0,0,0,4,8,0,0,0,0,0,0,0,0,4,8,0,0,2,},
{2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,},
{2,4,5,0,0,2,2,2,2,2,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,2,2,2,2,2,4,5,0,0,2,},
{2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,},
{2,4,8,0,0,2,2,2,2,2,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,2,2,2,2,2,4,8,0,0,2,},
{2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,},
{2,4,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,4,8,0,0,2,},
{2,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0,2,},
{2,4,8,0,0,0,0,0,0,0,0,4,8,0,0,0,0,4,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,0,0,0,0,4,8,0,0,0,0,0,0,0,0,4,8,0,0,2,},
{2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,},
{2,4,8,0,0,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,4,8,0,0,2,},
{2,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,},
{2,0,8,0,8,0,8,0,8,0,8,4,8,0,0,2,2,0,8,0,8,0,8,4,8,0,0,2,2,4,8,0,8,0,8,0,8,0,0,2,2,4,8,0,8,0,8,0,8,0,8,0,8,0,0,2,},
{2,0,0,0,0,0,0,0,0,0,0,4,0,0,0,2,2,0,0,0,0,0,0,4,0,0,0,2,2,4,0,0,0,0,0,0,0,0,0,2,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
{2,0,0,0,0,0,0,0,0,0,0,4,8,0,0,2,2,0,0,0,0,0,0,4,8,0,0,2,2,4,8,0,0,0,0,0,0,0,0,2,2,4,8,0,0,0,0,0,0,0,0,0,0,0,0,2,},
{2,2,2,2,2,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,2,2,2,2,2,},
{0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,2,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,2,2,4,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,4,8,0,0,2,2,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,2,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,2,2,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,2,2,4,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,0,0,2,2,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,},
{9,9,9,9,9,9,9,9,9,9,9,4,4,4,4,4,4,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,4,4,4,4,4,4,4,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
{8,0,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,4,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,0,8,0,8,0,},
{0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,0,4,8,0,0,0,0,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,0,0,4,8,0,0,0,0,0,0,0,0,0,0,0,0,0,},
{2,2,2,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,2,2,2,},
{0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,2,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,2,2,4,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,4,8,0,0,2,2,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,2,2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,2,2,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,8,0,0,2,2,4,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,0,0,2,2,4,8,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{0,0,0,0,0,0,0,0,0,0,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,0,0,0,0,0,0,0,0,0,0,},
{2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,},
{2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,},
{2,4,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,0,8,4,8,0,0,2,2,4,8,0,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,4,8,0,0,2,},
{2,4,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,2,2,4,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,0,0,0,2,},
{2,4,8,0,0,0,0,0,0,0,0,4,8,0,0,0,0,0,0,0,0,0,0,4,8,0,0,2,2,4,8,0,0,0,0,0,0,0,0,0,0,4,8,0,0,0,0,0,0,0,0,4,8,0,0,2,},
{2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,4,0,0,0,2,2,2,2,2,2,4,0,0,0,2,},
{2,4,8,0,0,2,2,2,2,2,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,4,8,0,0,2,2,2,2,2,2,4,8,0,0,2,},
{2,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,0,0,0,2,},
{2,0,5,0,8,4,8,0,0,2,2,4,8,0,8,0,8,4,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,4,8,0,8,0,8,4,8,0,0,2,2,4,8,0,8,0,5,0,0,2,},
{2,0,0,0,0,4,0,0,0,2,2,4,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,2,2,4,0,0,0,0,0,0,0,2,},
{2,0,0,0,0,4,8,0,0,2,2,4,8,0,0,0,0,4,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,8,0,0,0,0,4,8,0,0,2,2,4,8,0,0,0,0,0,0,2,},
{2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,},
{2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,},
{2,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,0,0,0,2,2,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,},
{2,4,8,0,8,0,8,0,8,0,8,0,8,0,0,2,2,0,8,0,8,0,8,4,8,0,0,2,2,4,8,0,8,0,8,0,8,0,0,2,2,0,8,0,8,0,8,0,8,0,8,4,8,0,0,2,},
{2,4,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,4,0,0,0,2,2,4,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,4,0,0,0,2,},
{2,4,8,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,4,8,0,0,2,2,4,8,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,4,8,0,0,2,},
{2,4,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,0,0,2,2,4,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,0,0,0,2,},
{2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,2,4,8,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,8,0,0,2,},
{2,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,2,},
{2,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,8,0,0,2,},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,},
{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,} };


void drawMap(SDL_Renderer* renderer)
{
	// Walls, pellets, power pellets, pacman, ghosts
	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (map[y][x] == 2) {
				SDL_Rect wallRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				SDL_RenderCopy(renderer, wallTexture, NULL, &wallRect);
			}
			else if (map[y][x] == 7) {
				//SDL_Rect wallmRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
				//SDL_RenderCopy(renderer, markWall, NULL, &wallmRect);
			}
			else if (map[y][x] == 8) {
				SDL_Rect dotRect = { x * TILE_SIZE + TILE_SIZE / 2 - 2, y * TILE_SIZE + TILE_SIZE / 2 - 2, 20, 20 };
				SDL_RenderCopy(renderer, dotTexture, NULL, &dotRect);
			}
			else if (map[y][x] == 5) {
				SDL_Rect powerPelletRect = { x * TILE_SIZE + TILE_SIZE / 2 - 8, y * TILE_SIZE + TILE_SIZE / 2 - 8, 16 * 2, 16 * 2 };
				SDL_RenderCopy(renderer, powerPelletTexture, NULL, &powerPelletRect);
			}
		}
	}
	SDL_Rect pacManRect = { pacManX + 8, pacManY + 8, TILE_SIZE * 3, TILE_SIZE * 3};
	SDL_RenderCopy(renderer, pacManTexture, NULL, &pacManRect);

	SDL_Rect ghostRect1 = { ghostX1 + 8, ghostY1 + 8, TILE_SIZE * 3, TILE_SIZE * 3 };
	SDL_RenderCopy(renderer, ghostTexture1, NULL, &ghostRect1);
	SDL_Rect ghostRect2 = { ghostX2 + 8, ghostY2 + 8, TILE_SIZE * 3, TILE_SIZE * 3 };
	SDL_RenderCopy(renderer, ghostTexture1, NULL, &ghostRect2);
	SDL_Rect ghostRect3 = { ghostX3 + 8, ghostY3 + 8, TILE_SIZE * 3, TILE_SIZE * 3 };
	SDL_RenderCopy(renderer, ghostTexture1, NULL, &ghostRect3);
	SDL_Rect ghostRect4 = { ghostX4 + 8, ghostY4 + 8, TILE_SIZE * 3, TILE_SIZE * 3 };
	SDL_RenderCopy(renderer, ghostTexture1, NULL, &ghostRect4);
}

void screenUpdate(SDL_Renderer* renderer) {
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Draw map
	drawMap(renderer);

	// Update screen
	SDL_RenderPresent(renderer);
}


int main(int argc, char* args[])
{


	SDL_Init(SDL_INIT_AUDIO);


	//Eat 1
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	//Eat 2
	SDL_AudioSpec wavSpec1;
	Uint32 wavLength1;
	Uint8* wavBuffer1;

	//Eat Pellet
	SDL_AudioSpec wavSpec2;
	Uint32 wavLength2;
	Uint8* wavBuffer2;

	SDL_LoadWAV("assets/player/munch_1.wav", &wavSpec, &wavBuffer, &wavLength);
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	SDL_LoadWAV("assets/player/munch_2.wav", &wavSpec1, &wavBuffer1, &wavLength1);
	SDL_AudioDeviceID deviceId1 = SDL_OpenAudioDevice(NULL, 0, &wavSpec1, NULL, 0);

	

	
	SDL_Window* window = NULL;

	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Pac-Man", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{

			// Load icon
			SDL_Surface* icon = IMG_Load("assets/icon.png");
			if (icon == NULL) {
				std::cout << "Icon could not be loaded! SDL_Error: " << SDL_GetError() << std::endl;
				printf("no icon lol");
			}
			else {
				SDL_SetWindowIcon(window, icon);
				SDL_FreeSurface(icon);
			}





			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill surface
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update surface
			SDL_UpdateWindowSurface(window);
		}

		// Create renderer
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}



		// Load textures
		wallTexture = IMG_LoadTexture(renderer, "assets/wall.png");
		if (wallTexture == NULL) {
			std::cout << "Could not load wall texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		dotTexture = IMG_LoadTexture(renderer, "assets/dot.png");
		if (dotTexture == NULL) {
			std::cout << "Could not load dot texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		powerPelletTexture = IMG_LoadTexture(renderer, "assets/power_pellet.png");
		if (powerPelletTexture == NULL) {
			std::cout << "Could not load power pellet texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		pacRight = IMG_LoadTexture(renderer, "assets/player/pac_right.png");
		if (pacRight == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		pacLeft = IMG_LoadTexture(renderer, "assets/player/pac_left.png");
		if (pacLeft == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		pacUp = IMG_LoadTexture(renderer, "assets/player/pac_up.png");
		if (pacUp == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		pacDown = IMG_LoadTexture(renderer, "assets/player/pac_down.png");
		if (pacDown == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		buffRight = IMG_LoadTexture(renderer, "assets/player/buff_right.png");
		if (pacRight == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		buffLeft = IMG_LoadTexture(renderer, "assets/player/buff_left.png");
		if (pacLeft == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		buffUp = IMG_LoadTexture(renderer, "assets/player/buff_up.png");
		if (pacUp == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		buffDown = IMG_LoadTexture(renderer, "assets/player/buff_down.png");
		if (pacDown == NULL) {
			std::cout << "Could not load Pac-Man texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		markWall = IMG_LoadTexture(renderer, "assets/wallm.png");
		if (markWall == NULL) {
			std::cout << "Could not load wall mark texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}
		pacManTexture = pacRight;

		ghostTexture1 = IMG_LoadTexture(renderer, "assets/player/ghost.png");
		if (ghostTexture1 == NULL) {
			std::cout << "Could not load ghost texture! SDL_Error: " << SDL_GetError() << std::endl;
			return 1;
		}

		const Uint8* keys = SDL_GetKeyboardState(NULL);

		// Key states
		bool upKeyHeld = false;
		bool downKeyHeld = false;
		bool leftKeyHeld = false;
		bool rightKeyHeld = false;
		bool rKeyHeld = false;

		// Timer
		Uint32 tickInterval = SDL_GetTicks() + TICK_INTERVAL;

		// Game loop
		bool quit = false;
		SDL_Event event;
		while (!quit) {
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT) {
					quit = true;
				}
				else if (event.type == SDL_KEYDOWN) {
					
					switch (event.key.keysym.sym) {
					case SDLK_UP:
						upKeyHeld = true;
						break;
					case SDLK_DOWN:
						downKeyHeld = true;
						break;
					case SDLK_LEFT:
						leftKeyHeld = true;
						break;
					case SDLK_RIGHT:
						rightKeyHeld = true;
						break;
					case SDLK_r:
						rKeyHeld = true;
						break;
					}
				}
				else if (event.type == SDL_KEYUP) {
					switch (event.key.keysym.sym) {
					case SDLK_UP:
						upKeyHeld = false;
						break;
					case SDLK_DOWN:
						downKeyHeld = false;
						break;
					case SDLK_LEFT:
						leftKeyHeld = false;
						break;
					case SDLK_RIGHT:
						rightKeyHeld = false;
						break;
					case SDLK_r:
						rKeyHeld = false;
						break;
					}
				}

				}

			// Handle key states
			Uint32 ticks = SDL_GetTicks();
			if (ticks >= tickInterval) {
				tickInterval = ticks + TICK_INTERVAL;
				//printf("x = %d, y = %d, pellet state = %d, xg = %d, yg = %d, xst = %d\n", pacManX, pacManY, map[6][2], pacManX / 16, pacManY / 16, map[(pacManY / 16)][(pacManX / 16)]);
				
				// Ghost 1 position
				bool rightM1 = false;
				bool leftM1 = false;
				bool upM1 = false;
				bool downM1 = false;
				int xg1 = ghostX1 / 16;
				int yg1 = ghostY1 / 16;

				if (map[yg1 - 1][xg1] != 4) {
					upM1 = false;
				}
				else if (pM1 == 2) {
					upM1 = false;
				}
				else {
					upM1 = true;
				}

				if (map[yg1 + 1][xg1] != 4) {
					downM1 = false;
				}
				else if (pM1 == 1) {
					downM1 = false;
				}
				else {
					downM1 = true;
				}

				if (map[yg1][xg1 - 1] != 4) {
					leftM1 = false;
				}
				else if (pM1 == 4) {
					leftM1 = false;
				}
				else {
					leftM1 = true;
				}

				if (map[yg1][xg1 + 1] != 4) {
					rightM1 = false;
				}
				else if (pM1 == 3) {
					rightM1 = false;
				}
				else {
					rightM1 = true;
				}
				int movement = 0;
				while (movement == 0) {
					int randN = rand() % 4 + 1;
					printf("%d", randN);
					if (randN == 1) {
						if (upM1 == false) {
							printf("r");
						}
						else {
							movement = 1;
						}
					}
					else if (randN == 2) {
						if (downM1 == false) {
							printf("r");
						}
						else {
							movement = 2;
						}
					}
					else if (randN == 3) {
						if (leftM1 == false) {
							printf("r");
						}
						else {
							movement = 3;
						}
					}
					else if (randN == 4) {
						if (rightM1 == false) {
							printf("r");
						}
						else {
							movement = 4;
						}
					}
				}
				printf("\n");

				if (movement == 1) {
					ghostY1 -= 32;
				}
				else if (movement == 2) {
					ghostY1 += 32;
				}
				else if (movement == 3) {
					ghostX1 -= 32;
				}
				else if (movement == 4) {
					ghostX1 += 32;
				}
				pM1 = movement;
				movement = 0;


				// Ghost 2 position
				bool rightM2 = false;
				bool leftM2 = false;
				bool upM2 = false;
				bool downM2 = false;
				int xg2 = ghostX2 / 16;
				int yg2 = ghostY2 / 16;

				if (map[yg2 - 1][xg2] != 4) {
					upM2 = false;
				}
				else if (pM2 == 2) {
					upM2 = false;
				}
				else {
					upM2 = true;
				}

				if (map[yg2 + 1][xg2] != 4) {
					downM2 = false;
				}
				else if (pM2 == 1) {
					downM2 = false;
				}
				else {
					downM2 = true;
				}

				if (map[yg2][xg2 - 1] != 4) {
					leftM2 = false;
				}
				else if (pM2 == 4) {
					leftM2 = false;
				}
				else {
					leftM2 = true;
				}

				if (map[yg2][xg2 + 1] != 4) {
					rightM2 = false;
				}
				else if (pM2 == 3) {
					rightM2 = false;
				}
				else {
					rightM2 = true;
				}

				while (movement == 0) {
					int randN = rand() % 4 + 1;
					printf("%d", randN);
					if (randN == 1) {
						if (upM2 == false) {
							printf("r");
						}
						else {
							movement = 1;
						}
					}
					else if (randN == 2) {
						if (downM2 == false) {
							printf("r");
						}
						else {
							movement = 2;
						}
					}
					else if (randN == 3) {
						if (leftM2 == false) {
							printf("r");
						}
						else {
							movement = 3;
						}
					}
					else if (randN == 4) {
						if (rightM2 == false) {
							printf("r");
						}
						else {
							movement = 4;
						}
					}
				}
				printf("\n");

				if (movement == 1) {
					ghostY2 -= 32;
				}
				else if (movement == 2) {
					ghostY2 += 32;
				}
				else if (movement == 3) {
					ghostX2 -= 32;
				}
				else if (movement == 4) {
					ghostX2 += 32;
				}
				pM2 = movement;
				movement = 0;


				// Ghost 3 position
				bool rightM3 = false;
				bool leftM3 = false;
				bool upM3 = false;
				bool downM3 = false;
				int xg3 = ghostX3 / 16;
				int yg3 = ghostY3 / 16;

				if (map[yg3 - 1][xg3] != 4) {
					upM3 = false;
				}
				else if (pM3 == 2) {
					upM3 = false;
				}
				else {
					upM3 = true;
				}

				if (map[yg3 + 1][xg3] != 4) {
					downM3 = false;
				}
				else if (pM3 == 1) {
					downM3 = false;
				}
				else {
					downM3 = true;
				}

				if (map[yg3][xg3 - 1] != 4) {
					leftM3 = false;
				}
				else if (pM3 == 4) {
					leftM3 = false;
				}
				else {
					leftM3 = true;
				}

				if (map[yg3][xg3 + 1] != 4) {
					rightM3 = false;
				}
				else if (pM3 == 3) {
					rightM3 = false;
				}
				else {
					rightM3 = true;
				}

				while (movement == 0) {
					int randN = rand() % 4 + 1;
					printf("%d", randN);
					if (randN == 1) {
						if (upM3 == false) {
							printf("r");
						}
						else {
							movement = 1;
						}
					}
					else if (randN == 2) {
						if (downM3 == false) {
							printf("r");
						}
						else {
							movement = 2;
						}
					}
					else if (randN == 3) {
						if (leftM3 == false) {
							printf("r");
						}
						else {
							movement = 3;
						}
					}
					else if (randN == 4) {
						if (rightM3 == false) {
							printf("r");
						}
						else {
							movement = 4;
						}
					}
				}
				printf("\n");

				if (movement == 1) {
					ghostY3 -= 32;
				}
				else if (movement == 2) {
					ghostY3 += 32;
				}
				else if (movement == 3) {
					ghostX3 -= 32;
				}
				else if (movement == 4) {
					ghostX3 += 32;
				}
				pM3 = movement;
				movement = 0;


				// Ghost 4 position
				bool rightM4 = false;
				bool leftM4 = false;
				bool upM4 = false;
				bool downM4 = false;
				int xg4 = ghostX4 / 16;
				int yg4 = ghostY4 / 16;

				if (map[yg4 - 1][xg4] != 4) {
					upM4 = false;
				}
				else if (pM4 == 2) {
					upM4 = false;
				}
				else {
					upM4 = true;
				}

				if (map[yg4 + 1][xg4] != 4) {
					downM4 = false;
				}
				else if (pM4 == 1) {
					downM4 = false;
				}
				else {
					downM4 = true;
				}

				if (map[yg4][xg4 - 1] != 4) {
					leftM4 = false;
				}
				else if (pM4 == 4) {
					leftM4 = false;
				}
				else {
					leftM4 = true;
				}

				if (map[yg4][xg4 + 1] != 4) {
					rightM4 = false;
				}
				else if (pM4 == 3) {
					rightM4 = false;
				}
				else {
					rightM4 = true;
				}

				while (movement == 0) {
					int randN = rand() % 4 + 1;
					printf("%d", randN);
					if (randN == 1) {
						if (upM4 == false) {
							printf("r");
						}
						else {
							movement = 1;
						}
					}
					else if (randN == 2) {
						if (downM4 == false) {
							printf("r");
						}
						else {
							movement = 2;
						}
					}
					else if (randN == 3) {
						if (leftM4 == false) {
							printf("r");
						}
						else {
							movement = 3;
						}
					}
					else if (randN == 4) {
						if (rightM4 == false) {
							printf("r");
						}
						else {
							movement = 4;
						}
					}
				}
				printf("\n");

				if (movement == 1) {
					ghostY4 -= 32;
				}
				else if (movement == 2) {
					ghostY4 += 32;
				}
				else if (movement == 3) {
					ghostX4 -= 32;
				}
				else if (movement == 4) {
					ghostX4 += 32;
				}
				pM4 = movement;
				movement = 0;
				
				
				
				
				
				int xc = pacManX / 16;
				int yc = pacManY / 16;
				if (rKeyHeld) {
					pacManX = 16;
					pacManY = 16;
				}
				if (upKeyHeld) {
					if (map[yc - 1][xc] != 4) {
						printf("no");
						SDL_Delay(160);
					}
					else {
						for (int i = 0; i < 32; i++) {
							if (buffCheck) {
								pacManTexture = buffUp;
							}
							else {
								pacManTexture = pacUp;
							}
							pacManY--;
							SDL_Delay(5);

							screenUpdate(renderer);
						}
					}
				}
				else if (downKeyHeld) {
					if (map[yc + 1][xc] != 4) {
						printf("no");
						SDL_Delay(160);
					}
					else {
						for (int i = 0; i < 32; i++) {
							if (buffCheck) {
								pacManTexture = buffDown;
							}
							else {
								pacManTexture = pacDown;
							}
							pacManY++;
							SDL_Delay(5);

							screenUpdate(renderer);
						}
					}
				}
				else if (leftKeyHeld) {
					if (map[yc][xc - 1] != 4) {
						printf("no");
						SDL_Delay(160);
					}
					else {
						for (int i = 0; i < 32; i++) {
							if (buffCheck) {
								pacManTexture = buffLeft;
							}
							else {
								pacManTexture = pacLeft;
							}
							pacManX--;
							SDL_Delay(5);

							screenUpdate(renderer);
						}
					}
				}
				else if (rightKeyHeld) {
					if (map[yc][xc + 1] != 4) {
						printf("no");
						SDL_Delay(160);
					}
					else {
						for (int i = 0; i < 32; i++) {
							if (buffCheck) {
								pacManTexture = buffRight;
							}
							else {
								pacManTexture = pacRight;
							}
							pacManX++;
							SDL_Delay(5);

							screenUpdate(renderer);
						}
					}
				}
				else {
					SDL_Delay(160);
				}
				if (map[yc + 1][xc + 1] == 5 || map[yc + 1][xc + 1] == 8) {
					if (map[yc + 1][xc + 1] == 5) {
						map[yc + 1][xc + 1] = 0;
						SDL_LoadWAV("assets/player/eat2.wav", &wavSpec2, &wavBuffer2, &wavLength2);
						SDL_AudioDeviceID deviceId2 = SDL_OpenAudioDevice(NULL, 0, &wavSpec2, NULL, 0);
						int success = SDL_QueueAudio(deviceId2, wavBuffer2, wavLength2);
						SDL_PauseAudioDevice(deviceId2, 0);
						int tempX = pacManX;
						int tempY = pacManY;
						for (int s = 0; s < 30; s++) {
							int randN = rand() % 9 - 4;
							int randN2 = rand() % 9 - 4;
							pacManX = tempX + randN;
							pacManY = tempY + randN2;
							screenUpdate(renderer);
							Sleep(100);
						}
						buffCheck = true;
						pacManX = tempX;
						pacManY = tempY;
						SDL_CloseAudioDevice(deviceId2);
						SDL_FreeWAV(wavBuffer2);
					}
					else if (map[yc + 1][xc + 1] == 8) {
						map[yc + 1][xc + 1] = 0;
						if (eatv % 2 == 0) {
							int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
							SDL_PauseAudioDevice(deviceId, 0);
							eatv++;
						}
						else {
							int success = SDL_QueueAudio(deviceId1, wavBuffer1, wavLength1);
							SDL_PauseAudioDevice(deviceId1, 0);
							eatv++;
						}
						
					}

					
				}
			}

			

				// Clear screen
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);

				// Draw map
				drawMap(renderer);

				// Update screen
				SDL_RenderPresent(renderer);
			}


		}

		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer);
		SDL_CloseAudioDevice(deviceId1);
		SDL_FreeWAV(wavBuffer1);

		

		//Destroy window
		SDL_DestroyWindow(window);

		//Quit SDL
		SDL_Quit();

		return 0;
	}

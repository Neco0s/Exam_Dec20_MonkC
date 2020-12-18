#pragma once
#include "Structures.h"

//Initialisation (Init.cpp)
void init(int map[map_height][map_width], t_entity* pisteurs, t_entity* monk, int n_pisteurs, t_img* images, SDL_Window* window, SDL_Renderer* renderer);
void place_pisteur(int index, t_entity* pisteurs);
void place_monk(int map[map_height][map_width], t_entity* monk, t_entity* pisteurs, int n_pisteurs);

//Tour du joueur (Player_Turn.cpp)
void manage_pisteur(int map[map_height][map_width], int index, t_entity* monk, t_entity* pisteurs, int n_pisteurs, t_img* images, SDL_Window* window, SDL_Renderer* renderer);
void move_pisteur(int map[map_height][map_width], int index, t_entity* pisteurs, int n_pisteurs);

//Tour du monk (Monk_Turn.cpp)
int monk_target(t_entity* pisteurs, t_entity monk, int n_pisteurs, int target);
void move_monk(int map[map_height][map_width], t_entity* monk, t_entity* pisteurs, int n_pisteurs, int target);
void update_leads(int map[map_height][map_width], t_entity* monk);

//Affichage de la map (Display.cpp)
void SDL_display(int map[map_height][map_width], t_img* images, SDL_Window* window, SDL_Renderer* renderer, t_entity monk, t_entity* pisteurs, int n_pisteurs);

void display_game(int map[map_height][map_width], t_entity monk, t_entity* pisteurs, int n_pisteurs);

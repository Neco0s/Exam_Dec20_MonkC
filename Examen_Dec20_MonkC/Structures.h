#pragma once
#include "Libraries.h"

#define map_height 14
#define map_width 29
#define map_border 100

typedef struct s_img {
	SDL_Texture* texture;
	SDL_Rect rect;
	SDL_Rect copy;
	char name[20];
}t_img;

typedef struct s_entity {
	int x;
	int y;
	int hp;
	int state;
}t_entity;
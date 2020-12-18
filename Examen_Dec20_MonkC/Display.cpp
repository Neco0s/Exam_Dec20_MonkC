#include "Prototypes.h"

void display_game(int map[map_height][map_width], t_entity monk, t_entity* pisteurs, int n_pisteurs)
//BUT: Afficher la map sous sa forme ASCII
//ENTREE: la map sous sa forme "modèle", le monk (copie), l'adresse du premier pisteur (et par conséquent de tous les autres) et le nombre total de pisteurs
//SORTIE: -
//ENTREE UTILISATEUR: NON
{
	for (int i = 0; i < map_height; i++)
	{
		char line[map_width+1] = { NULL };
		for (int j = 0; j < map_width; j++)
		{
			int player = 0;
			for (int k = 0; k < n_pisteurs; k++)
				if (i == pisteurs[k].y && j == pisteurs[k].x && pisteurs[k].state != 0)
					//Vérification de la présence d'un pisteur à l'emplacement indiqué
				{
					player = 1;
					if (pisteurs[k].state == 3) //Forme "rapport"
						line[j] = '!';
					else if (pisteurs[k].state == 2) //Forme "attente"
						line[j] = '?';
					else if (pisteurs[k].state == 1) //Forme "position"
						line[j] = 'P';
					else //Erreur dans le code
						line[j] = 'E';
				}
			if (player == 0)
			{
				if (map[i][j] == map_border)
					line[j] = '*';
				else if (map[i][j] == 15)
				{
					if (monk.state > 1) //Dernier endroit où le monk a séjourné, visible si le monk est blessé
						line[j] = '.';
					else
						line[j] = ' ';
				}
				else
				{
					if (player == 0)
						line[j] = ' ';
				}
			}
		}
		printf("%s\n", line); //Fin de la ligne de la map
	}
}

void SDL_display(int map[map_height][map_width], t_img* images, SDL_Window* window, SDL_Renderer* renderer, t_entity monk, t_entity* pisteurs, int n_pisteurs)
//BUT: Afficher sous SDL la map du jeu
//ENTREE: la map sous sa forme "modèle", l'ensemble des images créées, la fenêtre d'affichage, le renderer, le monk, l'adresse du premier pisteur (et par conséquent de tous les autres) et le nombre total de pisteurs
//SORTIE: -
//ENTREE UTILISATEUR: NON
{
	for (int i = 0; i < n_pisteurs; i++)
	{
		images[i + 2].rect.x = (pisteurs[i].state - 1) * images[i + 2].rect.h;
		images[i + 2].copy.x = 235 + pisteurs[i].x * images[i + 2].copy.w;
		images[i + 2].copy.y = 50 + pisteurs[i].y * images[i + 2].copy.h;
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (map[monk.y + i - 1][monk.x + j - 1] == 15)
			{
				images[1].copy.x = 235 + (monk.x + j - 1) * images[1].copy.w;
				images[1].copy.y = 50 + (monk.y + i - 1) * images[1].copy.h;
			}
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderCopy(renderer, images[0].texture, &images[0].rect, &images[0].copy);
	if (monk.state > 1)
		SDL_RenderCopy(renderer, images[1].texture, &images[1].rect, &images[1].copy);
	for (int i = 0; i < n_pisteurs; i++)
		if (pisteurs[i].state != 0)
			SDL_RenderCopy(renderer, images[i + 2].texture, &images[i + 2].rect, &images[i + 2].copy);
	SDL_RenderPresent(renderer);
}
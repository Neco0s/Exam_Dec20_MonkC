#include "Prototypes.h"

int main(int argc, char** argv)
//BUT: Reproduire le jeu La Traque (précédemment en BASIC) en C
//ENTREE: argc et argv, non utilisés
//SORTIE: 0, toujours
//ENTREES UTILISATEUR: OUI
{
	//Initialisation des variables nécessaires pour le fonctionnement du programme
	int map[map_height][map_width] = { NULL };
	int n_pisteurs = NULL;
	int game = 1;
	int target = -1;

	HWND consoleWindow = GetConsoleWindow();
	SetWindowPos(consoleWindow, 0, -8, -31, 1936, 311, SWP_NOZORDER);

	while (n_pisteurs < 1 || n_pisteurs > 10)
	//Boucle tant que le nombre de pisteurs n'est pas dans les limites imposées
	{
		printf("Veuillez choisir le nombre de pisteurs que vous voulez. Il en faut minimum 1. Vous pouvez en avoir maximum 10.\n");
		scanf("%d", &n_pisteurs); //Entrée du nombre de pisteurs au départ par l'utilisateur
	}
	t_img* images = (t_img*)calloc(2 + n_pisteurs, sizeof(t_img));
	if (images == NULL)
	{
		printf("Memory error for the images.\n");
		game = -1;
	}
	t_entity* pisteurs = (t_entity*)calloc(n_pisteurs, sizeof(t_entity)); //Création des pisteurs avec allocation de mémoire sécurisée
	if (pisteurs == NULL)
	{
		printf("Memory error for the trackers.\n");
		game = -1;
	}
	t_entity* monk = (t_entity*)calloc(1, sizeof(t_entity)); //Création du monk, avec allocation de mémoire sécurisée
	if (monk == NULL)
	{
		printf("Memory error for the monk.\n");
		game = -1;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0 && game > 0)
	{
		SDL_Window* window = SDL_CreateWindow("LA TRAQUE", 0, 271, 1920, 800, NULL);
		SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, NULL);
		SDL_Surface* surface;

		surface = IMG_Load("Assets/Map.png");
		images[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
		images[0].rect.w = surface->w;
		images[0].rect.h = surface->h;
		images[0].copy.w = 1450;
		images[0].copy.h = 700;
		images[0].copy.x = 235;
		images[0].copy.y = 50;
		strcpy(images[0].name, "Map");

		surface = IMG_Load("Assets/Monk_blood.png");
		images[1].texture = SDL_CreateTextureFromSurface(renderer, surface);
		images[1].rect.w = surface->w;
		images[1].rect.h = surface->h;
		images[1].copy.w = 50;
		images[1].copy.h = 50;
		strcpy(images[1].name, "Lead");

		surface = IMG_Load("Assets/Pisteur.png");
		for (int i = 0; i < n_pisteurs; i++)
		{
			images[i + 2].texture = SDL_CreateTextureFromSurface(renderer, surface);
			images[i + 2].rect.w = 50;
			images[i + 2].rect.h = 50;
			images[i + 2].copy.w = 50;
			images[i + 2].copy.h = 50;
			strcpy(images[i + 2].name, "Pisteur");
		}
		init(map, pisteurs, monk, n_pisteurs, images, window, renderer); //Explications dans Init.cpp

		while (game)
		//Boucle de jeu
		{
			game = 0;
			for (int i = 0; i < n_pisteurs; i++)
			{
				system("cls");
				manage_pisteur(map, i, monk, pisteurs, n_pisteurs, images, window, renderer); //Explications dans Player_Turn.cpp
				if (pisteurs[i].state > 0) //Si un seul pisteur est vivant, la variable repassera à 1 et le jeu vérifiera le tour du monk
					game = 1;
			}
			for (int i = 0; i < n_pisteurs; i++)
				if (pisteurs[i].hp > 0 && monk->hp > 0) //Si le pisteur est mort, le jeu passera son tour
				{
					system("cls");
					pisteurs[i].state = 2;
					//display_game(map, *monk, pisteurs, n_pisteurs); //Explications dans Display.cpp
					SDL_display(map, images, window, renderer, *monk, pisteurs, n_pisteurs); //Explications dans Display.cpp
					move_pisteur(map, i, pisteurs, n_pisteurs); //Explications dans Player_Turn.cpp
				}
			if (game && monk->hp > 0) //Explications des trois fonctions dans Monk_Turn.cpp
			{
				target = monk_target(pisteurs, *monk, n_pisteurs, target);
				move_monk(map, monk, pisteurs, n_pisteurs, target);
				update_leads(map, monk);
			}
			else
				game = 0; //Si le monk est mort, le jeu s'arrête
		}

		if (game == 0)
		{
			if (monk->hp == 0)
				printf("Bravo! Vous avez vaincu le monk!\n");
			else
				printf("Tous vos pisteurs se sont fait attraper, vous avez perdu.\n");
		}
	}

	//Libération de la mémoire allouée
	free(images);
	free(pisteurs);
	free(monk);
	return 0;
}
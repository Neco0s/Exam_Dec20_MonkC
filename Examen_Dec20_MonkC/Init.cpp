#include "Prototypes.h"

void init(int map[map_height][map_width], t_entity* pisteurs, t_entity* monk, int n_pisteurs, t_img* images, SDL_Window* window, SDL_Renderer* renderer)
//BUT: initialiser le jeu (la map, les pisteurs et le monk)
//ENTREE: la map sous sa forme "modèle", l'adresse du premier pisteur (et par conséquent de tous les autres), l'adresse du monk et le nombre de pisteurs
//SORTIE: -
//ENTREES UTILISATEUR: NON
{
	srand(time(NULL));
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
		{
			if (i == 0 || i == map_height - 1 || j == 0 || j == map_width - 1)
				map[i][j] = map_border; //Bords de la map
			else
				map[i][j] = 0; //Intérieur de la map
		}
	for (int i = 0; i < n_pisteurs; i++) //Initialisation des pisteurs dans cette boucle
	{
		system("cls");
		//display_game(map, *monk, pisteurs, n_pisteurs); //Explications dans display.cpp
		SDL_display(map, images, window, renderer, *monk, pisteurs, n_pisteurs); //Explications dans display.cpp
		place_pisteur(i, pisteurs); //Initialisation d'un pisteur
	}
	place_monk(map, monk, pisteurs, n_pisteurs); //Initialisation du monk
}

void place_pisteur(int index, t_entity* pisteurs)
//BUT: Positionner un pisteur
//ENTREE: L'adresse du premier pisteur (et par conséquent tous les autres), un integer "index" permettant de sélectionner le pisteur à placer
//SORTIE: -
//ENTREES UTILISATEUR: OUI
{
	int occupied = 1;
	while (occupied)
	//Boucle tant que le pisteur n'est pas à un endroit correct
	{
		occupied = 0;
		printf("Placez votre pisteur %d sur l'axe X. Choisissez un nombre entre 1 et %d.\n", index, map_width - 2);
		scanf("%d", &pisteurs[index].x); //Entrée de la position en X par l'utilisateur
		printf("Placez votre pisteur %d sur l'axe Y. Choisissez un nombre entre 1 et %d.\n", index, map_height - 2);
		scanf("%d", &pisteurs[index].y); //Entrée de la position en Y par l'utilisateur
		if (pisteurs[index].x > 0 && pisteurs[index].x < map_width - 1 && pisteurs[index].y > 0 && pisteurs[index].y < map_height - 1)
		//Vérification de l'existence de l'emplacement
		{
			for (int i = 0; i < index; i++)
				if (pisteurs[index].x == pisteurs[i].x && pisteurs[index].y == pisteurs[i].y)
				//Vérification de la disponibilité de l'emplacement
				{
					occupied = 1;
					printf("Cette place est prise par un autre pisteur.\n");
				}
		}
		else
		{
			occupied = 1;
			printf("Cette position est hors-limite");
		}
	}
	//Assignation des dernières variables du pisteur initialisé
	pisteurs[index].hp = 1;
	pisteurs[index].state = 1;
}

void place_monk(int map[map_height][map_width], t_entity* monk, t_entity* pisteurs, int n_pisteurs)
//BUT: Placer le "monk", c'est-à-dire l'ennemi du jeu
//ENTREE: La map sous sa forme "modèle", l'adresse du monk, l'adresse du premier pisteur (et par conséquent tous les autres) et le nombre total de pisteurs
//SORTIE: -
//ENTREES UTILISATEUR: NON
{
	int occupied = 1;
	while (occupied)
	//Boucle tant que le monk n'est pas à un endroit correct
	{
		occupied = 0;
		monk->x = rand() % (map_width - 2) + 1; //Position random maîtrisée sur l'axe X
		monk->y = rand() % (map_height - 2) + 1; //Position random maîtrisée sur l'axe Y
		for (int i = 0; i < 3; i++) //axe Y
			for (int j = 0; j < 3; j++) //axe X
				for (int k = 0; k < n_pisteurs; k++) //pour chaque pisteur
					if (monk->y + i - 1 == pisteurs[k].y && monk->x + j - 1 == pisteurs[k].x)
					//Vérification de la proximité de l'emplacement avec les pisteurs
						occupied = 1;
	}
	//Assignation des variables restante de la structure du monk et positionnement sur la map
	map[monk->y][monk->x] = 16;
	monk->hp = 4;
	monk->state = 1;
}
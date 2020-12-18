#include "Prototypes.h"

void manage_pisteur(int map[map_height][map_width], int index, t_entity* monk, t_entity* pisteurs, int n_pisteurs, t_img* images, SDL_Window* window, SDL_Renderer* renderer)
//BUT: Gérer la phase de rapport d'un pisteur
//ENTREE: la map sous sa forme "modèle", l'adresse du monk, l'adresse du premier pisteurs (et par conséquent de tous les autres), le nombre total de pisteurs et un integer index permettant de sélectionner le pisteur à gérer
//ENTREE DE PASSAGE: l'ensemble des images créées pour l'affichage, la fenêtre d'affichage et le renderer (tous par adresse)
//SORTIE: -
//ENTREES UTILISATEUR: OUI
{
	if (pisteurs[index].hp < 1 && pisteurs[index].state != 0)
	//Vérification de la santé du pisteur (et s'il était encore considéré comme vivant)
	{
		printf("Le pisteur %d s'est fait tuer!\n", index);
		pisteurs[index].state = 0;
		system("pause");
	}
	else if (pisteurs[index].state > 0)
	//Vérification de l'état du pisteur
	{
		char phrase[255] = { NULL }; //Tableau de caractères utilisé pour la phrase inscrite en cas de non-détection du monk
		char for_itoa[7] = { NULL }; //Tableau de caractères permettant l'utilisation de la fonction itoa()
		pisteurs[index].state = 3; //Passage du pisteur en mode "rapport"
		//display_game(map, *monk, pisteurs, n_pisteurs); //Explications dans Display.cpp
		SDL_display(map, images, window, renderer, *monk, pisteurs, n_pisteurs); //Explications dans Display.cpp
		int traces = 1; //Permet de commencer la phrase par les bons éléments
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (traces != 2 && (i != 1 || j != 1))
				//Vérification de la case (pour éviter celle du pisteur) et de la détection du monk
				{
					if (map[pisteurs[index].y - 1 + i][pisteurs[index].x - 1 + j] > 0 && map[pisteurs[index].y - 1 + i][pisteurs[index].x - 1 + j] < 16)
					//Détection de traces
					{
						if (traces == 0)
							strcat(phrase, ".\n");
						strcat(phrase, "Traces de fraicheur ");
						strcat(phrase, itoa(map[pisteurs[index].y - 1 + i][pisteurs[index].x - 1 + j], for_itoa, 10));
						strcat(phrase, " en ");
						strcat(phrase, itoa(i * 3 + j + 1, for_itoa, 10));
						strcat(phrase, ".\n");
						traces = 1;
					}
					else if (map[pisteurs[index].y - 1 + i][pisteurs[index].x - 1 + j] != 16)
					//Pas de traces ni de monk
					{
						if (traces)
						{
							traces = 0;
							strcat(phrase, "Pas de traces en ");
							strcat(phrase, itoa(i * 3 + j + 1, for_itoa, 10));
						}
						else
						{
							strcat(phrase, ", ");
							strcat(phrase, itoa(i * 3 + j + 1, for_itoa, 10));
						}
					}
					else
					//Détection du monk, pas de phrase parlant des traces
					{
						printf("Je le vois.\n");
						traces = 2;
					}
				}
		if (traces == 0)
		//Si la dernière case ne contient pas de traces (case 9)
			strcat(phrase, ".\n");
		if (traces == 2)
		//Si le monk est détecté
		{
			char shoot[2] = { NULL };
			printf("Appuyez sur 't' puis 'enter' pour tirer.\n");
			scanf("%s", &shoot); //Entrée de la commande de tir par le joueur
			if (strcmp(shoot, "t") == 0)
			//Vérification de l'entrée du joueur
			{
				printf("Le pisteur tire.\n");
				_sleep(1000);//Crée un suspens
				if ((rand() % 10) < 4)
				//Jet de dés pour le tir
				{
					printf("Il touche !\n");
					monk[index].hp -= 1;
					monk[index].state = 6; //Prend en compte le decay qui a lieu à la fin du tour
				}
				else
					printf("Il rate !\n");
			}
			else
				printf("Le pisteur ne tire pas.\n");
		}
		else
			printf("%s", phrase);
		pisteurs[index].state = 1; //Passage du pisteur en mode "position"
		system("pause");
	}
}

void move_pisteur(int map[map_height][map_width], int index, t_entity* pisteurs, int n_pisteurs)
//BUT: Déplacer le pisteur sur la carte
//ENTREE: la map sous sa forme de modèle, l'adresse du premier pisteur (et par conséquent de tous les autres), le nombre total de pisteurs et un integer index permettant de sélectionner le pisteur à déplacer
//SORTIE: -
//ENTREES UTILISATEUR: OUI
{
	int input = NULL;
	int moved = 0;
	while (!moved)
	//Boucle tant que le joueur ne se déplace pas
	{
		printf("Dans quelle direction doit aller le pisteur %d?\n1 Haut, 2 Droite, 3 Bas, 4 Gauche.\nSi vous ne pouvez pas bouger, entrez la valeur 0, cela vous fera recommencer la partie (mais vous aurez perdu).\n", index);
		scanf("%d", &input); //Entrée de la direction du déplacement par le joueur
		switch (input) //Chaque case a les mêmes instructions, mais concerne une direction différente
		{
		case 1: //Haut
			moved = 1;
			for (int i = 0; i < n_pisteurs; i++)
				if (i != index && pisteurs[i].x == pisteurs[index].x && pisteurs[i].y == pisteurs[index].y - 1 && pisteurs[i].hp > 0)
				//Vérification de la disponibilité de l'emplacement par rapport aux autres pisteurs
					moved = 0;
			if (moved && map[pisteurs[index].y - 1][pisteurs[index].x] < 16)
			//Vérification de la disponibilité de l'emplacement par rapport au monk et la limite de map
				pisteurs[index].y -= 1;
			else
			{
				printf("L'emplacement est pris.\n");
				moved = 0;
			}
			break;
		case 2: //cf case 1, Droite
			moved = 1;
			for (int i = 0; i < n_pisteurs; i++)
				if (i != index && pisteurs[i].x == pisteurs[index].x + 1 && pisteurs[i].y == pisteurs[index].y && pisteurs[i].hp > 0)
					moved = 0;
			if (moved && map[pisteurs[index].y][pisteurs[index].x + 1] < 16)
				pisteurs[index].x += 1;
			else
			{
				printf("L'emplacement est pris.\n");
				moved = 0;
			}
			break;
		case 3: //cf case 1, Bas
			moved = 1;
			for (int i = 0; i < n_pisteurs; i++)
				if (i != index && pisteurs[i].x == pisteurs[index].x && pisteurs[i].y == pisteurs[index].y + 1 && pisteurs[i].hp > 0)
					moved = 0;
			if (moved && map[pisteurs[index].y + 1][pisteurs[index].x] < 16)
				pisteurs[index].y += 1;
			else
			{
				printf("L'emplacement est pris.\n");
				moved = 0;
			}
			break;
		case 4: //cf case 1, Gauche
			moved = 1;
			for (int i = 0; i < n_pisteurs; i++)
				if (i != index && pisteurs[i].x == pisteurs[index].x - 1 && pisteurs[i].y == pisteurs[index].y && pisteurs[i].hp > 0)
					moved = 0;
			if (moved && map[pisteurs[index].y][pisteurs[index].x - 1] < 16)
				pisteurs[index].x -= 1;
			else
			{
				printf("L'emplacement est pris.\n");
				moved = 0;
			}
			break;
		case 0:
			for (int i = 0; i < n_pisteurs; i++)
			//Auto-détruit tous les pisteurs
			{
				pisteurs->state = 0;
				pisteurs->hp = 0;
				moved = 1;
			}
			break;
		}
	}
	if (pisteurs[index].state != 0)
		pisteurs[index].state = 1; //Passage du pisteur en mode "position"
}
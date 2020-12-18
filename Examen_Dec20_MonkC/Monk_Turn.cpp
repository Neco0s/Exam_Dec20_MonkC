#include "Prototypes.h"

int monk_target(t_entity* pisteurs, t_entity monk, int n_pisteurs, int target)
//BUT: D�finir la cible du monk pour ce tour, afin de d�terminer ses d�placements
//ENTREE: L'adresse du premier pisteur (et par cons�quent de tous les autres), le monk (copie), le nombre total de pisteurs et la target actuelle
//SORTIE: La nouvelle target
//ENTREES UTILISATEUR: NON
{
	if (target > -1 && target < n_pisteurs && pisteurs[target].hp > 0) //V�rification que le pisteur cibl� existe et est vivant
	{
		for (int i = 0; i < n_pisteurs; i++)
			if (abs(monk.x - pisteurs[i].x) + abs(monk.y - pisteurs[i].y) == 1 && pisteurs[i].hp > 0)
			//V�rification de la proximit� du monk et d'un pisteur
				target = i;
	}
	else //La target n'est pas d�finie ou le pisteur est mort
	{
		target = 0; //Ciblage par d�faut
		for (int i = 1; i < n_pisteurs; i++)
			if (abs(monk.x - pisteurs[i].x) + abs(monk.y - pisteurs[i].y) < abs(monk.x - pisteurs[target].x) + abs(monk.y - pisteurs[target].y) && pisteurs[i].hp > 0) //V�rification que le pisteur i est plus proche en nombre de mouvements que le pisteur cibl� du monk et que le pisteur i est vivant
				target = i; //Changement de cible
	}
	return (target);
}

void move_monk(int map[map_height][map_width], t_entity* monk, t_entity* pisteurs, int n_pisteurs, int target)
//BUT: D�placer le monk
//ENTREE: La map sous sa forme "mod�le", l'adresse du monk, l'adresse du premier pisteur (et par cons�quent de tous les autres), le nombre total de pisteurs et un integer permettant de s�lectionner le pisteur cibl� par le monk
//SORTIE: -
//ENTREES UTILISATEUR: NON
{
	int dir = NULL;
	int moved = NULL;
	while (!moved) //Boucle tant que le monk n'a pas boug�
	{
		if (abs(pisteurs[target].x - monk->x) > abs(pisteurs[target].y - monk->y))
		//Si le monk est plus loin en x qu'en y de sa cible
		{
			if (pisteurs[target].x < monk->x)
				dir = 4;
			else
				dir = 2;
		}
		else if (abs(pisteurs[target].x - monk->x) < abs(pisteurs[target].y - monk->y))
		//Si le monk est plus loin en y qu'en x de sa cible
		{
			if (pisteurs[target].y < monk->y)
				dir = 1;
			else
				dir = 3;
		}
		else
		//Si le monk est a distance �gale en x et en y par rapport � sa cible
		{
			dir = rand() % 2 + 1;
			if ((dir == 1 && pisteurs[target].y > monk->y) || (dir == 2 && pisteurs[target].x < monk->x))
				dir += 2;
		}
		switch (dir)
		{
		case 1: //Haut
			if (map[monk->y - 1][monk->x] != map_border) //V�rification de l'emplacement par rapport � la limite de map
			{
				for (int i = 0; i < n_pisteurs; i++)
					if (monk->y - 1 == pisteurs[i].y && monk->x == pisteurs[i].x) //V�rification de l'emplacement par rapport � un pisteur (mort du pisteur s'il s'y trouve)
						pisteurs[i].hp = 0;
				moved = 1;
				map[monk->y - 1][monk->x] = 16;
				monk->y -= 1;
			}
			break;
		case 2: //cf case 1, Droite
			if (map[monk->y][monk->x + 1] != map_border)
			{
				for (int i = 0; i < n_pisteurs; i++)
					if (monk->y == pisteurs[i].y && monk->x + 1 == pisteurs[i].x)
						pisteurs[i].hp = 0;
				moved = 1;
				map[monk->y][monk->x + 1] = 16;
				monk->x += 1;
			}
			break;
		case 3: //cf case 1, Bas
			if (map[monk->y + 1][monk->x] != map_border)
			{
				for (int i = 0; i < n_pisteurs; i++)
					if (monk->y + 1 == pisteurs[i].y && monk->x == pisteurs[i].x)
						pisteurs[i].hp = 0;
				moved = 1;
				map[monk->y + 1][monk->x] = 16;
				monk->y += 1;
			}
			break;
		case 4: //cf case 1, Gauche
			if (map[monk->y][monk->x - 1] != map_border)
			{
				for (int i = 0; i < n_pisteurs; i++)
					if (monk->y == pisteurs[i].y && monk->x - 1 == pisteurs[i].x)
						pisteurs[i].hp = 0;
				moved = 1;
				map[monk->y][monk->x - 1] = 16;
				monk->x -= 1;
			}
			break;
		}
	}
}

void update_leads(int map[map_height][map_width], t_entity* monk)
//BUT: Mettre � jour la fra�cheur des traces du monk ainsi que son statut
//ENTREE: la map sous sa forme "mod�le", l'adresse de monk
//SORTIE: -
//ENTREES UTILISATEUR: NON
{
	for (int i = 0; i < map_height; i++)
		for (int j = 0; j < map_width; j++)
		{
			if (map[i][j] > 0 && map[i][j] < 16)
				map[i][j] -= 1;
			else if (map[i][j] == 16)
				if (monk->y != i || monk->x != j) //V�rification du positionnement du monk
					map[i][j] -= 1;
		}
	if (monk->state > 1) //D�compte des tours d'affichage du monk bless�
		monk->state -= 1;
}
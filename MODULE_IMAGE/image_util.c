/**
* @file		image_util.c
* @author	Quentin & Tendry
* @version	1.0
* @brief	Code source des fonctions utilitaires du module image
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "image.h"
#include "point.h"
#include "image_util.h"

// Lit une valeur de pixel dans l'image et la place dans valeur
void image_read_pixel(image self, int x, int y, unsigned char* valeur)
{
	int* tab = NULL;
	int i = 0;

	// Vérification des valeurs passées
	assert(x >= 0 && x < image_give_largeur(self));
	assert(y >= 0 && y < image_give_hauteur(self));

	// On se place au bon endroit dans l'image
	Point point;
	COORDX(point) = x;
	COORDY(point) = y;

	image_move_to(self, &point);

	// On lit le pixel et on stocke sa valeur dans la valeur
	tab = image_lire_pixel(self);

	for(i = 0; i < image_give_dim(self); i++)
	{
		*(valeur+i) = *(tab+i);
	}
}

// Ecrit une valeur dans un pixel de l'image
void image_write_pixel(image self, int x, int y, unsigned char* valeur)
{
	int* tab = malloc(sizeof(int) * image_give_dim(self));
	int i = 0;

	// Vérification des valeurs passées
	assert(x >= 0 && x < image_give_largeur(self));
	assert(y >= 0 && y < image_give_hauteur(self));

	// On se place au bon endroit dans l'image
	Point point;
	COORDX(point) = x;
	COORDY(point) = y;

	image_move_to(self, &point);

	// On crée un tableau de valeurs qu'on va écrire dans le pixel
	for(i = 0; i < image_give_dim(self); i++)
	{
		*(tab+i) = *(valeur+i);
	}

	image_ecrire_pixel(self, tab);

	free(tab);
}

void draw_square(image self, int xmin, int ymin, int xmax, int ymax, unsigned char* couleur)
{
	int i,j;

	// Vérification des valeurs passées
	assert(xmin >= 0 && xmin < image_give_largeur(self));
	assert(ymin >= 0 && ymin < image_give_hauteur(self));
	assert(xmax >= 0 && xmax < image_give_largeur(self));
	assert(ymax >= 0 && ymax < image_give_hauteur(self));

	// On se place au bon endroit dans l'image
	/*Point point_HG;
	COORDX(point_HG) = xmin;
	COORDY(point_HG) = ymin;

	image_move_to(self, point_HG);*/

	for (i = xmin; i <= xmax; i++)
	{
		image_write_pixel(self,i,ymin,couleur);
		image_write_pixel(self,i,ymax,couleur);
	}

	for(j=ymin+1; j<ymax; j++)
	{
		image_write_pixel(self,xmin,j,couleur);
		image_write_pixel(self,xmax,j,couleur);
	}

}
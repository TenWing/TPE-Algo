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

	//On dessine les lignes horizontales
	for (i = xmin; i <= xmax; i++)
	{
		image_write_pixel(self,i,ymin,couleur);
		image_write_pixel(self,i,ymax,couleur);
	}

	//On dessine les lignes verticales
	for(j=ymin+1; j<ymax; j++)
	{
		image_write_pixel(self,xmin,j,couleur);
		image_write_pixel(self,xmax,j,couleur);
	}

}

void give_moments(image self, int xmin, int ymin, int xmax, int ymax, int* nombre_pixel, double* sum_intensity, double* sum_square_intensity)
{
	unsigned char* valeur = malloc(sizeof(unsigned char) * image_give_dim(self));
	double* actuel = malloc(sizeof(double) * image_give_dim(self));
	int i,j,k;

	*nombre_pixel = 0;

	for(i=0; i<image_give_dim(self); i++)
	{
		*(sum_intensity+i) = 0.0;
		*(sum_square_intensity + i) = 0.0;
	}


	for(i=xmin+1; i<xmax; i++)
	{
		for(j=ymin+1; j<ymax; j++)
		{
			*nombre_pixel = *nombre_pixel +1;
			image_read_pixel(self,i,j,valeur);

			for(k=0; k<image_give_dim(self); k++)
			{
				actuel[i]= (double) valeur[i];
				printf("%d,%d,%d\n", valeur[0], valeur[1], valeur[2]);
				printf("%f; %f, %f\n", actuel[0], actuel[1], actuel[2]);
getchar();
				//printf("%f\n", valeur[0]);
				*(sum_intensity+i)= (double)*(valeur+i)+ *(sum_intensity+i);
				*(sum_square_intensity+i) = (double)*(sum_square_intensity+i) + *(valeur+i)*(*(valeur+i));
			}
		}
	}

	free(valeur);
	free(actuel);
}
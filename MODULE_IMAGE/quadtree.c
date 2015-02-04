/**
* @file		quadtree.c
* @author	Quentin & Tendry
* @version	1.0
* @brief	Code source des fonctions utilitaires pour les quadtree
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "image.h"
#include "objet.h"
#include "point.h"
#include "image_util.h"
#include "quadtree.h"


/**
* @brief	Structure des quadtree
* @author	Quentin & Tendry
* @version	1.0
*/
struct quadtree
{
	quadtree sons[4];
	double M0,M1[3],M2[3];
	Point supgauche, infdroit;
};


quadtree create_quadtree()
{
	INSTANCIER(quadtree);

	return self;
}

void quadtree_subdivide(quadtree q)
{
	int i;

	//On initialise les quadtree de chaque fils
	for (i = 0; i < 4; i++)
	{
		q->sons[i] = create_quadtree();
	}

	//On définit la taille de chaque fils
	for (i=0; i < 4; i++)
	{
		switch(i)
		{
			case 0 :
				q->sons[i]->supgauche.coordx = q->supgauche.coordx;
				q->sons[i]->supgauche.coordy = q->supgauche.coordy;
				q->sons[i]->infdroit.coordx = q->infdroit.coordx/2;
				q->sons[i]->infdroit.coordy = q->infdroit.coordy/2;
				break;
			case 1 : 
				q->sons[i]->supgauche.coordx = q->supgauche.coordx/2;
				q->sons[i]->supgauche.coordy = q->supgauche.coordy;
				q->sons[i]->infdroit.coordx = q->infdroit.coordx;
				q->sons[i]->infdroit.coordy = q->infdroit.coordy/2;
				break;
			case 2 : 
				q->sons[i]->supgauche.coordx = q->supgauche.coordx/2;
				q->sons[i]->supgauche.coordy = q->supgauche.coordy;
				q->sons[i]->infdroit.coordx = q->infdroit.coordx;
				q->sons[i]->infdroit.coordy = q->infdroit.coordy/2;
				break;
			case 3 : 
				q->sons[i]->supgauche.coordx = q->supgauche.coordx;
				q->sons[i]->supgauche.coordy = q->supgauche.coordy;
				q->sons[i]->infdroit.coordx = q->infdroit.coordx/2;
				q->sons[i]->infdroit.coordy = q->infdroit.coordy/2;
				break;
			default :
				break;
		}
	}
}

void delete_quadtree(quadtree q)
{
	//Descente dans l'arbre
	if(q->sons[0] != NULL)
	{
		delete_quadtree(q->sons[0]);
		delete_quadtree(q->sons[1]);
		delete_quadtree(q->sons[2]);
		delete_quadtree(q->sons[3]);
	}
	//Libération de la mémoire
	else
	{
		free(q->sons[0]);
		free(q->sons[1]);
		free(q->sons[2]);
		free(q->sons[3]);
		free(q);
	}
}

quadtree split_image(image image, double seuil)
{

}

void draw_quadtree(image image, quadtree arbre, unsigned char* couleur)
{
	
}


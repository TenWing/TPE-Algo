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


extern quadtree create_quadtree()
{
	INSTANCIER(quadtree);

	int i;

	for (i = 0; i < 4; i++)
	{
		self->sons[i] = NULL;
	}	

	return self;
}

extern void quadtree_subdivide(quadtree q)
{
	int i;

	for (i = 0; i < 4; i++)
	{
		q->sons[i] = create_quadtree();
	}

/*	for (i=0; i < 4; i++)
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
	}*/
}

extern void delete_quadtree(quadtree q)
{

}

<<<<<<< HEAD
//(quadtree) malloc( 4 * sizeof(quadtree));
/*
struct point
{
  int coordx;
  int coordy;
};
*/
=======
quadtree split_image(image image, double seuil)
{

}

void draw_quadtree(image image, quadtree arbre, unsigned char* couleur)
{
	
}
>>>>>>> 61cb22d400ba2c66176a45b30cc01a4e33d71e77

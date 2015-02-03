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
	int xmin,ymin,xmax,ymax;
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
	/*q->M0 = 0;

	for (i = 0; i < 3; i++)
	{
		q->M1[i] = 0;
		q->M2[i] = 0;
	}

	q->xmin = 0;
	q->ymin = 0;
	q->xmax = 0;
	q->ymax = 0;*/
}

extern void delete_quadtree(quadtree q)
{

}
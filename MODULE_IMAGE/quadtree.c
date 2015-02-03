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

/**
* @brief	Structure des quadtree
* @author	Quentin & Tendry
* @version	1.0
*/
typedef struct quadtree Quadtree;
struct quadtree
{
	quadtree sons[4];
	double M0,M1[3],M2[3];
	int xmin,ymin,xmax,ymax;
};




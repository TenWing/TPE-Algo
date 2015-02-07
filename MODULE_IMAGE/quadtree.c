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
* @brief 	les positions des fils par rapport au père
* @author	Quentin & Tendry
*/
typedef enum Place Place;
enum Place
{
	HG = 0,
	HD = 1,
	BG = 2,
	BD = 3
};

// #########################################
// FONCTIONS PRIVEES DU MODULE QUADTREE

/**
* @brief 	crée un fils par rapport à son père
* @author	Quentin & Tendry
* @param 	q le quadtree père du fils créé
* @param 	p la place du fils par rapport au père
* @return 	un fils quadtree bien construit
*/
quadtree create_son(quadtree q, Place p);
// #########################################

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


quadtree create_quadtree(int supGaucheX, int supGaucheY, int infDroitX, int infDroitY)
{
	int i =0;

	// Création du quadtree
	INSTANCIER(quadtree);

	// On va mettre a null chaque fils
	for(i = 0; i < 4; i++)
	{
		self->sons[i] = NULL;
	}

	// Enfin on initialise les points du noeud
	self->supgauche.coordx = supGaucheX;
	self->supgauche.coordy = supGaucheY;
	self->infdroit.coordx = infDroitX;
	self->infdroit.coordy = infDroitY;

	return self;
}

void quadtree_subdivide(quadtree q)
{
	int i;

	//On initialise les quadtree de chaque fils
	for (i = 0; i < 4; i++)
	{
		q->sons[i] = create_son(q, i);
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

quadtree split_image(image self, double seuil)
{
	//quadtree arbre = create_quadtree();

	//give_moments(self,1, 1, self->largeur, self->hauteur, &(arbre->M0), arbre->M1, arbre->M2);
}

void draw_quadtree(image self, quadtree arbre, unsigned char* couleur)
{
	
}

quadtree create_son(quadtree q, Place p)
{
	// On teste bien que le père soit initialisé
	assert(q != NULL);

	// le fils
	quadtree fils = NULL;

	// Traitement différent en fonction de la place
	switch(p)
	{
		// En fonction de la place la zone qu'occupe le fils
		// est différente
		case HG :			
			fils = create_quadtree(COORDX(q->supgauche),
			 COORDY(q->supgauche), COORDX(q->infdroit)/2, 
			 COORDY(q->infdroit)/2);
			break;

		case HD : 
			fils = create_quadtree(COORDX(q->infdroit)/2,
			 COORDY(q->supgauche)/2, COORDX(q->infdroit), 
			 COORDY(q->infdroit)/2);
			break;

		case BG : 
			fils = create_quadtree(COORDX(q->supgauche),
			 COORDY(q->infdroit)/2, COORDX(q->infdroit)/2, 
			 COORDY(q->infdroit));
			break;

		case BD : 
			fils = create_quadtree(COORDX(q->infdroit)/2,
			 COORDY(q->infdroit)/2, COORDX(q->infdroit), 
			 COORDY(q->infdroit));
			break;

		default :
			break;
	}

	printf("%d %d // %d %d\n", fils->supgauche.coordx,
		fils->supgauche.coordy, fils->infdroit.coordx,
		fils->infdroit.coordy);

	return fils;
}
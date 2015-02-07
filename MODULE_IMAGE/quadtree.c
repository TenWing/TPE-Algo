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
	//On vérifie que l'image n'es pas nulle
	assert(self != NULL);

	//On déclare et initialise deux entiers
	int hauteur_image, largeur_image;

	largeur_image = image_give_largeur(self);
	hauteur_image = image_give_hauteur(self);

	//Création d'un quadtree
	quadtree q = create_quadtree(0, 0, largeur_image, hauteur_image );

	//Fonction de récurrence pour initialiser tout le quadtree
	split_image_sons(self,seuil,q);

	return q;
}

void draw_quadtree(image self, quadtree arbre, unsigned char* couleur)
{
	assert(self != NULL);

	if(arbre != NULL)
	{
		//Dessine le rectangle dans la zone du quadtree
		draw_square(self, COORDX(arbre->supgauche), COORDY(arbre->supgauche), COORDX(arbre->infdroit), COORDY(arbre->infdroit), couleur);

		draw_quadtree(self,arbre->sons[0],couleur);
		draw_quadtree(self,arbre->sons[3],couleur);
		
	}
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

	/*printf("%d %d // %d %d\n", fils->supgauche.coordx,
		fils->supgauche.coordy, fils->infdroit.coordx,
		fils->infdroit.coordy);*/

	return fils;
}

void split_image_sons(image self, double seuil, quadtree q)
{
	int j;
	int* nb_pixel;
	double* a,*b;
	double var[3];
	double compare[3];

	nb_pixel = (int*) malloc(sizeof(int));
	a = (double*) malloc (sizeof(double) * image_give_dim(self));
	b = (double*) malloc (sizeof(double) * image_give_dim(self));

	//On calcule les moments de l'image prédéfini
	give_moments(self, COORDX(q->supgauche), COORDY(q->supgauche), COORDX(q->infdroit), COORDY(q->infdroit), nb_pixel, a,b);
	
	q->M0 = *nb_pixel;

	for (j=0; j<3;j++)
	{
		q->M1[j] = *(a+j);
		q->M2[j] = *(b+j);
		var[j] = (q->M2[j] - q->M1[j]*q->M1[j]/q->M0)/q->M0;
		compare[j] = var[j] - seuil;
	}
	
	//On vérifie si la variance est bien supérieure au seuil
	if( compare[0] > 0 && compare[1] > 0 && compare[2] > 0 )
	{
		//On vérifie que des moments sont calculables pour la récurrence
		if(COORDX(q->supgauche) != COORDX(q->infdroit)-1 && COORDY(q->supgauche) != COORDY(q->infdroit)-1)
		{
			quadtree_subdivide(q);
			split_image_sons(self,seuil,q->sons[0]);
			split_image_sons(self,seuil,q->sons[1]);
			split_image_sons(self,seuil,q->sons[2]);
			split_image_sons(self,seuil,q->sons[3]);
		}
	}

	free(b);
	free(a);
	free(nb_pixel);
}
/**
* @file		quadtree.c
* @author	Quentin & Tendry
* @version	1.0
* @brief	Code source des fonctions utilitaires pour les quadtree
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "image.h"
#include "objet.h"
#include "point.h"
#include "image_util.h"
#include "quadtree.h"
#include "type_obj.h"

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
	double M1[3],M2[3];
	int M0;
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

	// Le quadtree n'est pas initialisé
	self->M0 = 0;
	self->M1[0] = -1;
	self->M2[0] = -1;

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

void delete_quadtree(quadtree* q)
{
	//Descente dans l'arbre
	if(!est_vide(*q))
	{
		quadtree tree = *q;
		delete_quadtree(&(tree->sons[0]));
		delete_quadtree(&(tree->sons[1]));
		delete_quadtree(&(tree->sons[2]));
		delete_quadtree(&(tree->sons[3]));
	}
	//Libération de la mémoire
	else
	{
		free(*q);
		*q = NULL;
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
	assert(arbre != NULL);

	if(!est_vide(arbre))
	{
		draw_quadtree(self,arbre->sons[0],couleur);
		draw_quadtree(self,arbre->sons[1],couleur);
		draw_quadtree(self,arbre->sons[2],couleur);
		draw_quadtree(self,arbre->sons[3],couleur);
	}
	else
	{
		draw_square(self, COORDX(arbre->supgauche), COORDY(arbre->supgauche),
			COORDX(arbre->infdroit), COORDY(arbre->infdroit), couleur);
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
			 COORDY(q->supgauche), 
			 COORDX(q->supgauche)/2 + COORDX(q->infdroit)/2, 
			 COORDY(q->supgauche)/2 + COORDY(q->infdroit)/2);
			break;

		case HD : 
			fils = create_quadtree(COORDX(q->supgauche)/2 + COORDX(q->infdroit)/2,
			 COORDY(q->supgauche), 
			 COORDX(q->infdroit), 
			 COORDY(q->supgauche)/2 + COORDY(q->infdroit)/2);
			break;

		case BG : 
			fils = create_quadtree(COORDX(q->supgauche),
			 COORDY(q->supgauche)/2 + COORDY(q->infdroit)/2, 
			 COORDX(q->supgauche)/2 + COORDX(q->infdroit)/2, 
			 COORDY(q->infdroit));
			break;

		case BD : 
			fils = create_quadtree(COORDX(q->infdroit)/2 + COORDX(q->supgauche)/2,
			 COORDY(q->infdroit)/2 + COORDY(q->supgauche)/2,
			 COORDX(q->infdroit), 
			 COORDY(q->infdroit));
			break;

		default :
			break;
	}

	return fils;
}

void split_image_sons(image self, double seuil, quadtree q)
{
	double variance;
	double compare;

	variance = calcule_variance(q, self);
	compare = variance - seuil;
	
	//On vérifie si la variance est bien supérieure au seuil
	if( compare > 0 )
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

}

booleen est_vide(quadtree arbre)
{
	if(arbre->sons[0] == NULL)
		return vrai;

	return faux;
}

quadtree create_default_quadtree(int xmin, int ymin, int xmax, int ymax, int hauteur)
{
	quadtree q = create_quadtree(xmin,ymin,xmax,ymax);

	if(hauteur == 0)
	{
		return q;
	}
	else
	{
		q->sons[0] = create_default_quadtree(xmin, ymin, (xmin + xmax)/2, (ymin + ymax)/2, hauteur-1);
		q->sons[1] = create_default_quadtree((xmin + xmax)/2, ymin, xmax, (ymin + ymax)/2, hauteur-1);
		q->sons[2] = create_default_quadtree(xmin, (ymin + ymax)/2, (xmin + xmax)/2, ymax, hauteur-1);
		q->sons[3] = create_default_quadtree((xmin + xmax)/2, (ymin + ymax)/2, xmax, ymax, hauteur-1);
	}

	return q;
}

void init_quadtree(quadtree q,image self)
{
	if(est_vide(q))
	{
		//On calcule les moments de l'image prédéfini
		give_moments(self, COORDX(q->supgauche), COORDY(q->supgauche), COORDX(q->infdroit),
			COORDY(q->infdroit), &(q->M0), q->M1, q->M2);
	}
	else
	{
		init_quadtree(q->sons[0], self);
		init_quadtree(q->sons[1], self);
		init_quadtree(q->sons[2], self);
		init_quadtree(q->sons[3], self);
	}	
}

void update_quadtree(quadtree q, image self, double seuil)
{
	// Test pour continuer les fonctions
	assert(self != NULL);
	assert(q != NULL);	

	double variance = calcule_variance(q, self);
	double compare = variance - seuil;

	if(est_vide(q))
	{
		if(compare > 0)
		{
			quadtree_subdivide(q);
		}
	}
	else
	{
		if(compare < 0)
		{
			delete_quadtree(&(q->sons[0]));
			delete_quadtree(&(q->sons[1]));
			delete_quadtree(&(q->sons[2]));
			delete_quadtree(&(q->sons[3]));			
		}
		else
		{
			update_quadtree(q->sons[0], self, seuil);
			update_quadtree(q->sons[1], self, seuil);
			update_quadtree(q->sons[2], self, seuil);
			update_quadtree(q->sons[3], self, seuil);
		}
	}
}

double calcule_variance(quadtree q, image self)
{
	// Test pour continuer les fonctions
	assert(self != NULL);
	assert(q != NULL);	

	int j = 0, dim = image_give_dim(self);

	// Les variances respectives en fonction de la dimension
	double var[3];

	// Calcul des moments que si c'est pas init
	if(!est_init(q))
		give_moments(self, COORDX(q->supgauche), COORDY(q->supgauche), 
			COORDX(q->infdroit), COORDY(q->infdroit), &(q->M0), q->M1, q->M2);

	// Ensuite on renvoie la variance
	for(j = 0; j < dim; j++)
	{
		var[j] = (q->M2[j] - q->M1[j]*q->M1[j]/q->M0)/q->M0;
	}	

	// Renvoi différent en fonction de la dimension
	if(dim > 1)
		return ((var[0] + var[1] + var[2])/3);
	else
		return var[0];
}

booleen est_init(quadtree q)
{
	assert(q != NULL);

	if(q->M0 == 0 || q->M1[0] == -1 || q->M2[0] == -1)
		return faux;

	return vrai;
}
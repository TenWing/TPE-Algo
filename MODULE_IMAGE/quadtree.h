/**
* @file		quadtree.c
* @author	Quentin & Tendry
* @version	1.0
* @brief	Contient les prototypes des fonctions utilitaires pour les quadtree
*/

#ifndef QUADTREE_H
#define QUADTREE_H

#include "objet.h"
#include "classe.h"

#include "point.h"
#include "move_type.h"

CLASSE(quadtree);

extern quadtree create_quadtree();
extern void quadtree_subdivide(quadtree q);
extern void delete_quadtree(quadtree q);

/**
* @brief	crée un quadtree en découpant une image avec des arguments de seuil
* @author	Quentin & Tendry
* @version	1.0
* @param	image image une image
* @param	double seuil la valeur de seuil pour le découpage
* @return	un quadtree
*/
extern quadtree split_image(image image, double seuil);

/**
* @brief	affiche les bordures dans l'image correspondant aux découpages du quad tree
* @author	Quentin & Tendry
* @version	1.0
* @param 	image l'image modifiée
* @param	quadtree l'arbre pour dessiner les bords
* @param 	couleur la couleur des bords
*/
extern void draw_quadtree(image image, quadtree arbre, unsigned char* couleur);

#endif
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

/**
* @brief	crée un quadtree 
* @author	Quentin & Tendry
* @param 	supGaucheX la coordonné x du point en haut a gauche
* @param 	supGaucheY la coordonné y du point en haut a gauche
* @param 	infDroitX la coordonné x du point en bas a droite
* @param 	infDroitY la coordonné y du point en bas a droite
* @version	2.0
* @return	un quadtree
*/
extern quadtree create_quadtree(int supGaucheX, int supGaucheY, int infDroitX, int infDroitY);

/**
* @brief	initialise le quadtree
* @author	Quentin & Tendry
* @version	1.0
* @param	quadtree le quadtree à initialiser
*/
extern void quadtree_subdivide(quadtree q);

/**
* @brief	détruit un quadtree (ses feuilles et sa racine)
* @author	Quentin & Tendry
* @version	1.0
* @param	quadtree le quadtree à détruire
*/
extern void delete_quadtree(quadtree q);

/**
* @brief	crée un quadtree en découpant une image avec des arguments de seuil
* @author	Quentin & Tendry
* @version	1.0
* @param	image image une image
* @param	double seuil la valeur de seuil pour le découpage
* @return	un quadtree
*/
extern quadtree split_image(image self, double seuil);

/**
* @brief	affiche les bordures dans l'image correspondant aux découpages du quad tree
* @author	Quentin & Tendry
* @version	1.0
* @param 	image l'image modifiée
* @param	quadtree l'arbre pour dessiner les bords
* @param 	couleur la couleur des bords
*/
extern void draw_quadtree(image self, quadtree arbre, unsigned char* couleur);

/**
* @brief	crée les fils d'un quadtree en découpant une image avec des arguments de seuil
* @author	Quentin & Tendry
* @version	1.0
* @param 	image l'image modifiée
* @param	quadtree l'arbre pour dessiner les bords
* @param 	seuil 	le sueil minimal pour initialiser les moments
*/
void split_image_sons(image self, double seuil, quadtree q);

/**
* @brief	vérifie si l'arbre est vide ou non
* @author	Quentin & Tendry
* @version	1.0
* @param 	quadtree le quadtree a vérifier
*/
booleen est_vide(quadtree arbre);

/**
* @brief	créé un arbre d'une certaine hauteur
* @author	Quentin & Tendry
* @version	1.0
* @param 	hauteur  	la hauteur de l'arbre à faire
* @param 	xmin 		coordonnées x du point en haut à gauche de l'image
* @param 	ymin 		coordonnées y du point en haut à gauche de l'image
* @param 	xmax 		coordonnées x du point en bas à droite de l'image
* @param 	ymax 		coordonnées x du point en bas à droite de l'image
*/
extern quadtree create_default_quadtree(int xmin, int ymin, int xmax, int ymax, int hauteur);

/**
* @brief	initialise les moments des feuilles d’un quadtree à partir de l’image puis en d ́eduit les moments de tous les noeuds.
* @author	Quentin & Tendry
* @version	1.0
* @param 	quadtree  le quadtree à initialiser
* @param 	image 	  l'image pour l'initialisation
*/
extern void init_quadtree(quadtree q,image self);

/**
* @brief	supprime l’ensemble des fils d’un noeud dont la 
*			variance est inférieure au seuil passé en 3 eme argument et découpe toute
*			feuille dont la variance est supérieure au même seuil.
* @author	Quentin & Tendry
* @version	1.0
* @param 	quadtree  le quadtree à mettre à jour
* @param 	image 	  l'image pour mettre à jour
* @param	seuil 	  le seuil pour la mise à jour
*/
extern void update_quadtree(quadtree q, image self, double seuil);

#endif
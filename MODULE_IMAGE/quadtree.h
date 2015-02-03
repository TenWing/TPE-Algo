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

#endif
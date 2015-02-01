/**
* @file		image_util.h
* @author	Quentin & Tendry
* @version	1.0
* @brief	Contient les prototypes des fonctions utilitaires du module image
*/

#ifndef IMAGE_UTIL_H
#define IMAGE_UTIL_H

/**
* @brief	lit une valeur de pixel dans une image et la place dans une chaîne
* @author	Quentin & Tendry
* @version	1.0
* @param 	self un pointeur d'image, 
			la macro self permet de simplifier la syntaxe d'accès aux attributs
* @param	x la coordonnée x du pixel dans l'image
* @param	y la coordonnée y du pixel dans l'image
* @param 	valeur la valeur du pixel en RGB si l'image 
			est en couleur ou juste sur 1 octet dans le cas 
			d'une image en niveaux de gris (dim = 3 ou 1)
*/
extern void image_read_pixel(image self, int x, int y, unsigned char* valeur);

/**
* @brief	écrit une valeur de pixel dans un pixel de l'image
* @author	Quentin & Tendry
* @version	1.0
* @param 	self un pointeur d'image, 
			la macro self permet de simplifier la syntaxe d'accès aux attributs
* @param	x la coordonnée x du pixel dans l'image
* @param	y la coordonnée y du pixel dans l'image
* @param 	valeur la valeur du pixel en RGB si l'image 
			est en couleur ou juste sur 1 octet dans le cas 
			d'une image en niveaux de gris (dim = 3 ou 1)
*/
extern void image_write_pixel(image self, int x, int y, unsigned char* valeur);

/**
* @brief	Dessine un rectance dans l'image
* @author	Quentin & Tendry
* @version	1.0
* @param 	self un pointeur d'image, 
			la macro self permet de simplifier la syntaxe d'accès aux attributs
* @param	xmin la coordonnée x du point en haut à gauche du rectangle à dessiner
* @param	ymin la coordonnée y du point en haut à gauche du rectangle à dessiner
* @param	xmax la coordonnée x du point en bas à droite du rectangle à dessiner
* @param	ymax la coordonnée y du point en bas à droite du rectangle à dessiner
* @param 	couleur la couleur du rectangle
*/
extern void draw_square(image self, int xmin, int ymin, int xmax, int ymax, unsigned char* couleur);

/**
* @brief	Calcul les moments d'ordre 0,1,2 dans un rectangle pré-établi
* @author	Quentin & Tendry
* @version	1.0
* @param 	self un pointeur d'image, 
			la macro self permet de simplifier la syntaxe d'accès aux attributs
* @param	xmin la coordonnée x du point en haut à gauche du rectangle à dessiner
* @param	ymin la coordonnée y du point en haut à gauche du rectangle à dessiner
* @param	xmax la coordonnée x du point en bas à droite du rectangle à dessiner
* @param	ymax la coordonnée y du point en bas à droite du rectangle à dessiner
* @param 	nb_pixel le nombre de pixel dans le rectangle	
* @param 	sum_intensity somme des intensité dans le rectangle
* @param 	sum_square_intensity somme des intensité au carré dans le rectangle
*/
extern void give_moments(image self, int xmin, int ymin, int xmax, int ymax, int* nb_pixel, double* sum_intensity, double* sum_square_intensity);

#endif
/**
* @file		image_util.h
* @author	Quentin & Tendry
* @version	1.0
* @brief	Contient les prototypes des fonctions du module image
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

#endif
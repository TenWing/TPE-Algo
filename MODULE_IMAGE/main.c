#include <stdio.h>
#include "image.h"
#include "objet.h"
#include "image_util.h"
#include "point.h"
#include "quadtree.h"

#define IMAGE "../IMAGES/lenna.ppm"
#define DESTINATION "../IMAGES/lenna_descend.ppm"
#define DESCEND 1
#define SEUIL 4000

int main(int argc,char* argv[])
{
  // Création lecture et chargement de l'image
  image picture = FAIRE_image();

  int ok = image_charger(picture, IMAGE);

  if(ok == 0)
  {
    quadtree q;
    if(DESCEND)
    {
      // Traitement
      q = split_image(picture, SEUIL);
    }
    else
    {
      q = create_default_quadtree(0, 0, image_give_largeur(picture)-1, image_give_hauteur(picture)-1, 4);
      init_quadtree(q, picture);
      update_quadtree(q, picture, SEUIL);
    }    

    unsigned char couleur[3];
    couleur[0] = 0;
    couleur[1] = 0;
    couleur[2] = 0;

    draw_quadtree(picture, q, couleur);

    image_sauvegarder(picture, DESTINATION);
    delete_quadtree(&q);
  }
  else
    printf("Erreur d'ouverture d'image\n");

  //image_to_stream(picture, stdout);
  // libération mémoire
  DEFAIRE_image(picture);
  return 0;
} 
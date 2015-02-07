#include <stdio.h>
#include "image.h"
#include "objet.h"
#include "image_util.h"
#include "point.h"
#include "quadtree.h"

int main(int argc,char* argv[])
{

  image degrade=FAIRE_image();
  //image_initialize(degrade,3,512,512);
   
  int color[3]={255,0,0};
  int col[3];
  int bleu[]={0,0,255};
  Point milieu;
  int * pix,nb_pix;
  float sum[3]={0.0,0.0,0.0};
  int i;
  image_initialize(degrade,3,512,512);
  image_debut(degrade);  // On se positionne au début
  do
    {
      do
	{
	  for(i=0;i<3;i++)
		col[i]=color[i]/2;
	  image_ecrire_pixel(degrade,col);
	}
      while(image_pixel_droite(degrade));// On  parcourt la ligne de gauche à droite
      color[1]++;color[2]++;
    }
  while(image_pixel_suivant(degrade)); // On passe à la ligne suivante

 COORDX(milieu)=0;
 COORDY(milieu)=255;
 image_move_to(degrade,&milieu);

do
{
	image_ecrire_pixel(degrade,bleu);
}
while(image_pixel_droite(degrade));

// calcul de la couleur moyenne de R par un parcour de l'image 
  nb_pix=0;
  image_debut(degrade);
  do
    {
      pix=image_lire_pixel(degrade);
      nb_pix++;
      for(i=0;i<DIM_MAX;i++)
	sum[i]+=pix[i];
    }
  while(image_pixel_suivant(degrade));
  fprintf(stderr,"moyenne: (%f,%f,%f)\n",
	  sum[0]/nb_pix,
	  sum[1]/nb_pix,
	  sum[2]/nb_pix);



  
  // RAJOUT PAR NOUS  
  quadtree q;

  q=split_image(degrade, 4000);

 // draw_quadtree(degrade, q, 0);

  delete_quadtree(q); 

  free(q);
  // EO RAJOUT PAR NOUS 

  // image_to_stream(degrade,stdout);
   DEFAIRE_image(degrade);
  return 0;
}
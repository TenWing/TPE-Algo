#include <stdio.h>
#include "image.h"
#include "image_util.h"
#include "quadtree.h"

int main(int argc,char* argv[])
{
  image degrade=FAIRE_image();
  int color[3]={255,0,0};
  int col[3];
  int bleu[]={0,0,255};
  Point milieu;
  int * pix,nb_pix;
  float sum[3]={0.0,0.0,0.0};
  int i;
  image_initialize(degrade,3,512,512);
  image_debut(degrade); /* On se positionne au début*/
  do
    {
      do
	{
	  for(i=0;i<3;i++)
		col[i]=color[i]/2;
	  image_ecrire_pixel(degrade,col);
	}
      while(image_pixel_droite(degrade));/* On  parcourt la ligne de gauche à droite*/
      color[1]++;color[2]++;
    }
  while(image_pixel_suivant(degrade));/* On passe à la ligne suivante*/

 COORDX(milieu)=0;
 COORDY(milieu)=255;
 image_move_to(degrade,&milieu);

do
{
	image_ecrire_pixel(degrade,bleu);
}
while(image_pixel_droite(degrade));

/* calcul de la couleur moyenne de R par un parcour de l'image*/
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
  unsigned char* relevant = malloc(sizeof(unsigned char) * image_give_dim(degrade));
  int* nombre_pixel = malloc(sizeof(int));
  double* sum_intensity;
  double* sum_square_intensity;
  quadtree q;

  image_read_pixel(degrade,5,5,relevant);

  sum_intensity = (double*) malloc(image_give_dim(degrade)*sizeof(double));
  sum_square_intensity = (double*) malloc(image_give_dim(degrade)*sizeof(double));

  give_moments(degrade, 5, 5, 500, 500, nombre_pixel, sum_intensity, sum_square_intensity);
  printf("%d, %lf, %lf\n", *nombre_pixel, sum_intensity[2], sum_square_intensity[2]);
  getchar();

  q = create_quadtree();

  printf("%p\n", q);
  quadtree_subdivide(q);
 // printf("%p\n", q->sons[0]);
  getchar();
  free(relevant);
  free(nombre_pixel);
  free(sum_intensity);
  free(sum_square_intensity);

  
  // EO RAJOUT PAR NOUS 

  image_to_stream(degrade,stdout);
  DEFAIRE_image(degrade);
  return 0;
}
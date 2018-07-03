
#include <math.h>
#include <float.h>
#include <stdio.h>
#include "nr_util.h"
#include "ad_globl.h"
#include "ad_prime.h"
#include "ad_matrx.h"
#include "ad_frsnl.h"
#include "ad_prime.h"
#include "ad_cone.h"


static void
PrintTestResults (int test, int cas, struct AD_slab_type *slab,
		  double aUR1, double aUT1, double aURU, double aUTU,
		  double bUR1, double bUT1, double bURU, double bUTU)
{
  printf ("\nTest:%d.%d\n", test, cas);
  printf ("Oblique angle           %10.5f\n",
	  acos (slab.cos_angle) * 180 / 3.1415926);
  printf ("Cosine of oblique angle %10.5f\n", slab.cos_angle);
  printf ("Albedo                  %10.5f\n", slab->a);
  printf ("Optical Depth           %10.5f\n", slab->b);
  printf ("Anisotropy              %10.5f\n", slab->g);
  printf ("Index for slab          %10.5f\n", slab->n_slab);
  printf ("Index for top slide     %10.5f\n", slab->n_top_slide);
  printf ("Index for bot slide     %10.5f\n", slab->n_bottom_slide);
  printf ("            truth        cone\n");
  printf ("UR1     %10.5f    %10.5f\n", aUR1, bUR1);
  printf ("UT1     %10.5f    %10.5f\n", aUT1, bUT1);
  printf ("URU     %10.5f    %10.5f\n", aURU, bURU);
  printf ("UTU     %10.5f    %10.5f\n", aUTU, bUTU);
}



static void
PrintUnityResults (int test, int cas, struct AD_slab_type *slab,
		   double aUR1, double aUT1, double aURU, double aUTU,
		   double bUR1, double bUT1, double bURU, double bUTU)
{
  double denom = 1 - slab.cos_angle * slab.cos_angle;

  printf ("\nTest:%d.%d\n", test, cas);
  printf ("Cone angle           %10.5f\n",
	  acos (slab.cos_angle) * 180 / 3.1415926);
  printf ("Cosine of cone angle %10.5f\n", slab.cos_angle);
  printf ("Albedo               %10.5f\n", slab->a);
  printf ("Optical Depth        %10.5f\n", slab->b);
  printf ("Anisotropy           %10.5f\n", slab->g);
  printf ("Index for slab       %10.5f\n", slab->n_slab);
  printf ("Index for top slide  %10.5f\n", slab->n_top_slide);
  printf ("Index for bot slide  %10.5f\n", slab->n_bottom_slide);
  printf ("            truth        cone\n");
  printf ("UR1               %10.5f\n", aUR1);
  printf ("UT1               %10.5f\n", aUT1);
  printf ("UR1+UT1                  %10.5f\n", aUR1 + aUT1);
  printf ("URU               %10.5f\n", aURU);
  printf ("UTU               %10.5f\n", aUTU);
  printf ("URU+UTU                  %10.5f\n", aURU + aUTU);
  printf ("rc + rd/(1-mu^2) = %10.5f\n", bUR1 - (bUR1 - aUR1) / denom);
  printf ("tc + td/(1-mu^2) = %10.5f\n", bUT1 - (bUT1 - aUT1) / denom);
  printf ("           total = %10.5f\n", bUR1 - (bUR1 - aUR1) / denom +
	  bUT1 - (bUT1 - aUT1) / denom);
  printf ("rc + rd/(1-mu^2) = %10.5f\n", bURU - (bURU - aURU) / denom);
  printf ("tc + td/(1-mu^2) = %10.5f\n", bUTU - (bUTU - aUTU) / denom);
  printf ("           total = %10.5f\n", bURU - (bURU - aURU) / denom +
	  bUTU - (bUTU - aUTU) / denom);
}



int
main (int argc, char **argv)
{
  double aUR1, aURU, aUT1, aUTU, bUR1, bURU, bUT1, bUTU;
  struct AD_slab_type slab;
  int N = 48;



  slab.n_slab = 1.0;
  slab.n_top_slide = 1.0;
  slab.n_bottom_slide = 1.0;
  slab.b_top_slide = 0;
  slab.b_bottom_slide = 0;
  slab.a = 0.0;
  slab.b = 0.1;
  slab.g = 0.0;
  N = 12;
  slab.phase_function = HENYEY_GREENSTEIN;

  slab.cos_angle = 1;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (1, 1, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);

  slab.a = 0.5;
  slab.b = 0.5;
  slab.g = 0.875;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (1, 2, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);

  slab.a = 0.0;
  slab.b = 0.1;
  slab.g = 0.875;
  slab.n_slab = 1.4;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (1, 3, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);

  slab.a = 0.5;
  slab.b = 0.5;
  slab.g = 0.875;
  slab.n_slab = 1.4;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (1, 4, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);

  slab.n_top_slide = 1.5;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (1, 5, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);

  slab.n_bottom_slide = 1.6;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (1, 6, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);




  printf
    ("*****************************************************************\n");
  printf
    ("See page 256-257 in van de Hulst, Multiple Light Scattering, volume 1\n");
  slab.cos_angle = 0.5;
  slab.n_slab = 1.0;
  slab.n_top_slide = 1.0;
  slab.n_bottom_slide = 1.0;
  slab.b_top_slide = 0;
  slab.b_bottom_slide = 0;
  slab.b = 1.0;
  slab.a = 0.99;
  slab.g = 0.00;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  aUR1 = 0.48652;
  aUT1 = 0.49163;
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (4, 1, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);

  printf
    ("*****************************************************************\n");
  printf
    ("See page 424-424 in van de Hulst, Multiple Light Scattering, volume 2\n");
  slab.b = 4.0;
  slab.g = 0.5;
  RT (N, &slab, &aUR1, &aUT1, &aURU, &aUTU);
  aUR1 = 0.61996;
  aUT1 = 0.30605;
  RT_Cone (N, &slab, slab.cos_angle, OBLIQUE, &bUR1, &bUT1, &bURU, &bUTU);
  PrintTestResults (4, 2, &slab, aUR1, aUT1, aURU, aUTU, bUR1, bUT1, bURU,
		    bUTU);


  return 0;
}

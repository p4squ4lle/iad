/*1:*/
#line 5 "ad_layers.w"

#include <math.h> 
#include <float.h> 
#include "nr_util.h"
#include "ad_globl.h"
#include "ad_bound.h"
#include "ad_doubl.h"
#include "ad_prime.h"
#include "ad_matrx.h"
#include "ad_prime.h"

/*4:*/
#line 48 "ad_layers.w"

/*3:*/
#line 36 "ad_layers.w"

void RT_Layers_All(int n,
double nslab,
double ntopslide,
double nbottomslide,
int nlayers,
double a[],
double b[],
double g[],
double*dUR1,double*dUT1,double*dURU,double*dUTU,
double*uUR1,double*uUT1,double*uURU,double*uUTU)

/*:3*/
#line 49 "ad_layers.w"

{
/*6:*/
#line 77 "ad_layers.w"

struct AD_slab_type slab;
struct AD_method_type method;
double*R01,*R10,*T01,*T10;
double*R34,*R43,*T34,*T43;
double**R12,**R21,**T12,**T21;
double**R23,**R32,**T23,**T32;
double**R13,**R31,**T13,**T31;
double**atemp,**btemp;
int i;
*dUR1= -1;
*dUT1= -1;
*dURU= -1;
*dUTU= -1;
*uUR1= -1;
*uUT1= -1;
*uURU= -1;
*uUTU= -1;

/*:6*/
#line 51 "ad_layers.w"

/*5:*/
#line 64 "ad_layers.w"


if(nlayers<1)return;
if(nslab<0)return;
if(ntopslide<0)return;
if(nbottomslide<0)return;

for(i= 0;i<nlayers;i++){
if(a[i]<0||a[i]> 1)return;
if(b[i]<0)return;
if(g[i]<-1||g[i]> 1)return;
}

/*:5*/
#line 52 "ad_layers.w"

/*7:*/
#line 96 "ad_layers.w"


R12= dmatrix(1,n,1,n);
R21= dmatrix(1,n,1,n);
T12= dmatrix(1,n,1,n);
T21= dmatrix(1,n,1,n);

R23= dmatrix(1,n,1,n);
R32= dmatrix(1,n,1,n);
T23= dmatrix(1,n,1,n);
T32= dmatrix(1,n,1,n);

R13= dmatrix(1,n,1,n);
R31= dmatrix(1,n,1,n);
T13= dmatrix(1,n,1,n);
T31= dmatrix(1,n,1,n);

atemp= dmatrix(1,n,1,n);
btemp= dmatrix(1,n,1,n);

/*:7*/
#line 53 "ad_layers.w"

/*9:*/
#line 136 "ad_layers.w"

slab.n_slab= nslab;
slab.n_top_slide= ntopslide;
slab.n_bottom_slide= nbottomslide;
slab.b_top_slide= 0;
slab.b_bottom_slide= 0;
slab.a= 0.0;
slab.b= 0.0;
slab.g= 0.0;
slab.phase_function= HENYEY_GREENSTEIN;
slab.cos_angle= 1.0;

/*:9*/
#line 54 "ad_layers.w"

/*10:*/
#line 155 "ad_layers.w"

RT_Matrices(n,&slab,&method,R23,T23);
Copy_Matrix(n,R23,R32);
Copy_Matrix(n,T23,T32);

/*:10*/
#line 55 "ad_layers.w"

/*8:*/
#line 119 "ad_layers.w"

R01= dvector(1,n);
R10= dvector(1,n);
T01= dvector(1,n);
T10= dvector(1,n);
Init_Boundary(slab,n,R01,R10,T01,T10,TOP_BOUNDARY);

R34= dvector(1,n);
R43= dvector(1,n);
T34= dvector(1,n);
T43= dvector(1,n);
Init_Boundary(slab,n,R34,R43,T34,T43,BOTTOM_BOUNDARY);

/*:8*/
#line 56 "ad_layers.w"

/*11:*/
#line 165 "ad_layers.w"


while(nlayers>=1){
nlayers--;
slab.a= a[nlayers];
slab.b= b[nlayers];
slab.g= g[nlayers];
RT_Matrices(n,&slab,&method,R12,T12);
Add(n,R12,R12,T12,T12,R23,R32,T23,T32,R13,R31,T13,T31);
Copy_Matrix(n,R13,R23);
Copy_Matrix(n,R31,R32);
Copy_Matrix(n,T13,T23);
Copy_Matrix(n,T31,T32);
}

/*:11*/
#line 57 "ad_layers.w"

/*12:*/
#line 188 "ad_layers.w"


Add_Top(n,R01,R10,T01,T10,R23,R32,T23,T32,R13,R31,T13,T31,atemp,btemp);
Add_Bottom(n,R13,R31,T13,T31,R34,R43,T34,T43,R23,R32,T23,T32,atemp,btemp);
URU_and_UR1(n,slab.n_slab,R23,dURU,dUR1);
URU_and_UR1(n,slab.n_slab,R32,uURU,uUR1);
Transpose_Matrix(n,T23);
Transpose_Matrix(n,T32);
URU_and_UR1(n,slab.n_slab,T23,dUTU,dUT1);
URU_and_UR1(n,slab.n_slab,T32,uUTU,uUT1);

/*:12*/
#line 58 "ad_layers.w"

/*13:*/
#line 199 "ad_layers.w"

free_dvector(R01,1,n);
free_dvector(R10,1,n);
free_dvector(T01,1,n);
free_dvector(T10,1,n);

free_dmatrix(R12,1,n,1,n);
free_dmatrix(R21,1,n,1,n);
free_dmatrix(T12,1,n,1,n);
free_dmatrix(T21,1,n,1,n);

free_dmatrix(R23,1,n,1,n);
free_dmatrix(R32,1,n,1,n);
free_dmatrix(T23,1,n,1,n);
free_dmatrix(T32,1,n,1,n);

free_dmatrix(R13,1,n,1,n);
free_dmatrix(R31,1,n,1,n);
free_dmatrix(T13,1,n,1,n);
free_dmatrix(T31,1,n,1,n);

free_dmatrix(atemp,1,n,1,n);
free_dmatrix(btemp,1,n,1,n);

free_dvector(R34,1,n);
free_dvector(R43,1,n);
free_dvector(T34,1,n);
free_dvector(T43,1,n);

/*:13*/
#line 59 "ad_layers.w"

}

/*:4*/
#line 16 "ad_layers.w"

/*15:*/
#line 242 "ad_layers.w"

/*14:*/
#line 231 "ad_layers.w"

void RT_Layers(int n,
double nslab,
double ntopslide,
double nbottomslide,
int nlayers,
double a[],
double b[],
double g[],
double*UR1,double*UT1,double*URU,double*UTU)

/*:14*/
#line 243 "ad_layers.w"

{
double uUR1,uUT1,uURU,uUTU;

RT_Layers_All(n,nslab,ntopslide,nbottomslide,nlayers,a,b,g,\
UR1,UT1,URU,UTU,&uUR1,&uUT1,&uURU,&uUTU);
}/*:15*/
#line 17 "ad_layers.w"


/*:1*/

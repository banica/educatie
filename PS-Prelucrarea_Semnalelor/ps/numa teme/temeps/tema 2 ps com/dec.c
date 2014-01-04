#include "t2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>


// Coeficienti transformata wavelet directa
/*
#define	L0	 0.602949
#define	L1	 0.266864
#define	L2	-0.078223			
#define	L3	-0.016864
#define	L4	 0.026749

#define	H0	 0.557544
#define	H1	-0.295636
#define	H2	-0.028772
#define	H3	 0.045636
*/

// astia merg sunt cei de mai sus doar ca sunt  cu "-" pt L1 L3 si H1 H3
#define	L0	 0.602949
#define	L1	-0.266864
#define	L2	-0.078223			
#define	L3	-0.016864
#define	L4	 0.026749

#define	H0	 0.557544
#define	H1	+0.295636
#define	H2	-0.028772
#define	H3	-0.045636




// Valori cuantizare
#define	QM	 1.0
#define	QA3	 1.6
#define	QB3	 1.6
#define	QC3	 2.4
#define	QA2	 3.7
#define	QB2	 3.7
#define	QC2	 7.2
#define	QA1	11.5
#define	QB1 11.5
#define	QC1	29.4

extern FILE * fd;
extern FILE * fs;


unsigned int masca[10];

void wavelet(float* x,int sz);//functie de transformare x -vectorul de codificat ;sz-dimensiunea
void decuantizare(void); //functie opusa functiei de cuantizare
int get_context(int,int,int,int,int);
int get_mag(float);
void decodifica_biti_valoare();//functie de decodificare a bitilor
int write_my_bitmap();//functie utilizator de test pentru scrierea imaginii fara compresie(blocurile R,G,B)
int read_my_bitmap();//asemanatoare doar ca permite citirea 


float my_round(float x)//functie de stabilirea a partii intregi a unui numar
{
      if (x>=0) return floor(0.5+x);
      else return -floor(0.5-x);

}


void decomprima(void)
{
int i,j,k;		

/*******************************************************************/
/*******************************************************************/
//ETAPA 4 ->decodificarea 
/********************************************************************/
/*******************************************************************/

printf("\ndecompresie\n");
masca[9] = 0xFFFFFC00;        // pentru decodificarea valorilor negative
masca[8] = 0xFFFFFE00;
masca[7] = 0xFFFFFF00;
masca[6] = 0xFFFFFF80;
masca[5] = 0xFFFFFFC0;
masca[4] = 0xFFFFFFE0;
masca[3] = 0xFFFFFFF0;
masca[2] = 0xFFFFFFF8;
masca[1] = 0xFFFFFFFC;
masca[0] = 0xFFFFFFFE;
decodifica_biti_valoare();



/*******************************************************************/
/*******************************************************************/
//ETAPA 3 ->cuantizarea pentru Ax Bx Cx
/********************************************************************/
/*******************************************************************/
//read_my_bitmap();
decuantizare();


/*******************************************************************/
/*******************************************************************/
//ETAPA 2 ->transformarea imaginii cu transformata wavelet
/********************************************************************/
//Se aplica filtrele FTJ si FTS esantioanelor impare respectiv pare
/*******************************************************************/
//read_my_bitmap();
printf("\nAplicare transformata\n");

//'rup' vectorul linie cu linie si apoi coloana cu coloana
float * tmp ;//se va tine minte in el o linie sau o coloana
tmp=(float *)malloc(dy*sizeof(float *));
if(tmp==NULL){
		printf("Memorie insuficienta pt tmp!\n");
		return;
		}
int _2_p_y=128;//dimensiunea unui vector	2*p	pe y
int _2_p_x=128;//dimensiunea unui vector	2*p	pe x
int p;
//aici chiar nu stiu ce sa fac decat atunci cand imaginea e patrata
// in rest ce sa fac cu injumatatirea daca imaginea e foarte lata???

int cul=1;//culoarea care se decodifica -  1=red 2=green 3=blue
//s-a facut un singur ciclu.Se aplica wavelet prima data pentru red
//apoi pentru green si blue.dupa ce a terminat cu red se incrementeaza
//culoarea care se va decodifica (cul)
while(cul<4)//culoarea care se decodifica in momentul de fata
{		
//aplicare pe coloana ---------------------------------/
for (i=0,k=0;i<_2_p_x;i++,k++)  
           {                     //j+=2 
           for (j=0,p=0;j<_2_p_y;j++ ,p++) 
                   switch(cul)
                       {            
                       case 1:tmp[p]=r[j][i];break;
                       case 2:tmp[p]=g[j][i];break;
                       case 3:tmp[p]=b[j][i];break;                  
                       }//switch 1        

            wavelet(tmp,_2_p_y);  

          //dupa aplicare trebuie rescrise r,g,b
          // rgb <- tmp
               for (j=0,p=0;j<_2_p_y;j++ ,p++) 
                  { 
                   switch(cul)
                       {            
                       case 1:r[p][k]=tmp[p];break;
                       case 2:g[p][k]=tmp[p];break;
                       case 3:b[p][k]=tmp[p];break;                  
                       }//switch 1        
                  }             
           }//for 2 
//aplicare pe linie ----------------------------------------/
          for (j=0,p=0;j<_2_p_y;j++,p++)
           {
           //tmp <- rgb                 
           for (i=0,k=0;i<_2_p_x;i++ ,k++) 
                  { 
                   switch(cul)
                       {            
                       case 1:tmp[k]=r[j][i];break;
                       case 2:tmp[k]=g[j][i];break;
                       case 3:tmp[k]=b[j][i];break;                  
                       }//switch 1        
                  }             
            wavelet(tmp,_2_p_x);
          //dupa aplicare trebuie rescrise r,g,b
          // rgb <- tmp

           for (i=0,k=0;i<_2_p_x;i++  ,k++) 
                  { 
                   switch(cul)
                       {            
                       case 1:r[p][k]=tmp[k];break;
                       case 2:g[p][k]=tmp[k];break;
                       case 3:b[p][k]=tmp[k];break;                  
                       }//switch 1        
                  }             

           }//for 1 



_2_p_x*=2;_2_p_y*=2;//injumatatirea matricii

if ((_2_p_y>dy)||(_2_p_x>dx)) 
   {printf("\t [%i/3] ",cul);
   cul++; 
   _2_p_y=128;_2_p_x=128;
   };;

}//while

free(tmp);

/*******************************************************************/
//ETAPA 1 ->conversie de culoare
/********************************************************************/

// Aloca memorie pentru vectorii cu pointeti catre liniile
// matricilor r,g si b
// Y U V -reprezinta niste vectori : se aloca decat pentru o linie -pe coloana
//read_my_bitmap();
float * Y ;
Y=(float *)malloc(dy*sizeof(float *));
if(Y==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}

float * U ;
U=(float *)malloc(dy*sizeof(float *));
if(U==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}

float * V;
V=(float *)malloc(dy*sizeof(float *));
if(V==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}

//inmultirile intre matricea RGB si cea predefinita


//inmultirea    
printf("\nconversie culoare\n");
for (i=0;i<dx;i++)
 {
 for (j=0;j<dy;j++)
  {
    //mare dilema ----in laborator sunt inversati coeficientii 
    //fata de documentatie!!!!!!!!
  Y[j] = 1    * r[j][i] + 0.0042 * g[j][i] + 1.4014 * b[j][i];
  U[j] = 1    * r[j][i] - 0.3342 * g[j][i] - 0.7136 * b[j][i];  
  V[j] = 1    * r[j][i] + 1.7809 * g[j][i] + 0.0055 * b[j][i];

  }//end of for 2.1

 //se copiaza rezultatul Y U V la loc in r g b pt 

 for (j=0;j<dy;j++)
 { 
 r[j][i]=Y[j];
 g[j][i]=U[j];
 b[j][i]=V[j]; 
}//end of for 2.2


} //end of for 1



/**************************************/
///test !!!!!!!!!!!!!!!!! a se sterge 
////////////////////////////////////
//write_my_bitmap();
/**************************************/
///end of test !!!!!!!!!!!!!!!!! a se sterge 
////////////////////////////////////





/////////////////////////////////////////////////////////

////////////****  zona dealocare memorie *******///////
free((void*)Y);
free((void*)U);
free((void*)V);
printf("\nAm dealocat zonele de momorie ");
//getch();
///////////////////////////////////////////////////////










   
}//end of decomprima(void)



//----------------------------------------------------------------/
//---------------   WAVELET TRANSORM    -------------------------/
//---------------------------------------------------------------/

void wavelet(float * x,int sz)//sz - dimensiunea unei linii ce se prelucreaza
                              //sz =2 *p     
{
int i,j,k;                              
int p=sz/2;

//lungime L + lungime H=2*p
float *L=(float *)malloc(2*p*sizeof(float *));
if(L==NULL){
		printf("Memorie insuficienta pt L!\n");
		return;
		};

float *H=(float *)malloc(2*p*sizeof(float *));
if(H==NULL){
		printf("Memorie insuficienta pt H!\n");
		return;
		};

float *sum=(float *)malloc(2*p*sizeof(float *));//suma vectorilor S si D
if(sum==NULL){
		printf("Memorie insuficienta pt sum !\n");
		return;
		};


for (i=0;i<=p-1;i++) 
   {L[i*2+1 ]    =0  ; L[i*2   ]=x[i]     ;
    H[i*2+1 ]    =x[i+p];     ; H[i*2     ]  =0;
   } ;
   
/*
for (i=0;i<=p-1;i++) 
   {L[i*2+1 ]    =x[i]  ; L[i*2   ]=    0    ;
    H[i*2+1 ]    =0     ; H[i*2     ]  =x[i+p];;
    }
*/
   
for (i=0;i<=2*p-1;i++)    
    sum[i]=0;
//************************************************************//
//X -vectorul de date ce se prelucreaza
//************************************************************//


//************************************************************//
//se determina L(Q ^-1)
sum[0]=0*L[4] + H3*L[3] + H2*L[2] + H1*L[1]+ H0*L[0] +  H1*L[1] + H2*L[2] + H3*L[3] + 0*L[4];
sum[1]=0*L[3] + H3*L[2] + H2*L[1] + H1*L[0]+ H0*L[1] +  H1*L[2] + H2*L[3] + H3*L[4] + 0*L[5];
sum[2]=0*L[2] + H3*L[1] + H2*L[0] + H1*L[1]+ H0*L[2] +  H1*L[3] + H2*L[4] + H3*L[5] + 0*L[6];
sum[3]=0*L[1] + H3*L[0] + H2*L[1] + H1*L[2]+ H0*L[3] +  H1*L[4] + H2*L[5] + H3*L[6] + 0*L[7];
sum[4]=0*L[0] + H3*L[1] + H2*L[2] + H1*L[3]+ H0*L[4] +  H1*L[5] + H2*L[6] + H3*L[7] + 0*L[8];
        
for (k=5;k<=2*p-6;k++)
  {
                    
   sum[k]=0*L[k-4] + H3*L[k-3] + H2*L[k-2] + H1*L[k-1]+ H0*L[k+0] +
        H1*L[k+1] + H2*L[k+2] + H3*L[k+3] + 0*L[k+4];
  }

sum[2*p-5]=0*L[2*p-1] + H3*L[2*p-2] + H2*L[2*p-3] + H1*L[2*p-4]+ H0*L[2*p-5] +  H1*L[2*p-4] + H2*L[2*p-3] + H3*L[2*p-2] + 0*L[2*p-1];
sum[2*p-4]=0*L[2*p-2] + H3*L[2*p-1] + H2*L[2*p-2] + H1*L[2*p-3]+ H0*L[2*p-4] +  H1*L[2*p-3] + H2*L[2*p-2] + H3*L[2*p-1] + 0*L[2*p-2];
sum[2*p-3]=0*L[2*p-3] + H3*L[2*p-2] + H2*L[2*p-1] + H1*L[2*p-2]+ H0*L[2*p-3] +  H1*L[2*p-2] + H2*L[2*p-1] + H3*L[2*p-2] + 0*L[2*p-3];
sum[2*p-2]=0*L[2*p-4] + H3*L[2*p-3] + H2*L[2*p-2] + H1*L[2*p-1]+ H0*L[2*p-2] +  H1*L[2*p-1] + H2*L[2*p-2] + H3*L[2*p-3] + 0*L[2*p-4];
sum[2*p-1]=0*L[2*p-5] + H3*L[2*p-4] + H2*L[2*p-3] + H1*L[2*p-2]+ H0*L[2*p-1] +  H1*L[2*p-2] + H2*L[2*p-3] + H3*L[2*p-4] + 0*L[2*p-5];


//************************************************************//
//se determina H(Q ^-1)
sum[0]+= L4*H[4] +L3*H[3] + L2*H[2] + L1*H[1]+ L0*H[0] +  L1*H[1] + L2*H[2] + L3*H[3] + L3*H[4];
sum[1]+= L4*H[3] +L3*H[2] + L2*H[1] + L1*H[0]+ L0*H[1] +  L1*H[2] + L2*H[3] + L3*H[4] + L3*H[5];
sum[2]+= L4*H[2] +L3*H[1] + L2*H[0] + L1*H[1]+ L0*H[2] +  L1*H[3] + L2*H[4] + L3*H[5] + L3*H[6];
sum[3]+= L4*H[1] +L3*H[0] + L2*H[1] + L1*H[2]+ L0*H[3] +  L1*H[4] + L2*H[5] + L3*H[6] + L3*H[7];
sum[4]+= L4*H[0] +L3*H[1] + L2*H[2] + L1*H[3]+ L0*H[4] +  L1*H[5] + L2*H[6] + L3*H[7] + L3*H[8];
        
for (k=5;k<=2*p-6;k++)
  {
                    
   sum[k]+=+ L4*H[k-4] + L3*H[k-3] + L2*H[k-2] + L1*H[k-1]+ L0*H[k+0] +
         L1*H[k+1] + L2*H[k+2] + L3*H[k+3] + L4*H[k+4];
  }

sum[2*p-5]+=L4*H[2*p-1] +L3*H[2*p-2] + L2*H[2*p-3] + L1*H[2*p-4]+ L0*H[2*p-5] +  L1*H[2*p-4] + L2*H[2*p-3] + L3*H[2*p-2]+ L4*H[2*p-1];
sum[2*p-4]+=L4*H[2*p-2] +L3*H[2*p-1] + L2*H[2*p-2] + L1*H[2*p-3]+ L0*H[2*p-4] +  L1*H[2*p-3] + L2*H[2*p-2] + L3*H[2*p-1]+ L4*H[2*p-2];
sum[2*p-3]+=L4*H[2*p-3] +L3*H[2*p-2] + L2*H[2*p-1] + L1*H[2*p-2]+ L0*H[2*p-3] +  L1*H[2*p-2] + L2*H[2*p-1] + L3*H[2*p-2]+ L4*H[2*p-3];
sum[2*p-2]+=L4*H[2*p-4] +L3*H[2*p-3] + L2*H[2*p-2] + L1*H[2*p-1]+ L0*H[2*p-2] +  L1*H[2*p-1] + L2*H[2*p-2] + L3*H[2*p-3]+ L4*H[2*p-4];
sum[2*p-1]+=L4*H[2*p-5] +L3*H[2*p-4] + L2*H[2*p-3] + L1*H[2*p-2]+ L0*H[2*p-1] +  L1*H[2*p-2] + L2*H[2*p-3] + L3*H[2*p-4]+ L4*H[2*p-5];

//************************************************************//

//a 3-a incercare
for (k=0;k<=2*p-1;k++)
  x[k]=sum[k]*2;
    
 


//************************************************************//


//-------------dealocare
free((void*)L);
free((void*)H);
free((void*)sum);
};//end of wavelet

//---------------------------------------------------------/
//-------------functie de cuantizare ----------------------/
//---------------------------------------------------------/

void decuantizare()
{
float q_st_jos;//coeficient de esantionare cadran st jos
float q_dr_sus;//coeficient de esantionare cadran dr sus
float q_dr_jos;//coeficient de esantionare cadran dr sus
int stop=0;
int i,j,k;

int _2_p_y=dy,_2_p_x=dx;


while(stop!=1)
{        
         
//se stabileste q pt fiecare cadran

switch (dy/_2_p_x)
{
case  1:{q_st_jos=QB1;q_dr_sus=QA1;q_dr_jos=QC1;break;}
case  2:{q_st_jos=QB2;q_dr_sus=QA2;q_dr_jos=QC2;break;}
case  4:{q_st_jos=QB3;q_dr_sus=QA3;q_dr_jos=QC3;break;}
case  8:{q_st_jos=QM ;q_dr_sus=QM ;q_dr_jos=QM ;break;}

}


                                 
//aplicare pe colt st jos  ***********************************/                                 
          for (j=_2_p_y / 2  ;   j<_2_p_y     ; j++)
            for (i=0         ;   i<_2_p_x /2  ; i++) 
                  {
                   r[j][i]=my_round(r[j][i])*q_st_jos;
                   g[j][i]=my_round(g[j][i])*q_st_jos;
                   b[j][i]=my_round(b[j][i])*q_st_jos;
                   
                  }//for 1 

//aplicare pe colt dr sus  **********************************/

         for (j= 0          ;  j<_2_p_y /2     ; j++)  
           for (i=_2_p_x/2  ;  i<_2_p_x        ; i++)
                  {r[j][i]=my_round(r[j][i])*q_dr_sus; 
                   g[j][i]=my_round(g[j][i])*q_dr_sus;
                   b[j][i]=my_round(b[j][i])*q_dr_sus;                  
                  }//for 1 
            
//aplicare pe colt dr jos  **********************************/
         for (j=_2_p_y / 2       ; j<_2_p_y       ;j++)  
           for (i=_2_p_x / 2     ; i<_2_p_x       ;i++)
                  {r[j][i]=my_round(r[j][i])*q_dr_jos; 
                   g[j][i]=my_round(g[j][i])*q_dr_jos;
                   b[j][i]=my_round(b[j][i])*q_dr_jos;                  
                  }//for 1 

//--se aplica doar daca suntem in cadranul M  -st sus
if (dy/_2_p_x==8)
         for (j=   0            ; j<_2_p_y/2     ;j++)  
         {for (i=  0            ; i<_2_p_x/2     ;i++)
                  {r[j][i]=my_round(r[j][i]*QM); 
                   g[j][i]=my_round(g[j][i]*QM);
                   b[j][i]=my_round(b[j][i]*QM);                  
                   }//for 1 

           }
            
_2_p_x/=2;_2_p_y/=2;//injumatatire

if ((_2_p_y<=32)||(_2_p_x<=32)) {printf("\n cuantizare ");stop=1;};;
}//while

}//end of decuantizare




//----------------------------------------------------------------/
//------------------ functie ce stabileste magnitudinea-----------/
//----------------------------------------------------------------/

int get_mag(int nr)
{
//functie ce da contextul
/*
Clasa (SSSS) - 4 biti 	Valoare diferenta
1 (0001)	-1,1
2 (0010)	-3,-2,2,3
3 (0011)	-7,...,-4,4,...7
4 (0100)	-15,...,-8,8,...,15
5 (0101)	-31,...,-16,16,...,31
6 (0110)	-63,...,-32,32,...,63
7 (0111)	-127,...,-64,64,...,127
8 (1000)	-255,...,-128,128,...,255
9 (1001)	-511,...,-256,256,...,511
10 (1010)	-1023,...,-512,512,...,1023
*/
int ret;
//if (nr==-65000) ret=-1;
if (nr==-65000) ret=-1;
else if (nr==0) ret=0;
else if ( (nr==-1)              || (nr ==1)     )       ret=1;
else if ( (  nr>=-3    && nr<=   -2   ) || (nr >=  2    && nr<=  3   ) ) ret=2;
else if ( (  nr>=-7    && nr<=   -4   ) || (nr >=  4    && nr<=  7   ) ) ret=3;
else if ( (  nr>=-15   && nr<=   -8   ) || (nr >=  8    && nr<=  15  ) ) ret=4;
else if ( (  nr>=-31   && nr<=   -16  ) || (nr >=  16   && nr<=  31  ) ) ret=5;
else if ( (  nr>=-63   && nr<=   -32  ) || (nr >= 32    && nr<=  63  ) ) ret=6;
else if ( (  nr>=-127  && nr<=   -64  ) || (nr >= 64    && nr<=  127 ) ) ret=7;
else if ( (  nr>=-255  && nr<=   -128 ) || (nr >= 128   && nr<=  255 ) ) ret=8;
else if ( (  nr>=-511  && nr<=   -256 ) || (nr >= 256  && nr<=   511 ) ) ret=9;
else if ( (  nr>=-1023                ) || (nr <=1023                ) ) ret=10;




return ret;
}

//----------------------------------------------------------------/
//------------------ functie ce stabileste contextul   -----------/
//----------------------------------------------------------------/

//functie ce stabileste contextul
int get_context(int coef_S,int coef_N,int coef_V,int coef_NV,int prag)
{
    int context=0;
    
    if (get_mag(coef_S)>=prag)
      context+=1;;

    if (get_mag(coef_N)>=prag)
      context+=2;;

    if (get_mag(coef_V)>=prag)
      context+=4;;

    if (get_mag(coef_NV)>=prag)
      context+=8;;
    
    context=16*(prag-1)+context;
    return context;  
      
      
}


//----------------------------------------------------------------/
//------------------ functie ce decodifica patratele     -----------/
//----------------------------------------------------------------/


void decodifica_biti_valoare()
{

int _2_p_x=dx/4;
int _2_p_y=dy/4;
int prag;//prag 
int mag;//magnitudine
int i=0,j=0,cont;
const int nul=0;//valoare care sa da unui nu exista vecin
int cul=1;
int S,N,NV,V;


char * tmp1=(char *)malloc(dx/8);

 for (j=0;j<dy/8;j++)
 {
     fread(tmp1,dx/8,1,fs);
  for (i=0;i<dx/8;i++) 
     r[j][i]=tmp1[i];
 }
 for (j=0;j<dy/8;j++)
 {
  fread(tmp1,dx/8,1,fs);
  for (i=0;i<dx/8;i++) 
     g[j][i]=tmp1[i];
 }
 for (j=0;j<dy/8;j++)
 {
  fread(tmp1,dx/8,1,fs);
  for (i=0;i<dx/8;i++) 
     b[j][i]=tmp1[i];
 }
free(tmp1);
start_decompresie();

///////////////////////////////

while( (cul <=3) ) //se mareste dreptunghiul in care se
                                   //face analiza
{
                                   
                                   
//----------se scrie patratul A --------------                                  

for (j=0;j<_2_p_y/2;j++)//se face verificarea pe dy   
   {
                             
  for (i=_2_p_x/2;i<_2_p_x;i++)//se face verificarea pe dx   
       {
                                    //intf("\n %d",i);getch();
      
                                
        //corespund valorilor elementelor din matrici
        //verific daca am vecini  --doar general!!a se verifica indecsii            
        //elementul 0,0 
        
           // getch();        
          int coef; 
          //coef=1; 
          switch(cul)
          {
          case 1:coef=r[j][i];break;
          case 2:coef=g[j][i];break;
          case 3:coef=b[j][i];break;
          }
          if(_2_p_y==dy/4)
                          S=nul;
          else
                    switch(cul)
                    {
                               case 1:coef=r[j][i];S=r[j/2][_2_p_x/4+i/2];break;
                               case 2:coef=g[j][i];S=g[j/2][_2_p_x/4+i/2];break;
                               case 3:coef=b[j][i];S=b[j/2][_2_p_x/4+i/2];break;
                    }
          

         
         if(i==_2_p_x/2 && j==0)  //elem [0][0]
         {
                        V=nul;N=nul;NV=nul;
         }
          else if(i==_2_p_y/2) //prima coloana
         {
              switch(cul)
              {
                         case 1:V=nul;NV=nul;N=r[j-1][i];break;
                         case 2:V=nul;NV=nul;N=g[j-1][i];break;
                         case 3:V=nul;NV=nul;N=b[j-1][i];break;
              }
              
              
         }          
         else if(j==0)        //prima linie
         {
              switch(cul)
              {
                         case 1:V=r[j][i-1];NV=nul;N=nul;break;
                         case 2:V=g[j][i-1];NV=nul;N=nul;break;
                         case 3:V=b[j][i-1];NV=nul;N=nul;break;
              }
         }
        
         else // restu'
         {
              switch(cul)
              {
                         case 1:V=r[j][i-1];NV=r[j-1][i-1];N=r[j-1][i];break;
                         case 2:V=g[j][i-1];NV=g[j-1][i-1];N=g[j-1][i];break;
                         case 3:V=b[j][i-1];NV=b[j-1][i-1];N=b[j-1][i];break;
              }
         }
        

//scrie magnitudinea
      int tmp,poz_neg=0;
       prag=10;
       while(prag>0)
       {
       cont=get_context(S,N,V,NV,prag);
       if(decomprima_bit(cont)==1) {break;}
       else    prag--;
       }
       tmp=0;
     mag=prag;
     if(prag)
        {
                tmp = tmp*2 + decomprima_bit(cont);
                if(tmp) poz_neg =  1;
                else    poz_neg = -1;
                mag=prag-1;
                while(mag-- > 0)
                        tmp = tmp*2 + decomprima_bit(cont);
                if(poz_neg == -1)
                {
                        tmp |= masca[prag-1];
                        tmp  =-(~tmp);
                }
        }
        

        switch(cul)
        {
                   case 1: r[j][i]=(float)tmp;break;
                   case 2: g[j][i]=(float)tmp;break;
                   case 3: b[j][i]=(float)tmp;
                   
        }
       

       }//for end of verificare pe dx

  }//for end of verificare pe dy

//-----------end of scrie patrat A/

//----------se scrie patratul B --------------                                  
printf("\n A..");//getch();
for (j=_2_p_y/2;j<_2_p_y;j++)//se face verificarea pe dy   
   {
  for (i=0;i<_2_p_x/2;i++)//se face verificarea pe dx   
       {
      
        int N,V,NV,S;//corespund valorilor elementelor din matrici
        //verific daca am vecini  --doar general!!a se verifica indecsii            
        //elementul 0,0 

          int coef;
          switch(cul)
          {
          case 1:coef=r[j][i];break;
          case 2:coef=g[j][i];break;
          case 3:coef=b[j][i];break;
          }
          if(_2_p_y==dy/4)
                          S=nul;
          else
                    switch(cul)
                    {
                               case 1:coef=r[j][i];S=r[_2_p_y/4+j/2][i/2];break;
                               case 2:coef=g[j][i];S=g[_2_p_y/4+j/2][i/2];break;
                               case 3:coef=b[j][i];S=b[_2_p_y/4+j/2][i/2];break;
                    }
          

         
         if(i==0 && j==_2_p_y/2)  //elem [0][0]
         {
                        V=nul;N=nul;NV=nul;
         }  
         else if(i==0) //prima coloana
         {
              switch(cul)
              {
                         case 1:V=nul;NV=nul;N=r[j-1][i];break;
                         case 2:V=nul;NV=nul;N=g[j-1][i];break;
                         case 3:V=nul;NV=nul;N=b[j-1][i];break;
              }
              
              
         }        
         else if(j==_2_p_y/2)        //prima linie
         {
              switch(cul)
              {
                         case 1:V=r[j][i-1];NV=nul;N=nul;break;
                         case 2:V=g[j][i-1];NV=nul;N=nul;break;
                         case 3:V=b[j][i-1];NV=nul;N=nul;break;
              }
         }
         
         else // restu'
         {
              switch(cul)
              {
                         case 1:V=r[j][i-1];NV=r[j-1][i-1];N=r[j-1][i];break;
                         case 2:V=g[j][i-1];NV=g[j-1][i-1];N=g[j-1][i];break;
                         case 3:V=b[j][i-1];NV=b[j-1][i-1];N=b[j-1][i];break;
              }
         }

                 int tmp,poz_neg;
       prag=10;
       while(prag>0)
       {
       cont=get_context(S,N,V,NV,prag);
       if(decomprima_bit(cont)==1) {break;}
       else    prag--;
       }
     mag=prag;tmp=0;
     if(prag)
        {
                tmp = tmp*2 + decomprima_bit(cont);
               if(tmp) poz_neg =  1;
                 else    poz_neg = -1;
                mag=prag-1;
                while(mag-- > 0)
                        tmp = tmp*2 + decomprima_bit(cont);
                if(poz_neg == -1)
                {
                        tmp |= masca[prag-1];
                        tmp  =-(~tmp);
                }
        }

        switch(cul)
        {
                   case 1: r[j][i]=(float)tmp;break;
                   case 2: g[j][i]=(float)tmp;break;
                   case 3: b[j][i]=(float)tmp;
                   
        }
   
   
    }//for end of verificare pe dx
  
 }//for 2 end of verificare pe dy
printf("\n B..");//getch();
//-----------end of scrie patrat B


//----------se scrie patratul C --------------                                  

for (j=_2_p_y/2;j<_2_p_y;j++)//se face verificarea pe dy   
   {
  for (i=_2_p_x/2;i<_2_p_x;i++)//se face verificarea pe dx   
       {
      
        int N,V,NV,S;//corespund valorilor elementelor din matrici
        //verific daca am vecini  --doar general!!a se verifica indecsii            
        //elementul 0,0 

          int coef;  
           
          switch(cul)
          {
          case 1:coef=r[j][i];break;
          case 2:coef=g[j][i];break;
          case 3:coef=b[j][i];break;
          }
          if(_2_p_y==dy/4)
                          S=nul;
          else
                    switch(cul)
                    {
                               case 1:coef=r[j][i];S=r[_2_p_y/4+j/2][i/2];break;
                               case 2:coef=g[j][i];S=g[_2_p_y/4+j/2][i/2];break;
                               case 3:coef=b[j][i];S=b[_2_p_y/4+j/2][i/2];break;
                    }
      
         
         if(i==_2_p_x/2 && j==_2_p_y/2)  //elem [0][0]
         {
                        V=nul;N=nul;NV=nul;
         } 
         else if(i==_2_p_x/2) //prima coloana
         {
              switch(cul)
              {
                         case 1:V=nul;NV=nul;N=r[j-1][i];break;
                         case 2:V=nul;NV=nul;N=g[j-1][i];break;
                         case 3:V=nul;NV=nul;N=b[j-1][i];break;
              }
              
              
         }         
         else if(j==_2_p_y/2)        //prima linie
         {
              switch(cul)
              {
                         case 1:V=r[j][i-1];NV=nul;N=nul;break;
                         case 2:V=g[j][i-1];NV=nul;N=nul;break;
                         case 3:V=b[j][i-1];NV=nul;N=nul;break;
              }
         }
         
         else // restu'
         {
              switch(cul)
              {
                         case 1:V=r[j][i-1];NV=r[j-1][i-1];N=r[j-1][i];break;
                         case 2:V=g[j][i-1];NV=g[j-1][i-1];N=g[j-1][i];break;
                         case 3:V=b[j][i-1];NV=b[j-1][i-1];N=b[j-1][i];break;
              }
         }


        

//scrie magnitudinea
                  int tmp,poz_neg;
       prag=10;
       while(prag>0)
       {
       cont=get_context(S,N,V,NV,prag);
       if(decomprima_bit(cont)==1) {break;}
       else    prag--;
       }
     mag=prag;tmp=0;
     if(prag)
        {
                tmp = tmp*2 + decomprima_bit(cont);
                          if(tmp) poz_neg =  1;
                                else    poz_neg = -1;
                mag=prag-1;
                while(mag-- > 0)
                        tmp = tmp*2 + decomprima_bit(cont);
                if(poz_neg == -1)
                {
                        tmp |= masca[prag-1];
                        tmp  =-(~tmp);
                }
        }

        switch(cul)
        {
                   case 1: r[j][i]=(float)tmp;break;
                   case 2: g[j][i]=(float)tmp;break;
                   case 3: b[j][i]=(float)tmp;
                   
        }
                
       }//for  end of verificare pe dx
  
  }//for end of verificare pe dy

printf("\n C..");//getch();
//-----------end of scrie patrat C




printf("\t[%i/%i]",_2_p_x,dy); 

_2_p_y*=2;_2_p_x*=2;
if( (_2_p_y>dy) ||(_2_p_x>dx) ) {_2_p_y=dy/4;_2_p_x=dx/4; cul++;}


}



///////////////////////////////



}//end of functie


int write_my_bitmap()
{
    int i,j;
typedef	struct{	unsigned char	b,g,r;}rgb;

rgb * tmp1=(rgb *)malloc(1);

 for (j=0;j<dy;j++) 
  for (i=0;i<dx;i++) 
   {

   tmp1->r=r[j][i]-128;
   tmp1->g=g[j][i]-128;
   tmp1->b=b[j][i]-128;

   fwrite((unsigned char *)tmp1,1,sizeof(rgb),fd);
   }
free(tmp1);
fclose(fd);
} 

int read_my_bitmap()
{
    int i,j;
typedef	struct{	unsigned char	b,g,r;}rgb;

rgb * tmp1=(rgb *)malloc(1);

 for (j=0;j<dy;j++) 
  for (i=0;i<dx;i++) 
   {

   fread(tmp1,1,sizeof(rgb),fs);
   r[j][i]=tmp1->r-128;
   g[j][i]=tmp1->g-128;
   b[j][i]=tmp1->b-128;

   
   }
free(tmp1);
fclose(fs);
} 






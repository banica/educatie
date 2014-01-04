//#include <ansi_c.h>
#include <stdio.h>
#include <stdlib.h>
#include "t3d.h"
#define VALCONT 0

int max(int dx, int dy){
      
      return (dx>dy)?dx:dy;
}

int det_mag(int nr){//determinare magnitudine
int cf;
    
    cf=abs(nr);
	if(cf>=512) return 10;
	if(cf>=256) return 9;
	if(cf>=128) return 8;
	if(cf>=64)  return 7;
	if(cf>=32)  return 6;
	if(cf>=16)  return 5;
	if(cf>=8)   return 4;
	if(cf>=4)   return 3;
	if(cf>=2)   return 2;
	if(cf>=1)   return 1;
	return 0;
}

int det_c(int coef_S,int coef_N,int coef_V,int coef_NV,int prag){//determinare context

    int context=0;
    
    if (det_mag(coef_S)>=prag)
      context+=1;

    if (det_mag(coef_N)>=prag)
      context+=2;

    if (det_mag(coef_V)>=prag)
      context+=4;

    if (det_mag(coef_NV)>=prag)
      context+=8;
    
    context=16*(prag-1)+context;
    
    return context;  
}
short citesteval(short m)
{
	short i, coef=0;
	int prag = 0;
    char bit;
    int poz=1;
    
	if (m== 0) return 0;
		
	if(decomprima_bit(0)==0)
	{
        coef = -2;
        poz=0;
	}
	    else coef=1;

	coef=coef+(bit<<m);
	for (i=m-2;i>=0;i--)
        {
		bit = decomprima_bit(0);
        coef=coef&(bit>>i);
        } 
	//if (poz == 0)
	//{
	//	coef ++;
	//}
//	return coef;
} 


void decodif_submat(short **m,int dx1, int dy1, int dx2, int dy2, int hasS){
    int i,j;
    int N,V,NV,S=0;
    int mag, prag;
    int context=0;
    char bit;

    printf("decompress submat %d %d %d %d\n", dx1,dy1,dx2,dy2);
    for (i=dy1;i<dy2;i++){                             
        for (j=dx1;j<dx2;j++){
        
              if (hasS)
                 S=m[i/2][j/2];
    
              if ((i==dx1)&&(j==dy1)){
                 V=N=NV=0;
                 }
              if ((i==dx1)&&(j>dy1)){
                 V = NV = 0;
                 N = m[i][j-1];
                 }
              if ((i>dx1)&&(j==dy1)){
                 N = NV = 0;
                 V = m[i-1][j];
                 }
              if ((i>dx1)&&(j>dy1)){
                 V =  m[i-1][j];
                 NV = m[i-1][j-1];
                 N =  m[i][j-1];
                 }
            prag = 11;              
            do {
                 prag--; 
                 context = det_c(S,N,V,NV,prag); 
                 bit = decomprima_bit(context);
               } 
            while ((bit!= 0) && (prag > 0)); 
            mag=prag;
            m[i][j]=citesteval(mag); 
            
        }//end for j
    }//end for i
            
}
void citeste_m(short **m,int dx, int dy){
     int i,j,k;
     
     for (i=0;i<dy;i++){
         for (j=0;j<dx;j++){
             m[i][j]=0;
             for ( k = sizeof(short)*8 - 1; k >= 0; k--)
					m[i][j] |= decomprima_bit(VALCONT)<<k; //se scrie M neschimbata
         }
     }
}

void decodif_mat(short **m, int dx, int dy){
     
     citeste_m(m,dx/8,dy/8);//M
     decodif_submat(m,dx/8,  0 ,dx/4,dy/8,1);//A3
     decodif_submat(m,0   ,dy/8,dx/8,dy/4,0);//B3
     decodif_submat(m,dx/8,dy/8,dx/4,dy/4,1);//C3
     decodif_submat(m,dx/4,   0,dx/2,dy/4,1);//A2
     decodif_submat(m,0,   dy/4,dx/4,dy/2,0);//B2
     decodif_submat(m,dx/4,dy/4,dx/2,dy/2,1);//C2
     decodif_submat(m,dx/2,   0,  dx,dy/2,1);//A1
     decodif_submat(m,0,   dy/2,dx/2,  dy,0);//B1
     decodif_submat(m,dx/2,dy/2,  dx,  dy,1);//C1
}

void ti_pe_linii(short **mat, short *s, short *d, int dx, int dy){
     
     int i,j,pp,p=dx/2;

     printf("pe linii %d %d\n",dx,dy);     
     for (i=0;i<dy;i++){
         
         for (j=0;j<p;j++){
             s[j]=mat[i][j];
             d[j]=mat[i][j+p];
         }
	 mat[i][0] = s[0] + ((d[0]+1)>>1);
	 mat[i][1] = s[0] - (d[0]>>1);
 	 
     for (j=1;j<p-1;j++){
             pp = d[j]-(-s[j-1]+ s[j+1] +2)/4;
             mat[i][2*j]=s[j] + (pp+1)/2;
             mat[i][2*j+1]=s[j] - pp/2;
         }
	 mat[i][2*p-2] = s[p-1] +((d[p-1]+1)>>1);	
	 mat[i][2*p-1] = s[p-1] - (d[p-1]>>1);
     }
}
             
void ti_pe_coloane(short **mat, short *s, short *d, int dx, int dy){
     int i,j,pp,p=dy/2;

     for (j=0;j<dx;j++){
         
         for (i=0;i<p;i++){
             s[i]=mat[i][j];
             d[i]=mat[i+p][j];
         }

    	 mat[0][j] = s[0] + ((d[0]+1)>>1);
    	 mat[1][j] = s[0] - (d[0]>>1);
     	 
         for (i=1;i<p-1;i++){
                 pp = d[i]- (-s[i-1]+ s[i+1] +2)/4;
                 mat[2*i][j]=s[i] + (pp+1)/2;
                 mat[2*i+1][j]=s[i] - pp/2;
             }
       
    	 mat[2*p-2][j] = s[p- 1] +((d[p-1]+1)>>1);	
    	 mat[2*p-1][j] = s[p-1] - (d[p-1]>>1);
  }

}
void ti(short **mat,short *s, short *d, int dx,int dy){
     ti_pe_coloane(mat,s,d,dx/4,dy/4);
     ti_pe_linii(mat,s,d,dx/4,dy/4);
     ti_pe_coloane(mat,s,d,dx/2,dy/2);
     ti_pe_linii(mat,s,d,dx/2,dy/2);
     ti_pe_coloane(mat,s,d,dx,dy);
     ti_pe_linii(mat,s,d,dx,dy);
     }


void free_mat(short **m, int dy){
     int i;
     
     for (i=0;i<dy;i++)
         free(m[i]);
     
     free(m);
     }


void decomprima(void)
{
     short				**c0;
     short				**cg;
     short				**y;
     short				t;
     short              *s,*d;
     int				i,j,p,n,maxim;

     
     start_decompresie();
    

             
     //decodificare
     decodif_mat(r,dx,dy);
     decodif_mat(g,dx,dy);     
     decodif_mat(b,dx,dy);
     
     maxim = max(dx,dy);

     s=(short *)malloc(maxim/2*sizeof(short));
     if(s==NULL){ 
                  printf("Memorie insuficienta !\n"); 
                  system("PAUSE");return; 
     } 
     d=(short *)malloc(maxim/2*sizeof(short));
     if(d==NULL){ 
                  printf("Memorie insuficienta !\n"); 
                  system("PAUSE");return; 
     } 
     
     //wavelet inversa
     ti(r,s,d,dx,dy);
     ti(g,s,d,dx,dy);
     ti(b,s,d,dx,dy);
     
     
     //revenire la r g b
        c0=(short **)malloc(dy*sizeof(short *));
    	if(c0==NULL){
    		printf("Memorie insuficienta !\n");
          system("PAUSE");	
    		return;
    		}
    	cg=(short **)malloc(dy*sizeof(short *));
    	if(cg==NULL){
    		printf("Memorie insuficienta !\n");
          system("PAUSE");	
    		return;
    		}
    	y=(short **)malloc(dy*sizeof(short *));
    	if(y==NULL){
    		printf("Memorie insuficienta !\n");
          system("PAUSE");	
    		return;
    		}
    
         for (i=0;i<dy;i++){
             c0[i]=(short *)malloc(dx*sizeof(short));
        		if(c0[i]==NULL){
        			printf("Memorie insuficienta !\n");
              system("PAUSE");	
        			return;
        			}
        		cg[i]=(short *)malloc(dx*sizeof(short));
        		if(cg[i]==NULL){
        			printf("Memorie insuficienta !\n");
              system("PAUSE");	
        			return;
        			}
        		y[i]=(short *)malloc(dx*sizeof(short));
        		if(y[i]==NULL){
        			printf("Memorie insuficienta !\n");
              system("PAUSE");	
        			return;
        			}
     	     for (j=0;j<dx;j++){
                 y[i][j]=r[i][j];
                 c0[i][j]=g[i][j];
                 cg[i][j]=b[i][j];
                 
                 //revin la r g b initiale
                 b[i][j] = y[i][j] - (c0[i][j]>>1) - cg[i][j];
                 r[i][j] = c0[i][j] + b[i][j];
                 g[i][j] = cg[i][j] + b[i][j] + (c0[i][j]>>1);
                 }

           }    
    

     free(s);
     free(d);
     
     printf("\nAm dealocat zonele de momorie ");

}

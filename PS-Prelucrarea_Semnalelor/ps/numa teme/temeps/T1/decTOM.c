#include "t3d.h"
#include <stdlib.h>
#include <stdio.h>


short				**Co;
short				**Cg;
short				**Y;
extern FILE   *fs;
FILE *test1;
FILE *test2;

void td (short *x, short *y, int N)
{
	short *s, *d;
	short p, n, t=0, p1=0;

	p = N >> 1;
	s =(short *)malloc(p*sizeof(short));
	if(s==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}
	d =(short *)malloc(p*sizeof(short));
	if(d==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}	

	for (n=0;n<p;n++)
	{
		s[n] = y[n];
		d[n] = y[n+p];
	}

	x[0] = s[0] + ((d[0]+1)>>1);
	x[1] = s[0] - (d[0]>>1);
	x[2*p-2] = s[p-1] + ((d[p-1]+1)>>1);
	x[2*p-1] = s[p-1] - (d[p-1]>>1);
	for (n=1;n<p-1;n++)
	{
		p1 = d[n] - ((s[n+1] - s[n-1] + 2)>>2);
		x[2*n] = s[n] + ((p1+1)>>1);
		x[2*n+1] = s[n] - ((p1)>>1);
	}

	free(s);
	free(d);
}


int magn(short coef)
{
	int m = 0;
	coef = abs(coef);
	if (coef > 1023) return 10;
	while (coef != 0)
	{
		m ++;
		coef = coef>>1;
	}
	return m;
}


int coef_S(short y, short x, short matrice)
{
	switch (matrice)
	{
	case 0: return Co [y>>1][x>>1];
	case 1: return Cg [y>>1][x>>1];
	case 2: return Y [y>>1][x>>1]; 
	}
	return 0;
}


int coef_N(short y, short x, short matrice)
{
	short ymin = 0;

	if (y >= (dy>>3)) ymin = dy>>3;
	if (y >= (dy>>2)) ymin = dy>>2;
	if (y >= (dy>>1)) ymin = dy>>1;
	
	if (y <= ymin) return 0;
	switch (matrice)
	{
	case 0: return Co [y-1][x];
	case 1: return Cg [y-1][x];
	case 2: return Y [y-1][x]; 
	}
	return 0;
}


int coef_V(short y, short x, short matrice)
{
	short xmin = 0;

	if (x >= (dx>>3)) xmin = dx>>3;
	if (x >= (dx>>2)) xmin = dx>>2;
	if (x >= (dx>>1)) xmin = dx>>1;
	
	if (x <= xmin) return 0;
	switch (matrice)
	{
	case 0: return Co [y][x-1];
	case 1: return Cg [y][x-1];
	case 2: return Y [y][x-1]; 
	}
	return 0;
}


int coef_NV(short y, short x, short matrice)
{
	short xmin = 0, ymin = 0;

	if (x >= (dx>>3)) xmin = dx>>3;
	if (x >= (dx>>2)) xmin = dx>>2;
	if (x >= (dx>>1)) xmin = dx>>1;
	if (y >= (dy>>3)) ymin = dy>>3;
	if (y >= (dy>>2)) ymin = dy>>2;
	if (y >= (dy>>1)) ymin = dy>>1;
	
	if (x <= xmin || y <= ymin) return 0;
	switch (matrice)
	{
	case 0: return Co [y-1][x-1];
	case 1: return Cg [y-1][x-1];
	case 2: return Y [y-1][x-1]; 
	}
	return 0;
}



int det_context(short y, short x, short matrice, int prag)
{
	int context = 0;
	if (magn(coef_S(y, x, matrice)) >= prag)
		context += 1;
	if (magn(coef_N(y, x, matrice)) >= prag)
		context += 2;
	if (magn(coef_V(y, x, matrice)) >= prag)
		context += 4;
	if (magn(coef_NV(y, x, matrice)) >= prag)
		context += 8;
	context += ((prag - 1) * 16);
#ifdef FISIER
	fprintf(test1,"%d ",context);
	fprintf(test2,"%d ",prag);
#endif
	return context;
}

short citeste_valoare(short magnitudine, int context)
{
	short i, coef=0;
	int prag = 0;

	if (context<0) return 0;
	if (magnitudine == 0) return 0;
		
	if(decomprima_bit(context)==0)
	{
        coef = coef - 1;
		coef=(coef<<1)+0;
	}
	else
			coef=(coef<<1)+1;

	for (i=magnitudine-1;i>0;i--)
		if(decomprima_bit(context)==0)
			coef=(coef<<1)+0;
		 else
			coef=(coef<<1)+1;
	if ((coef & (0x0001 << (magnitudine-1))) == 0)
	{
		coef ++;
	}
	return coef;
} 

void decodificare(short y, short x, short matrice)
{
	short prag = 11;
	int context;
	short coef=0, magnitudine=0;
		
	do
	{
		prag--;
		context = det_context(y, x, matrice, prag);
		if (decomprima_bit(context) == 0)
			magnitudine = prag;	
	}
	while (magnitudine != prag && prag > 1);
	
	//context = det_context(y, x, matrice, prag);
	coef = citeste_valoare(magnitudine, 0);	

	switch (matrice)
	{
	case 0: Co [y][x] = coef; break;
	case 1: Cg [y][x] = coef; break;
	case 2: Y [y][x] = coef; break;
	}
}

 


void decomprima(void)
{
	short x,y,i;
	short *aux;
	short t;
	FILE *test;
	char nume[20];



	if(NULL==(test1=fopen("contexte.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","contexte.txt");
		return;
		}
	if(NULL==(test2=fopen("prag.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","prag.txt");
		return;
		}
//alocare start
	Co=(short **)malloc(dy*sizeof(short *));
	if(Co==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}
	Cg=(short **)malloc(dy*sizeof(short *));
	if(Cg==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}
	Y=(short **)malloc(dy*sizeof(short *));
	if(Y==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}

	for (y=0;y<dy;y++)
	{
		Co[y]=(short *)malloc(dx*sizeof(short));
		if(Co[y]==NULL){
			printf("Memorie insuficienta !\n");
			return;
			}
		Cg[y]=(short *)malloc(dx*sizeof(short));
		if(Cg[y]==NULL){
			printf("Memorie insuficienta !\n");
			return;
			}
		Y[y]=(short *)malloc(dx*sizeof(short));
		if(Y[y]==NULL){
			printf("Memorie insuficienta !\n");
			return;
			}
	}
//alocare sfarsit

//etapa 3 start

	for (y=0;y<(dy>>3);y++)
		for (x=0;x<(dx>>3);x++)
		{
			fread(&t,sizeof(short),1,fs);
			Co[y][x] = t;
		}

	for (y=0;y<(dy>>3);y++)
		for (x=0;x<(dx>>3);x++)
		{
			fread(&t,sizeof(short),1,fs);
			Cg[y][x] = t;
		}

	for (y=0;y<(dy>>3);y++)
		for (x=0;x<(dx>>3);x++)
		{
			fread(&t,sizeof(short),1,fs);
			Y[y][x] = t;
		}
	
	start_decompresie();

	for (i=3;i>0;i--)
	{
		for (y=0;y<(dy>>i);y++)
			for (x=(dx>>i);x<(dx>>(i-1));x++)
			{
				decodificare(y, x, 0);//decodificam A
			}
		for (y=(dy>>i);y<(dy>>(i-1));y++)
			for (x=0;x<(dx>>i);x++)
			{
				decodificare(y, x, 0);//decodificam B
			}
		for (y=(dy>>i);y<(dy>>(i-1));y++)
			for (x=(dx>>i);x<(dx>>(i-1));x++)
			{
				decodificare(y, x, 0);//decodificam C
			}
	}


	for (i=3;i>0;i--)
	{
		for (y=0;y<(dy>>i);y++)
			for (x=(dx>>i);x<(dx>>(i-1));x++)
			{
				decodificare(y, x, 1);
			}
		for (y=(dy>>i);y<(dy>>(i-1));y++)
			for (x=0;x<(dx>>i);x++)
			{
				decodificare(y, x, 1);
			}
		for (y=(dy>>i);y<(dy>>(i-1));y++)
			for (x=(dx>>i);x<(dx>>(i-1));x++)
			{
				decodificare(y, x, 1);
			}
	}


	for (i=3;i>0;i--)
	{
		for (y=0;y<(dy>>i);y++)
			for (x=(dx>>i);x<(dx>>(i-1));x++)
			{
				decodificare(y, x, 2);
			}
		for (y=(dy>>i);y<(dy>>(i-1));y++)
			for (x=0;x<(dx>>i);x++)
			{
				decodificare(y, x, 2);
			}
		for (y=(dy>>i);y<(dy>>(i-1));y++)
			for (x=(dx>>i);x<(dx>>(i-1));x++)
			{
				decodificare(y, x, 2);
			}
	}
//etapa 3 sfarsit AM TERMINAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAT!!!!!!!!!!!!!!!!! 


	
//etapa 2 start
	aux =(short *)malloc(dy*sizeof(short *));// vector auxiliar in care tinem minte coloanele
	if(aux==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}
	for (i=2;i>=0;i--)
	{
#ifdef FISIER
		strcpy(nume, "etapa2_Co_ .txt");
		nume[10] = i+48;
		if(NULL==(test=fopen(nume,"wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n",nume);
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",Co[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
	strcpy(nume, "etapa2_Cg_ .txt");
		nume[10] = i+48;
		if(NULL==(test=fopen(nume,"wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n",nume);
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",Cg[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
	strcpy(nume, "etapa2_Y_ .txt");
		nume[9] = i+48;
		if(NULL==(test=fopen(nume,"wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n",nume);
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",Y[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
#endif
		for (x=0;x<(dx>>i);x++)
        { 
			for (t=0;t<(dy>>i);t++)
				aux[t] = Co[t][x];
            td(aux, aux, dy>>i);
			for (t=0;t<(dy>>i);t++)
				Co[t][x] = aux[t];

            for (t=0;t<(dy>>i);t++)
				aux[t] = Cg[t][x];
            td(aux, aux, dy>>i);
			for (t=0;t<(dy>>i);t++)
				Cg[t][x] = aux[t];

            for (t=0;t<(dy>>i);t++)
				aux[t] = Y[t][x];
            td(aux, aux, dy>>i);
			for (t=0;t<(dy>>i);t++)
				Y[t][x] = aux[t];
		}
		for (y=0;y<(dy>>i);y++)
        { 
            for (t=0;t<(dx>>i);t++)
				aux[t] = Co[y][t];
            td(aux, aux, dy>>i);
			for (t=0;t<(dx>>i);t++)
				Co[y][t] = aux[t];
			
			for (t=0;t<(dx>>i);t++)
				aux[t] = Cg[y][t];
            td(aux, aux, dy>>i);
			for (t=0;t<(dx>>i);t++)
				Cg[y][t] = aux[t];
			
			for (t=0;t<(dx>>i);t++)
				aux[t] = Y[y][t];
            td(aux, aux, dy>>i);
			for (t=0;t<(dx>>i);t++)
				Y[y][t] = aux[t];
		}
	}
#ifdef FISIER

	if(NULL==(test=fopen("etapa1_Co.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","etapa1_Co.txt");
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",Co[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
	if(NULL==(test=fopen("etapa1_Cg.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","etapa1_Cg.txt");
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",Cg[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
	if(NULL==(test=fopen("etapa1_Y.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","etapa1_Y.txt");
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",Y[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
#endif
//etapa 2 sfarsit

//etapa 1 start
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
		{
			t = Y[y][x] - (Cg[y][x] / 2);
			g[y][x] = Cg[y][x] + t;
			b[y][x] = t - (Co[y][x] / 2);
			r[y][x] = b[y][x] + Co[y][x];
		}
	}
#ifdef FISIER
	if(NULL==(test=fopen("etapa0_r.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","etapa1_r.txt");
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",r[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
	if(NULL==(test=fopen("etapa0_g.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","etapa1_g.txt");
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",g[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
	if(NULL==(test=fopen("etapa0_b.txt","wt"))){
		printf("Eroare la deschiderea fisierului <%s> !\n","etapa1_b.txt");
		return;
		}
	for (y=0;y<dy;y++)
	{
		for (x=0;x<dx;x++)
			fprintf(test,"%d ",b[y][x]);
		fprintf(test,"\n");
	}
	fclose(test);
//etapa 1 sfarsit
	fclose(test1);
	fclose(test2);
#endif
}


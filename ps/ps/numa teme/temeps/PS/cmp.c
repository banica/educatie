#include "t3c.h"
#include <stdlib.h>
#include <stdio.h>


short				**Co;
short				**Cg;
short				**Y;


void td (short *x, short *y, int N)
{
	short *s, *d;
	short p, n;

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
		s[n] = (x[2*n] + x[2*n+1])/2;

	d[0] = x[0] - x[1];
	d[p-1] = x[2*p-2] - x[2*p-1];
	for (n=1;n<p-1;n++)
		d[n] = x[2*n] - x[2*n+1] + (s[n+1] - s[n-1])>>2;


	for (n=0;n<p;n++)
	{
		y[n] = s[n];
		y[n+p] = d[n];
	}
	free(s);
	free(d);
}


int magn(short coef)
{
	int m = 0;
	coef = abs(coef);
	while (coef != 0)
	{
		m ++;
		coef = coef>>1;
	}
	return m;
}


int coef_S(short y, short x, short matrice)
{
	if (y==0 && x==0) return 0;
	switch (matrice)
	{
	case 0: return Co [y>>1][x>>1];
	case 1: return Cg [y>>1][x>>1];
	case 2: return Y [y>>1][x>>1]; 
	}
}


int coef_N(short y, short x, short matrice)
{
	if (y == 0) return 0;
	switch (matrice)
	{
	case 0: return Co [y-1][x];
	case 1: return Cg [y-1][x];
	case 2: return Y [y-1][x]; 
	}
}


int coef_V(short y, short x, short matrice)
{
	if (x == 0) return 0;
	switch (matrice)
	{
	case 0: return Co [y][x-1];
	case 1: return Cg [y][x-1];
	case 2: return Y [y][x-1]; 
	}
}


int coef_NV(short y, short x, short matrice)
{
	if (x == 0 || y == 0) return 0;
	switch (matrice)
	{
	case 0: return Co [y-1][x-1];
	case 1: return Cg [y-1][x-1];
	case 2: return Y [y-1][x-1]; 
	}
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
	return context;
}



void scrie_valoare(short coef)
{
	short i;
	
	if (coef < 0)
		coef--;
	
	for (i=magn(coef);i>=0;i--)
        if (coef & (1<<i))
				scrie_bit(1);
			else
				scrie_bit(0);
}


void codificare(short y, short x, short matrice)
{
	short prag = 11;
	int context;
	short coef, magnitudine;
	switch (matrice)
	{
	case 0: coef = Co [y][x]; break;
	case 1: coef = Cg [y][x]; break;
	case 2: coef = Y [y][x]; break;
	default: coef = 0;
	}
	
	magnitudine = magn(coef);
	do
	{
		prag--;
		context = det_context(y, x, matrice, prag);
		if (magnitudine == prag)
			comprima_bit(0, context);
		else 
			comprima_bit(1, context);
	}
	while (magnitudine != prag && prag > 1);

	scrie_valoare(coef);
}


void comprima(void)
{
	unsigned short x,y,i;
	short *aux;
	short t;

	/*for (i=0;i<dx;i++)
	{
		for (j=0;j<dy;j++)
			printf("  %d",r[i][j]);
		printf("\n");
	}
	for (i=0;i<dx;i++)
	{
		for (j=0;j<dy;j++)
			printf("  %d",g[i][j]);
		printf("\n");
	}
	for (i=0;i<dx;i++)
	{
		for (j=0;j<dy;j++)
			printf("  %d",b[i][j]);
		printf("\n");
	}*/
//etapa 1 start
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
		for (x=0;x<dx;x++)
		{
			Co[y][x] = r[y][x] - b[y][x];
			t = b[y][x] + (Co[y][x] >> 1);
			Cg[y][x] = g[y][x] - t;
			Y[y][x] = t + (Cg[y][x] >> 1);
		}
	}
//etapa 1 sfarsit


//etapa 2 start
	aux =(short *)malloc(dy*sizeof(short *));// vector auxiliar in care 
//tinem minte coloanele
	if(aux==NULL){
		printf("Memorie insuficienta !\n");
		return;
		}
	for (i=0;i<3;i++)
	{
		for (y=0;y<dy;y++)
        { 
            td(Co[y], Co[y], dx>>i);
            td(Cg[y], Cg[y], dx>>i);
            td(Y[y], Y[y], dx>>i);
		}
		for (x=0;x<dx;x++)
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
	}


//etapa 2 sfarsit

//etapa 3 start

	start_compresie();

	for (y=0;y<(dy>>3);y++)
		for (x=0;x<(dx>>3);x++)
		{
			codificare(y, x, 0);//codificam M
		}

	for (i=3;i>0;i--)
	{
		for (y=0;y<(dy>>i);y++)
			for (x=(dx>>i);x<(dx>>(i-1))-1;x++)
			{
				codificare(y, x, 0);//codificam A
			}
		for (y=(dy>>i);y<(dy>>(i-1))-1;y++)
			for (x=0;x<(dx>>i);x++)
			{
				codificare(y, x, 0);//codificam B
			}
		for (y=(dy>>i);y<(dy>>(i-1))-1;y++)
			for (x=(dx>>i);x<(dx>>(i-1))-1;x++)
			{
				codificare(y, x, 0);//codificam C
			}
	}


	for (y=0;y<(dy>>3);y++)
		for (x=0;x<(dx>>3);x++)
		{
			codificare(y, x, 1);
		}

	for (i=3;i>0;i--)
	{
		for (y=0;y<(dy>>i);y++)
			for (x=(dx>>i);x<(dx>>(i-1))-1;x++)
			{
				codificare(y, x, 1);
			}
		for (y=(dy>>i);y<(dy>>(i-1))-1;y++)
			for (x=0;x<(dx>>i);x++)
			{
				codificare(y, x, 1);
			}
		for (y=(dy>>i);y<(dy>>(i-1))-1;y++)
			for (x=(dx>>i);x<(dx>>(i-1))-1;x++)
			{
				codificare(y, x, 1);
			}
	}


	for (y=0;y<(dy>>3);y++)
		for (x=0;x<(dx>>3);x++)
		{
			codificare(y, x, 2);
		}

	for (i=3;i>0;i--)
	{
		for (y=0;y<(dy>>i);y++)
			for (x=(dx>>i);x<(dx>>(i-1))-1;x++)
			{
				codificare(y, x, 2);
			}
		for (y=(dy>>i);y<(dy>>(i-1))-1;y++)
			for (x=0;x<(dx>>i);x++)
			{
				codificare(y, x, 2);
			}
		for (y=(dy>>i);y<(dy>>(i-1))-1;y++)
			for (x=(dx>>i);x<(dx>>(i-1))-1;x++)
			{
				codificare(y, x, 2);
			}
	}

	stop_compresie();

//etapa 3 sfarsit AM 
//TERMINAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAT!!!!!!!!!!!!!!!!!
}
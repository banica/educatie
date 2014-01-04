#include <stdio.h>
#include <stdlib.h>

// Structura de date de tip RGB utilizata pentru citirea
//  din fisierul bitmap
typedef	struct{	unsigned char	b,g,r;}rgb;

// Matrici imagine pentru componentele
//  r - rosu
//  g - verde
//  b - albastru
float				**r;
float				**g;
float				**b;

// Dimensiunile imaginii (multiple de 16)
unsigned short		dx,dy;

// Fisier sursa
FILE				*fs;
FILE			    *fd;

extern	void decomprima(void);

int main(void)
{
	char			baza[32];
	char			nume[32];
	int				i;
	unsigned char	antet[54];
	unsigned short	dxi,dyi,nl,x,y;
	rgb				*t;
	float			val;

	// Citeste de la tastatura nmele fisierului
	printf("Nume fisier [.img]: ");
	scanf("%s",baza);

	// Genereaza numele fisierului sursa prin completarea
	//  extensiei implicite [.img]
	i=-1;
	while(baza[++i]!=0) nume[i]=baza[i];
	nume[i++]='.';
	nume[i++]='i';
	nume[i++]='m';
	nume[i++]='g';
	nume[i]=0;

	// Deschide fisierul sursa
	if(NULL==(fs=fopen(nume,"rb"))){
		printf("Eroare la deschiderea fisierului <%s> !\n",nume);
		return 1;
		}

	// Citeste antetul fisierului sursa
	fread(antet,1,54,fs);

	// Extrage dimensiunile imaginii
	dxi=*((unsigned short *)(antet+18));
	dyi=*((unsigned short *)(antet+22));

	// Calculeaza dimensiunea unei linii din fisierul bitmap
	nl=4*((3*dxi+3)/4);

	// Calculeaza dimensiunile prin extindere la cel mai apropiat
	//  intreg multilu de 16
	dx=16*((dxi+15)/16);
	dy=16*((dyi+15)/16);
	printf("Dx: %u -> %u , Dy: %u -> %u  (nl: %u)\n",dxi,dx,dyi,dy,nl);
	
	// Genereaza numele fisierului destinatie prin completarea
	//  extensiei implicite [.bmp]
	i=-1;
	while(baza[++i]!=0) nume[i]=baza[i];
	nume[i++]='_';
	nume[i++]='.';
	nume[i++]='b';
	nume[i++]='m';
	nume[i++]='p';
	nume[i]=0;

	// Deschide fisierul destinatie
	if(NULL==(fd=fopen(nume,"wb"))){
		printf("Eroare la deschiderea fisierului <%s> !\n",nume);
		return 1;
		}

	// Scrie antetul in fisierul destinatie
	fwrite(antet,1,54,fd);
	
	// Aloca memorie pentru vectorii cu pointeti catre liniile
	//  matricilor r,g si b
	r=(float **)malloc(dy*sizeof(float *));
	if(r==NULL){
		printf("Memorie insuficienta !\n");
		return 1;
		}
	g=(float **)malloc(dy*sizeof(float *));
	if(g==NULL){
		printf("Memorie insuficienta !\n");
		return 1;
		}
	b=(float **)malloc(dy*sizeof(float *));
	if(b==NULL){
		printf("Memorie insuficienta !\n");
		return 1;
		}

	// Aloca memorie pentru liniile matricilor
	for(y=0;y<dy;y++){
		r[y]=(float *)malloc(dx*sizeof(float));
		if(r[y]==NULL){
			printf("Memorie insuficienta !\n");
			return 1;
			}
		g[y]=(float *)malloc(dx*sizeof(float));
		if(g[y]==NULL){
			printf("Memorie insuficienta !\n");
			return 1;
			}
		b[y]=(float *)malloc(dx*sizeof(float));
		if(b[y]==NULL){
			printf("Memorie insuficienta !\n");
			return 1;
			}
		}

	// Aloca memorie pentru vectorul temporar in care se va citi
	//  cite o linie din fisierul bitmap
	t=(rgb *)malloc(nl);
	if(t==NULL){
		printf("Memorie insuficienta !\n");
		return 1;
		}
		
	// ********** Decompresie
	decomprima();

	// Scrie imaginea in fisierul bitmap
	for(y=0;y<dyi;y++){
		// Copiaza o linie in vectorul temporar
		for(x=0;x<dxi;x++){
			// Copiaza valoarea pentru rosu fortind incadrarea in limite
			val=r[y][x]+128;
			if(val>255)
				val=255;
			if(val<0)
				val=0;
			t[x].r=(unsigned char)val;

			// Copiaza valoarea pentru verde fortind incadrarea in limite
			val=g[y][x]+128;
			if(val>255)
				val=255;
			if(val<0)
				val=0;
			t[x].g=(unsigned char)val;

			// Copiaza valoarea pentru albastru fortind incadrarea in limite
			val=b[y][x]+128;
			if(val>255)
				val=255;
			if(val<0)
				val=0;
			t[x].b=(unsigned char)val;
			}

		// Scrie linia in fisierul bitmap
		fwrite((unsigned char *)t,1,nl,fd);
		}
 }

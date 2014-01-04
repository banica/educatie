#include <stdio.h>
#include <stdlib.h>

// Structura de date de tip RGB utilizata pentru citirea
//  din fisierul bitmap
typedef	struct{	unsigned char	b,g,r;}rgb;

// Matrici imagine pentru componentele
//  r - rosu
//  g - verde
//  b - albastru
short				**r;
short				**g;
short				**b;

// Dimensiunile imaginii (multiple de 8)
unsigned short		dx,dy;
int mycnt=0;

// Fisier sursa
FILE				*fs;

extern	void decomprima(void);
extern void free_mat(short **,int);

void main(void)
{
	char			baza[32];
	char			nume[32];
	int				i;
	FILE			*fd;
	unsigned char	antet[54];
	unsigned short	dxi,dyi,nl,x,y;
	rgb				*t;
	short			val;

   // printf("val=%d\n", citesteval(1,0));
	// Citeste de la tastatura nmele fisierului
	printf("Nume fisier [.img]: ");
	//scanf("%s",baza);
    strcpy(baza,"lena512");
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
		system("PAUSE");
        return;
		}

	// Citeste antetul fisierului sursa
	fread(antet,1,54,fs);

	// Extrage dimensiunile imaginii
	dxi=*((unsigned short *)(antet+18));
	dyi=*((unsigned short *)(antet+22));

	// Calculeaza dimensiunea unei linii din fisierul bitmap
	nl=4*((3*dxi+3)/4);

	// Calculeaza dimensiunile prin extindere la cel mai apropiat
	//  intreg multilu de 8
	dx=8*((dxi+7)/8);
	dy=8*((dyi+7)/8);
	printf("Dx: %u -> %u , Dy: %u -> %u  (nl: %u)\n",dxi,dx,dyi,dy,nl);
//	system("PAUSE");
	
	// Genereaza numele fisierului destinatie prin completarea
	//  extensiei implicite [.bmp]
	i=-1;
	while(baza[++i]!=0) nume[i]=baza[i];
	nume[i++]='.';
	nume[i++]='d';
	nume[i++]='i';
	nume[i++]='b';
	nume[i]=0;

	// Deschide fisierul destinatie
	if(NULL==(fd=fopen(nume,"wb"))){
		printf("Eroare la deschiderea fisierului <%s> !\n",nume);
	    system("PAUSE");
    	return;
		}

	// Scrie antetul in fisierul destinatie
	fwrite(antet,1,54,fd);
	
	// Aloca memorie pentru vectorii cu pointeti catre liniile
	//  matricilor r,g si b
	r=(short **)malloc(dy*sizeof(short *));
	if(r==NULL){
		printf("Memorie insuficienta !\n");
		system("PAUSE");
        return;
		}
	g=(short **)malloc(dy*sizeof(short *));
	if(g==NULL){
		printf("Memorie insuficienta !\n");
		system("PAUSE");
        return;
		}
	b=(short **)malloc(dy*sizeof(short *));
	if(b==NULL){
		printf("Memorie insuficienta !\n");
		system("PAUSE");return;
		}

	// Aloca memorie pentru liniile matricilor
	for(y=0;y<dy;y++){
		r[y]=(short *)malloc(dx*sizeof(short));
		if(r[y]==NULL){
			printf("Memorie insuficienta !\n");
			system("PAUSE");return;
			}
		g[y]=(short *)malloc(dx*sizeof(short));
		if(g[y]==NULL){
			printf("Memorie insuficienta !\n");
			system("PAUSE");return;
			}
		b[y]=(short *)malloc(dx*sizeof(short));
		if(b[y]==NULL){
			printf("Memorie insuficienta !\n");
			system("PAUSE");return;
			}
		}

	// Aloca memorie pentru vectorul temporar in care se va citi
	//  cite o linie din fisierul bitmap
	t=(rgb *)malloc(nl);
	if(t==NULL){
		printf("Memorie insuficienta !\n");
		system("PAUSE");return;
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
//     printf("\ndupa compresie %d\n",mycnt);
//     system("PAUSE");
     free_mat(r,dy);
     free_mat(g,dy);
     free_mat(b,dy);

 }

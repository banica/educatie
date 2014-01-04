#include <stdio.h>

#define	NUMAR_CONTEXTE	160

// Fisierul in care se scriu codurile
extern	FILE	*fd;

// Proceduri de scriere pe disc la nivel de bit
unsigned char	biti,nb=0;

void scrie_bit(char bit)
{
	if(bit==0)
		biti=(biti<<1)+0;
	  else
	  	biti=(biti<<1)+1;
	if(++nb==8){
		fwrite(&biti,1,1,fd);
		nb=0;
		}
}

void descarca_biti(void)
{
	while(nb++!=8)
		biti<<=1;
	fwrite(&biti,1,1,fd);
}

// Proceduri pentru compresie aritmetica
unsigned short	sus;
unsigned short 	jos;
unsigned short	ind;
unsigned long	ctx[NUMAR_CONTEXTE];


void start_compresie(void)
{
	int			i;
	
	for(i=0;i<NUMAR_CONTEXTE;i++)
		ctx[i]=0x80000000;
	sus=0xFFFF;
	jos=0x0000;
	ind=0;
}

void comprima_bit(char bit,int context)
{
	unsigned short	qe,x;
	unsigned long	prob;

	// Selecteaza contextul
	if(context<0||context>=NUMAR_CONTEXTE)
		return;
	qe=ctx[context]>>16;
	
	// Actualizeaza intervalul
	if(bit==0)
		jos=sus-(((unsigned long)qe*(unsigned long)(sus-jos))>>16);
	 else
		sus=sus-(((unsigned long)qe*(unsigned long)(sus-jos))>>16);

	// Actualizeaza contextul
	prob=ctx[context];
	if(bit==0)
		prob+=(0xFFFFFFFF-ctx[context])>>8;
	  else
	  	prob-=prob>>8;
	if(prob<0x01000000)
		prob=0x01000000;
	if(prob>=0xFE000000)
		prob=0xFE000000;
	ctx[context]=prob;
	  	
	// Normalizeaza intervalul
	do{
		x=((sus&0xC000)>>12)+((jos&0xC000)>>14);
		switch(x){
			case 0x00:
			case 0x04:
			case 0x05:
				scrie_bit(0);
				while(ind>0){
					scrie_bit(1);
					ind--;
					}
				sus<<=1;
				jos<<=1;
				break;
			case 0x0A:
			case 0x0E:
			case 0x0F:
				scrie_bit(1);
				while(ind>0){
					scrie_bit(0);
					ind--;
					}
				sus<<=1;
				jos<<=1;
				break;
			case 0x09:
				ind++;
				sus=(sus-0x4000)<<1;
				jos=(jos-0x4000)<<1;
				break;
			default:
				return;
			}
		}while(1);
}

void stop_compresie(void)
{
	while(jos!=0){
		if(jos&0x8000){
			scrie_bit(1);
			while(ind>0){
				scrie_bit(0);
				ind--;
				}
			}
		 else{
			scrie_bit(0);
			while(ind>0){
				scrie_bit(1);
				ind--;
				}
			}
		jos<<=1;
		}
	descarca_biti();
}

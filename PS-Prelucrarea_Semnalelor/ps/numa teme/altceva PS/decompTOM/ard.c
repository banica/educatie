#include <stdio.h>

#define	NUMAR_CONTEXTE	160

// Fisierul din care se citesc codurile
extern	FILE	*fs;

// Procedura de citire din fisier la nivel de bit
unsigned char	biti,nb=0;

char citeste_bit(void)
{
	if(nb==0){
		fread(&biti,1,1,fs);
		nb=8;
		}
	nb--;
	if(biti&0x80){
		biti<<=1;
		return(1);
		}
	  else{
	  	biti<<=1;
	  	return(0);
	  	}
}

// Proceduri decompresie aritmetica
unsigned short	sus;
unsigned short	jos;
unsigned short	cod;
unsigned short	prag;
unsigned long	ctx[NUMAR_CONTEXTE];

void start_decompresie(void)
{
	int			i;
	
	for(i=0;i<NUMAR_CONTEXTE;i++)
		ctx[i]=0x80000000;
		
	sus=0xFFFF;
	jos=0x0000;
	for(i=0;i<16;i++)
		if(citeste_bit()==0)
			cod=(cod<<1)+0;
		 else
			cod=(cod<<1)+1;
}

char decomprima_bit(int context)
{
	unsigned short	qe,x;
	unsigned long	prob;
	
	// Selecteaza contextul
	if(context<0||context>=NUMAR_CONTEXTE)
		return(0);
	qe=ctx[context]>>16;
	
	// Calculeaza prag de decizie
	prag=sus-(((unsigned long)qe*(unsigned long)(sus-jos))>>16);
	
	// Decodifica bitul
	if(cod>=prag){
		jos=prag;
		
		// Actualizeaza contextul
		prob=ctx[context];
		prob+=(0xFFFFFFFF-ctx[context])>>8;
		if(prob<0x01000000)
			prob=0x01000000;
		if(prob>=0xFE000000)
			prob=0xFE000000;
		ctx[context]=prob;
	//	printf("-> %8X\n",ctx[context]);
		
		// Normalizeaza intervalul
		do{
			x=((sus&0xC000)>>12)+((jos&0xC000)>>14);
			switch(x){
				case 0x00:
				case 0x04:
				case 0x05:
					sus<<=1;
					jos<<=1;
					if(citeste_bit()==0)
						cod=(cod<<1)+0;
					 else
						cod=(cod<<1)+1;
					break;
				case 0x0A:
				case 0x0E:
				case 0x0F:
					sus<<=1;
					jos<<=1;
					if(citeste_bit()==0)
						cod=(cod<<1)+0;
					 else
						cod=(cod<<1)+1;
					break;
				case 0x09:
					sus=(sus-0x4000)<<1;
					jos=(jos-0x4000)<<1;
					if(citeste_bit()==0)
						cod=((cod-0x4000)<<1)+0;
					 else
						cod=((cod-0x4000)<<1)+1;
					break;
				default:
					return(0);
				}
			}while(1);
		}
	 else{
		sus=prag;
		
		// Actualizeaza contextul
		prob=ctx[context];
	  	prob-=prob>>8;
	  	if(prob<0x01000000)
			prob=0x01000000;
		if(prob>=0xFE000000)
			prob=0xFE000000;
		ctx[context]=prob;
	//	printf("-> %8X\n",ctx[context]);
		
		// Normalizeaza intervalul
		do{
			x=((sus&0xC000)>>12)+((jos&0xC000)>>14);
			switch(x){
				case 0x00:
				case 0x04:
				case 0x05:
					sus<<=1;
					jos<<=1;
					if(citeste_bit()==0)
						cod=(cod<<1)+0;
					 else
						cod=(cod<<1)+1;
					break;
				case 0x0A:
				case 0x0E:
				case 0x0F:
					sus<<=1;
					jos<<=1;
					if(citeste_bit()==0)
						cod=(cod<<1)+0;
					 else
						cod=(cod<<1)+1;
					break;
				case 0x09:
					sus=(sus-0x4000)<<1;
					jos=(jos-0x4000)<<1;
					if(citeste_bit()==0)
						cod=((cod-0x4000)<<1)+0;
					 else
						cod=((cod-0x4000)<<1)+1;
					break;
				default:
					return(1);
				}
			}while(1);
		}
	return(0);
}

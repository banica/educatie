#include <stdio.h>
#define MAX_NR_OF_NODURI 4096
#define MAX_BUFFER_SIZE 10000000 //a bit less than 10M

unsigned long int parinte[4096] , fs[4096] , fd[4096] , iE , iF , pondere[4096] , ord[4096] , index[4096] , index_char[256] , nod ;
unsigned char caracter[4096] , c , ch , c_bit =0, f_in_name[250], f_out_name[250] , f_out2_name[250],  c_tmp=0 , c_new = 0 , mask = 0 , mask_tmp = 0, bit_curent = 0 , bit_curent_tmp=0 ,  buffer[11000000], c_tmp_2;
FILE * f_in, * f_out, *f_out2;
size_t offset = 0;


unsigned long int schimba_noduri(unsigned long int i,unsigned long int i_tmp);
unsigned long int verifica_frat(unsigned long int i);
unsigned long int debug();
unsigned long int write_binary_index(unsigned long int i);
unsigned long int write_binary_char(unsigned char c);
unsigned long int burn(unsigned char c);


unsigned long int burn(unsigned char c)
{
	buffer[offset++] = c;
}

unsigned long int write_bit(unsigned char bit)
{
unsigned char mask;
	if (bit == 1 && bit_curent ==0)
		bit = 1;
	mask = (bit << ((7-bit_curent)));
	c_bit = mask | c_bit;
	if (++bit_curent > 7)
	{
		bit_curent = 0;
		burn(c_bit);
		c_bit = 0x00;
	}
}

unsigned long int write_binary_index(unsigned long int i)
{
if (i > 0)
{
	write_binary_index(parinte[i]);
	if (i == fs[parinte[i]])
		write_bit(0);
	else
		write_bit(1);
}
}

unsigned long int init() //A
{
unsigned long int i;
pondere[0] = 2;
pondere[1] = 1;
pondere[2] = 1;
parinte[0] = 0;
parinte[1] = 0;
parinte[2] = 0;
fs[0] = 1;
fd[0] = 2;
fs[1] = 0;
fs[2] = 0;
fd[1] = 0;
fd[2] = 0;
iE = 2;
iF = 1;
index[0] = 0;
index[1] = 1;
index[2] = 2;
ord[0] = 0;
ord[1] = 1;
ord[2] = 2;
for (i=0;i<=255; i++)
	index_char[i] = 0;
}


unsigned long int verifica_frat(unsigned long int i) //B
{
	unsigned long int i_tmp = i;
	if (i_tmp == 0)
		return 0;
	while (pondere[index[ord[i_tmp] - 1]] == pondere[i])
	{
		i_tmp = index[ord[i_tmp] - 1];
		if (i == i_tmp)
		{
			return i;
		}
	}

	return i_tmp;
}

unsigned long int refa_frat(unsigned long int i) //D
{
	unsigned long int i_tmp = verifica_frat(i);

	if(i_tmp !=i)
		schimba_noduri(i,i_tmp);
	pondere[i]++;
	if (i_tmp > 0)
		refa_frat(parinte[i]);
}


unsigned long int schimba_noduri(unsigned long int i,unsigned long int i_tmp) //C
{
	unsigned long int tmp;
	if (i == fs[parinte[i]])	//i este fiu stanga
		if (i_tmp == fs[parinte[i_tmp]])	//i_tmp este fiu stanga
		{
			tmp = fs[parinte[i]];
			fs[parinte[i]] = fs[parinte[i_tmp]];
			fs[parinte[i_tmp]] = tmp;
		}
		else	//i_tmp este fiu dreapta
		{
			tmp = fs[parinte[i]];
			fs[parinte[i]] = fd[parinte[i_tmp]];
			fd[parinte[i_tmp]] = tmp;
		}
	else	//i este fiu dreapta
		if (i_tmp == fs[parinte[i_tmp]])	//i_tmp este fiu stanga
		{
			tmp = fd[parinte[i]];
			fd[parinte[i]] = fs[parinte[i_tmp]];
			fs[parinte[i_tmp]] = tmp;
		}
		else	//i_tmp este fiu dreapta
		{
			tmp = fd[parinte[i]];
			fd[parinte[i]] = fd[parinte[i_tmp]];
			fd[parinte[i_tmp]] = tmp;
		}

	tmp = parinte[i];
	parinte[i] = parinte[i_tmp];
	parinte[i_tmp] = tmp;

	tmp = index[ord[i]];
	index[ord[i]] = index[ord[i_tmp]];
	index[ord[i_tmp]] = tmp;

	tmp = ord[i];
	ord[i] = ord[i_tmp];
	ord[i_tmp] = tmp;


	return i_tmp;
}//schimba_noduri

unsigned long int push_char(char c)
{
	unsigned long int index_de_refacut;
	if (index_char[c] == 0)
	{
		parinte[iE + 1] = iE;
		parinte[iE + 2] = iE;
		fs[iE] = iE + 1;
		fd[iE] = iE + 2;
		fs[iE+1]=0;
		fd[iE+1]=0;
		fs[iE+2]=0;
		fd[iE+2]=0;
		pondere[iE+1] = 1;
		pondere[iE+2] = 1;
		ord[iE+1] = iE+1;
		ord[iE+2] = iE+2;
		index[iE+1] = iE+1;
		index[iE+2] = iE+2;
		caracter[iE+1] = c;
		index_char[c] = iE+1;
		index_de_refacut = iE;
		iE += 2;
	}
	else
		index_de_refacut = index_char[c];

	refa_frat(index_de_refacut);

}//push_char

unsigned long int debug()
{
unsigned long int i,ix;
unsigned char c_debug;
printf("\r\nNR:%lu\r\niE:%lu\r\niF:%lu\r\n",iE,iE,iF);
for (ix = 0; ix<= iE ; ix++)
{
	i = index[ix];
c_debug = caracter[i];
if (c==0)
	c_debug = "*";
printf("%lu: caracter=%d [%c] parinte= %lu; fs= %lu; fd= %lu ;pondere= %lu ;ord= %lu - index[ord] = %lu \r\n",i,caracter[i],caracter[i],parinte[i],fs[i],fd[i],pondere[i],ord[i],index[ord[i]]);
}

}

int display_bit(unsigned char c)
{
	printf("%d",c);
}
int printf_binary_char(unsigned char c)
{
unsigned char mask = 128 , c_display = c;
//	printf (" [");
	while (mask > 0)
	{
		if (c >= mask)
		{
			printf("1");
			c -= mask;
		}
		else
			printf("0");
		mask = mask / 2;
	}
	printf(" ");
}

unsigned long int write_binary_char(unsigned char c)
{
unsigned char mask = 128 , c_display = c;
	while (mask > 0)
	{
		if (c >= mask)
		{
			write_bit(1);
			c -= mask;
		}
		else
			write_bit(0);
		mask = mask / 2;
	}
}




int main(int argc, char *argv[])
{

if (argc < 2)
{
	printf ("please pass the name of the file in the command line.");
  while ((ch = getchar()) != '\n' && ch != EOF);
	return 1;
}
	init();
	strcpy(f_in_name,argv[1]);


	if ((f_in = fopen(f_in_name,"rb")) && (f_out = fopen("compressed","wb")))
	{
		while (fread (&c,sizeof(unsigned char),1,f_in))
		{
			if (index_char[c] == 0)
			{
				write_binary_index(iE);
				write_binary_char(c);
			}
			else
				write_binary_index(index_char[c]);
			if (offset >= 2)
			{
				fwrite (buffer,sizeof(unsigned char) , offset, f_out);
				offset = 0;
			}
			push_char(c);
		}
		write_binary_index(iF);
		burn(c_bit);
				fwrite (buffer,sizeof(unsigned char) , offset, f_out);
				offset = 0;
		fclose(f_in);
		fclose(f_out);
	}
	else
		printf("EROARE: NU AM PUTUT DESCHIDE %s.",f_in_name);

	if ((f_in = fopen("compressed","rb")) && (f_out = fopen("decompressed","wb")))
	{


init();
nod = 0;
	printf("\r\nDecompression... \r\n");
	mask_tmp = 128;
	c_tmp = 0;
	while (fread(&c,sizeof(unsigned char) , 1 , f_in))
	{
			if (offset >= 2)
			{
				fwrite (buffer,sizeof(unsigned char) , offset, f_out);
				offset = 0;
			}
		for (bit_curent = 0; bit_curent < 8; bit_curent ++)
		{
			mask = (128 >> bit_curent);
			if ((fd[nod]>0) || (fs[nod]>0))
			{
				if ((c & mask) > 0)
				{
					if (fd[nod] > 0)
						nod = fd[nod];
					else
						printf("\r\nERROR 1\r\n");
				}
				else
				{
					if (fs[nod] > 0)
						nod = fs[nod];
					else
						printf("\r\nERROR 0\r\n");
				}
			}
			else
			{
				if (nod != iE)
				{
					burn(caracter[nod]);
					push_char(caracter[nod]);
					if ((c & mask) > 0)
						nod = fd[0];
					else
						nod = fs[0];
				}
				else
				{
					if (c&mask)
						c_tmp += mask_tmp;
					mask_tmp /= 2;
					if (mask_tmp == 0)
					{
						burn(c_tmp);
						push_char(c_tmp);
						nod = 0;
						c_tmp = 0;
						mask_tmp = 128;
					}
				}
			}
		}
		c = c_new;

		if (offset >= MAX_BUFFER_SIZE)
		{
			fwrite (buffer,sizeof(unsigned char),offset,f_out);
			offset = 0;
		}
	}
		if (offset >= MAX_BUFFER_SIZE)
		{
			fwrite (buffer,sizeof(unsigned char),offset,f_out);
			offset = 0;
		}

		fclose(f_in);
		fclose(f_out);
	}
	else
		printf("EROARE");
return 0;
}








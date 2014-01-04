#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main()
{
int i,j,k,n,x,a[50],c[50],c1[50],cf[50],v,m[50],mf[50];
int exp=0,nr_noduri=1,nr_pasi=0,pas=0,pas1=0,step=0;
int pid1, pid2, pipe1[2], pipe2[2];

/*printf("Dati gradul polinomului: n=");
scanf("%d",&n);
printf("\n");

printf("Dati valoarea de calcul a polinomului: x=");
scanf("%d",&x);
printf("\n");

for(i=0;i<=n;i++)
	{
	printf("Dati coficientii a[%d]=",i);
	scanf("%d",&a[i]);
	printf("\n");
	}
*/
n = 7;
x = 2;
a[0] = a[1] = a[2] = a[3] = a[4] = a[5] = a[6] = a[7] = 1;

//initializare

for(i=0;i<=n;i++)
{
	c[i]=a[i];
}

v=x;

//Calculez numarul de pasi si numarul de noduri
while(nr_noduri < n + 1)
{
	nr_noduri = nr_noduri*2;
	nr_pasi = nr_pasi + 1;
}

for(i=0;i<=nr_noduri-1;i++)
	m[i]=i%2;
//Pas 1

if (pipe(pipe1) == -1)
{
	perror("pipe1()");
	exit(1);
}

if (pipe(pipe2) == -1)
{
	perror("pipe2()");
	exit(1);
}

if ((pid1 = fork()) == -1)
{
	perror("fork1()");
	exit(1);
}

if( pid1 > 0 ) /* Parinte = P1 */
{
	close(pipe1[WRITE]);
	close(pipe2[READ]);
	while( pas < nr_pasi )
	{
		for(k=0;k<=nr_noduri-1;k++)
		{
			exp=m[k];
			if(exp==0)
				c[k]=c[k]*1;
			if(exp==1)
				c[k]=c[k]*v;
		}
		
		v=v*v;
		pas++;
		
		for(i=0; i<nr_noduri; i++)
			if ((read(pipe1[READ], &m[i], sizeof(int))) < 0)
			{
				perror("read1()");
				exit(1);
			}	
	}
	
	for(j = 0;j<=nr_noduri-1;j++)
			printf("CCC[%d] = %d\n",j,c[j]);
		printf("\n");
			
	for(i=0; i<nr_noduri; i++)
		if ((write(pipe2[WRITE], &c[i], sizeof(int))) < 0)
		{
			perror("write2()");
			exit(1);
		}
	
		if (wait(NULL) == -1)
		{
			perror("wait()");
			exit(1);
		}
		//sleep(10);

	close(pipe1[READ]);
	exit(0);	 
	}
	else /* Copil = P2 */
	{
		if((pid2 = fork()) == -1)
		{
			perror("fork2()");
			exit(1);
		}
		close(pipe1[READ]);
		if (pid2 > 0)
		{
			while( pas1 < nr_pasi-1 )
			{
				for(i = 0;i<=nr_noduri-1;i++)
				{	
					if((i >= 0) && (i <= nr_noduri / 2 - 1))
						mf[2 * i] = m[i];
					if((i >= nr_noduri / 2) && (i <= nr_noduri - 1))
						mf[2 * i + 1 - nr_noduri] = m[i];
				}
				for(j = 0;j<=nr_noduri-1;j++) 
					m[j] = mf[j];
			
				for(i=0; i<nr_noduri; i++)
		   			if ((write(pipe1[WRITE], &m[i], sizeof(int))) < 0)
		     			{
						perror("write1()");
						exit(1);
					}		
				pas1++;		
			}
			
			/*if(wait(NULL)< 0)
			{
				perror("waitP3()");
				exit(1);
			}*/
		
			close(pipe1[READ]);
			exit(0);
		
		}	
		else /* P3 */
		{
			close(pipe2[WRITE]);
			printf("cevaaaaaaaaa");
//sleep(100);
			for(i=0; i<nr_noduri; i++)
			if ((read(pipe2[READ], &c1[i], sizeof(int))) < 0)
		   	{
				perror("read1()");
				exit(1);
			}
			while (step < nr_pasi)
			{
				// shuffle intre noduri
				for( i = 0;i<=nr_noduri - 1;i++)
				{
					if ((i >= 0) && (i <= nr_noduri / 2 - 1))
						cf[2 * i] = c1[i];
     					if ((i >= nr_noduri / 2) && (i <= nr_noduri - 1))
						cf[2 * i + 1 - nr_noduri] = c1[i];
				} 
         			//exchange
		        	if (nr_noduri == 1)
             				cf[0] = c1[0];
         			else
             				for( i = 0;i<=nr_noduri - 2;i=i+2)
					{		
						cf[i] = cf[i + 1] + cf[i];
            					cf[i + 1] = cf[i];
					}
				for( i = 0;i<=nr_noduri-1;i++)
					c1[i] = cf[i];
				step++;	
			}

		close(pipe2[READ]);
		printf("Valoarea polinomului in punctul %d este: %d",x,c1[nr_noduri-1]);
		printf("\n");
		exit(0);	
		} 	
		
		/*if(wait(NULL)< 0)
		{
			perror("waitP3()");
			exit(1);
		}*/
		
	close(pipe1[WRITE]);
	//exit(0);
	}

return 0;
}

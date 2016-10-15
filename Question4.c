#include <stdlib.h>
#include <stdio.h>
#include <math.h>
/* funcao pra validar se e possivel fazer a multiplicao entre
 * as matrizes dadas
 */
int invalido(int ca, int lb)
{
	if (ca != lb)
		return -1;

	return 0;
} 

float norm2(int n, float * b)
{
	//for vectors
  	int i;
  	float s = 0;
	for(i=0;i<n;i++)
	{
	   s += b[i]*b[i];
	}
	s = sqrt(s);
	return s;	  
}
void sor (int n,float w, float A[][n], float b[], float x[])
{
	float sub1 =0;
	float sub2 =0;
	int i,j;
	for(i=0;i<n;i++)
	{
        for(j=0;j<i;j++)
		{
			sub1 += A[i][j]*x[j];
		}
		for(j=(i+1);j<n;j++)
		{
			sub2 += A[i][j]*x[j];
		}
		x[i] = (1-w)*x[i] + (w/A[i][i])*(b[i]-(sub1+sub2));
		sub1 = 0;
		sub2 = 0;
	}	
}

int main(int argc, char **argv)
{
	int la, ca, lb;
	float w; // soh usa pro sor
    int i, j;
    float k;
	printf("Informe o Numero de Linhas  A : ");
	scanf("%d", &la);
	printf("Informe o Numero de Colunas A : ");
	scanf("%d", &ca);
	if (ca>4 || la>4)
	{
		printf("limite de colunas e/ou linhas atingido(s)\n");
	}
	else 
	{
		float A[la][ca];
		printf("Preencha a Matrix: \n");
		for (i = 0 ; i < la; i++ )
		{
			for (j = 0; j < ca; j++) 
			{
				printf("Posicao a%d%d \n", i+1, j+1);
				scanf("%f", &A[i][j]);
			}
			printf("\n");
		}
		printf("Informe o Numero de Linhas  b : ");
		scanf("%d", &lb);
		if(invalido(ca, lb)) 
		{
			fprintf(stderr, "Erro:\n");
			fprintf(stderr, "Numero de colunas da Matriz A deve ser igual ao Numero de Linhas da Matrix B\n");
			exit(EXIT_FAILURE);
		}
		float b[lb];
		float t[lb];
    	float x[lb]; // soh usa pro sor
    	printf("Preencha o vetor: \n");
		for (i = 0 ; i < lb; i++ )
		{
			printf("Posicao b%d \n", i+1);
			scanf("%f", &b[i]);
			printf("\n");
		}
    	printf("Entre com a tolerancia:\n");
    	scanf("%f",&k);
    	printf("\n");     
    	printf("Entre com os valores iniciais de x:\n");       
    	for(i=0;i<lb;i++)
    	{
        	scanf("%f",&x[i]); 
    	}
    	printf("Entre com o valor de W (Valor deve estar entre 0 e 2):\n");  
    	do
    	{
        	scanf("%f",&w);
    	}while (!(w>0 && w<2));
    	do
    	{
			for(i=0;i<lb;i++)
			{
		   		t[i]=0;
			}
			sor(lb,w,A,b,x);
			for(i=0;i<lb;i++)
			{
            	for(j=0;j<lb;j++)
            	{
                	t[i] += A[i][j]*x[j];
            	}
			}
        	for(i=0;i<lb;i++)
        	{
            	t[i]-=b[i];     
        	}
		}while((norm2(lb,t)>k));
    	printf("Resultado do Sor:\n");
    	for (i=0;i<lb;i++)
    	{ 
        	printf("%f\n", x[i]);
    	}
	}
	return 0;
}

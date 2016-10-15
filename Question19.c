#include <stdio.h>
#include <math.h>
#include <stdlib.h>


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

int main()
{
	int ordem, i, j, k, guassConverge=1, Converge=1;
	printf("Digite a ordem da matriz A: ");
	scanf("%d,",&ordem);
	float A[ordem][ordem];
	float vetorX[ordem][1];
	float x[ordem];
	float b[ordem];
	float iteracao[100][ordem];/*jacobi*/
	float iteracaoGauss[100][ordem];/*gauss*/
	float xG[ordem];
	float xJ[ordem];
	float xS[ordem];/*sor*/
	float w, e, g=0, s=0, ja=0;
	printf("Digite a matriz A");
	for(i=0; i<ordem; i++)
	{
		for(j=0; j<ordem; j++)
		{
			printf("\nA[%d][%d]: ", i+1, j+1);
			scanf("%f", &A[i][j]);
		}
	}
	printf("\n");
	printf("Digite o vetor x");
	for(i=0; i<ordem; i++)
	{
		printf("\nx[%d]: ", i+1);
		scanf("%f", &x[i]);
	}
	printf("\n");
	printf("Digite o vetor b");
	for(i=0; i<ordem; i++)
	{
		printf("\nb[%d]: ", i+1);
		scanf("%f", &b[i]);
	}
	/*Jacobi*/
	for(k =0; k < 100; k++)
	{
		for(i = 0; i < ordem; i ++)
		{
			iteracao[k][i] = 0;
			if(k == 0)
			{
				iteracao[k][i] = vetorX[i][0];
			}
		}
	}
	for(k = 1; k < 100; k ++)
	{
		for(i = 0; i < ordem; i ++)
		{
			for(j = 0; j < ordem; j ++)
			{
				if(i == j)
				{
					iteracao[k][i] += b[i];
				}
				else
				{
					iteracao[k][i] -= iteracao[k-1][j] * A[i][j];
				}
			}
			iteracao[k][i] /= A[i][i];
		}
	}
	for(i = 0; i < ordem; i ++)
	{
		if(abs(abs(iteracao[99][i]) - abs(iteracao[98][i])) > 0.1)
		{
			Converge = 0;
			printf("Jacobi não convergiu.\n");
			break;
		}
	}
	if(Converge == 1)
	{
		printf("Jacobi converge, vetor x: ");
		for(i = 0; i < ordem; i ++)
		{
			xJ[i]=iteracao[99][i];
			printf("%.3f\n ", iteracao[99][i]);
		}
	}
	printf("\n");
	/*Gauss*/
	for(k =0; k < 100; k++)
	{
		for(i = 0; i < ordem; i ++)
		{
			iteracaoGauss[k][i] = 0;
			if(k == 0)
			{
				iteracaoGauss[k][i] = vetorX[i][0];
			}
		}
	}
	for(k = 1; k < 100; k ++)
	{
		for(i = 0; i < ordem; i ++)
		{
			for(j = 0; j < ordem; j ++)
			{
				if(i == j)
				{
					iteracaoGauss[k][i] += b[i];
				}
				else
				{
					if(j <= i)
						iteracaoGauss[k][i] -= iteracaoGauss[k][j] * A[i][j];
					else
						iteracaoGauss[k][i] -= iteracaoGauss[k-1][j] * A[i][j];
				}
			}
			iteracaoGauss[k][i] /= A[i][i];
		}
	}

	for(i = 0; i < ordem; i ++)
	{
		if(abs(abs(iteracao[99][i]) - abs(iteracao[98][i])) > 0.1)
		{
			guassConverge = 0;
			printf("Gauss não convergiu.\n");
			break;
		}
	}

	if(guassConverge == 1)
	{
		printf("Gauss converge, vetor x: ");
		for(i = 0; i < ordem; i ++)
		{
			xG[i]=iteracaoGauss[99][i];
			printf("%lf ", iteracaoGauss[99][i]);
		}
	}
	printf("\n");
	printf("Entre com a tolerancia:\n");
    scanf("%f",&e);
	printf("Entre com o valor de W (Valor deve estar entre 0 e 2):\n");
	do
    {
       	scanf("%f",&w);
    }while (!(w>0 && w<2));
    do
    {
		for(i=0;i<ordem;i++)
		{
	   		xS[i]=0;
		}
		sor(ordem,w,A,b,x);
		for(i=0;i<ordem;i++)
		{
           	for(j=0;j<ordem;j++)
           	{
               	xS[i] += A[i][j]*x[j];
           	}
		}
       	for(i=0;i<ordem;i++)
       	{
           	xS[i]-=b[i];     
       	}
	}while((norm2(ordem,xS)>k));
	printf("Resultado do Sor:\n");
    for (i=0;i<ordem;i++)
    { 
       	printf("%f\n", xS[i]);
    }
    for (i=0;i<ordem;i++)
    { 
       	xG[i]=xG[i]-x[i];
    }
    for (i=0;i<ordem;i++)
    { 
       	xJ[i]=xJ[i]-x[i];
    }
    for (i=0;i<ordem;i++)
    { 
       	xS[i]=xS[i]-x[i];
    }
    g=norm2(ordem, xG)/norm2(ordem, x);
    ja=norm2(ordem, xJ)/norm2(ordem, x);
    s=norm2(ordem, xS)/norm2(ordem, x);

    if(g<j && g<s)
    {
    	printf("Gauss é o melhor metodo\n");
    }
    else if(j<g && j<s)
    {
    	printf("Jacobi é o melhor metodo\n");
    }
    else if(s<j && s<g)
    {
    	printf("Sor é o melhor metodo\n");
    }
    else
    {
    	printf("Deu ruim, 2/3 metodos são iguais:\n");
    	printf("Residuo de Jacobi %f\n", ja);
    	printf("Residuo de Gauss %f\n", g);
    	printf("Residuo do Sor %f\n", s);
    }
    return 0;
}
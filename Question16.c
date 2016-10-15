/* 
Código desenvolvido para a disciplina IM478 - ÁLGEBRA LINEAR COMPUTACIONAL
PROF: ERITO MARQUES DE SOUZA FILHO
desenvolvido por: FELIPE RANGEL DA SILVA - 201678013-2
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void NormaFrob(int ordem, double **matriz)
{
	//função que calcula a norma de frobenius
    double norma_f=0;
    int i, j;
    for (i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            norma_f += pow(matriz[i][j],2);
        }
    }
    printf("A Norma de Frobenius da matriz A é: %.2lf\n",sqrt(norma_f));
}

void Norma1(int ordem, double **matriz)
{
	double sum2=0,norma1 = 0;
	int i, j;
    for (j=0;j<ordem;j++)
    {
        for(i=0;i<ordem;i++)
        {
            if(matriz[i][j] > 0)
                sum2 += matriz[i][j];
            else
                sum2 += ((matriz[i][j]) * (-1));
        }
        if(sum2 > norma1)
        {
          	norma1 = sum2;
          	sum2 = 0;    
       	}else
            	sum2 = 0;
    }
        printf("A Norma 1 da matriz A é: %.2lf\n",norma1);
}

double NormaInf(int ordem, double **matriz)
{
	//função que calcula a norma infinito da matriz A
    double sum=0,normainf = 0;
    int i, j;
    for (i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            if(matriz[i][j] > 0)
                sum += matriz[i][j];
            else
                sum += ((matriz[i][j]) * (-1));
        }
        if(sum > normainf)
        {
            normainf = sum;
            sum = 0;
        }else
            sum = 0;
    }
    //printf("A Norma Infinito da matriz A é: %.2lf\n",normainf);
    return normainf;
}

double **CalcInversa(int x, double **V, double **m)
{
	int i, pivo, j, k, e;

	for(i = 0; i < 3; i++)
	{
  		pivo = V[i][i];
  		for(j = i; j < 3; j++)
  		{
    		V[i][j] = (V[i][j])/(pivo); 
    		m[i][j] = (m[i][j])/(pivo); 
  		}
  		for(e = 0; e < 3; e++)
  		{
    		if(e != i)
    		{
      			k = V[e][i];
      			for(j = 0; j < 3; j++)
      			{
        			V[e][j] = (V[e][j]) - (k * V[i][j]); 
        			m[e][j] = (m[e][j]) - (k * m[i][j]);  
      			}
    		}
  		}  
	}
	return (m);
}
double **Alocar_matriz_real(int m, int n)
{
	double **v;  /* ponteiro para a matriz */
	int   i;    /* variavel auxiliar      */

	if (m < 1 || n < 1) { /* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}

	/* aloca as linhas da matriz */
	v = calloc (m, sizeof(double *));	/* Um vetor de m ponteiros para double */
	if (v == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		return (NULL);
	}

	/* aloca as colunas da matriz */
	for ( i = 0; i < m; i++ ) {
		v[i] =  calloc (n, sizeof(double));	/* m vetores de n doubles */
		if (v[i] == NULL) {
			printf ("** Erro: Memoria Insuficiente **");
			return (NULL);
		}
	}

	return (v); /* retorna o ponteiro para a matriz */
}

void **Liberar_matriz_real (int m, int n, double **v)
{
	int  i;  /* variavel auxiliar */

	if (m < 1 || n < 1) {  /* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
	}

	for (i = 0; i < m; i++)
	   	free (v[i]); /* libera as linhas da matriz */

	free (v);      /* libera a matriz (vetor de ponteiros) */
}

double **ler_mata(int m, int n, double **v)
{
	int i, j;

	printf("Preencha a Matrix: \n");
	for (i = 0 ; i < m; i++ )
		for (j = 0; j < n; j++) {
			printf("Posicao a%d%d \n", i+1, j+1);
			scanf("%lf", &v[i][j]);
		}
	printf("\n");

	return(v); 
}

int main(int argc, char const *argv[])
{
	

	int l, c, ordem=3;
	double **MatrizA, **Ident;
	double **Inv;
	/* Chama a funcao para alocar a matriz */
	MatrizA = Alocar_matriz_real (ordem, ordem);
	Ident = Alocar_matriz_real (ordem, ordem);
	Inv = Alocar_matriz_real (ordem, ordem);
	//Entrar com a matriz A
	MatrizA=ler_mata(ordem, ordem, MatrizA);
	//Gerando uma matriz identidade
	for(l = 0; l < ordem; l++)
	{         
		for(c = 0; c < ordem; c++)
		{             
			if(l == c)
			{                 
				Ident[l][c] = 1;             
			}   
			else
			{                 
				Ident[l][c] = 0;             
			}         
		}     
	}
	
	Inv=CalcInversa(ordem, MatrizA, Ident);
	Norma1(ordem, Inv);
	double ninfinv=NormaInf(ordem, Inv);
	printf("A Norma Infinito da matriz A inversa é: %.2lf\n",ninfinv);
	double ninf=NormaInf(ordem, MatrizA);
	NormaFrob(ordem, Inv);
	double cond = ninfinv * ninf; 
	printf("O número condição da Matriz A é: %.3f", cond);
	/* desaloca a memoria, nao mais nescessaria */
	Liberar_matriz_real (ordem, ordem, MatrizA);
	Liberar_matriz_real (ordem, ordem, Inv);
	Liberar_matriz_real (ordem, ordem, Ident);
	MatrizA=NULL;
	Inv=NULL;
	Ident=NULL;
	return 0;

}
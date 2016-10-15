#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* aloca memoria para as matrizes  */
float **Alocar_matriz_real(int m, int n)
{
	float **v;  /* ponteiro para a matriz */
	int   i;    /* variavel auxiliar      */

	if (m < 1 || n < 1) { /* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}

	/* aloca as linhas da matriz */
	v = calloc (m, sizeof(float *));	/* Um vetor de m ponteiros para float */
	if (v == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		return (NULL);
	}

	/* aloca as colunas da matriz */
	for ( i = 0; i < m; i++ ) {
		v[i] =  calloc (n, sizeof(float));	/* m vetores de n floats */
		if (v[i] == NULL) {
			printf ("** Erro: Memoria Insuficiente **");
			return (NULL);
		}
	}

	return (v); /* retorna o ponteiro para a matriz */
}

/* Libera memoria ocupada pelas matrizes */
float **Liberar_matriz_real (int m, int n, float **v)
{
	int  i;  /* variavel auxiliar */

	if (v == NULL)
	   	return (NULL);

	if (m < 1 || n < 1) {  /* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (v);
	}

	for (i = 0; i < m; i++)
	   	free (v[i]); /* libera as linhas da matriz */

	free (v);      /* libera a matriz (vetor de ponteiros) */

	return (NULL); /* retorna um ponteiro nulo */
}

/* Funcao para receber os dados que preencherao as matrizes */
float **ler_mata(int m, int n, float **v)
{
	int i, j;

	printf("Preencha a Matrix: \n");
	for (i = 0 ; i < m; i++ )
		for (j = 0; j < n; j++) {
			printf("Posicao a%d%d \n", i+1, j+1);
			scanf("%f", &v[i][j]);
		}
	printf("\n");

	return(v);
}
float **CalcTransposta(int la, int ca, float **v, float **m)
{
	int i, j;
	for (i=0; i<la; i++)
	{
		m[i][i]=v[i][i];
		for(j=0; j<ca; j++)
		{
			if(i<j)
			{
				m[i][j]=v[j][i];
			}
		}
	}
	return (m);
}

float **CalcInversa(int la, int ca, float **V, float **m)
{
	int i, pivo, j, k, e;

	for(i = 0; i < la; i++)
	{
  		pivo = V[i][i];
  		for(j = i; j < ca; j++)
  		{
    		V[i][j] = (V[i][j])/(pivo);
    		m[i][j] = (m[i][j])/(pivo);
  		}
  		for(e = 0; e < la; e++)
  		{
    		if(e != i)
    		{
      			k = V[e][i];
      			for(j = 0; j < ca; j++)
      			{
        			V[e][j] = (V[e][j]) - (k * V[i][j]);
        			m[e][j] = (m[e][j]) - (k * m[i][j]);
      			}
    		}
  		}
	}
	return (m);
}
float **identidade(int m, int n, float **v)
{
	int i, j;
	for (i = 0 ; i < m; i++ )
		for (j = 0; j < n; j++)
		{
			if(i==j)
			{
				v[i][j]=1;
			}
			else
			{
				v[i][j]=0;
			}
		}

	return(v);
}

int main(void)
{
	float **A;  /* matriz a ser alocada */
	float **B;
	float **C;
	float **Id;
	int la, ca, i, j;   /* numero de linhas e colunas da matriz */

	printf("Informe o Numero de Linhas  A : ");
	scanf("%d", &la);
	printf("Informe o Numero de Colunas A : ");
	scanf("%d", &ca);
	/* Chama a funcao para alocar a matriz */
	A = Alocar_matriz_real (la, ca);
	C = Alocar_matriz_real (la, ca);
	B = Alocar_matriz_real (la, ca);
	Id = Alocar_matriz_real (la, ca);
	/* Chama funcao pra preencher as matrizes  */
	A = ler_mata(la, ca, A);
	/*Chama função pra preencher a matriz identidade*/
	Id=identidade(la, ca, Id);
	B=CalcInversa(la,ca,A,Id);
	C=CalcTransposta(la,ca,A,C);
	for(i=0;i<la;i++)
	{
        for(j=0;j<ca;j++)
        {
            if(B[i][j]!=C[i][j])
            {
                printf("A matriz não eh ortogonal. ");
                return 0;
            }
        }
	}
	printf("A matriz eh ortogonal.");
	return 0;
}
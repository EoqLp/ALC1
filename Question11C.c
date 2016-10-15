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

int main(int argc, char **argv)
{
	float **A;  /* matriz a ser alocada */
	int i;
	int j;

	int la, ca;   /* numero de linhas e colunas da matriz */

	printf("Informe o Numero de Linhas  A : ");
	scanf("%d", &la);
	printf("Informe o Numero de Colunas A : ");
	scanf("%d", &ca);


	/* Chama a funcao para alocar a matriz */
	A = Alocar_matriz_real (la, ca);
	/* Chama funcao pra preencher as matrizes  */
	A = ler_mata(la, ca, A);
	int e, k, flops2=0;
	float h=0;
    do
    {
    	e=rand()%2;
    	k=rand()%3;
    }while(e==k);
    
    for(i=0; i<la;i++)
    {
        flops2+=2;
        h+=A[i][e]*A[i][k];
    }
    printf("Produto interno: %.2f\n", h);
    printf("Flops desta operação = %d\n", flops2);


	/* desaloca a memoria, nao mais necessaria */
	A = Liberar_matriz_real (la, ca, A);
	return 0;
} /* fim do programa */
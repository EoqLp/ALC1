#include <stdio.h>
#include <stdlib.h>

int flops;
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

/* Essa funcao faz a multiplicacao entre as matrizes.
 * Retorna um matriz com resultado da multplicao
 * */
float **mult(int ma, int mb , int na, int nb, float **a, float **b, float **mr)
{
	int i, j , v;
	flops=0;
	for (i = 0 ; i < ma; i++ )
		for (j = 0; j < nb; j++)
			for (v = 0; v < na; v++)
			{
				flops+=2;
				mr[i][j] = mr[i][j] + a[i][v] * b[v][j];
			}

	return(mr);
}

/* funcao pra imprimir na tela as matrizes  */
void imprime(int ma , int na, float t)
{
	printf("Ordem da matriz: %d x %d\n", ma, na);
	printf("traço: %f\n", t);
	printf("numero de flops: %d\n", flops);
}


float traco(int la, int ca, float **v)
{
	int i, j;
	float t=0;
	for(i=0; i<la; i++)
	{
		for(j=0; j<ca; j++)
		{
			if(i==j)
			{
				t+=v[i][j];
			}
		}
	}
	return t;
}

/*
 * Essa e a funcao principal
 */
int main(int argc, char **argv)
{
	float **A;  /* matriz a ser alocada */
	float **MR;  /* matriz a ser alocada */
	float t;
	int i;
	int j;

	int la, ca;   /* numero de linhas e colunas da matriz */

	printf("Informe o Numero de Linhas  A : ");
	scanf("%d", &la);
	printf("Informe o Numero de Colunas A : ");
	scanf("%d", &ca);


	/* Chama a funcao para alocar a matriz */
	A = Alocar_matriz_real (la, ca);
	MR = Alocar_matriz_real (la, ca);

	/* Chama funcao pra preencher as matrizes  */
	A = ler_mata(la, ca, A);

	/* chama a funcao pra fazer muultiplicacao das matrizes */
	MR = mult(la, la, ca, ca, A, A, MR);

	/*chama a função que calcula o traço*/
	t=traco(la, ca, MR);

	/* chama a funcao pra mostrar na tela o resultado da multiplicacao */
	imprime(la , ca, t);
	/* desaloca a memoria, nao mais necessaria */
	A = Liberar_matriz_real (la, ca, A);
	MR = Liberar_matriz_real (la, ca, MR);

	return 0;
} /* fim do programa */
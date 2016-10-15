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
float **ler_mat(int m, int n, float **v)
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

/* funcao pra imprimir na tela as matrizes  */
void imprime(int ma, int na, float **a)
{
	int i, j;

	/* Impressao das Matrizes */
	printf("MATRIX A:\n");
	for (i = 0; i < ma; i++) {
		for ( j = 0; j < na; j++)
			printf("%.f ", a[i][j]);
		printf("\n");
	}
}

/* funcao pra validar se e possivel fazer a multiplicao entre
 * as matrizes dadas
 */
int invalido(int na)
{
	if (na >4)
		return -1;

	return 0;
}
/* Essa funcao faz a conta da determinante
 * */
void determinant(float **matriz, int ordem)
{
	float det;
	/*Calculando o determinante de uma matriz 2x2*/
    if(ordem == 2)
    {
        det = matriz[0][0]*matriz[1][1] - matriz[0][1]*matriz[1][0];
        printf("O determinante é: %f\n\n", det);
    }
    /* Fim do calculo do det2*/
    /* Calculando o determinante de uma matriz 3x3*/
	if(ordem == 3)
	{
		det = (matriz[0][0]*matriz[1][1]*matriz[2][2]) + (matriz[0][1]*matriz[1][2]*matriz[2][0]) + (matriz[0][2]*matriz[1][0]*matriz[2][1])
        - ((matriz[0][1]*matriz[1][0]*matriz[2][2]) + (matriz[0][0]*matriz[1][2]*matriz[2][1]) + (matriz[0][2]*matriz[1][1]*matriz[2][0]));
        printf("O determinante é: %f\n\n", det);
    }
    /* Fim do calculo do det3*/          
    /* Calculando o determinante de uma matriz 4x4 */
    if(ordem == 4)
    {
        det = (matriz[0][0] * ((matriz[1][1]*matriz[2][2]*matriz[3][3]) + (matriz[1][2]*matriz[2][3]*matriz[3][1]) + (matriz[1][3]*matriz[2][1]*matriz[3][2])
        - ((matriz[1][2]*matriz[2][1]*matriz[3][3]) + (matriz[1][1]*matriz[2][3]*matriz[3][2]) + (matriz[1][3]*matriz[2][2]*matriz[3][1]) )))
        + ( (-matriz[0][1]) * ((matriz[1][0]*matriz[2][2]*matriz[3][3]) + (matriz[1][2]*matriz[2][3]*matriz[3][0]) + (matriz[1][3]*matriz[2][0]*matriz[3][0])
        - ((matriz[1][2]*matriz[2][0]*matriz[3][3]) + (matriz[1][0]*matriz[2][3]*matriz[3][2]) + (matriz[1][3]*matriz[2][2]*matriz[3][0]) )))
        + ( matriz[0][2] * ((matriz[1][0]*matriz[2][1]*matriz[3][3]) + (matriz[1][1]*matriz[2][3]*matriz[3][0]) + (matriz[1][3]*matriz[2][0]*matriz[3][1])
        - ((matriz[1][1]*matriz[2][0]*matriz[3][3]) + (matriz[1][0]*matriz[2][3]*matriz[3][1]) + (matriz[1][3]*matriz[2][1]*matriz[3][0]) )))
        + ((-matriz[0][3]) * ((matriz[1][0]*matriz[2][1]*matriz[3][2]) + (matriz[1][1]*matriz[2][3]*matriz[3][0]) + (matriz[1][3]*matriz[2][0]*matriz[3][1])
        - ((matriz[1][1]*matriz[2][0]*matriz[3][2]) + (matriz[1][0]*matriz[2][3]*matriz[3][1]) + (matriz[1][3]*matriz[2][1]*matriz[3][0]))));    
   		printf("O determinante é: %f\n\n", det);
    }
}

/*
 * Essa e a funcao principal
 */
int main(int argc, char **argv)
{
	float **A;	/* matriz a ser alocada */
	int la, ca, ordem;	/* numero de linhas e colunas da matriz */
	float det; /* valor da determinant*/

	printf("Informe a ordem da matriz  A : ");
	scanf("%d", &ordem);

	if(invalido(ordem)) {
		fprintf(stderr, "Erro:\n");
		fprintf(stderr, "Ordem deve ser menor ou igual a 4\n");
		exit(EXIT_FAILURE);
	}
	la = ordem;
	ca = ordem;

	/* Chama a funcao para alocar a matriz */
	A = Alocar_matriz_real (la, ca);
	
	/* Chama funcao pra preencher a matriz  */
	A = ler_mat(la, ca, A);

	/* chama a funcao pra mostrar na tela o resultado da multiplicacao */
	imprime(la, ca, A);

	/* chama a funcao pra calcular a determinante da matriz */
	determinant(A, ordem);
	
	/* desaloca a memoria, nao mais nescessaria */
	A = Liberar_matriz_real (la, ca, A);

	return 0;
} /* fim do programa */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
double res;
/* aloca memoria para as matrizes  */
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

/* Libera memoria ocupada pelas matrizes */
double **Liberar_matriz_real (int m, int n, double **v)
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
double **ler_matb(int m, double **v)
{
	int i;

	printf("Preencha o Vetor: \n");
	for (i = 0 ; i < m; i++ )
	{
			printf("Posicao b%d \n", i+1);
			scanf("%lf", &v[i][1]);
	}
	printf("\n");
	return(v); 
}

double **geraA(int ordem, double **V)
{
	int i, j;
	for(i = 0;i<ordem;i++)
	{
		for(j = 0;j<ordem;j++)
		{
			int a = 10 + i * 6 + j * 7;
			int numeroAleatorio1 = rand() % a;
			srand ((unsigned) time (NULL));
			V[i][j] = numeroAleatorio1;
	 	}
	}
	return (V);
}

double **cholesky(int ordem, double **vetorX, double **matrizA, double **vetorB)
{
	double matrizR[ordem][ordem];
	double matrizRTransposta[ordem][ordem];
	int somatorio = 0, i, j, k;
	double somador = 0;
	double vetorY[ordem];
	double temp = 0;
	//Decomposição Cholesky
	for ( i = 0; i < ordem; i++)
	{
		for(j = i; j < ordem; j++)
		{
			k = 0;
			for(k = 0; k < i; k++)
			{
				somatorio += matrizR[k][i] * matrizR[k][j];
			}

			if(i == j)
				matrizR[i][j]  = sqrt((matrizA[i][j] - somatorio));
			else
				matrizR[i][j]  = (matrizA[i][j] - somatorio) / matrizR[i][i];
		}
	}
	//Criando uma matriz Transporta de R
	for ( i = 0; i < ordem; i++)
	{
		for(j = 0; j < ordem; j++)
		{
			matrizRTransposta[i][j] = matrizR[j][i];
		}
	}
	//Substituicao pra frente
	vetorY[0] = vetorB[0][1]/matrizRTransposta[0][0];
    for(i = 1;i<ordem;i++)
    {
    	for(j = 0;j<i;j++)
    	{
    		somador += matrizRTransposta[i][j]*vetorY[j];
    	}
    	vetorY[i] = (vetorB[i][1] - somador)/matrizRTransposta[i][i];
    	somador = 0;
    }
    // mesma lógica da substituicao para frente, porém, ao invez de começar do y1, começamos do Yn.
    vetorX[ordem-1][1] = vetorY[ordem-1]/matrizR[ordem-1][ordem-1];
    somador = 0;

  	for(i = ordem-2;i>=0;i--){
  		for(j= ordem-1;j>i;	j--){
  			somador += matrizR[i][j]*vetorX[j][1];
  			
  		}
  		vetorX[i][1] = (vetorY[i] - somador)/matrizR[i][i];
  		somador=0;
  	}
    printf("Vetor X por Cholesky: \n");
    for(i = 0; i < ordem; i++)
        printf("%.3f\n", vetorX[i][1]);
	for(i = 0; i < ordem; i++)
	{
	  for(j = 0; j < ordem; j++)
	  {
		  temp += pow(matrizR[i][j],2);
	  }
	}
	printf("\n");
	res = sqrt(temp);
    return (vetorX);
}

double **gaus(double **matrizA, double **vetorB, int ordem, double **V)
{
	double vetorInteracaoGauss[100][ordem];
	int k = 0, i, j;
	for(k =0; k < 100; k++)
	{
		for(i = 0; i < ordem; i ++)
		{
			vetorInteracaoGauss[k][i] = 0;
			if(k == 0){
				vetorInteracaoGauss[k][i] = 50;
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
					vetorInteracaoGauss[k][i] += vetorB[i][1];
				}
				else
				{
					if(j <= i)
						vetorInteracaoGauss[k][i] -= vetorInteracaoGauss[k][j] * matrizA[i][j];
					else
						vetorInteracaoGauss[k][i] -= vetorInteracaoGauss[k-1][j] * matrizA[i][j];
				}
			}
			vetorInteracaoGauss[k][i] /= matrizA[i][i];
		}
	}

	int guassConverge = 1;
	for(i = 0; i < ordem; i ++){
		if(abs(abs(vetorInteracaoGauss[99][i]) - abs(vetorInteracaoGauss[98][i])) > 0.1){
			guassConverge = 0;
			printf("Gauss não convergiu.\n");
			break;
		}
	}

	if(guassConverge == 1){
		printf("Vetor X por Gauss: \n");
		for(i = 0; i < ordem; i ++){
			printf("%.3f \n", vetorInteracaoGauss[99][i]);
			V[i][1]=vetorInteracaoGauss[99][i];
		}
	}
	printf("\n");
	return(V);
}

void compara(double **matrizA, double **vetorX, double **vetorInteracaoGauss, int ordem)
{
	double **multiplicacaoCholesky;
	double **multiplicacaoGauss;
	int i, j, x=1;
	multiplicacaoCholesky=Alocar_matriz_real(ordem, x);
	multiplicacaoGauss=Alocar_matriz_real(ordem, x);
	for(i = 0; i < ordem; i++){
		multiplicacaoCholesky[i][1] = 0;
		multiplicacaoGauss[i][1] = 0;
		for(j = 0; j < ordem; j++){
				multiplicacaoCholesky[i][1] = multiplicacaoCholesky[i][1] + matrizA[i][j] * vetorX[j][1];
				multiplicacaoGauss[i][1] = multiplicacaoGauss[i][1] + matrizA[i][j] * vetorInteracaoGauss[j][1];
		}
	}

	printf("Vetor b substituindo pela solução por decomposição de Cholesky\n");
	for(i = 0; i < ordem; i++){
		printf("%.3f \n",multiplicacaoCholesky[i][1]);
	}
	printf("\n");
	printf("Vetor b substituindo pela solução por Gauss\n");
	for(i = 0; i < ordem; i++){
		printf("%.3f \n",multiplicacaoGauss[i][1]);
	}
	printf("\n");
	multiplicacaoCholesky=Liberar_matriz_real(ordem, x, multiplicacaoCholesky);
	multiplicacaoGauss=Liberar_matriz_real(ordem, x, multiplicacaoGauss);
}

int main()
{
	double **A;
	double **b;
	double **xC;
	double **xG;
	int k, x=1;

	printf("Digite a ordem da matriz A: ");
	scanf("%d,",&k);

	A=Alocar_matriz_real(k, k);
	b=Alocar_matriz_real(k, x);
	xC=Alocar_matriz_real(k, x);
	xG=Alocar_matriz_real(k, x);

	A=geraA(k, A);
	b=ler_matb(k, b);
	xC=cholesky(k, xC, A, b);
	xG=gaus(A, b, k, xG);
	compara(A, xC, xG, k);
	printf("Norma de Frobenius da matriz Cholesky\n");
	printf("%.3f \n", res);

	A=Liberar_matriz_real(k, k, A);
	b=Liberar_matriz_real(k, x, b);
	xC=Liberar_matriz_real(k, x, xC);
	xG=Liberar_matriz_real(k, x, xG);

	return 0;
}
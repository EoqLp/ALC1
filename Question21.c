
// Questao 21

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define W 150
double absoluto(double valor)
{
	if (valor < 0)
	{
		return valor  * -1;
	}
	return valor;
}

void imprimirMatriz(double** matriz,int tamC,int tamL)
{
	int i,j;

		for(i=0;i<tamC;i++)
		{
			for(j=0;j<tamL;j++)
			{
				printf("%.3lf ",matriz[i][j]);
			}
			printf("\n");
		}
}

/*
 * Normas para Matrizes
 */

double normaFrobenius(double** A,int tamC,int tamL)
{
	int i,j =0;
	double norma = 0;
	for(i=0;i<tamC;i++)
	{
		for(j=0;j<tamL;j++)
		{
			norma += A[i][j]*A[i][j];
		}
	}
	norma = sqrt(norma);
	return norma;

}

double distanciaMatrizes(double** A,double** B,int tamC,int tamL)
{
	int j,i =0;

	double** matriz = (double**) malloc(sizeof(double*)*tamC*tamL);

	for(i=0;i<tamC;i++)
	{
		matriz[i] = (double*) malloc(sizeof(double)*tamC);
		for(j=0;j<tamL;j++)
		{
			matriz[i][j] = A[i][j] - B[i][j];
		}
	}
	double resultado = normaFrobenius(matriz,tamC,tamL);
	return resultado;
}


double normaInfinito(double** A,int tamC,int tamL)
{

	int i,j =0;
	double norma = 0;
	for(i=0;i<tamC;i++)
	{
		double normaTemp = 0;
		for(j=0;j<tamL;j++)
		{
			normaTemp += absoluto(A[i][j]);
		}
		if (norma < normaTemp)
		{
			norma = normaTemp;
		}
	}

		return norma;
}
double norma1(double** A,int tamC,int tamL)
{

	int i,j =0;
	double norma = 0;
	for(i=0;i<tamL;i++)
	{
		double normaTemp = 0;
		for(j=0;j<tamC;j++)
		{
			normaTemp += absoluto(A[j][i]);
		}
		if (norma < normaTemp)
		{
			norma = normaTemp;
		}
	}

		return norma;
}

double*** lerMatriz(const char* file_name)
{
  FILE* file = fopen (file_name, "r");
  int coluna = 0;
  int linha = 0;
  //Coluna
  fscanf (file, "%d", &coluna);
  fscanf (file, "%d", &linha);

  int i =  0;
  int j = 0;
  double** matriz = (double**) malloc(sizeof(double*)*coluna*linha);
  matriz[i] = (double*) malloc(sizeof(double)*coluna);
  while (!feof (file))
  {
	  fscanf (file, "%lf", &matriz[i][j]);
	  j++;
	  if(coluna == j)
	  {
		  j = 0;
		  i++;
		  matriz[i] = (double*) malloc(sizeof(double)*coluna);
	  }
  }
  fclose (file);
  double*** retorno = (double***) malloc(sizeof(double***)*3);
  retorno[0] = matriz;
  retorno[1] = (double**) malloc(sizeof(double*));
  retorno[1][0] = (double*) malloc(sizeof(double)*2);
  retorno[1][0][0] = (double) coluna;
  retorno[1][0][1] = (double) linha;
  return retorno;

}
double limitanteInferiorNumeroCondicao(double** A,double** AI,int tamC,int tamL,int w)
{
	int i,j;
	double** matrizTemp = (double**) malloc(sizeof(double*)*tamC*tamL);
	for (i = 0; i < tamL; ++i)
	{
		matrizTemp[i] = (double*) malloc(sizeof(double)*tamL);
		for (j = 0; j < tamC; ++j)
		{
			matrizTemp[i][j] = AI[i][j] * w;
		}
	}

	double dividendo = norma1(A,tamC,tamL) * norma1(matrizTemp,tamC,tamL);
	double divisor = w;
	double resultado = dividendo / divisor;
	return resultado;
}

int main()
{
	double*** matrizComInformacaoA = lerMatriz("A.csv");
	double** matrizA = matrizComInformacaoA[0];

	int coluna = (int) matrizComInformacaoA[1][0][0];
	int linha = (int) matrizComInformacaoA[1][0][1];
	printf("\n\n--- Matriz com informação A ---\n\n");
	imprimirMatriz(matrizA,linha,coluna);
	double*** matrizComInformacaoB = lerMatriz("AI.csv");
	double** matrizB = matrizComInformacaoB[0];
	printf("\n\n--- Matriz com informação B ---\n\n");
	imprimirMatriz(matrizB,linha,coluna);

	double numeroCondicao = limitanteInferiorNumeroCondicao(matrizA,matrizB,coluna,linha,W);

	printf("\n\nLimitante inferior do numero Condicao = %lf\n",numeroCondicao);
	printf("\n\n--- Fim de Execucao --- \n\n");
	return 0;
}

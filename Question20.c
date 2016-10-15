
// Questao 20

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
	printf("\n\n--- Matriz ---\n\n");

		for(i=0;i<tamC;i++)
		{
			for(j=0;j<tamL;j++)
			{
				printf("%lf ",matriz[i][j]);
			}
			printf("\n");
		}
	printf("\n--- Fim ---\n");
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


double normaInfinitoM(double** A,int tamC,int tamL)
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
double norma1M(double** A,int tamC,int tamL)
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


/*
 * Normas para Vetores
 */
double norma1(double* A,int tam)
{
	int i =0;
	double norma = 0;
	for (i = 0; i < tam; ++i)
	{
		norma += absoluto(A[i]);
	}
	return norma;

}

double norma2(double* A,int tam)
{

	int i =0;
	double norma = 0;
	for (i = 0; i < tam; ++i)
	{
		norma += A[i]*A[i];
	}
	norma = sqrt(norma);
	return norma;
}

double normaInfinito(double* A,int tam)
{
	int i =0;
	double norma = A[0];
	for (i = 1; i < tam; ++i)
	{
		if(norma < absoluto(A[i]))
		{
			norma = absoluto(A[i]);
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
double** lerVetor(const char* file_name)
{
  FILE* file = fopen (file_name, "r");
  int tamanho = 0;

  //tamanho do polinomio caracteristico
  fscanf (file, "%d", &tamanho);

  int i =  0;
  double* vetor = (double*) malloc(sizeof(double)*tamanho);

  while (!feof (file))
  {
	  fscanf (file, "%lf", &vetor[i]);
	  i++;
  }
  fclose (file);

  double** retorno = (double**) malloc(sizeof(double*)*2);
  retorno[0] = vetor;
  retorno[1] = (double*) malloc(sizeof(double));
  retorno[1][0] = tamanho;
  return retorno;

}

double distanciaEntreVetores(double* vet1,double* vet2,int tam, int norma)
{
	int i = 0;
	double* vetorResultado = (double*) malloc(sizeof(double)*tam);
	for (i = 0; i < tam; ++i)
	{
		vetorResultado[i] = vet1[i] - vet2[i];
	}

	if(norma == 1)
	{
		return norma1(vetorResultado,tam);
	}
	else if(norma == 2)
	{
		return norma2(vetorResultado,tam);
	}
	else
	{
		return normaInfinito(vetorResultado,tam);
	}
}

double produtoInternoVetores(double* vet1,double* vet2,int tam)
{
	int i = 0;
	double resultado = 0;
	for (i = 0; i < tam; ++i)
	{
		resultado += vet1[i]*vet2[i];
	}
	return resultado;

}
double anguloEntreVetores(double* vet1,double* vet2,int tam)
{
	double dividendo = produtoInternoVetores(vet1,vet2,tam);
	double divisor = norma2(vet1,tam) + norma2(vet2,tam);
	double resultado = dividendo / divisor;
	return resultado;
}

void questaoA(double* A,int tam)
{
	printf("\n---Questao A ---\n");
	printf("Norma1 = %lf\n",norma1(A,tam));
	printf("Norma2 = %lf\n",norma2(A,tam));
	printf("Norma Infinito = %lf\n",normaInfinito(A,tam));
}
void questaoB(double* A,double* B,int tam)
{
	printf("\n---Questao B ---\n");
	printf("Distancia entre vetores com a norma1 = %lf\n",distanciaEntreVetores(A,B,tam,1));
	printf("Distancia entre vetores com a norma2 = %lf\n",distanciaEntreVetores(A,B,tam,2));
	printf("Distancia entre vetores com a norma infinito = %lf\n",distanciaEntreVetores(A,B,tam,3));
}
void questaoC(double* A,double* B,int tam)
{
	printf("\n---Questao C ---\n");
	printf("Produto interno entre 2 vetores = %lf\n",produtoInternoVetores(A,B,tam));
	printf("Angulo entre dois vetores = %lf\n",anguloEntreVetores(A,B,tam));
}
void questaoD(double** A,double** B,int tamC,int tamL)
{
	printf("\n---Questao D ---\n");

	printf("Matriz A:\n");
	printf("norma1 = %lf\n",norma1M(A,tamC,tamL));
	printf("Norma de Frobenius= %lf\n",normaFrobenius(A,tamC,tamL));
	printf("Norma Infinito = %lf\n",normaInfinitoM(A,tamC,tamL));
	printf("\n\n");
	printf("Matriz B:\n");
	printf("norma1 = %lf\n",norma1M(B,tamC,tamL));
	printf("Norma de Frobenius= %lf\n",normaFrobenius(B,tamC,tamL));
	printf("Norma Infinito = %lf\n",normaInfinitoM(B,tamC,tamL));
	printf("\nDistancia entre as matrizes = %lf\n",distanciaMatrizes(A,B,tamC,tamL));
}

int main()
{

	int opcao;
	printf("1 ~~ norma 1, norma 2 e norma infinito do vetor\n");
	printf("2 ~~ distancia entre dois vetores usando norma 1, 2 e infinito \n");
	printf("3 ~~ produto interno e angulo entre dois vetores \n");
	printf("4 ~~ norma 1, norma infinito e norma de Frobenius de matrizes na qual cada vetor representa uma linha. Calcule a distância entre quaisquer dessas matrizes \n");
	printf("Escolha a questao escrevendo o numero correspondente:");
	scanf ("%d", &opcao);
	if (opcao == 1)
	{
		printf("Qual arquivo contem o Vetor:\n");
		char end[255];
		scanf("%s",end);
		double** vetorComInformacao = lerVetor(end);

		double* vetor = vetorComInformacao[0];
		int tamanho = (int)vetorComInformacao[1][0];
		questaoA(vetor,tamanho);
	}
	else if (opcao == 2)
	{
		printf("Qual arquivo contem o Vetor A:\n");
		char endA[255];
		scanf("%s",endA);
		double** vetorComInformacaoA = lerVetor(endA);
		double* vetorA = vetorComInformacaoA[0];
		int tamanho = (int)vetorComInformacaoA[1][0];

		printf("Qual arquivo contem o Vetor B:\n");
		char endB[255];
		scanf("%s",endB);
		double** vetorComInformacaoB = lerVetor(endB);
		double* vetorB = vetorComInformacaoB[0];

		questaoB(vetorA,vetorB,tamanho);
	}
	else if (opcao == 3)
		{
			printf("Qual arquivo contem o Vetor A:\n");
			char endA[255];
			scanf("%s",endA);
			double** vetorComInformacaoA = lerVetor(endA);
			double* vetorA = vetorComInformacaoA[0];
			int tamanho = (int)vetorComInformacaoA[1][0];

			printf("Qual arquivo contem o Vetor B:\n");
			char endB[255];
			scanf("%s",endB);
			double** vetorComInformacaoB = lerVetor(endB);
			double* vetorB = vetorComInformacaoB[0];

			questaoC(vetorA,vetorB,tamanho);
		}
	else if (opcao == 4)
	{
		printf("Qual arquivo contem a matriz A:\n");
		char endA[255];
		scanf("%s",endA);

		double*** matrizComInformacaoA = lerMatriz(endA);
		double** matrizA = matrizComInformacaoA[0];

		int coluna = (int) matrizComInformacaoA[1][0][0];
		int linha = (int) matrizComInformacaoA[1][0][1];

		imprimirMatriz(matrizA,linha,coluna);

		printf("Qual arquivo contem a matriz B:\n");
		char endB[255];
		scanf("%s",endB);

		double*** matrizComInformacaoB = lerMatriz(endB);
		double** matrizB = matrizComInformacaoB[0];

		imprimirMatriz(matrizB,linha,coluna);
		questaoD(matrizA,matrizB,coluna,linha);
	}

	printf("\n\n--- Fim de Execucao --- \n\n");
	return 0;
}

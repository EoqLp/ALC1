#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int ordem,i,j, ColunasOk = 1, LinhasOk = 1, SassenfeldOk = 1, max=0, k=0, Converge = 1, guassConverge = 1;

	printf("Digite a ordem da matriz A: ");
	scanf("%d,",&ordem);
	double vetorX[ordem][1];
	double matrizA[ordem][ordem];
	double vetorSolucao[ordem][1];
	double iteracao[100][ordem];
	double iteracao1[100][ordem];
	double iteracao2[100][ordem];
	double iteracaoGauss[100][ordem];
	double iteracaoGauss1[100][ordem];
	double iteracaoGauss2[100][ordem];
	double perturbacao = 0;
	double SPerturbado[ordem][1];
	double matrizAP[ordem][ordem];
	double e[ordem];
	double diagonal = 0;
	double outros = 0;
	double perturbacaoNaMatrizA = 0;
	/*Pegando a matriz e o vetor solução!*/
	printf("Digite a matriz A, linha por linha: \n");
	for(i = 0;i<ordem;i++)
	{
		for(j = 0;j<ordem;j++)
		{
			scanf("%lf",&matrizA[i][j]);
		}
	}

	printf("Digite o vetor b: \n");
	for(i = 0;i<ordem;i++)
	{
		scanf("%lf",&vetorSolucao[i][0]);
	}
	for(i = 0; i < ordem; i++)
	{
		for(j = 0; j < ordem; j++)
		{
				if(i == j)
					diagonal = abs(matrizA[i][j]);
				else
					outros += abs(matrizA[i][j]);
		}

		if(diagonal < outros)
		{
			printf("Não satisfaz o critério das linhas \n");
			LinhasOk = 0;
			break;
		}
	}	
	if(LinhasOk == 1)
		printf("Satistaz o critério das Linhas!\n");

	/*Critério Coluna*/
	for(i = 0; i < ordem; i++)
	{
		diagonal = 0;
		outros = 0;
		for(j = 0; j < ordem; j++)
		{
				if(i == j)
					diagonal = abs(matrizA[i][j]);
				else
					outros += abs(matrizA[j][i]);
		}
		if(diagonal < outros)
		{
			printf("Não satisfaz o critério das Colunas \n");
			ColunasOk = 0;
			break;
		}
	}
	if(ColunasOk == 1)
		printf("Satistaz o critério das Colunas!\n");
	/*Sassenfeld*/
	for(i = 0; i < ordem; i++)
	{
		diagonal = 0;
		outros = 0;
		for(j = 0; j < ordem; j++)
		{
			if(i == j)
				diagonal = abs(matrizA[i][j]);
			else{
				if(j >= i)
					outros += abs(matrizA[i][j]);
				else
					outros += abs(matrizA[i][j]) * e[j];
			}
		}

		e[i] = outros / diagonal;
		if(e[i] >= 1){
			SassenfeldOk = 0;
			break;
		}
	}

	if(SassenfeldOk == 1)
	{
		printf("Satisfaz o critério de Sassenfeld! ");
		for(int i = 0; i < ordem; i++)
		{
			if(e[i] > e[max])
				max = i;
		}

		printf("O maior é: %.3f\n", e[max]);
	}
	else
		printf("Não satisfaz o critério de Sassenfeld\n");
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
					iteracao[k][i] += vetorSolucao[i][0];
				}
				else
				{
					iteracao[k][i] -= iteracao[k-1][j] * matrizA[i][j];
				}
			}
			iteracao[k][i] /= matrizA[i][i];
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
			printf("%.3f\n ", iteracao[99][i]);
		}
	}
	printf("\n");
	/*Gauss*/
	k = 0;
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
					iteracaoGauss[k][i] += vetorSolucao[i][0];
				}
				else
				{
					if(j <= i)
						iteracaoGauss[k][i] -= iteracaoGauss[k][j] * matrizA[i][j];
					else
						iteracaoGauss[k][i] -= iteracaoGauss[k-1][j] * matrizA[i][j];
				}
			}
			iteracaoGauss[k][i] /= matrizA[i][i];
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
			printf("%lf ", iteracaoGauss[99][i]);
		}
	}
	printf("\n");
	/*Execução e avaliação de perturbações no vetor b */
	printf("Insira o valo da perturbação no vetor b: \n");
	scanf("%lf", &perturbacao);

	for(i = 0; i < ordem; i++)
	{
		SPerturbado[i][0] = vetorSolucao[i][0];
		SPerturbado[i][0] += perturbacao;
	}

	printf("Vetor b normal: ");
	for(i = 0; i < ordem; i++)
	{
		printf("%lf ", vetorSolucao[i][0]);
	}
	printf("\n");

	printf("Vetor b perturbado: ");
	for(i = 0; i < ordem; i++)
	{
		printf("%lf ", SPerturbado[i][0]);
	}
	printf("\n");

	/* Código de Jacobi feito acima*/
	if(Converge == 1)
	{
		for(k =0; k < 100; k++)
		{
			for(i = 0; i < ordem; i ++)
			{
				iteracao1[k][i] = 0;
				if(k == 0)
				{
					iteracao1[k][i] = vetorX[i][0];
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
						iteracao1[k][i] += vetorSolucao[i][0];
					}
					else
					{
						iteracao1[k][i] -= iteracao[k-1][j] * matrizA[i][j];
					}
				}
				iteracao1[k][i] /= matrizA[i][i];
			}
		}
		printf("\n");
		printf("vetor x:\n");
		for(i = 0; i < ordem; i ++)
		{
			printf("%.3lf\n ", iteracao1[99][i]);
		}
		printf("\n");
	}
	else if(guassConverge == 1)
	{
		/* Código de Gauss feito acima*/
		k = 0;
		for(k =0; k < 100; k++)
		{
			for(i = 0; i < ordem; i ++)
			{
				iteracaoGauss1[k][i] = 0;
				if(k == 0)
				{
					iteracaoGauss1[k][i] = vetorX[i][0];
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
						iteracaoGauss1[k][i] += vetorSolucao[i][0];
					}
					else
					{
						if(j <= i)
							iteracaoGauss1[k][i] -= iteracaoGauss1[k][j] * matrizA[i][j];
						else
							iteracaoGauss1[k][i] -= iteracaoGauss1[k-1][j] * matrizA[i][j];
					}
				}
				iteracaoGauss1[k][i] /= matrizA[i][i];
			}
		}
			printf("Gauss converge, vetor x: ");
			for(i = 0; i < ordem; i ++)
			{
				printf("%lf ", iteracaoGauss1[99][i]);
			}
		printf("\n");	
	}
	else
	{
		printf("Nenhum dos métodos converge\n");
	}
	printf("Insira o valor da perturbação na matriz A: \n");
	scanf("%lf", &perturbacaoNaMatrizA);

	for(i = 0; i < ordem; i ++){
		for(j = 0; j  < ordem; j++){
			matrizAP[i][j] = matrizA[i][j] + perturbacaoNaMatrizA;
		}
	}

 	printf("Matriz A perturbada: \n");
	for(i = 0; i < ordem; i ++){
		for(j = 0; j  < ordem; j++){
			printf("%lf ",matrizAP[i][j]);
		}
		printf("\n");
	}
	/* Código de Jacobi feito acima*/
	if(Converge == 1)
	{
		for(k =0; k < 100; k++)
		{
			for(i = 0; i < ordem; i ++)
			{
				iteracao2[k][i] = 0;
				if(k == 0)
				{
					iteracao2[k][i] = vetorX[i][0];
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
						iteracao2[k][i] += vetorSolucao[i][0];
					}
					else
					{
						iteracao2[k][i] -= iteracao2[k-1][j] * matrizAP[i][j];
					}
				}
				iteracao2[k][i] /= matrizAP[i][i];
			}
		}
		printf("Jacobi converge, vetor x: ");
		for(i = 0; i < ordem; i ++)
		{
			printf("%.3f ", iteracao2[99][i]);
		}
		
		printf("\n");
	}
	else if(guassConverge == 1)
	{
		/* Código de Gauss feito acima*/
		for(k =0; k < 100; k++)
		{
			for(i = 0; i < ordem; i ++)
			{
				iteracaoGauss2[k][i] = 0;
				if(k == 0)
				{
					iteracaoGauss2[k][i] = vetorX[i][0];
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
						iteracaoGauss2[k][i] += vetorSolucao[i][0];
					}
					else
					{
						if(j <= i)
							iteracaoGauss2[k][i] -= iteracaoGauss2[k][j] * matrizAP[i][j];
						else
							iteracaoGauss2[k][i] -= iteracaoGauss2[k-1][j] * matrizAP[i][j];
					}
				}
				iteracaoGauss2[k][i] /= matrizAP[i][i];
			}
		}
		printf("Gauss converge, vetor x: ");
		for(i = 0; i < ordem; i ++)
		{
			printf("%lf ", iteracaoGauss2[99][i]);
		}
		printf("\n");	
	}
	else
	{
		printf("Nenhum dos métodos converge\n");
	}
	return 0;
}
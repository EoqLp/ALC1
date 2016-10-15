#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double norm2(int n, double * b)
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

int main()
{
	int ordem, i, j, k, criterio_linhas=0, criterio_colunas=0;
	printf("Digite a ordem da matriz A: ");
	scanf("%d,",&ordem);
	double A[ordem][ordem];
	double vetorX[ordem][1];
	double x[ordem];
	double b[ordem];
	double iteracao[100][ordem];
	double iteracao1[100][ordem];
	double iteracao2[100][ordem];
	double resultado[ordem][ordem];
	double resultado2[ordem][ordem];
	double iteracaoGauss[100][ordem];
	double iteracaoGauss1[100][ordem];
	double iteracaoGauss2[100][ordem];
	double xJ[ordem];
	double xG[ordem];
	double perturbacao = 0.02;
	double SPerturbado[ordem][1];
	double AP[ordem][ordem];
	double g=0, ja=0;
	double sum1[ordem],//soma para fazer a norma linha
          sum2[ordem],//soma para fazer a norma coluna
          maximum1[ordem],//valor maximo de cada linha
          maximum2[ordem],//valor maximo de cada coluna
          norma1[ordem],//vetor usado para avaliar o criterio da norma
          norma=0;

	printf("Digite a matriz B");
	for(i=0; i<ordem; i++)
	{
		for(j=0; j<ordem; j++)
		{
			printf("\nB[%d][%d]: ", i+1, j+1);
			scanf("%lf", &A[i][j]);
		}
	}
	printf("\n");
	printf("Digite o vetor x");
	for(i=0; i<ordem; i++)
	{
		printf("\nx[%d]: ", i+1);
		scanf("%lf", &x[i]);
	}
	printf("\n");
	printf("Digite o vetor b");
	for(i=0; i<ordem; i++)
	{
		printf("\nb[%d]: ", i+1);
		scanf("%lf", &b[i]);
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
	printf("Resultado de x por Jacobi:\n");
	for(i = 0; i < ordem; i ++)
	{
		xJ[i]=iteracao[99][i];
		printf("%.3f\n ", iteracao[99][i]);
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
	printf("Resultado de x por Gauss: ");
	for(i = 0; i < ordem; i ++)
	{
		xG[i]=iteracaoGauss[99][i];
		printf("%lf ", iteracaoGauss[99][i]);
	}
	printf("\n");
	for (i=0;i<ordem;i++)
    { 
       	xG[i]=xG[i]-x[i];
    }
    for (i=0;i<ordem;i++)
    { 
       	xJ[i]=xJ[i]-x[i];
    }
    g=norm2(ordem, xG)/norm2(ordem, x);
    ja=norm2(ordem, xJ)/norm2(ordem, x);

    if(g<ja)
    {
    	printf("Gauss é o melhor metodo\n");
    }
    else if(ja<g)
    {
    	printf("Jacobi é o melhor metodo\n");
    }
    else
    {
    	printf("Deu ruim, metodos com resultados iguais:\n");
    	printf("Residuo de Jacobi %f\n", ja);
    	printf("Residuo de Gauss %f\n", g);
    }
    /*B----------------------------------------------*/
    printf("Avaliar criterio das linhas e das colunas para B*B, B*B*B, B+B\n\n");
    printf("B*B\n");
    //iniciando os vetores e matrizes com 0
    for(i=0;i<ordem;i++)
    {
        sum1[i]=0;
    }
        
    for(i=0;i<ordem;i++)
    {
        sum2[i]=0;
    }
    for(i=0;i<ordem;i++)
        maximum1[i]=0;

    for(i=0;i<ordem;i++)
        maximum2[i]=0;

    //multiplicando matriz b*b
	for(i = 0; i < ordem; i++)
    {
        for(j = 0; j < ordem; j++)
        {
            resultado[i][j] = 0;
        }
    }
    for(i = 0; i < ordem; i++)
    {
        for(j = 0; j < ordem; j++)
        {
            for(k = 0; k < ordem; k ++)
                resultado[i][j] += A[i][k] * A[k][j];
        }
    }
	//fazendo as respectivas somas
    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            sum1[i]+= resultado[i][j];
        }
    }
        
    for(j=0;j<ordem;j++)
    {
        for(i=0;i<ordem;i++)
        {
            sum2[j]+= resultado[i][j];
        }
    }
    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            if(maximum1[i]<resultado[i][j])
            {
                maximum1[i]= resultado[i][j];
            }
        }
    }

    for(j=0;j<ordem;j++)
    {
        for(i=0;i<ordem;i++)
        {
            if(maximum2[j]<resultado[i][j])
            {
                maximum2[j]= resultado[i][j];
            }
        }
    }
     //removendo o valor maximo da soma
    for(i=0;i<ordem;i++)
    {
        sum1[i]-= maximum1[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        sum2[i]-= maximum2[i];
    }


    //divisao das somas pelos valores maximos
    for(i=0;i<ordem;i++)
    {
        sum1[i]= sum1[i]/maximum1[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        sum2[i]= sum2[i]/maximum2[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        if(sum1[i]>=1)
        {
            criterio_linhas=0;
            break;
        }
        else
            criterio_linhas=1;
    }

    for(i=0;i<ordem;i++)
    {
        if(sum2[i]>=1)
        {
            criterio_colunas=0;
            break;
        }
        else
            criterio_colunas=1;
    }

    if(criterio_linhas)
        printf("A Matriz A atende ao criterio das linhas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das linhas, logo nada podemos afirmar\n");
    
    if(criterio_colunas)
        printf("A Matriz A atende ao criterio das colunas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das colunas, logo nada podemos afirmar\n");
    // multiplicando b*b*b
    // ZERANDO MATRIZ RESULTADO
    printf("B*B*B\n");
	for (i = 0; i< ordem; i++)
	{
		for (j = 0; j < ordem; j++)
		{
			
			resultado[i][j]=0;
		}
	}
    for(i = 0; i < ordem; i++)
    {
        for(j = 0; j < ordem; j++)
        {
            for(k = 0; k < ordem; k ++)
                resultado2[i][j] += A[i][k] * A[k][j];
        }
    }
    for(i = 0; i < ordem; i++)
    {
        for(j = 0; j < ordem; j++)
        {
            for(k = 0; k < ordem; k ++)
                resultado[i][j] += A[i][k] * resultado2[k][j];
        }
    }
	//iniciando os vetores e matrizes com 0
    for(i=0;i<ordem;i++)
    {
        sum1[i]=0;
    }
        
    for(i=0;i<ordem;i++)
    {
        sum2[i]=0;
    }
    for(i=0;i<ordem;i++)
        maximum1[i]=0;

    for(i=0;i<ordem;i++)
        maximum2[i]=0;

//fazendo as respectivas somas
    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            sum1[i]+= resultado[i][j];
        }
    }
        
    for(j=0;j<ordem;j++)
    {
        for(i=0;i<ordem;i++)
        {
            sum2[j]+= resultado[i][j];
        }
    }
    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            if(maximum1[i]<resultado[i][j])
            {
                maximum1[i]= resultado[i][j];
            }
        }
    }

    for(j=0;j<ordem;j++)
    {
        for(i=0;i<ordem;i++)
        {
            if(maximum2[j]<resultado[i][j])
            {
                maximum2[j]= resultado[i][j];
            }
        }
    }
     //removendo o valor maximo da soma
    for(i=0;i<ordem;i++)
    {
        sum1[i]-= maximum1[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        sum2[i]-= maximum2[i];
    }


    //divisao das somas pelos valores maximos
    for(i=0;i<ordem;i++)
    {
        sum1[i]= sum1[i]/maximum1[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        sum2[i]= sum2[i]/maximum2[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        if(sum1[i]>=1)
        {
            criterio_linhas=0;
            break;
        }
        else
            criterio_linhas=1;
    }

    for(i=0;i<ordem;i++)
    {
        if(sum2[i]>=1)
        {
            criterio_colunas=0;
            break;
        }
        else
            criterio_colunas=1;
    }

    if(criterio_linhas)
        printf("A Matriz A atende ao criterio das linhas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das linhas, logo nada podemos afirmar\n");
    
    if(criterio_colunas)
        printf("A Matriz A atende ao criterio das colunas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das colunas, logo nada podemos afirmar\n");

    // B+B
    printf("B+B\n");
    // ZERANDO MATRIZ RESULTADO
	for (i = 0; i< ordem; i++)
	{
		for (j = 0; j < ordem; j++)
		{
			
			resultado[i][j]=0;
		}
	}
    for(i = 0; i < ordem; i++)
    {
        for(j = 0; j < ordem; j++)
        {
            for(k = 0; k < ordem; k ++)
            {
                resultado[i][j] = A[i][k] + A[i][k];
            }
        }
    }
	//iniciando os vetores e matrizes com 0
    for(i=0;i<ordem;i++)
    {
        sum1[i]=0;
    }
        
    for(i=0;i<ordem;i++)
    {
        sum2[i]=0;
    }
    for(i=0;i<ordem;i++)
        maximum1[i]=0;

    for(i=0;i<ordem;i++)
        maximum2[i]=0;

//fazendo as respectivas somas
    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            sum1[i]+= resultado[i][j];
        }
    }
        
    for(j=0;j<ordem;j++)
    {
        for(i=0;i<ordem;i++)
        {
            sum2[j]+= resultado[i][j];
        }
    }
    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            if(maximum1[i]<resultado[i][j])
            {
                maximum1[i]= resultado[i][j];
            }
        }
    }

    for(j=0;j<ordem;j++)
    {
        for(i=0;i<ordem;i++)
        {
            if(maximum2[j]<resultado[i][j])
            {
                maximum2[j]= resultado[i][j];
            }
        }
    }
     //removendo o valor maximo da soma
    for(i=0;i<ordem;i++)
    {
        sum1[i]-= maximum1[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        sum2[i]-= maximum2[i];
    }


    //divisao das somas pelos valores maximos
    for(i=0;i<ordem;i++)
    {
        sum1[i]= sum1[i]/maximum1[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        sum2[i]= sum2[i]/maximum2[i];
    }
    
    for(i=0;i<ordem;i++)
    {
        if(sum1[i]>=1)
        {
            criterio_linhas=0;
            break;
        }
        else
            criterio_linhas=1;
    }

    for(i=0;i<ordem;i++)
    {
        if(sum2[i]>=1)
        {
            criterio_colunas=0;
            break;
        }
        else
            criterio_colunas=1;
    }

    if(criterio_linhas)
        printf("A Matriz A atende ao criterio das linhas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das linhas, logo nada podemos afirmar\n");
    
    if(criterio_colunas)
        printf("A Matriz A atende ao criterio das colunas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das colunas, logo nada podemos afirmar\n");

    /*C--------------------------*/
    /*Execução e avaliação de perturbações no vetor b */
	for(i = 0; i < ordem; i++)
	{
		SPerturbado[i][0] = b[i];
		SPerturbado[i][0] += perturbacao;
	}

	printf("Vetor b normal: ");
	for(i = 0; i < ordem; i++)
	{
		printf("%lf ", b[i]);
	}
	printf("\n");

	printf("Vetor b perturbado: ");
	for(i = 0; i < ordem; i++)
	{
		printf("%lf ", SPerturbado[i][0]);
	}
	printf("\n");

	/* Código de Jacobi feito acima*/
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
						iteracao1[k][i] += b[i];
					}
					else
					{
						iteracao1[k][i] -= iteracao[k-1][j] * A[i][j];
					}
				}
				iteracao1[k][i] /= A[i][i];
			}
		}
		printf("\n");
		printf("vetor x:\n");
		for(i = 0; i < ordem; i ++)
		{
			printf("%.3lf\n ", iteracao1[99][i]);
		}
		printf("\n");
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
						iteracaoGauss1[k][i] += b[i];
					}
					else
					{
						if(j <= i)
							iteracaoGauss1[k][i] -= iteracaoGauss1[k][j] * A[i][j];
						else
							iteracaoGauss1[k][i] -= iteracaoGauss1[k-1][j] * A[i][j];
					}
				}
				iteracaoGauss1[k][i] /= A[i][i];
			}
		}
		printf("Resultado de gauss com o vetor perturbado: ");
		for(i = 0; i < ordem; i ++)
		{
			printf("%lf ", iteracaoGauss1[99][i]);
		}
		printf("\n");
		printf("Resultado de gauss com a matriz perturbado: ");
		for(i = 0; i < ordem; i ++)
		{
			for(j = 0; j  < ordem; j++)
			{
				AP[i][j] = A[i][j] + perturbacao;
			}
		}
	

 	printf("Matriz A perturbada: \n");
	for(i = 0; i < ordem; i ++){
		for(j = 0; j  < ordem; j++){
			printf("%lf ",AP[i][j]);
		}
		printf("\n");
	}
	/* Código de Jacobi feito acima*/
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
						iteracao2[k][i] += b[i];
					}
					else
					{
						iteracao2[k][i] -= iteracao2[k-1][j] * AP[i][j];
					}
				}
				iteracao2[k][i] /= AP[i][i];
			}
		}
		printf("Resultado de X com a perturbado: ");
		for(i = 0; i < ordem; i ++)
		{
			printf("%.3f ", iteracao2[99][i]);
		}
		
		printf("\n");
	
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
						iteracaoGauss2[k][i] += b[i];
					}
					else
					{
						if(j <= i)
							iteracaoGauss2[k][i] -= iteracaoGauss2[k][j] * AP[i][j];
						else
							iteracaoGauss2[k][i] -= iteracaoGauss2[k-1][j] * AP[i][j];
					}
				}
				iteracaoGauss2[k][i] /= AP[i][i];
			}
		}
		printf("resultado com A perturbado em gauss: ");
		for(i = 0; i < ordem; i ++)
		{
			printf("%lf ", iteracaoGauss2[99][i]);
		}
		printf("\n");	


    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double stop(int ordem,double xo[ordem],double *x)
{
	int i;
	double norma=0,dx[ordem],norma2;
	for(i=0;i<ordem;i++)
	{
		dx[i]=*(x+i)-xo[i];
	}
	for(i=0;i<ordem;i++)
	{
		norma = norma + dx[i]*dx[i];	
	}
	for(i=0;i<ordem;i++)
	{
		norma2 = norma2 + *(x+i)**(x+i);
	}
	norma = sqrt(norma)/sqrt(norma2);
	
return norma;	
}



int main()
{
	int ordem,i,j,k;

	printf("Qual é a ordem da Matriz A?\n");
	scanf("%d,",&ordem);

	double vetX[ordem], vetB[ordem], vetAngulo[ordem], matA[ordem][ordem], Q[ordem][ordem]; 
	double QT[ordem][ordem], sen=0, cos=0, vetorC[ordem], matrizR[ordem][ordem], x[ordem];

	printf("Digite por linha a\n");
	for(i = 0;i<ordem;i++){
		for(j = 0;j<ordem;j++){
			scanf("%lf",&matA[i][j]);
		}
	}

	vetAngulo[0] = matA[0][0];
	vetAngulo[1] = matA[1][0];

	printf("Digite o vetor b: \n");
	for(i = 0;i<ordem;i++){
		scanf("%lf",&vetB[i]);
	}

	cos = vetAngulo[0] / sqrt((vetAngulo[0] * vetAngulo[0]) + (vetAngulo[1] * vetAngulo[1]));
	sen = vetAngulo[1] / sqrt((vetAngulo[0] * vetAngulo[0]) + (vetAngulo[1] * vetAngulo[1]));

	QT[0][0] = cos;
	QT[0][1] = sen;
	QT[1][0] = -sen;
	QT[1][1] = cos;

	
	for(i = 0; i < ordem; i++){
		vetorC[i] = 0;
		for(k = 0; k < ordem; k ++){
			vetorC[i] += QT[i][k] * vetB[k];
		}
	}
	
	matrizR[ordem][ordem];
	for(i = 0; i < ordem; i++){
		for(j = 0; j < ordem; j++){
			matrizR[i][j] = 0; 
			for(k = 0; k < ordem; k ++)
				matrizR[i][j] += QT[i][k] * matA[k][j];
		}
	}

	//matrizR[1][0] = 0;

	printf("matriz Q \n");
	for(i = 0; i < ordem; i++){
		for(j = 0; j < ordem; j++){
			printf("%lf ", QT[j][i]);
		}
		printf("\n");
	}
   	
   	printf("matriz R \n");
	for(i = 0; i < ordem; i++){
		for(j = 0; j < ordem; j++){
			printf("%lf ", matrizR[i][j]);
		}
		printf("\n");
	}


	vetX[ordem-1] = vetorC[ordem-1]/matrizR[ordem-1][ordem-1];
    double somador = 0;

  	for(i = ordem-2;i>=0;i--){
  		for(j = ordem-1;j>i;j--){
  			somador += matrizR[i][j]*vetX[j];
  			
  		}
  		vetX[i] = (vetorC[i] - somador)/matrizR[i][i];
  		somador=0;
  	}

  	printf("Vetor Solução:\n");
  	for(i = 0; i < ordem; i ++){
  		printf("%lf\n", vetX[i] );
  	}


	printf("Vamos resolver por SOR\n\nDigite o valor de x Inicial\n");
	for(i=0;i<ordem;i++)
	{
		scanf("%lf",&x[i]);
	}
	int iteracao=0,parada=1,max=50;
	double soma=0,xo[ordem];
	int w = 1;
	printf("Insira o valor de w:");
	scanf("%i", &w);

	while(parada==1 && iteracao<max)
	{
		for(i=0;i<ordem;i++)
		{
			xo[i] = *(x+i);
		}
		for(i=0;i<ordem;i++)
		{
			soma = 0;
			for(j=0;j<ordem;j++)
			{	
				if(i!=j)
				{
					soma = soma + (matA[i][j]**(x+j));
				}
			}
			*(x+i)= (1-w)**(x+i) + (w/matA[i][i])*(vetB[i] - soma);
		}

		iteracao++;
		printf("Iteracao %d: ",iteracao);
		for(i=0;i<ordem;i++)
		{
			printf("%lf ",*(x+i));
		}
		printf("\n");
		if(stop(ordem,xo,x)<0.0000001)
		{
			parada=0;
		}
	}

	return 0;
}
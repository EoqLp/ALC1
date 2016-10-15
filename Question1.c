#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void Vandermonde()
{
    int ordem=0,i,j,m, d, n;
    printf("Digite a ordem da matriz\n");
    scanf("%d",&ordem);
    if(ordem == 1)
    {
        do
        {
            printf("\nDigite uma ordem maior ou igual a dois:\n");
            scanf("%d",&ordem);
        }while(ordem == 1);
    }
    printf("\n");
    double matrix[ordem][ordem];
    for (i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            matrix[i][j]=0;
        }
    }
	//recebe a matriz digitada pelo usuário
    printf("\nDigite a matriz %d X %d\n",ordem,ordem);
    for (i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            printf("A[%d][%d]",i+1,j+1);
            scanf("%lf",&matrix[i][j]);
        }
    }
    printf("\n");
    //Verifica se a matriz entrada pelo arquivo é Vandermonde, usando a definição.
    int v=0;
    double b=0,p=0;
    for(i=0;i<ordem;i++)
    {
        b= matrix[i][1];
        p = b;
        if (matrix[i][0] != 1) //se pelo menos o primeiro elemento de uma linha for diferente de 0, o código já encerra.
        { 
            v=0;
            break;
        }else
            v=1;
        for(j=2;j<ordem;j++) //loop que verifica linha por linha os seus elementos.
        { 
            p*=b;
            if(matrix[i][j] == p)
            {
                v=1;
            }else{
                v=0;
                break;
            }
        }
        b=0;
    }
    if (v)
    {
        printf("\n A matriz é Vandermonde\n");
    }else{
    	printf("\n A matriz não é Vandermonde\n");
    	exit(1);
    }
    printf("\nDeseja calcular o determinante? 1-Sim || 2-Não\n");
    scanf("%d",&d);
    if(d==1)
    {
    	int k = 0;
        double determinante = 1;
        i = 0;
        for(i=0;i<ordem;i++)
        {
            for(k=i+1;k<ordem;k++)
            {
                if(matrix[i][1]>=matrix[k][1])
                {
                    determinante = ((determinante)*((matrix[i][1]) - (matrix[k][1])));
                }else{
                    determinante = ((determinante)*((matrix[k][1]) - (matrix[i][1])));
                }
            }
        }
        printf(" O Determinate da Matriz é: %.2lf\n", determinante);
    }
    printf("\n Deseja calcular a norma de Frobenius, norma linha, norma de coluna A e o produto interno entra a primeira linha e a segunda coluna bem como o ângulo entre esses dois vetores? 1-Sim || 2-Não\n");
    scanf("%d", &n);
    if(n==1)
    {
    	//bloco que calcula a norma de frobenius
        double norma_f=0;
        for (i=0;i<ordem;i++)
        {
            for(j=0;j<ordem;j++)
            {
                norma_f += pow(matrix[i][j],2);
            }
        }
        printf("A Norma de Frobenius da matriz A é: %.2lf\n",sqrt(norma_f));
        //bloco que calcula a norma linha da matriz A
        double sum=0,norma_linha = 0;
        for (i=0;i<ordem;i++)
        {
            for(j=0;j<ordem;j++)
            {
                if(matrix[i][j] > 0)
                    sum += matrix[i][j];
                else
                    sum += ((matrix[i][j]) * (-1));
            }
            if(sum > norma_linha)
            {
                norma_linha = sum;
                sum = 0;
            }else
                sum = 0;
        }
        printf("A Norma Linha da matriz A é: %.2lf\n",norma_linha);
        //bloco que calcula a norma coluna da matrz A
        double sum2=0,norma_coluna = 0;
        for (j=0;j<ordem;j++)
        {
            for(i=0;i<ordem;i++)
            {
                if(matrix[i][j] > 0)
                    sum2 += matrix[i][j];
                else
                    sum2 += ((matrix[i][j]) * (-1));
            }
            if(sum2 > norma_coluna)
            {
                norma_coluna = sum2;
                sum2 = 0;
            }else
                sum2 = 0;
        }
        printf("A Norma Coluna da matriz A é: %.2lf\n",norma_coluna);
        //bloco que calcula o produto interno entre a primeira linha e a segunda coluna
        double col2_t[ordem]; // um vetor que armazena a coluna 2 transposta
        double prod_int;//variável que armazena o produto interno.
        for(i=0;i<ordem;i++)
        { 
            col2_t[i] = matrix[i][1];//o vetor recebe a coluna
        }
        for(j=0;j<ordem;j++){
            prod_int += ((col2_t[j])*(matrix[0][j]));
        }
        printf(" O Produto interno da primeira linha e da segunda coluna da Matriz A é: %.2lf\n", prod_int);
        //bloco que calula o angulo entre esses dois vetores
        double norma_2=0, norma_2b=0, ang=0;
        for (i=0;i<ordem;i++)
        {
            norma_2 += pow(col2_t[i],2);
        }
        norma_2 = sqrt(norma_2);
        for (j=0;j<ordem;j++)
        {
            norma_2b += pow(matrix[0][j],2);
        }
        norma_2b = sqrt(norma_2b);
        ang = acos((prod_int)/((norma_2) * (norma_2b)));
        ang = ang*(180.0/3.14159265);
        printf(" O Angulo entre esses vetores eh: %.2lf\n\n", ang);
    }
}

int main(){
	Vandermonde();
	return 0;
}
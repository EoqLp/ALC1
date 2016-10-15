#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void preencheMatriz(int dim,int dim1, float MatrizA[][dim])
{   
    int i,j;

    printf("Entre com os elementos da matriz: \n");
    
    for(i=0;i<dim;i++)
        for(j=0;j<dim1;j++)
            scanf("%f", &MatrizA[i][j]);
}

int sassenfeldCriteria(int dim, int dim1,float MatrizA[dim][dim1])
{
    /*Variaveis locais*/
    float vetorBeta[dim1],
          maxBeta=0;
    int i,j;

    for(i=0;i<dim1;i++)/*Atribui 1 para todo elemento do vetor Beta*/
        vetorBeta[i]=1;
    
    for(i=0;i<dim;i++)
    {
        vetorBeta[i]=0;/*Faz com que o termo atual receba 0 para nao haver erro no calculo*/
        
        for(j=0;j<dim1;j++)
        {
            if(MatrizA[i][j]<0)/*Aplica o modulo nos elementos da matriz*/
                MatrizA[i][j]=MatrizA[i][j]*(-1.0);
            
            if(i!=j)
               vetorBeta[i]+=MatrizA[i][j]*vetorBeta[j];/*Calculo do Beta i*/
        }
        
        vetorBeta[i]/=MatrizA[i][i];/*Calculo do Beta i onde ele e divido pelo aii*/
        
        if(vetorBeta[i]>maxBeta)
            maxBeta=vetorBeta[i];/*Ve qual e o maior beta*/
    }
        if(maxBeta<1)
            return 1;
        else
            return 0;
}

int main(void)
{
    int i,j,
        dim,dim1,
        criterio_linhas=0,
        criterio_colunas=0,
        criterio_norma=1;//variaveis booleanas para confirmar se atendem aos criterios
    
    printf("Digite a ordem da Matriz A: \n\n");
    scanf("%d %d",&dim,&dim1);//recebe a ordem da matriz

    float MatrizA[dim][dim1],
          sum1[dim],//soma para fazer a norma linha
          sum2[dim1],//soma para fazer a norma coluna
          maximum1[dim],//valor maximo de cada linha
          maximum2[dim1],//valor maximo de cada coluna
          norma1[dim],//vetor usado para avaliar o criterio da norma
          norma=0;//o valor maximo gerado pela norma

    
    //iniciando os vetores e matrizes com 0
    for(i=0;i<dim;i++)
        sum1[i]=0;
        
    for(i=0;i<dim1;i++)
        sum2[i]=0;
    
    for(i=0;i<dim;i++)
        maximum1[i]=0;

    for(i=0;i<dim1;i++)
        maximum2[i]=0;
    
    for(i=0;i<dim;i++)
        norma1[i]=0;
    
    for(i=0;i<dim;i++)
        for(j=0;j<dim1;j++)
            MatrizA[i][j]=0;
        
    for(i=0;i<dim;i++)
        for(j=0;j<dim1;j++)
            MatrizA[i][j]=0;
        
    preencheMatriz(dim,dim1,MatrizA);
    
    //fazendo as respectivas somas
    for(i=0;i<dim;i++)
        for(j=0;j<dim1;j++)
            sum1[i]+= MatrizA[i][j];
        
    for(j=0;j<dim1;j++)
        for(i=0;i<dim;i++)
            sum2[j]+= MatrizA[i][j];
        
    //norma 1
    for(i=0;i<dim;i++)
        for(j=0;j<dim1;j++)
        {
            if(MatrizA[i][j]<0)
            {
                norma1[i]+= MatrizA[i][j]*(-1);
            }
            else
                norma1[i]+= MatrizA[i][j];
        }

    norma=norma1[0];

    for(i=1;i<dim;i++)
        if(norma1[i]>norma)
            norma= norma1[i];
            
    if(norma == 0)
    {
        for(j=0;j<dim1;j++)
        {
            for(i=0;i<dim;i++)
            {
                if(MatrizA[i][j]!=0)
                {
                    criterio_norma=0;
                }
                else
                {
                    criterio_norma=1;
                }
            }
        }
    }

    for(i=0;i<dim;i++)
        for(j=0;j<dim1;j++)
            if(maximum1[i]<MatrizA[i][j])
                maximum1[i]= MatrizA[i][j];

    for(j=0;j<dim1;j++)
        for(i=0;i<dim;i++)
            if(maximum2[j]<MatrizA[i][j])
                maximum2[j]= MatrizA[i][j];
    
    //removendo o valor maximo da soma
    for(i=0;i<dim;i++)
        sum1[i]-= maximum1[i];
    
    for(i=0;i<dim1;i++)
        sum2[i]-= maximum2[i];
    
    //divisao das somas pelos valores maximos
    for(i=0;i<dim;i++)
        sum1[i]= sum1[i]/maximum1[i];
    
    for(i=0;i<dim1;i++)
        sum2[i]= sum2[i]/maximum2[i];
    
    for(i=0;i<dim;i++)
    {
        if(sum1[i]>=1)
        {
            criterio_linhas=0;
            break;
        }
        else
            criterio_linhas=1;
    }

    for(i=0;i<dim1;i++)
    {
        if(sum2[i]>=1)
        {
            criterio_colunas=0;
            break;
        }
        else
            criterio_colunas=1;
    }

    printf("\n\nComo os criterios nao garantem nada, alguns dos metodos iterativos que podem ser utilizados para resolver o sistema são:\n");
    printf("Jacobi, Gauss Seidel, SOR, Gradiente Conjugado, entre outros.\n\n");
    
    if(criterio_linhas)
        printf("A Matriz A atende ao criterio das linhas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das linhas, logo nada podemos afirmar\n");
    
    if(criterio_colunas)
        printf("A Matriz A atende ao criterio das colunas, logo converge para o Metodo de Jacobi\n");
    else
        printf("A Matriz A nao atende ao criterio das colunas, logo nada podemos afirmar\n");
    
    if(sassenfeldCriteria(dim,dim1,MatrizA))
         printf("A Matriz A atende ao criterio de Sassenfeld, logo converge para o Metodo de Gauss Seidel\n");
    else
        printf("A Matriz A nao atende ao criterio de Sassenfeld, logo nada podemos afirmar\n");
    
    if(criterio_norma)
        printf("A Matriz A atende ao criterio das normas, possuindo uma norma linha de %.2lf\n",norma);
    else
        printf("A Matriz A nao atende ao criterio das normas, logo nao eh um espaco normado\n");

    return 0;
}
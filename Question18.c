#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float Norma1(int ordem,float vetor[ordem]);
float Norma1Matriz(int ordem, float matZ[ordem][ordem]);

float SubsFrenteTras(int ordem, float matL[ordem][ordem],float matU[ordem][ordem], float matA[ordem][ordem])
{
    float vetY[ordem],vetW[ordem],vetC[ordem],somador = 0, limitante = 0, A, W, C;
    int i,j;
    
    printf("LUc = W\n");

   
    for(i=0;i<ordem;i++)
    {
        printf("Elemento %d do vetor W : ",i+1);
        scanf("%f",&vetW[i]);
    }

    printf("\nLY = W\nSubstituicao pra frente / Obtem Y\n");
   
    vetY[0] = vetW[0]/matL[0][0];

    for(i = 1;i<ordem;i++)
    {
        for(j = 0;j<i;j++)
        {
            somador += matL[i][j]*vetY[j];
        }
        vetY[i] = (vetW[i] - somador)/matL[i][i];
        somador = 0;
    }

    printf("Y = ");
    for(i=0;i<ordem;i++)
        printf("%3lf",vetY[i]);

        printf("\n\n");


        printf("Uc = Y\n");
        printf("Substituicao pra tras / Obtem C\n");

    vetC[ordem-1] = vetY[ordem-1]/matU[ordem-1][ordem-1];
    somador = 0;
    for(i = ordem-2;i>=0;i--)
    {
        for(j= ordem-1;j>i;j--)
        {
            somador += matU[i][j]*vetC[j];

        }

        vetC[i] = (vetY[i] - somador)/matU[i][i];
        somador=0;
    }

    printf("C = ");
    for(i=0;i<ordem;i++)
        printf("%3lf",vetC[i]);

        printf("\n\n");

// Limitante Inferior

        A = Norma1Matriz(ordem,matA);
        C = Norma1(ordem,vetC);
        W = Norma1(ordem,vetW);


    limitante = (A*C)/W;

   printf("O limitante inferior é:  %f\n", limitante);


        return 0;
}


float Norma1(int ordem,float vetor[ordem])
{
    float norma = 0;
    int i, j;


        for(i=0;i<ordem;i++)
        {
            if(vetor[i]<0)
                norma +=  (vetor[i] * -1);

            else
            {
                norma += vetor[i];
            }

        }

    return norma;
}

float Norma1Matriz(int ordem, float matZ[ordem][ordem])
{
  float normaM = 0;
    int i, j;

    for(i=0;i<ordem;i++)
    {
        for(j=0;j<ordem;j++)
        {
            if(matZ[i][j]<0)
                normaM +=  (matZ[i][j] * -1);

            else
            {
                normaM += matZ[i][j];
            }

        }
    }

    return normaM;
}

int main ()
{
    int i,j,k;
    int ordem;

    printf("Ordem das Matrizes : \n");
    scanf("%d",&ordem);

    float matL[ordem][ordem],matU[ordem][ordem], matA[ordem][ordem];
    int X[ordem];

        printf("MatrizL :\n");
        for(i = 0; i < ordem; i++)
        {
                for(j = 0; j< ordem; j++)
                {
                    printf("Elemento (%d)(%d) : ",i+1,j+1);
                    scanf("%f",&matL[i][j]);
                }
        }

        printf("Matriz U:\n");
        for(i = 0; i < ordem; i++)
        {
                for(j = 0; j< ordem; j++)
                {
                    printf("Elemento (%d)(%d) : ",i+1,j+1);
                    scanf("%f",&matU[i][j]);
                }
        }

// Matriz A

for(i = 0;i < ordem; i++)
{
            j = 0;
            for(j< 0;j< ordem; j++)
            {
                matA[i][j] = 0;
                k = 0;
                for (k = 0; k< ordem; k++)
                {
                    matA[i][j] += matL[i][k]*matU[k][j];
                }
            }
}

SubsFrenteTras(ordem, matL,matU,matA);
return 0;
}

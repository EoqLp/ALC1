#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float norm2(int n, float b[])
{
	//for vectors
  int i;
   float s = 0;


	for(i=0;i<n;i++)
	   s += b[i]*b[i];

	   s = sqrt(s);
	   return s;

}

void sor (int n,float w, float a[][n], float b[], float x[])
{
	float sub1 =0;
	float sub2 =0;
	int i,j;
	for(i=0;i<n;i++)
	{
        for(j=0;j<i;j++)
		{
			sub1 += a[i][j]*x[j];

		}

		for(j=(i+1);j<n;j++)
		{
			sub2 += a[i][j]*x[j];

		}

		x[i] = (1-w)*x[i] + (w/a[i][i])*(b[i]-(sub1+sub2));
		sub1 = 0;
		sub2 = 0;

	}

}

void substituicao_tras (int n, float a[][n], float b [])
{
 int i,j;
 float c[n];

 for(i=0;i<n;i++)
     c[i] = b[i];

 for(i=0;i<n;i++) // Rt * y = b
     {
        if (i>0)
            for(j=0;j<=(i-1);j++)
                c[i] = c[i] - a[i][j] * c[j];

            c[i] = c[i]/a[i][i];
        }
        for(i=0;i<n;i++)
           b[i] = c[i];


      }

void substituicao_frente (int n, float a[][n], float b [])
{
	int i,j;
        float c[n];

        for(i=0;i<n;i++)
            c[i] = b[i];

	for(i=n-1;i>=0;i--) // R * x  = y
        {
            for(j=n-1;j>=i+1;j--)
                c[i] = c[i] - a[i][j] * c[j];

            c[i] = c[i]/a[i][i];
         }

     for(i=0;i<n;i++)
           b[i] = c[i];

}

int main()
{
    int tamanho;
/*  int tamanho -> Dimensão, magnitude, tamanho da matriz. A partir daí, teremos uma matriz quadrada, pois na fatoração
    por Cholesky só se trabalha com matrizes quadradas.
    Por exemplo: se temos que tamanho == 2, a matriz terá uma medida de 2 x 2 */

    printf("Dê o tamanho da sua matriz: \n");
    scanf("%d", &tamanho);

    float A[tamanho][tamanho], w, At[tamanho][tamanho];
    float b[tamanho], t[tamanho], tol, x[tamanho];
    int i, j;

    printf("Defina a sua matriz A: \n\n");

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<tamanho;j++)
        {
            scanf("%f", &A[i][j]);
        }
    }

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<tamanho;j++)
        {
            if(A[i][j] != A[j][i])
            {
                printf("A matriz não é simétrica. Logo, não será possível obter o fator de Cholesky. \n\n");
                return 0;
            }
            else
            {
                continue;
            }
        }
    }

    printf("A matriz é simétrica. \n\n");

    int aux = 1;
    float det = 1;
    float det2 = 1;
    int k;

    while(aux<tamanho) //cálculo de determinantes das submatrizes de A começa a partir daqui.
    {
        det = 1;
        det2 = 1;
        j = 0;
        k = 0;

        if(aux==1)
        {
            det = (A[0][0]*A[1][1])-(A[0][1]*A[1][0]);
            printf("Determinante da submatriz %d: %f\n\n",aux,det);
            aux++;

            if(det<=0)
            {
                printf("O determinante eh menor ou igual a zero. Logo, a matriz nao eh positiva definida, e não eh possível obter o fator de Cholesky. ");
                return 0;
            }
        }
        else
        {
            for(i=0;i<aux;i++)
            {
                det = det * A[i][j];
                j++;
            }

            k = aux;

            for(i=0;i<aux;i++)
            {
                det2 = det2 * A[i][k-1];
                k--;
            }

            det = det - det2;

            printf("Determinante da submatriz %d: %f\n\n",aux,det);

            aux++;

            if(det<=0)
            {
                printf("O determinante eh menor ou igual a zero. Logo, a matriz nao eh positiva definida, e não eh possível obter o fator de Cholesky. \n\n");
                return 0;
            }
        }
    }

    printf("A matriz eh positiva definida. \n\n");

    k = 0;

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<i;j++){
            A[i][i] = A[i][i] - pow(A[j][i],2);
        }

        A[i][i] = sqrt(A[i][i]);
        for(j=i+1;j<=tamanho;j++)
        {
            for(k=0;k<i;k++)
            {
                A[i][j] = A[i][j] - A[k][i] * A[k][j];
            }
            A[i][j] = A[i][j]/A[i][i];
        }
    }

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<tamanho;j++)
        {
            if(i > j)
            {
                A[i][j]=0;
            }
            At[i][j]=A[i][j];
        }
    }

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<tamanho;j++)
        {
            if(i > j)
            {
                k=At[i][j];
                A[i][j]=At[j][i];
                A[j][i]=k;
            }
        }
    }

    printf("A sua matriz L: \n\n");

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<tamanho;j++)
        {
            printf("%f  ",A[i][j]);
        }
        printf("\n\n");
    }

    printf("A sua matriz L transposta: \n\n");

    for (i=0;i<tamanho;i++)
    {
	    for(j=0;j<tamanho;j++)
        {
            printf("%f  ",At[i][j]);
        }
        printf("\n\n");
    }

    printf("Entre com o b da equacao: \n");

    for(i=0;i<tamanho;i++)
    {
        scanf("%f",&b[i]);
    }

    printf("\n");

    substituicao_tras(tamanho,A,b);
    substituicao_frente(tamanho,At,b);

    printf("O vetor x eh:\n");

    for (i=0;i<tamanho;i++)
    {
        printf("%f\n", b[i]);
    }

    printf("\n\n\n");


    //A partir de agora, será executado o método SOR


    printf("Defina a sua matriz A: \n\n");

    for(i=0;i<tamanho;i++)
    {
        for(j=0;j<tamanho;j++)
        {
            scanf("%f", &A[i][j]);
        }
    }

    printf("Entre com um vetor b: \n");
       for(i=0;i<tamanho;i++)
        {
          scanf("%f",&b[i]);

       }


    printf("Entre com uma tolerância: \n");
       scanf("%f",&tol);
       printf("\n");


       printf("Entre com um valor de x: \n");

       for(i=0;i<tamanho;i++)
           scanf("%f",&x[i]);

      printf("Entre com um w entre 0 e 2: \n");


      do
         scanf("%f",&w);
      while (!(w>0 && w<2));

      do
      {
		for(i=0;i<tamanho;i++)
		   t[i]=0;
		sor(tamanho,w,A,b,x);
		for(i=0;i<tamanho;i++)
            for(j=0;j<tamanho;j++)
                t[i] += A[i][j]*x[j];
        for(i=0;i<tamanho;i++)
            t[i]-=b[i];

	}

    while((norm2(tamanho,t))>tol);

    printf("Resultado do SOR: \n");
    for (i=0;i<tamanho;i++)
         printf("%f\n", x[i]);





    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void substituicaofrente (int n, double a[][n], double b [])
{
 int i,j;
 double c[n];

 for(i=0;i<n;i++)
     c[i] = b[i];

 for(i=0;i<n;i++)
        {
			if (i>0)
            for(j=0;j<=(i-1);j++)
                c[i] = c[i] - a[i][j] * c[j];

            c[i] = c[i]/a[i][i];
        }
        for(i=0;i<n;i++)
           b[i] = c[i];


}

void substituicaotras (int n, double a[][n], double b [])
{
	int i,j;
 double c[n];

 for(i=0;i<n;i++)
     c[i] = b[i];

	for(i=n-1;i>=0;i--)
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
	int i,j,n,superior=0,inferior=0;
    double k;

	printf("Entre com o tamanho da matriz A: \n");
	scanf("%d",&n);

	double a[n][n],l[n][n],u[n][n];
	double b[n],v[n],z[n];

	printf("Entre com os elementos de A: \n");

	for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%lf", &a[i][j]);

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i<j)
            {
                if(a[i][j]==0)
                {
                    inferior++;
                }
            }

            if(j<i)
            {
                if(a[i][j]==0)
                {
                    superior++;
                }
            }
        }
    }

    if(superior==6)
    {
        printf("A matriz é triangular superior. \n");
    }

    if(inferior==6)
    {
        printf("A matriz é triangular inferior. \n");
    }

    if((superior!=6) &&(inferior!=6))
    {
        printf("A matriz não é triangular. \n");
        return 0;
    }



    // L.U--------------------------------------------------
     for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(j<=i)
            {
                u[j][i]=a[j][i];
                if(j==i)
                    l[j][i]=1;
                else
                    l[j][i]=0;
            }
            else
            {
                l[j][i]=a[j][i];
                u[j][i]=0;
            }
        }
    }



   // printa L
   printf ("Entre com o fator L: \n");
    for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)

                printf("%.1lf ", l[i][j]);
             printf("\n");
         }
         printf("\n");

    printf ("Entre com o fator U: \n");
    for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)

                printf("%.1lf ", u[i][j]);
             printf("\n");
          }
        printf("\n");

    printf("Entre com o vetor b: \n" );

    for (i=0;i<n;i++)
        {
			scanf("%lf",&b[i]);
	    }

    for(i=0;i<n;i++)
    {
        z[i] = b[i];
    }

    substituicaofrente(n,l,b);
    substituicaotras(n,u,b);

    printf("Resultado: \n");
    for (i=0;i<n;i++)
    printf("%.1lf\n", b[i]);



    printf("Digite um valor para k: ");
    scanf("%lf",&k);

    double soma=0;
    double raiz;

    for(i=0;i<n;i++)
    {
        v[i]=z[i]*k;
    }

    for(i=0;i<n;i++)
    {
        soma+=pow(v[i],2);
    }
    printf("%lf",soma);
    raiz = sqrt(soma);

    for(i=0;i<n;i++)
    {
        v[i]=v[i]/raiz;
    }

    printf("Vetor com mesmo sentido e direção de x:");
    for(i=0;i<n;i++)
    {
        printf("\n%lf",v[i]);
    }

	return 0;
}

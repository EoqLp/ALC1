#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **Alocar_matriz_real(int m, int n)
{
	double **v;  /* ponteiro para a matriz */
	int   i;    /* variavel auxiliar      */

	if (m < 1 || n < 1) { /* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (NULL);
	}

	/* aloca as linhas da matriz */
	v = calloc (m, sizeof(double *));	/* Um vetor de m ponteiros para double */
	if (v == NULL) {
		printf ("** Erro: Memoria Insuficiente **");
		return (NULL);
	}

	/* aloca as colunas da matriz */
	for ( i = 0; i < m; i++ ) {
		v[i] =  calloc (n, sizeof(double));	/* m vetores de n doubles */
		if (v[i] == NULL) {
			printf ("** Erro: Memoria Insuficiente **");
			return (NULL);
		}
	}

	return (v); /* retorna o ponteiro para a matriz */
}

double **Liberar_matriz_real (int m, int n, double **v)
{
	int  i;  /* variavel auxiliar */

	if (v == NULL)
	   	return (NULL);

	if (m < 1 || n < 1) {  /* verifica parametros recebidos */
		printf ("** Erro: Parametro invalido **\n");
		return (v);
	}

	for (i = 0; i < m; i++)
	   	free (v[i]); /* libera as linhas da matriz */

	free (v);      /* libera a matriz (vetor de ponteiros) */

	return (NULL); /* retorna um ponteiro nulo */
}

double **ler_mata(int m, int n, double **v)
{
	int i, j;

	printf("Preencha a Matrix: \n");
	for (i = 0 ; i < m; i++ )
		for (j = 0; j < n; j++) {
			printf("Posicao a%d%d \n", i+1, j+1);
			scanf("%lf", &v[i][j]);
		}
	printf("\n");

	return(v); 
}
double **identidade(int m, int n, double **v)
{
	int i, j;
	for (i = 0 ; i < m; i++ )
		for (j = 0; j < n; j++) 
		{
			if(i==j)
			{
				v[i][j]=1;
			}
			else
			{
				v[i][j]=0;
			}
		}

	return(v); 
}
double det(int n , double **v )
{
	int i,j,k,l;
	double d = 0;
	double **m;
	//m=Alocar_matriz_real(n-1, n-1);
	if(n==2)
	{
  		d = (v[0][0]*v[1][1])-(v[0][1]*v[1][0]);
    	return(d);
  	}
  	else
  	{
		m=Alocar_matriz_real(n-1, n-1);
		for (k=0;k<n;k++)
	 	{
		   	for (i=1;i<n;i++) 
	   		{
            	l = 0;
        		for (j=0;j<n;j++) 
        		{
            		if (j == k)
                		continue;
            		m[i-1][l] = v[i][j];
               		l++;
            	}
        	}
        	d += pow(-1.0,k) * v[0][k] * det(n-1,m);
		}
		m=Liberar_matriz_real(n-1, n-1, m);
   	}
   	//m=Liberar_matriz_real(n-1, n-1, m);
    return d;
}
int PosDef(int n, double **a,double **at)
{
	int i,j;

    for(i=0;i<n;i++)
    {
        for(j=0;j<i;j++)
            a[i][i] = a[i][i] - pow(a[j][i],2);
        if(a[i][i] <= 0)
            return 0;
    }
    return 1;
}

int trid(int x, double **a)
{
	int i, j, k, m;
	for(i=0; i<x; i++)
	{
		if(a[i][i]==0)
		{
			return 0;
		}
		j=i+1;
		if(j==x)
		{
			if(a[j][j]==0)
			{
				return 0;
			}
		}
		k=i-1;
		if(k!=0)
		{
			if(a[k][k]==0)
			{
				return 0;
			}
		}
		for(m=0; m<x; m++)
		{
			if(m!=k && m!=j && m!=i)
			{
				if(a[i][m]!=0)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

double **CalcTransposta(int x, double **v, double **m)
{
	int i, j;
	for (i=0; i<x; i++)
	{
		m[i][i]=v[i][i];
		for(j=0; j<x; j++)
		{
			if(i<j)
			{
				m[i][j]=v[j][i];
			}
		}
	}
	return (m);
}

double **CalcInversa(int x, double **V, double **m)
{
	int i, pivo, j, k, e;

	for(i = 0; i < 3; i++)
	{
  		pivo = V[i][i];
  		for(j = i; j < 3; j++)
  		{
    		V[i][j] = (V[i][j])/(pivo); 
    		m[i][j] = (m[i][j])/(pivo); 
  		}
  		for(e = 0; e < 3; e++)
  		{
    		if(e != i)
    		{
      			k = V[e][i];
      			for(j = 0; j < 3; j++)
      			{
        			V[e][j] = (V[e][j]) - (k * V[i][j]); 
        			m[e][j] = (m[e][j]) - (k * m[i][j]);  
      			}
    		}
  		}  
	}
	return (m);
}

int Verif(int x, double **V, double **m)
{
	int i, j;
	for (i=0; i<x; i++)
	{
		for (j=0; j<x; j++)
		{
			if(V[i][j]!=m[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}

int main (void)
{
	double **A,**at, **Inv, **Id, **Transp;
	double de;
	int x, b, e, k;
	printf("Digite a ordem da matriz\n");
	scanf("%d", &x);

	/* Chama a funcao para alocar a matriz */
	A = Alocar_matriz_real (x, x);
	Id = Alocar_matriz_real (x, x);
	Inv = Alocar_matriz_real (x, x);
	at = Alocar_matriz_real (x, x);
	Transp = Alocar_matriz_real (x, x);
	/* Chama funcao pra preencher as matrizes  */
	A = ler_mata(x, x, A);
	/*Chama função pra preencher a matriz identidade*/
	Id=identidade(x, x, Id); 
	/* Verifica a determinante  da matriz */
	de=det(x,A);
	/* Calcula a matriz transposta */
	Transp=CalcTransposta(x, A, Transp);
	/*Calcula a matriz inversa */
	Inv=CalcInversa(x, A, Id);
	/*Chama a função que verifica se a matriz transposta é igual a matriz inversa*/
	k=Verif(x, Transp, Inv);
	/*Verifica se é positiva definida */
	b=PosDef(x, A, at);
	if(b)
	{
		printf("Essa matriz é positiva definida\n");
	}
	else if(k)
	{
		printf("Essa matriz é Ortogonal\n");
	}
	else
	{
		if(x>3)
		{
			e=trid(x, A);
			if(e)
			{
				printf("Essa matriz é tridiagonal\n");
			}
		}
	}
	/* desaloca a memoria, nao mais nescessaria */
	A = Liberar_matriz_real (x, x, A);
	at = Liberar_matriz_real (x, x, at);
	Id = Liberar_matriz_real (x, x, Id);
	Inv = Liberar_matriz_real (x, x, Inv);
	Transp = Liberar_matriz_real (x, x, Transp);
	return 0;
}

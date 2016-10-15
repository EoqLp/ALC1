#include <stdio.h>
#include <math.h>

float norma2(int dim, float VetorB[])
{
  	int i;
  	float s = 0;
  
    for(i=0;i<dim;i++)
		s+=VetorB[i]*VetorB[i]; 
  	
  	s=sqrt(s);
	
	return s;	  
}
	
void preencheMatriz(int dim, float MatrizA[][dim])
{   
    int i,j;

	printf("Entre com os elementos da matriz: \n");
	
	for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
            scanf("%f", &MatrizA[i][j]);
}

void preencheVetor(int dim, float VetorB[dim])
{
  int i,j;

  for (i=0;i<dim;i++)
    scanf("%f",&VetorB[i]);	
}

void mult_matrix(int dim, float Diagonal[][dim], float LU[][dim], float T[][dim])
{

  int   i,j,k;

  float sum; 

  for(i=0;i<dim;i++)
  {

    for(j=0;j<dim;j++)
    {
 
      T[i][j]= 0.0;
 
      for(k=0;k<dim;k++)
      {
        T[i][j] += Diagonal[i][k] * LU[k][j];
    
      }

    }
  }
}

float W_Otimo(int dim, float MatrizA[][dim])
{

 int   i,j,k;
 float Diagonal[dim][dim],
        LU[dim][dim],
        L[dim][dim],
        U[dim][dim],
        T[dim][dim],
        r,
        w;

  for(i=0; i<dim;i++)
  {  
    for (j=0; j<dim; j++)
    {
      if(i!=j)
         Diagonal[i][j]=0;
      else
        Diagonal[i][j]=1/MatrizA[i][j];
    }
  }

  for(i=0; i<dim;i++)
  {  
    for (j=0; j<dim; j++)
    {
      if(i>j)
      {
        L[i][j]=MatrizA[i][j]*-1.0;
        U[j][i]=MatrizA[j][i]*-1.0;
      }
      else
      {
        L[i][j]=0;
        U[i][j]=0;
      }
    }
  }
  
  for(i=0; i<dim;i++)
  {
    for (j=0; j<dim; j++)
    {
      LU[i][j ]= L[i][j] + U[i][j];
    }
  }

  mult_matrix(dim,Diagonal,LU,T);
  
  r = T[2][3] * T[3][2];
  r+= T[1][2] * T[2][1];

  r=sqrt(r);
  r= r*r;
  w=sqrt(1.0-r);

  w +=1.0;
  w = 2.0/w;

  return w;
}

void sor (int dim,float W, float MatrizA[][dim], float VetorB[], float X[])
{
  int i,j;
  float sub1 =0,
        sub2 =0;

  for(i=0;i<dim;i++)
  {
    for(j=0;j<i;j++)
      sub1 += MatrizA[i][j]*X[j];
        
    for(j=(i+1);j<dim;j++)
      sub2 += MatrizA[i][j]*X[j];
      
    X[i] = (1-W)*X[i] + (W/MatrizA[i][i])*(VetorB[i]-(sub1+sub2));
    sub1 = 0;
    sub2 = 0;
  }  
}

int main(void)
{
  int dim =3,
      i,j;
  float MatrizA[dim][dim],
        VetorB[dim],
        Tolerancia,
        Temp[dim],
        X[dim],
        W; 

  preencheMatriz(dim,MatrizA);

  W = W_Otimo(dim,MatrizA);
  printf("O W otimo é: \n %f\n",W);

  printf("Entre com os elementos do vetor B: \n");
  preencheVetor(dim,VetorB);

  printf("Entre com a tolerancia: \n");
  scanf("%f",&Tolerancia);

  printf("Entre com os elementos inicias do vetor X: \n");
  preencheVetor(dim,X);

  do
  {
    for(i=0;i<dim;i++)
      Temp[i]=0;
   
    sor(dim,W,MatrizA,VetorB,X);

    for(i=0;i<dim;i++)
      for(j=0;j<dim;j++)
        Temp[i] += MatrizA[i][j]*X[j];
    
    for(i=0;i<dim;i++)
      Temp[i]-=VetorB[i];     
    
  }
  while((norma2(dim,Temp)>Tolerancia));


  printf("Resultado Sor: \n");
  for (i=0;i<dim;i++) 
    printf("%f\n", X[i]);

  return 0;
}
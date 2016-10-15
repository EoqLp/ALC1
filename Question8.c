#include <stdio.h>
#include <math.h>
int p;
void substituicaofrente (int dim, float MatrizA[][dim], float VetorB [dim])
{

 int   i,
 	   j;
 float temp[dim];
 
 for(i=0;i<dim;i++)
     temp[i] = VetorB[i]; 


 for(i=0;i<dim;i++) 
    {
		if (i>0)
           	for(j=0;j<=(i-1);j++)
               	temp[i] = temp[i] - MatrizA[i][j] * temp[j];
                
        temp[i] = temp[i]/MatrizA[i][i];
    }
 for(i=0;i<dim;i++)
    VetorB[i] = temp[i];    

}

void substituicaotras (int dim, float MatrizA[][dim], float VetorB [dim])
{

 int   i,
  	   j;
 float temp[dim];
 
 for(i=0;i<dim;i++)
     temp[i] = VetorB[i]; 

 for(i=dim-1;i>=0;i--) 
    {
        for(j=dim-1;j>=i+1;j--)
            temp[i] = temp[i] - MatrizA[i][j] * temp[j];
          
        temp[i] = temp[i]/MatrizA[i][i];
    }
   
    for(i=0;i<dim;i++)
        VetorB[i] = temp[i]; 
     


}

void Fatoracao_LU(int dim, float MatrizA[][dim], float L[][dim], float U[][dim], float VetorB [dim])
{
	int i,j,
		k;
 	
 	for(i=0;i<dim;i++)
    {
        for(j=0;j<dim;j++)
        {
            if(j<=i)
            {
                U[j][i]=MatrizA[j][i];

                for(k=0;k<=j-1;k++)
                    U[j][i]-=L[j][k]*U[k][i];
                
                if(j==i)
                    L[j][i]=1;

                else
                    L[j][i]=0;
            }

            else
            {
                L[j][i]=MatrizA[j][i];

                for(k=0;k<=i-1;k++)
                    L[j][i]-=L[j][k]*U[k][i];

                L[j][i]/=U[i][i];

                U[j][i]=0;
            }
        }
    }

//  IMPRIME NA TELA A MATRIZ L
    printf ("Matriz L: \n");

    for(i=0;i<dim;i++)
        {
    		for(j=0;j<dim;j++)
            	printf("%f ", L[i][j]);
         
         	printf("\n");
        }
        
//	IMPRIME NA TELA A MATRIZ U

    printf ("\nMatriz U: \n");

    for(i=0;i<dim;i++)
        {
            for(j=0;j<dim;j++)      
                printf("%f ", U[i][j]);
             
             printf("\n");
        }
    
    substituicaofrente(dim,L,VetorB);    
    
    substituicaotras(dim,U,VetorB);
    
    printf(" \n ");
    
    for (i=0;i<dim;i++) 
        printf(" %f ",VetorB[i]);
}

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

void preencheVetor(int dim, float VetorB[dim], float VetorB1[dim])
{
    int i,j;
         
    for (i=0;i<dim;i++)
    {
        scanf("%f",&VetorB[i]);	
        VetorB1[i]=VetorB[i];
    }
}

void Gauss_Seidel(int dim, float MatrizA[][dim], float X[dim], float Tolerancia, float VetorB [])
{
	int   i,
		  j,
		  flag;

	float R1,
		  R2,
		  sub1=0,
		  sub2=0,
		  T[dim];

	for(i=0;i<dim;i++)
	    {
           for(j=0;j<i;j++)
			   sub1 += MatrizA[i][j] * X[j];
		
		   for(j=(i+1);j<dim;j++)
			  sub2 += MatrizA[i][j] * X[j];
		
		    X[i] = (1-1)*X[i] + (1/MatrizA[i][i]) * (VetorB[i]-(sub1+sub2));
		    
		    sub1 = 0;
		    sub2 = 0;
		
	    }
	    
	    for(i=0;i<dim;i++)
		    T[i]=0;
	
		for(i=0;i<dim;i++)
            for(j=0;j<dim;j++)
                T[i] += MatrizA[i][j] * X[j];

        for(i=0;i<dim;i++)
            T[i]-=VetorB[i];
        
        R2 = norma2(dim,T);	
        
    do
    {
		R1 = R2;
	
	    for(i=0;i<dim;i++)
	    {

           for(j=0;j<i;j++)
			   sub1 += MatrizA[i][j] * X[j];
		
		   for(j=(i+1);j<dim;j++)
			  sub2 += MatrizA[i][j] * X[j];
		
		    X[i] = (1-1)*X[i] + (1/MatrizA[i][i])*(VetorB[i]-(sub1+sub2));
		    
		    sub1 = 0;
		    sub2 = 0;
		
	    }
	    
	    for(i=0;i<dim;i++)
		    T[i]=0;
	
		for(i=0;i<dim;i++)
            for(j=0;j<dim;j++)
                T[i] += MatrizA[i][j] * X[j];
        
        for(i=0;i<dim;i++)
            T[i]-=VetorB[i];
        
        R2 = norma2(dim,T);
        if ( R2 > R1);
        {
			flag = 1;
			break;
		}	
	}
    while((R2>Tolerancia));
    
    if(flag)
    {
    	p=100;
    	printf("\nO sistema não converge para o metodo de Gauss-Seidel\n");
       
	}
	else
	{
		printf("Resultado do metodo de Gauss-Seidel\n");
	    
	    for(i=0;i<dim;i++)
           printf("%f\n", X[i]);                
	}
	
}

void MatrizBanda(int dim,float MatrizA[][dim])
{
    int i,j;

    for(i=0;i<dim;i++)
    {
        for(j=0;j<dim;j++)
        {
            if(i!=j&&i!=j-1&&i!=j+1)
            {
                if(MatrizA[i][j]!=0)
                {
                    printf("\nNão é uma matriz banda.\n");
                    i=dim;
                    j=dim;

                }
                else
                	printf("\nÉ uma matriz banda.\n");
            }

        }

    }
    
}

int main()
{
	int dim;
	 int i;
	
	printf("Entre com a dimensão da matriz: \n");

	scanf("%d",&dim);

	float MatrizA[dim][dim],
		  L[dim][dim],
		  U[dim][dim],
		  VetorB[dim],
          VetorB1[dim],
          VetorB2[dim],
		  Tolerancia,
		  X[dim];

    preencheMatriz(dim,MatrizA);
    
    printf("\nEntre com os elementos do vetor B: \n" ); 
    preencheVetor(dim,VetorB,VetorB1);
    
      
    printf("\nEntre com o valor da tolerancia:\n");
    scanf("%f",&Tolerancia);
    
    Fatoracao_LU(dim,MatrizA,L,U,VetorB);

    Gauss_Seidel(dim,MatrizA,X,Tolerancia,VetorB1);

    
    printf("\n");
    if (p==0)
    {
        for (i=0;i<dim;i++) 
           printf("  %f  ", X[i]);
    }
    
    printf("\n");
    MatrizBanda(dim,MatrizA);
}

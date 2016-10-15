#include <stdio.h>
#include <math.h>

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

  for(i=0;i<dim;i++)
        {
			printf("\n %f\n",VetorB[i]);        
        }   

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
    {
        scanf("%f",&VetorB[i]); 
    }
}
int main (void)
{
    int dim;

    printf("Entre com a dimensão da matriz: \n");

    scanf("%d",&dim);

    float MatrizA[dim][dim],
          L[dim][dim],
          U[dim][dim],
          VetorB[dim];

    preencheMatriz(dim,MatrizA);
    
    printf("\nEntre com os elementos do vetor B: \n" ); 
    preencheVetor(dim,VetorB);
    
    Fatoracao_LU(dim,MatrizA,L,U,VetorB);

    
  
}

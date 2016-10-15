#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void substituicaofrente (int dim, float MatrizA[][dim], float VetorB [])
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

void substituicaotras (int dim, float MatrizA[][dim], float VetorB [])
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
    
    printf("\nEntre com os elementos do vetor B: \n" ); 
     
    for (i=0;i<dim;i++)
        scanf("%f",&VetorB[i]); 
}

void cholesky(int dim, float MatrizA[][dim],float MatrizAT[][dim])
{
    int   i,j,
          k;
    float aux;

    for( i=0; i<dim; i++)
    {

        for( j=0; j<i; j++)
            MatrizA[i][i] = MatrizA[i][i] - pow(MatrizA[j][i],2);

        if(MatrizA[i][i] <= 0)
         {
            printf("Essa matriz não é positiva definida.");
            exit (0);
         }

        MatrizA[i][i] = sqrt(MatrizA[i][i]);

        for( j=i+1; j<=dim; j++)
        {
            for( k=0; k<i; k++)
                MatrizA[i][j] = MatrizA[i][j] - MatrizA[k][i] * MatrizA[k][j];


            MatrizA[i][j] = MatrizA[i][j]/MatrizA[i][i];
        }
    }

    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
        {
            if(i > j)
                MatrizA[i][j]=0;
            
            MatrizAT[i][j]=MatrizA[i][j];
        } 
       
    for( i=0; i<dim; i++)
    {
        for(j=0;j<dim;j++)
        {

            if(i > j)
            {
                aux=MatrizAT[i][j];
                MatrizA[i][j]=MatrizAT[j][i];
                MatrizA[j][i]=aux;
            }

        }
            
    }      

}

void mostra(int dim, float Matriz[][dim])
{
    int i,
        j;

    for( i=0; i<dim; i++)
        {
            for(j=0;j<dim;j++)
                printf("%f ", Matriz[i][j]);
         
            printf("\n");
        }
}

float determinante(int dim, float MatrizA[][dim])
{
    int i,j,
        k,l;
    float det = 0;
    float aux[dim-1][dim-1];
  
    if(dim==2)
    {
        det = (MatrizA[0][0]*MatrizA[1][1])-(MatrizA[0][1]*MatrizA[1][0]);

        return(det);
    }

    else
        {
            for (k=0;k<dim;k++)
            {
                for (i=1;i<dim;i++)   
                {
                    //"trhow away" the line 0
                    l = 0;
                    for (j=0;j<dim;j++) 
                    {
                        if (j == k) // trhow away the column [k] 
                        
                        continue;
                        aux[i-1][l] = MatrizA[i][j];
                        
                        l++;
                    }
                }
                
                det += pow(-1.0,k) * MatrizA[0][k] * determinante(dim-1,aux);
                //when k is even a sum happens, when k is odd a subtraction happens
            }
        }

    return det;
}

int main()
{
    int dim,
        i,w;

    printf("Entre com a dimensão da matriz: \n");

    scanf("%d",&dim);

    float MatrizA[dim][dim],
          MatrizAT[dim][dim],
          VetorB[dim];

    preencheMatriz(dim,MatrizA);
    
    w = determinante(dim,MatrizA);
    
    if(!w)
    {
	   printf("A matriz é singular.\n");
	   
       return 0;
    }
    
    cholesky(dim,MatrizA,MatrizAT);

    preencheVetor(dim,VetorB);

    substituicaofrente(dim,MatrizA,VetorB);
    substituicaotras(dim,MatrizAT,VetorB);

    printf("Fator R de Cholesky é: \n");

    mostra(dim,MatrizA);

    printf("\nFator RT de Cholesky é: \n");

    mostra(dim,MatrizAT);

    printf("\nO vetor X é:\n");

    for ( i=0; i<dim; i++) 
       printf("%f\n", VetorB[i]);

}
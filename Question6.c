#include <stdio.h>
#include <math.h>

int main (void)
{
	int n, d, i, j, k, count = 0;

	printf("Insira a quantidade de vetores a serem analisados:\n");
	scanf ("%d", &n);
	if (n < 1)
	{
		printf ("ERRO! INSIRA UM VALOR VÁLIDO");
	}
	printf("Insira a quantidade de elementos dentro do vetor a ser analisado:\n");
	scanf ("%d", &d);

	if (d < 1)
	{
		printf ("ERRO! INSIRA UM VALOR VÁLIDO");
	}
	float vet[n][d], mat[n][d], neg = 0, temp, rest = 0, soma2 = 0, somaq, soma;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < d; j++)
		{	
			
			printf ("INSIRA OS ELEMENTOS DO VETOR %d\n", i+1);
			scanf("%f", &vet[i][j]);
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{	
			mat[i][j] = vet[i][j];
		}
		printf ("\n");
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{	
			printf ("elemento %d\n", i+1);
			printf("%f\n", vet[i][j]);
		}
		printf ("\n");
	}

	for(i = 0; i < n - 1; i++)
    {
        if(vet[i][i] == 0)
        {
            for(k = i; k < n; k++)
            {
                if(vet[k][i] != 0)
                {
                    for(j = 0; j < n; j++)
                    {
                        temp = vet[i][j];
                        vet[i][j] = vet[k][j];
                        vet[k][j] = temp;
                    }
                    k = n;
                }
            }
            count++;
        }

        if(vet[i][i] != 0)
        {
            for(k = i + 1; k < n; k++)
            {
                neg = -1.0 * vet[k][i] /  vet[i][i];
                for(j = i; j < n; j++)
                {
                    vet[k][j] = vet[k][j] + (neg * vet[i][j]);
                }
            }
        }
    }

    temp = 1.0;
    rest = count%2;
    for(i = 0; i < n; i++)
        temp *= vet[i][i];

    printf("\nDeterminante:\n");
    if(rest == 0)
        printf("%f \n", temp);
    else
        printf("%f \n", -1.0 * temp);

    if (temp == 0)
    {
    	printf("Esse sistema é linearmente dependente\n\n\n");
    }
    else
    {
    	printf("Esse sistema é linearmente independente\n\n\n");
    }
    // LETRA B
    for (i = 0; i < n; i++)
	{
        soma = 0;
        somaq = 0;
		for (j = 0; j < d; j++)
		{	
			soma = pow(mat[i][j],2) + soma;
		}
		for (k = 0; k< d; k++)
		{
			somaq = mat[i][k] / (sqrt(soma));
			printf ("vetor unitario %d: %f\n", i+1, somaq);
		}
		
	}


	return 0;

}
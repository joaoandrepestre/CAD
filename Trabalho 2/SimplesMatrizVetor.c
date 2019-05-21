#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>


int **geraMatriz(int lin, int col);
int *geraVetor(int dim);
int *produtoMatrizVetorSequencial(int **mat, int *vet, int matLin, int matCol, int vetSize);
int *produtoMatrizVetorParalelo(int **mat, int *vet, int matLin, int matCol, int vetSize);


int main()
{

    time_t t;
    srand(time(&t));

    clock_t begin, end;
    int clks;

    int fim = 4;
    
    int **mat = geraMatriz(fim, fim);
    int *vet = geraVetor(fim);
    int *tmp;

    printf("AQUI ESTÁ A MATRIZ: \n\n");
    for (int i = 0; i < fim; i++) {
        for(int j = 0; j < fim; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    printf("AQUI ESTÁ O VETOR: \n\n");
    for (int i = 0; i < fim; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n\n");

    
    double wtime = omp_get_wtime();

    //tmp = produtoMatrizVetorSequencial(mat, vet, fim, fim, fim);
    tmp = produtoMatrizVetorParalelo(mat, vet, fim, fim, fim);

    wtime = omp_get_wtime() - wtime;


    printf("AQUI ESTÁ O RESULTADO: \n\n");
    for (int i = 0; i < fim; i++) {
        printf("%d ", tmp[i]);
    }
    printf("\n\n");

    printf("DEMOROU %f SEGUNDOS\n", wtime);



    return 0;
}

int **geraMatriz(int lin, int col)
{
    int **mat = (int **)malloc(lin * sizeof(int *));
    int i;
    for (i = 0; i < lin; i++)
    {
        mat[i] = (int *)malloc(col * sizeof(int));
        int j;
        for (j = 0; j < col; j++)
        {
            int r = (int) rand() % 10;
            mat[i][j] = r;
        }
    }
    return mat;
}

int *geraVetor(int dim)
{
    int *vet = (int *)malloc(dim * sizeof(int));
    int i;
    for (i = 0; i < dim; i++)
    {
        int r = (int) rand() % 10;
        vet[i] = r;
    }
    return vet;
}

int *produtoMatrizVetorParalelo(int **mat, int *vet, int matLin, int matCol, int vetSize)
{
    if (matCol != vetSize)
    {
        printf("A matriz e o vetor devem ter as mesmas dimensoes");
        return NULL;
    }

    int *ret = (int *)malloc(matLin * sizeof(int));
    
    #pragma omp parallel
    {
        int *ret_thread = (int *)malloc(matLin * sizeof(int));
        int i, j;   

        for (i = 0; i < matLin; i++)
        {
            #pragma omp for
            for (j = 0; j < matCol; j++)
            {
                ret_thread[i] += mat[i][j] * vet[j];
            }
        
        }
    
        #pragma omp critical
        {
            for (i=0; i < matLin; i++) {
                ret[i] += ret_thread[i];
            }
        }
    }
    return ret;
}

int *produtoMatrizVetorSequencial(int **mat, int *vet, int matLin, int matCol, int vetSize)
{
    if (matCol != vetSize)
    {
        printf("A matriz e o vetor devem ter as mesmas dimensoes");
        return NULL;
    }

    int *ret_thread = (int *)malloc(matLin * sizeof(int));
    int *ret = (int *)malloc(matLin * sizeof(int));
    
    int i, j;
    
    for (i = 0; i < matLin; i++)
    {
        for (j = 0; j < matCol; j++)
        {
            ret_thread[i] += mat[i][j] * vet[j];
        }
    
    }

    for (i=0; i < matLin; i++) {
        ret[i] += ret_thread[i];
    }
    return ret;
}
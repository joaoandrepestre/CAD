#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

double **geraMatriz(int lin, int col);
double *geraVetor(int dim);
double *produtoMatrizVetorParalelo(double **mat, double *vet, int matLin, int matCol, int vetSize);
double *produtoMatrizVetorSequencial(double **mat, double *vet, int matLin, int matCol, int vetSize);

int main()
{
    FILE *fp;
    fp = fopen("output-graph.csv", "w");
    fprintf(fp, "Tipo de Execução,Tamanho,Tempo (s)\n");

    double wtime_p, wtime_s;
    omp_set_num_threads(4);

    int fim = 10000;
    double **mat = geraMatriz(fim, fim);
    double *vet = geraVetor(fim);
    double *tmp;

    int n = 100;
    while (n <= fim)
    {

        wtime_p = omp_get_wtime();

        tmp = produtoMatrizVetorParalelo(mat, vet, n, n, n);

        wtime_p = omp_get_wtime() - wtime_p;
        fprintf(fp, "PARALELO,%d,%f\n", n, wtime_p);
        n += 100;
    }

    n = 100;
    while (n <= fim)
    {
        wtime_s = omp_get_wtime();

        tmp = produtoMatrizVetorSequencial(mat, vet, n, n, n);

        wtime_s = omp_get_wtime() - wtime_s;
        
        fprintf(fp, "SEQUENCIAL,%d,%f\n", n, wtime_s);
        n += 100;
    }
    return 0;
}

double **geraMatriz(int lin, int col)
{
    double **mat = (double **)malloc(lin * sizeof(double *));
    int i;
    for (i = 0; i < lin; i++)
    {
        mat[i] = (double *)malloc(col * sizeof(double));
        int j;
        for (j = 0; j < col; j++)
        {
            double r = 10 * ((double)rand() / (double)RAND_MAX);
            mat[i][j] = r;
        }
    }
    return mat;
}

double *geraVetor(int dim)
{
    double *vet = (double *)malloc(dim * sizeof(double));
    int i;
    for (i = 0; i < dim; i++)
    {
        double r = 10 * ((double)rand() / (double)RAND_MAX);
        vet[i] = r;
    }
    return vet;
}

double *produtoMatrizVetorParalelo(double **mat, double *vet, int matLin, int matCol, int vetSize)
{
    if (matCol != vetSize)
    {
        printf("A matriz e o vetor devem ter as mesmas dimensoes");
        return NULL;
    }

    double *ret = (double *)malloc(matLin * sizeof(double));
   

    #pragma omp parallel 
    {
        double *ret_thread = (double *)malloc(matLin * sizeof(double));
        int i, j;

        #pragma omp for
        for (i = 0; i < matLin; i++)
        {

            
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

double *produtoMatrizVetorSequencial(double **mat, double *vet, int matLin, int matCol, int vetSize)
{
    if (matCol != vetSize)
    {
        printf("A matriz e o vetor devem ter as mesmas dimensoes");
        return NULL;
    }

    double *ret = (double *)malloc(matLin * sizeof(double));
    int i;
    for (i = 0; i < matLin; i++)
    {
        int j;
        for (j = 0; j < matCol; j++)
        {
            ret[i] += mat[i][j] * vet[j];
        }
    }
    return ret;
}

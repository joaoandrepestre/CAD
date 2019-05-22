#include <stdlib.h>
#include <stdio.h>
#include <time.h>

double **geraMatriz(int lin, int col);
double *geraVetor(int dim);
double *produtoMatrizVetorParalelo(double **mat, double *vet, int matLin, int matCol, int vetSize);
double *produtoMatrizVetorSequencial(double **mat, double *vet, int matLin, int matCol, int vetSize);

int main()
{
    FILE *fp;
    fp = fopen("output-graph.csv", "w");
    fprintf(fp, "Tamanho,Tempo (s)\n");

    clock_t begin, end;
    int clks;

    int fim = 10000;
    double **mat = geraMatriz(fim, fim);
    double *vet = geraVetor(fim);
    double *tmp;

    int n = 100;
    while (n <= fim)
    {
        begin = clock();
        tmp = produtoMatrizVetorParalelo(mat, vet, n, n, n);
        end = clock();
        clks = (int)(end - begin);
        fprintf(fp, "%d\t%d\n", n, clks);
        n += 100;
    }

    n = 100;
    while (n <= fim)
    {
        begin = clock();
        tmp = produtoMatrizVetorSequencial(mat, vet, n, n, n);
        end = clock();
        clks = (int)(end - begin);
        fprintf(fp, "%d\t%d\n", n, clks);
        n += 100;
    }
    return 0;
}

double **geraMatriz(int lin, int col)
{
    time_t t;
    srand(time(&t));
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
    time_t t;
    srand(time(&t));
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

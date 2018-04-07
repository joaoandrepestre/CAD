#include <stdlib.h>
#include <stdio.h>
#include <time.h>

float** geraMatriz(int lin, int col);
float* geraVetor(int dim);
float* produtoMatrizVetor(float** mat, float* vet, int matLin, int matCol, int vetSize);

int main()
{
    FILE* fp;
    fp = fopen("output.txt","w");
    fprintf(fp,"Tamanho\tClocks\n");   

    int fim = 10000;
    float** mat = geraMatriz(fim,fim);
    float* vet = geraVetor(fim);
    
    int n = 100;
    while(n<=fim){
        clock_t begin = clock();
        float* tmp = produtoMatrizVetor(mat,vet,n,n,n);
        clock_t end = clock();
        int clks = (int)(end-begin);
        fprintf(fp,"%d\t%d\n",n,clks); 
        n+=1000;
    }
    return 0;
}

float** geraMatriz(int lin, int col)
{
    time_t t;
    srand(time(&t));
    float** mat = (float**) malloc(lin*sizeof(float*));
    int i;
    for(i=0;i<lin;i++){
        mat[i] = (float*) malloc(col*sizeof(float));
        int j;
        for(j=0;j<col;j++){
            float r = 10*((float)rand()/(float)RAND_MAX);
            mat[i][j] = r;
        }
    }
    return mat;
}

float* geraVetor(int dim)
{
    time_t t;
    srand(time(&t));
    float* vet = (float*) malloc(dim*sizeof(float));
    int i;
    for(i=0;i<dim;i++){
        float r = 10*((float)rand()/(float)RAND_MAX);
        vet[i] = r;
    }
    return vet;
}

float* produtoMatrizVetor(float** mat, float* vet, int matLin, int matCol, int vetSize)
{
    if(matCol != vetSize){
        printf("A matriz e o vetor devem ter as mesmas dimensoes");
        return NULL;
    }

    float* ret = (float*) malloc(matLin*sizeof(float));
    int i;
    for(i=0;i<matLin;i++){
        float s = 0.0;
        int j;
        for(j=0;j<matCol;j++){
            s += mat[i][j]*vet[j];
        }
        ret[i] = s;
    }
    return ret;
}
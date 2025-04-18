#include <stdio.h>
#include <math.h>

typedef struct DATA
{
    float distancia;
    int cliente;
}DATA;

//faz a leitura dos dados e cria as respectivas matrizes
void *readDataFromFile(const char *filename, int *rows, int *cols) 
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
    printf("N~ao foi poss ́ıvel abrir o arquivo %s\n", filename);
    return NULL;
    }
    void *data = NULL;
    // Ler o cabe ̧calho: n ́umero de linhas e colunas
    fread(rows, sizeof(int), 1, file);
    fread(cols, sizeof(int), 1, file);
    printf("Matriz %s - Linhas: %d, Colunas: %d\n", filename, *rows, *cols);
    // Verifica se  ́e uma matriz com uma coluna (nesse caso, trata como int) ou uma matriz com m ́ultiplas colunas (trata como float)
    if (*cols == 1) {
    // Tratar como matriz de uma coluna de inteiros
    data = (int **)malloc(*rows * sizeof(int *));
    for (int i = 0; i < *rows; i++) {
    ((int **)data)[i] = (int *)malloc(sizeof(int));
    fread(((int **)data)[i], sizeof(int), 1, file); // Ler cada elemento como int
    }
    } else {
    // Tratar como matriz de m ́ultiplas colunas de floats
    data = (float **)malloc(*rows * sizeof(float *));
    for (int i = 0; i < *rows; i++) {
    ((float **)data)[i] = (float *)malloc(*cols * sizeof(float));
    fread(((float **)data)[i], sizeof(float), *cols, file); // Ler linha por linha como float
    }
    }
    fclose(file);
    return data;
}

//calcula a distancia entre os vetores
float distacia_euclidiana(float* v1, float* v2, int colunas)
{
    float sum_parametros = 0;
    for(int j = 0; j < colunas;j++)
    {
        sum_parametros += powf(v1[j] - v2[j],2);
    }
    return sqrtf(sum_parametros);
}

//verifica a semelhanca entre os k primeiros elementos
void verificar_semelhanca(int **Y, int **Y2, DATA* v_D,int k, int lin_A,double *acertos)
{   
    int n_acertos = 0;
    for(int i = 0; i < k;i++)
    {
        if(Y[v_D[i].cliente][0] == Y2[lin_A][0]) 
        {
            n_acertos++;
            //puts("Acerto\n");
        }
        else{n_acertos--;}
    }
    if(n_acertos >= 0){*acertos += 1;}
}

//imprime o vetor D para debug
void imprimir_v_D(DATA v_D[], int n)
{
    for (int i = 0; i < n; i++) 
    {
        printf("Cliente: %d, Distância: %.2f\n", v_D[i].cliente, v_D[i].distancia);
    }   
}

//calcula a media de tempo da soma fornecida
double media_tempo(double sum_tempos, int n_clientes_avaliar)
{
    double r = sum_tempos/(double)n_clientes_avaliar;
    return r;
}

//ALGORITIMOS DE ORDENACAO
void selection_sort(int n, DATA v[]) {
    int i, j, min;
    DATA x;

    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (v[j].distancia < v[min].distancia) {
                min = j;
            }
        }
        x = v[i];
        v[i] = v[min];
        v[min] = x;
    }
}

void insertion_sort(int n, DATA v[]) 
{
    int i, j;
    DATA x;
    for (j = 1; j < n; j++) 
    {
        x = v[j];
        for (i = j-1; i >= 0 && v[i].distancia > x.distancia; i--)
            {
                v[i+1] = v[i];
            }
        v[i+1] = x;
    }
}

void shell_sort(int n, DATA arr[]) 
{
    /* Inicia com um gap (h) e vai reduzindo */
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        /* Ordene por inserção com gaps para esse tamanho de gap*/
        for (int i = gap; i < n; i += 1)
        {
            DATA temp = arr[i];
            /*Desloca elementos por gaps até encontrar o local correto para a[i]*/
            int j;
            for (j = i; j >= gap && arr[j - gap].distancia > temp.distancia; j -= gap)
            {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp; // Coloque temp na posição correta
        }
    }
}

void intercala(int p, int q, int r, DATA v[])
{
    int i, j , k;
    DATA* w = (DATA*) malloc((r-p) *sizeof(DATA));
    i = p; j = q; k = 0;
    while(i < q && j < r)
    {
        if( v[i].distancia <= v[j].distancia)
        {
            w[k++] = v[i++];
        }
        else
        {
            w[k++] = v[j++];
        }
    }
    while(i < q) {w[k++] = v[i++];}
    while(j < r) {w[k++] = v[j++];}
    for(i=p; i < r; i++) {v[i] = w[i-p];}
    free(w);
}

void mergesort(int p, int r, DATA v[])
{
    if(p < r-1)
    {
        int q = (p + r)/2;
        mergesort(p, q, v);
        mergesort(q, r, v);
        intercala(p, q, r, v);
    }
}

int separa(int p, int r, DATA v[])
{
    int j, k;
    DATA t, c;
    c = v[r]; //set ultimo elemento como pivo
    j = p;
    for(k = p; k < r; k++)
    {
        if(v[k].distancia <= c.distancia)
        {
            t = v[j];
            v[j] = v[k];
            v[k] = t;
            j++;
        }
    }
    v[r] = v[j];
    v[j] = c;
    return j;
}

void quick_sort(int p, int r, DATA v[])
{
    int j;
    if(p < r)
    {
        j = separa(p, r, v);
        quick_sort(p, j-1, v);
        quick_sort(j+1, r, v);
    }
}




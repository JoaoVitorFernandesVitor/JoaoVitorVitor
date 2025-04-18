#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.c"


int main() 
{
    int o = 4;                                                  //variavel que aponta o metodo de ornadecao
    int k[] = {1,3,5,7,9,11};                               // vetor com os valores de k
    double porcen_acerto = 0, acertos = 0, tempo_i, tempo_f,sum_tempos = 0;
    char* ordenacao;
    
    // Nomes dos arquivos binarios referencia
    char *filename_cliente_dados = "clientes_dados_referencia.dat";
    char *filename_cliente_credito = "clientes_credito_referencia.dat";
    // Vari ́aveis para armazenar as dimensoes
    int rows_X, cols_X, rows_Y, cols_Y;
    // Ler a matriz de dados do arquivo (float)
    float **X = (float **)readDataFromFile(filename_cliente_dados, &rows_X, &cols_X);
    // Ler a "matriz de uma coluna" de r ́otulos do arquivo (int)
    int **Y = (int **)readDataFromFile(filename_cliente_credito, &rows_Y, &cols_Y);

    // Nomes dos arquivos binarios avaliar
    char *filename_cliente_dados_avaliar = "clientes_dados_avaliar.dat";
    char *filename_cliente_credito_avaliar = "clientes_credito_avaliar.dat";
    // Vari ́aveis para armazenar as dimens~oes
    int rows_X2, cols_X2, rows_Y2, cols_Y2;
    // Ler a matriz de dados do arquivo (float)
    float **X2 = (float **)readDataFromFile(filename_cliente_dados_avaliar, &rows_X2, &cols_X2);
    // Ler a "matriz de uma coluna" de r ́otulos do arquivo (int)
    int **Y2 = (int **)readDataFromFile(filename_cliente_credito_avaliar, &rows_Y2, &cols_Y2);
    puts("");

    for (int c = 0; c < 6; c++) 
    {//percorre o vetor k calculando baseado no valor de k[c]
        sum_tempos = 0;
        acertos = 0;
        double porcen_acerto = 0;
        
        for(int lin_A = 0; lin_A < rows_X2; lin_A++)
        {//percorrer a matriz de avaliação e calcular suas distancias em relação aos clientes referencia
            DATA v_D[rows_X]; //vetor que armazena as distancias entre o cliente de avaliacao e os clietes de referencias
            
            
            for (int lin_X = 0; lin_X < rows_X; lin_X++)
            {//percorro as linhas da matriz referencia
                float distance = distacia_euclidiana(X2[lin_A],X[lin_X],cols_X2);   //calculo a distancia entre o vetor na lin_A
                v_D[lin_X].cliente = lin_X;
                v_D[lin_X].distancia = distance;    
            }
            int D = rows_X;
            if(o == 1)
            {//Case 1: Selection sort
                tempo_i = clock();
                selection_sort(D,v_D);
                ordenacao = "Selection Sort";
                tempo_f = clock();
                sum_tempos += (tempo_f - tempo_i);
            }
            else if(o == 2)
            {//Case 2: Insertion Sort
                tempo_i = (clock());
                insertion_sort(D, v_D);
                ordenacao = "Insertion Sort";
                tempo_f = clock();
                sum_tempos += (tempo_f - tempo_i);
            }
            else if(o == 3)
            {//Case 3: Shell sort
                tempo_i = clock();
                shell_sort(D, v_D);
                ordenacao = "Shell Sort";
                tempo_f = clock();
                sum_tempos += (tempo_f - tempo_i);
            }
            else if(o == 4)
            {//Case 4: Merge sort
                tempo_i = clock();
                mergesort(0, D, v_D);
                ordenacao = "Merge Sort";
                tempo_f = clock();
                sum_tempos += (tempo_f - tempo_i);
            }
            else if(o == 5)
            {//Case 5: Quick sort
                tempo_i = clock();
                quick_sort(0,D-1, v_D);
                ordenacao = "Quick Sort";
                tempo_f = clock();
                sum_tempos += (tempo_f - tempo_i);
            }
                       
            verificar_semelhanca(Y, Y2, v_D, k[c],  lin_A, &acertos);                  //baseado na cosnt K avaliamos o cliente
        }
        porcen_acerto = (acertos/rows_Y2)*100;
        
        if(c == 0 ) {puts(ordenacao);puts("Acuracia\tTempo medio");}
        printf(" %.1f%%", porcen_acerto);
        printf("\t\t %f s\n", media_tempo(sum_tempos,rows_X2)/CLOCKS_PER_SEC);
        
    }


    // Liberar memoria alocada para Y2 e X2
    for (int i = 0; i < rows_X2; i++) free(X2[i]);
    free(X2);
    for (int i = 0; i < rows_Y2; i++) free(Y2[i]);
    free(Y2);

    // Liberar memoria alocada para Y e X
    for (int i = 0; i < rows_X; i++) free(X[i]);
    free(X);
    for (int i = 0; i < rows_Y; i++) free(Y[i]);
    free(Y);
    
    return 0;
}




#include <bits/stdc++.h>

using namespace std;

// Print menu on terminal
void intro()
{
    printf("\n");
    printf("#####################################\n");
    printf("#                                   #\n");
    printf("#             MERGE SORT            #\n");
    printf("#                                   #\n");
    printf("#####################################\n");
    printf("#                                   #\n");
    printf("#     Aluno: Thiago Veras Machado   #\n");
    printf("#         M: 16/0146682             #\n");
    printf("# Aluno: Gabriel Cunha Bessa Vieira #\n");
    printf("#         M: 16/0120811             #\n");
    printf("#                                   #\n");
    printf("#####################################\n");
    printf("\n");
    printf("How many files you want to read ? : ");
}

// Function which inter calls both halves called by merge sort
void intercalar(int *v, int *aux, int ini1, int ini2, int fim2)
{

    int in1 = ini1, in2 = ini2, fim1 = in2 - 1, au = 0;

    // Colocando os elementos ordenados no vetor aux
    while (in1 <= fim1 and in2 <= fim2)
    {

        if (v[in1] < v[in2])
            aux[au++] = v[in1++];

        else
            aux[au++] = v[in2++];
    }

    // Colocando os resto dos elementos caso nao tenha terminado de pegar todos os elementos do vetor v
    while (in1 <= fim1)
        aux[au++] = v[in1++];

    while (in2 <= fim2)
        aux[au++] = v[in2++];

    for (int i = 0; i < au; i++)
        v[i + ini1] = aux[i];
}

// Funcao de ordenacao do vetor
void mergeSort(int *v, int *aux, int esq, int dir)
{

    // Se a posicao onde o vetor comeca eh maior ou igual onde ele termina, eh porque nao precisa ordenar
    if (esq >= dir)
        return;

    // Chama recursivamente o algoritmo ordenando do comeco ate a metade
    mergeSort(v, aux, esq, (esq + dir) / 2);

    // Chama recursivamente da metade + 1 ate o final
    mergeSort(v, aux, (esq + dir) / 2 + 1, dir);

    // Intercala tudo
    intercalar(v, aux, esq, (esq + dir) / 2 + 1, dir);
}

// Imprime os valores do vetor
void print_array(int *v, int n)
{

    // Fazendo loop e andando pelos elementos do vetor
    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);

    // Quebra de linha
    puts("");
}

int main()
{
    // Variavel para pegar o tamanho do vetor
    int n;

    // Iteracao com o usuario
    printf("Digite o tamanho do vetor :");

    // Lendo o tamanho do vetor
    cin >> n;

    // Criando o vetor de tamanho n e um auxiliar para poder ordenar
    int array[n], aux[n];

    // Lendo n numeros e salvando no vetor
    for (int i = 0; i < n; i++)
        cin >> array[i];

    // Chamando o algoritmo de ordenacao merge sort
    mergeSort(array, aux, 0, n - 1);

    // Imprimindo o vetor
    print_array(array, n);

    return 0;
}
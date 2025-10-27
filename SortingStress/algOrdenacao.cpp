// SortingStress/algOrdenacao.cpp
#include "algOrdenacao.hpp"
#include <algorithm>
#include <random>
#include <vector>

using namespace std;

void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int chave = arr[i];
        int j = (int)i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}

void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
        }
    }
}

void shellSort(vector<int>& arr) {
    for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < arr.size(); i++) {
            int aux = arr[i];
            size_t j;
            for (j = i; j >= gap && arr[j - gap] > aux; j -= gap) arr[j] = arr[j - gap];
            arr[j] = aux;
        }
    }
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivo = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivo) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        quickSort(arr, low, i);
        quickSort(arr, i + 2, high);
    }
}

void selectionSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        size_t minIdx = i;
        for (size_t j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

void heapify(vector<int>& arr, int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    if (esq < n && arr[esq] > arr[maior]) maior = esq;
    if (dir < n && arr[dir] > arr[maior]) maior = dir;
    if (maior != i) {
        swap(arr[i], arr[maior]);
        heapify(arr, n, maior);
    }
}

void heapSort(vector<int>& arr) {
    int n = (int)arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void merge(vector<int>& arr, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    vector<int> E(n1), D(n2);
    for (int i = 0; i < n1; i++) E[i] = arr[esq + i];
    for (int j = 0; j < n2; j++) D[j] = arr[meio + 1 + j];
    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (E[i] <= D[j]) { arr[k++] = E[i++]; }
        else { arr[k++] = D[j++]; }
    }
    while (i < n1) arr[k++] = E[i++];
    while (j < n2) arr[k++] = D[j++];
}

void mergeSort(vector<int>& arr, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        merge(arr, esq, meio, dir);
    }
}

vector<int> gerarVetorAleatorio(int tamanho) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1000000);
    vector<int> vetor(tamanho);
    for (int i = 0; i < tamanho; i++) vetor[i] = dis(gen);
    return vetor;
}

vector<int> gerarVetorPiorCaso(int tamanho) {
    vector<int> vetor(tamanho);
    for (int i = 0; i < tamanho; i++) vetor[i] = tamanho - i;
    return vetor;
}

vector<int> gerarVetorMelhorCaso(int tamanho) {
    vector<int> vetor(tamanho);
    for (int i = 0; i < tamanho; i++) vetor[i] = i;
    return vetor;
}

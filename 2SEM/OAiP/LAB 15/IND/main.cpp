#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(){
    srand(time(NULL));
    int n;
    cout << "Введите число элементов массива: ";
    cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; i++)
        A[i] = rand() % 100;
    
    int* B = new int[n];
    int bCount = 0;
    for (int i = 0; i < n; i++)
        if(i % 2 != 0 && i + 1 < n && (A[i+1] % 2 != 0))
            B[bCount++] = A[i];
    
    if(bCount == 0) {
        cout << "Исходный массив: пустой";
        delete[] A;
        delete[] B;
        return 0;
    }
    
    cout << "Исходный массив: ";
    for (int i = 0; i < bCount; i++){
        cout << B[i] << (i < bCount - 1 ? ", " : "\n");
    }
    
    int* B_bubble = new int[bCount];
    int* B_quick = new int[bCount];
    for (int i = 0; i < bCount; i++){
        B_bubble[i] = B[i];
        B_quick[i] = B[i];
    }
    
    auto start_bubble = chrono::high_resolution_clock::now();
    bubbleSort(B_bubble, bCount);
    auto end_bubble = chrono::high_resolution_clock::now();
    auto timeBubble = chrono::duration_cast<chrono::microseconds>(end_bubble - start_bubble);

    auto start_quick = chrono::high_resolution_clock::now();
    quickSort(B_quick, 0, bCount - 1);
    auto end_quick = chrono::high_resolution_clock::now();
    auto timeQuick = chrono::duration_cast<chrono::microseconds>(end_quick - start_quick);
    
    cout << "Отсортированный массив: ";
    for (int i = 0; i < bCount; i++){
        cout << B_bubble[i] << (i < bCount - 1 ? ", " : "\n");
    }
    
    cout << "Время выполнения сортировки пузырьком: " << timeBubble.count() << " микросекунд\n";
    cout << "Время выполнения быстрой сортировки: " << timeQuick.count() << " микросекунд\n";
    
    delete[] A;
    delete[] B;
    delete[] B_bubble;
    delete[] B_quick;
    return 0;
}

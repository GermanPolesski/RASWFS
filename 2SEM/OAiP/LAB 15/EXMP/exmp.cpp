#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cstring>
using namespace std;

// Вспомогательная функция для обмена элементов
void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

// Сортировка выбором (Selection Sort)
int* sort1(int m[], int lm) {
    for (int i = 0; i < lm - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < lm; j++) {
            if (m[j] < m[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(m[i], m[min_index]);
        }
    }
    return m;
}

// Вспомогательная функция для быстрой сортировки
void quickSort(int arr[], int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    
    // Упорядочиваем left, mid, right для выбора медианы
    if (arr[left] > arr[mid]) swap(arr[left], arr[mid]);
    if (arr[left] > arr[right]) swap(arr[left], arr[right]);
    if (arr[mid] > arr[right]) swap(arr[mid], arr[right]);
    
    int pivot = arr[mid];
    int i = left, j = right;
    
    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

// Быстрая сортировка (Quick Sort)
int* sort2(int m[], int lm) {
    quickSort(m, 0, lm - 1);
    return m;
}

// Генерация случайных чисел
int getRandKey(int reg = 0) {
    if (reg > 0)
        srand((unsigned)time(NULL));
    int rmin = 0, rmax = 100000;
    return (int)(((double)rand() / (double)RAND_MAX) * (rmax - rmin) + rmin);
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    const int N = 50000;
    int k[N], f[N];
    clock_t t1, t2;
    
    getRandKey(1);
    for (int i = 0; i < N; i++)
        f[i] = getRandKey(0);
    
    for (int n = 10000; n <= N; n += 10000) {
        cout << "n = " << n << endl;
        
        cout << "Сортировка 1 ";
        memcpy(k, f, n * sizeof(int));
        t1 = clock();
        sort1(k, n);
        t2 = clock();
        cout << "Прошло " << t2 - t1 << " тактов времени" << endl;
        
        cout << "Сортировка 2 ";
        memcpy(k, f, n * sizeof(int));
        t1 = clock();
        sort2(k, n);
        t2 = clock();
        cout << "Прошло " << t2 - t1 << " тактов времени" << endl << endl;
    }
    return 0;
}
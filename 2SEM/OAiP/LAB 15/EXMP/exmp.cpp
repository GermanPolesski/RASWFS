#include <iostream>
using namespace std;

int getHoarBorder(int A[], int sm, int em) {
    int i = sm - 1, j = em + 1;
    int brd = A[sm], buf;
    while (true) {
        do { j--; } while (A[j] > brd);
        do { i++; } while (A[i] < brd);
        if (i < j) {
            buf = A[j];
            A[j] = A[i];
            A[i] = buf;
        } else {
            return j;
        }
    }
}

void sortHoar(int A[], int sm, int em) {
    if (sm < em) {
        int hb = getHoarBorder(A, sm, em);
        sortHoar(A, sm, hb);
        sortHoar(A, hb + 1, em);
    }
}

int main() {
    setlocale(LC_ALL, "Rus");
    int size, i, A[100];
    cout << "Количество элементов = ";
    cin >> size;
    for (i = 0; i < size; i++) {
        cout << i + 1 << " элемент = ";
        cin >> A[i];
    }
    sortHoar(A, 0, size - 1);
    cout << "Результирующий массив: ";
    for (i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
    return 0;
}
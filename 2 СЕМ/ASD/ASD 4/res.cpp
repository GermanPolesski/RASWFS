#include <iostream>

using namespace std;

int main(){
    bool F;
    short buff;

    short N;
    short costs[1000];
    short bill[1000];

    cout << "Enter number of products: ";
    cin >> N;

    cout << "Enter list of costs: ";
    for(int i = 0; i < N; i++){
        cin >> costs[i];
    }

    for(int j = 1; j < N - 1; j++){
        F = 0;
        for(int i = 0; i < N-1-j; i++){
            if (costs[i] > costs[i+1]){
                buff = costs[i];
                costs[i] = costs[i+1];
                costs[i+1] = buff;

                F = 1;
            }
        }
        if(F == 0){
            break;
        }
    }

    cout << "Sorted list of costs: ";
    for(int i = 0; i < N; i++){
        cout << costs[i] << " ";
    }

    short middle = N / 2;
    short billIndex = 0;

    for (short j = 0; j < middle; j++) {
        bill[billIndex++] = costs[middle + j];
        bill[billIndex++] = costs[j];
    }
    if (N % 2 != 0) {
        bill[billIndex] = costs[N - 1];
    }

    cout << "Bill: ";
    for (int i = 0; i < N; i++) {
        cout << bill[i] << " ";
    }
    cout << endl;
}

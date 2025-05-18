#include <iostream>
#include <cstdarg>
#include <climits>

using namespace std;

int ivarparm(int count, ...) {
    va_list args;
    va_start(args, count);

    int total = 1;

    for (int i = 0; i < count; i++) {
        total *= va_arg(args, int);
    }

    va_end(args);
    
    return total;
}

int svarparm(short count, ...) {
    if (count <= 0) return INT_MIN;

    va_list args;
    va_start(args, count);

    int max = INT_MIN;

    for (int i = 0; i < count; ++i) {
        int current = va_arg(args, int);
        if (current > max) {
            max = current;
        }
    }

    va_end(args);
    return max;
}

float fvarparm(int count, ...) {
    if (count <= 0)
        return 0.0f;  // Если аргументов нет, возвращаем 0

    va_list args;
    va_start(args, count);
    double total = 0.0;

    // Извлекаем каждый аргумент, но пропускаем прибавление передпоследнего
    for (int i = 0; i < count; i++) {
        double value = va_arg(args, double);  // Обязательно извлекаем аргумент
        if (i != count - 2) {
            total += value;
        }
    }
    
    va_end(args);
    return static_cast<float>(total) + count;
}

float dvarparm(int count, ...) {
    if (count <= 0)
        return 0.0f;  // Если аргументов нет, возвращаем 0

    va_list args;
    va_start(args, count);
    double total = 0.0;

    // Извлекаем каждый аргумент, но пропускаем прибавление передпоследнего
    for (int i = 0; i < count; i++) {
        double value = va_arg(args, double);  // Обязательно извлекаем аргумент
        if (i != count - 2) {
            total += value;
        }
    }
    
    va_end(args);
    return static_cast<double>(total) + count;
}

int main() {
    cout << ivarparm(3, 2, 3, 4) << endl;  // Expected output: 24
    cout << svarparm(3, 2, 3, 4) << endl;  // Expected output: 4
    cout << fvarparm(3, 2.0f, 3.8f, 4.5f) << endl;  // Expected output: 9.5
    cout << dvarparm(3, 2.0, 3.8, 4.5) << endl;  // Expected output: 9.5

    return 0;
}
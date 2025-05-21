#include <iostream>
using namespace std;

int add(int a, int b) {
    if (b == 0) return a;
    return add(a + 1, b - 1);
}

int subtract(int a, int b) {
    if (b == 0) return a;
    if (a == 0) return 0;
    return subtract(a - 1, b - 1);
}

int multiply(int a, int b) {
    if (b == 0) return 0;
    return add(a, multiply(a, b - 1));
}

int power(int a, int b) {
    if (b == 0) return 1;
    return multiply(a, power(a, b - 1));
}

int main() {
    cout << "5 + 3 = " << add(5, 3) << endl;
    cout << "0 + 4 = " << add(0, 4) << endl;
    
    cout << "5 - 3 = " << subtract(5, 3) << endl;
    cout << "3 - 5 = " << subtract(3, 5) << endl;
    
    cout << "4 × 3 = " << multiply(4, 3) << endl;
    cout << "0 × 5 = " << multiply(0, 5) << endl;
    
    cout << "2³ = " << power(2, 3) << endl;
    cout << "5⁰ = " << power(5, 0) << endl;
    cout << "0² = " << power(0, 2) << endl;

    return 0;
}
#include <iostream>

using namespace std;

float defaultparm(int a, int b, int c, int d = 2, int e = 3){
    return (a+b+c+d+e)/5;
}

int main(){
    cout << defaultparm(1, 2, 3) << endl;
    cout << defaultparm(1, 2, 3, 20, 6) << endl;

    return 0;
}
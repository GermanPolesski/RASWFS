#include <iostream>
#include "calls.h"

using namespace std;

int main(){
    int number = 10;
    int* pointer{&number};

    cout << "_cdecl returns: " << _cdecl(10, 3, 4) << endl;
    cout << "_stdcall returns: " << _stdcall(pointer, 3, 4) << endl;
    cout << "_cfst returns: " << _cfst(2, 3, 4, 5) << endl;

    return 0;
}
#include "calls.h"

int _cdecl(int first, int second, int third){
    return first + second + third;
}
int _stdcall(int *first, int second, int third){
    int num1 = *first;
    return num1 * second * third;
}
int _cfst(int first, int second, int third, int forth){
    return first + second + third + forth;
}
#include <iostream>

void by_value(int x) {
    x += 1;
}

void by_pointer(int* x) {
    *x += 1;
}

void by_reference(int& x) {
    x += 1;
}

int main() {
    int a = 42;

    by_value(a);     // no modifica a
    by_pointer(&a);  // sí modifica a
    by_reference(a); // sí modifica a

    std::cout << a << std::endl;
    return 0;
}

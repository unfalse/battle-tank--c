#include <stdio.h>

void func() {
    printf("Hello from func!\n");
}

int main() {
    void (*f)();
    f = func;
    f();
    return 0;
}


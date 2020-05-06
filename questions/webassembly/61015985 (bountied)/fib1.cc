#include <emscripten.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
int fib(int n) {
    if (n > 12) {
        EM_ASM(
            throw Error("out_of_range");    // JS error with EM_ASM
        );
    }

    int a {0}, b {1};
    for ( int i {0}; i < n; ++i ) {
        const auto t = a + b;
        a = b;
        b = t;
    }
    return b;
}

}

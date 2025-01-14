#include <stdio.h>

int main(void) {
    int f[4];

    // 以下に適切な値を設定する
    f[0] = 0;
    f[1] = 1;
    f[2] = 2;
    f[3] = 52;

    // "Hello,World\n" と出力してほしい
    printf("%d\n", f[0]);

    // f[0] をいじる
    f[0] += 0.0;

    // "hello,World\n" と出力してほしい
    printf("%c\n", f[3]);

    return 0;
}
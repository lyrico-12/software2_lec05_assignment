#include <stdio.h>
#include "calc_magicnumber.h"

int main(void) {
    float f[12];

    // // 以下に適切な値を設定する
    // f[0] = 0.0;
    // f[1] = 1.0;
    // f[2] = 2.0;
    // f[3] = 3.0;

    FILE *fp = fopen("src/helloworld.txt", "r");
    if (fp == NULL) {
        perror("ファイルを開けませんでした\n");
        return 1;
    }

    calc_magicnumber(fp, f);

    // "Hello,World\n" と出力してほしい
    for (int i = 0; i < 12; i++) {
        printf("%c", (char)f[i]);
    }

    // f[0] をいじる
    lower_to_upper(f);
    
    // "hello,World\n" と出力してほしい
    for (int i = 0; i < 12; i++) {
        printf("%c", (char)f[i]);
    }

    fclose(fp);

    return 0;
}
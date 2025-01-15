#include <stdio.h>
#include <stdlib.h>
#include "calc_magicnumber.h"

// Hello worldは12文字(改行含む)
// 3文字ずつの4部屋に分割する
// アスキーコードのcharに直してから、floatにキャスト？
// char3文字ずつに分割する。
// 1バイト(8ビット)ずつ左シフトして文字を追加

void calc_magicnumber(FILE *fp, float f[12]) {
    int c;
    int i = 0;
    while ((c = getc(fp)) != EOF) {
        f[i] = (float)c;
        i++;
    }
}

// 32を引く
void lower_to_upper(float f[12]){
    f[0] += 32.0;
}
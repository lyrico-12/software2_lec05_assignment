#include <stdio.h>
#include <stdlib.h>

void permutation(int *pattern, int *used, size_t number);

int main(int argc, char **argv) {
    size_t number = 7;

    int *pattern = (int *)calloc(number, sizeof(int));
    int *used = (int *)calloc(number, sizeof(int));

    for (int i = 0; i < number; i++) {
        // まだパターンが確定してないことのフラグを立てておく
        pattern[i] = -1;
    }

    permutation(pattern, used, number);

    free(used);
    free(pattern);

    return 0;
}

void permutation(int *pattern, int *used, size_t number) {// 
    int start = -1;// pattern配列の中で値がまだ確定していない最初のインデックス
    // usedは０か１

    // patternをfor文で確認し，未確定の最初のインデックスをstartに入れる
    for (int i = 0; i < number; i++) {
        if (pattern[i] == -1) {
            start = i;
            break;
        }
    }

    // パターンが確定した場合（再帰の終端）
    if (start == -1) {
        printf("[ ");
        for (int i = 0; i < number; i++) {
            printf("%d ", pattern[i]);
        }
        printf("]\n");
        return;
    }

    // パターンが確定してない場合の処理をを以下にかく
    // used と pattern を更新しながらpermutationを呼び出す
    for (int i = 0; i < number; i++) {
        if (!used[i]) {// 使っていなかったら
            pattern[start] = i;// 
            used[i] = 1;
            permutation(pattern, used, number);
            pattern[start] = -1;
            used[i] = 0;
        }
    }

    // 終了
    return;
}
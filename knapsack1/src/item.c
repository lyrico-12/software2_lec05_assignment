#include <stdio.h>
#include <stdlib.h>

#include "item.h"

// 以下は構造体定義

// 構造体 Item
// 価値valueと重さweightが格納されている
struct item {
    double value;
    double weight;
};

// 構造体 Item
// 価値valueと重さweightが格納されている
// Itemポインタをmallocする必要あり
struct itemset {
    size_t number;
    Item *item;
};

// バイナリファイルからItemsetを設定 [未実装, 課題1] 
// バイナリは最初に品物数を表すsize_t、 そのあと価値が品物数分double で、その後重さが品物数分double で表されているとする。
Itemset *load_itemset(char *filename) {
    FILE *fp = fopen(filename, "r");

    // 品物数読み取り
    size_t number;
    if (fread(&number, sizeof(size_t), 1, fp) != 1) {
        printf(stderr, "Failed to read item-number from binary file.\n");
        fclose(fp);
        return NULL;
    }

    // 価値の読み取り
    double* values = (double *)malloc(sizeof(double) * number);
    if (values == NULL) {
        printf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }
    if (fread(values, sizeof(double), number, fp) != number) {
        printf(stderr, "Failed to read item-values from binary file.\n");
        fclose(fp);
        return NULL;
    }

    // 品物数の読み取り
    double* weights = (double *)malloc(sizeof(double) * number);
    if (weights == NULL) {
        printf(stderr, "Memory allocation failed\n");
        fclose(fp);
        return NULL;
    }
    if (fread(weights, sizeof(double), number, fp) != number) {
        printf(stderr, "Failed to read item-values from binary file.\n");
        fclose(fp);
        return NULL;
    }

    // 品物数に応じてitemsetのメモリ確保
    Item* item = (Item*)malloc(sizeof(item) * number);

    for (int i = 0; i < number; i++) {
        item[i].value = values[i];
        item[i].weight = weights[i];
    }

    Itemset* itemset;
    itemset->number = number;
    itemset->item = item;

    fclose(fp);
    return itemset;
}

// ↓標準入力の話
// 第一引数にファイル名を受け取るようにする。第二引数に重さの上限を入力する。第一引数が数字だった場合はその数字に基づいて従来のプログラムが動くようにする。
Itemset *init_itemset(size_t number, int seed, char* filename) {
    if (filename == NULL) {
        Itemset *items = (Itemset *)malloc(sizeof(Itemset));
        Item *item = (Item *)malloc(sizeof(Item) * number);

        srand(seed);
        for (int i = 0; i < number; i++) {// ここをファイル入力にする
            item[i].value = 0.25 * (rand() % 200);
            item[i].weight = 0.25 * (rand() % 200 + 1);
        }
        *items = (Itemset){.number = number, .item = item};
        return items;
    } else {
        Itemset *items = load_itemset(filename);
        return items;
    }
}

// itemset の free関数
void free_itemset(Itemset *list) {
    free(list->item);
    free(list);
}

// 表示関数
void print_itemset(const Itemset *list) {
    size_t n = list->number;
    const char *format = "v[%d] = %4.1f, w[%d] = %4.1f\n";
    for (int i = 0; i < n; i++) {
        Item *item = get_item(list, i);
        printf(format, i, get_itemvalue(item), i, get_itemweight(item));
    }
    printf("----\n");
}

Item *get_item(const Itemset *list, size_t index) {
    return &(list->item[index]);
}

size_t get_nitem(const Itemset *list) { return list->number; }

double get_itemweight(const Item *item) { return item->weight; }

double get_itemvalue(const Item *item) { return item->value; }

#include <stdio.h>
#include <stdlib.h>

typedef struct matrix {
    long x[4];
} Matrix;

typedef struct vector {
    long x[2];
} Vector;

Matrix* multi_mat(Matrix *a, Matrix *b);
Vector* multi_mat_and_vector(Matrix* a, Vector* v);
Matrix* mat_n_power(int n);

// ユーザ入力でnを受け付けるようにする。
int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    if (n > 90) {// nが90以上ならシステムエラーを起こすようにする。
        perror("n must be under 90.");
        return EXIT_FAILURE;
    }
    if (n == 0) {
        printf("Fibonatti result\n");
        printf("F(0) = 0\n");
        return 0;
    }

    Matrix* pmat = mat_n_power(n - 1);

    printf("matrix_n_power\n");
    printf("[%ld, %ld]\n", pmat->x[0], pmat->x[1]);
    printf("[%ld, %ld]\n", pmat->x[2], pmat->x[3]);

    Vector basic_vec;
    basic_vec.x[0] = 1;
    basic_vec.x[1] = 0;

    Vector* result = multi_mat_and_vector(pmat, &basic_vec);

    printf("Fibonatti result\n");
    printf("F(%d) = %ld\n", n, result->x[0]);

    return 0;
}

// 行列と行列の積
Matrix* multi_mat(Matrix *a, Matrix *b) {
    Matrix* pres = (Matrix*)malloc(sizeof(Matrix));
    pres->x[0] = a->x[0] * b->x[0] + a->x[1] * b->x[2];
    pres->x[1] = a->x[0] * b->x[1] + a->x[1] * b->x[3];
    pres->x[2] = a->x[2] * b->x[0] + a->x[3] * b->x[2];
    pres->x[3] = a->x[2] * b->x[1] + a->x[3] * b->x[3];

    return pres;
}

// 行列とベクトルの積
Vector* multi_mat_and_vector(Matrix* a, Vector* v) {
    Vector* pres = (Vector*)malloc(sizeof(Vector));
    pres->x[0] = a->x[0] * v->x[0] + a->x[1] * v->x[1];
    pres->x[1] = a->x[2] * v->x[0] + a->x[3] * v->x[1];

    return pres;
}

// 途中
Matrix* mat_n_power(int n) {
    Matrix* pres = (Matrix*)malloc(sizeof(Matrix));
    if (n == 0) {
        pres->x[0] = 1;
        pres->x[1] = 0;
        pres->x[2] = 0;
        pres->x[3] = 1;
        return pres;
    }
    if (n == 1) {
        pres->x[0] = 1;
        pres->x[1] = 1;
        pres->x[2] = 1;
        pres->x[3] = 0;
        return pres;
    }

    if (n % 2 == 0) {
        Matrix* half1 = mat_n_power(n / 2);
        Matrix* pres1 = multi_mat(half1, half1);
        free(half1);// 再起呼び出しでピープ領域に確保したメモリ領域を解放
        return pres1;
    } else {
        Matrix* half2 = mat_n_power((n - 1) / 2);
        Matrix basic_mat = {1, 1, 1, 0};
        Matrix* pres2 = multi_mat(multi_mat(half2, half2), &basic_mat);
        free(half2);// 再起呼び出しでピープ領域に確保したメモリ領域を解放
        return pres2;
    }

}
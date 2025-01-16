# software2_lec05_assignment
## 課題１ helloworld
helloworld.txtで一文字ずつ読み取ってfloat型に変換。表示時にまたcharに変換。バイナリデータを使ってないのが不安。

## 課題２ fibo
フィボナッチ数列の再帰の行列積を用いた計算。
行列積を再帰的に計算して表示した。nの数はユーザの標準入力から受け取るようにしている。

## 課題3 knapsack問題
(確認できるバイナリデータがないのでまだ実行して確認できてない)

### 新たに追加した関数(src/item.c)
- `Itemset *load_itemset(char *filename);`<br>
品物をバイナリファイルから読み取って構造体`Itemset`に格納する。
- `int contains_char(const char* str);`<br>
`argv[1]`がファイル名なのか数字なのかを判定する。

### 実際の動かし方
- `main`関数
標準入力`argv[1]`が数字だったら乱数で初期化する。ファイル名だったら、`load_itemset`を使ってitemsetを初期化する。



## 課題4 Traveling Salesman Problem
山登り法の2optで実装した。
- 2optは、クロスしている経路があったら、それを解く作業を順次やっていく。
### 全探索からの変更点
- `search`を`two_opt_search`として、2optを実装した。(以下の通り)
- その他の関数は変更していない。
```c
Answer two_opt_search(const City *city, int n, int *route, int *visited) {
    // routeを初期化
    for (int i = 0; i < n; i++) {
        route[i] = i;
    }

    // two-opt
    int improved = 1;
    while (improved) {
        improved = 0;
        for (int i = 1; i < n - 2; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                double old_dist = distance(get_city(city, route[i - 1]), get_city(city, route[i])) + 
                                    distance(get_city(city, route[j]), get_city(city, route[j + 1] % n));
                double new_dist = distance(get_city(city, route[i - 1]), get_city(city, route[j])) + 
                                    distance(get_city(city, route[i]), get_city(city, route[j + 1] % n));
                
                // swapする
                if (new_dist < old_dist) {
                    int temp;
                    while (i < j) {
                        temp = route[i];
                        route[i] = route[j];
                        route[j] = temp;
                        i++;
                        j--;
                    }
                    improved = 1;
                }
             }
        }
    }

    // 最適化後の総距離を計算
    double total_dist = 0.0;
    for (int i = 0; i < n - 1; i++) {
        total_dist += distance(get_city(city, route[i]), get_city(city, route[i + 1]));
    }
    total_dist += distance(get_city(city, route[n - 1]), get_city(city, route[0]));

    // 結果をAnswer構造体に格納
    Answer ans;
    ans.dist = total_dist;
    ans.route = (int *)malloc(sizeof(int) * n);
    memcpy(ans.route, route, sizeof(int) * n);

    return ans;
}
```

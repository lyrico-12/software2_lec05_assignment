#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "city.h"
#include "map.h"
#include "solve.h"

double solve(const City *city, int n, int *route, int *visited) {
    route[0] = 0;  // 循環した結果を避けるため、常に0番目からスタート
    visited[0] = 1;

    Answer ans = two_opt_search(city, n, route, visited);

    memcpy(route, ans.route, sizeof(int) * n);
    free(ans.route);
    return ans.dist;
}

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

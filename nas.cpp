/*
idea taka, że dla każdej wartości mamy zbiór pozycji na których ta wartość występuje
potem dla każdej wartości szukamy najdłuższego spójnego podciągu rosnącego o 1 w tym zbiorze
i bierzemy maksa z tego
ale to nie przechodziło pamięciowo xD
więc zamiast map<int, set<int>> jest map<int, vector<int>> a potem usuwamy duplikaty/sortujemy.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <set>

using namespace std;

#define FOR(n) for(int i = 0; i < n; i++)
#define FOR2(a, b) for (int i = a; i <= b; i++)
#define LOAD_ARRAY(n, t) for (int i = 0; i < n; i++) cin >> t[i]


int main() {

    int n, m;

    scanf("%d", &n);
    scanf("%d", &m);
   
    map<int, vector<int>> x;
    int temp;
    FOR(n) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &temp);
            x[temp].push_back(j);
            
        }
    }

    int max_ans = 1;
    int ans = 1;

    for (auto& it : x) {
        ans = 1;
        sort(it.second.begin(), it.second.end());
        it.second.erase(unique( it.second.begin(), it.second.end() ), it.second.end());

        for (auto it2 = it.second.begin(); it2 != it.second.end(); it2++) {
            auto next_ = next(it2, 1);
            if (next_ == it.second.end()) continue;

            if (*it2 == *next_ - 1) {
                ans++;
                max_ans = max(max_ans, ans);
            }
            else {
                max_ans = max(max_ans, ans);
                ans = 1;
            }

        }

    }

    printf("%d", max_ans);

}

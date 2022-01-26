/*
solv: posortować, potem przeiterować się po każdym elemencie i binsearchem wyszukać drugi, O(nlogn)
ew. tak jak niżej wsadzić wszystko do multiseta, koncepcja ta sama
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

#define FOR(n) for(int i = 0; i < n; i++)


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, d;
    cin >> n >> d;
    unordered_multiset<int> t;
    FOR(n) {
        int temp;
        cin >> temp;
        t.insert(temp);
    }

    for (auto iter : t) {
        int to_find = iter - d;
        auto found = t.find(to_find);
        if (found != t.end()) {
            if (iter == to_find && t.count(to_find) == 1) {
                continue;
            }
            cout << iter << " " << to_find;
            return 0;

        }
        
    }

    cout << "NIE";

}

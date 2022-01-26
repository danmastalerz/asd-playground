#include <iostream>

// solv: symulacja dodawania pod kreska liczb binarnych i guess.
// poczatkowo myslalem ze czasowka moze wyjebac bo max z tych liczb moze nie byc O(n)
// (chociaz w sumie w tresci kazde a_i ma to samo ograniczenie co n), ale siadlo 100

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    int t[n];

    int m = -1;
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
        m = max(m, t[i]);
    }

    int num[m + 1];
    for(int i = 0; i <= m; ++i) {
        num[i] = 0;
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        ++res;
        int cur = t[i];
        while(num[cur] == 1) {
            num[cur] = 0;
            --res;
            ++cur;
        }
        num[cur] = 1;
        cout << res << '\n';
    }

    return 0;
}


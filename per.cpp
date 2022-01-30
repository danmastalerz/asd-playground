#include <iostream>
#include <vector>

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> t(n);

    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }

    uint64_t res = 0;
    if (n <= 3) {
        for (int i = 0; i < n; ++i) {
            res += t[i];
        }
        cout << res << '\n';
        return 0;
    }

    vector<uint64_t> y0 (n, 0);
    y0[2] = 0;
    vector<uint64_t> y1 (n, 0);
    y1[2] = 0;
    vector<uint64_t> y23 (n, 0);
    y23[2] = t[0] + t[1] + t[2];

    vector<uint64_t> n0 (n, 0);
    n0[2] = t[0] + t[1];
    vector<uint64_t> n1 (n, 0);
    n1[2] = t[0] + t[2];
    vector<uint64_t> n2 (n, 0);
    n2[2] = t[1] + t[2];

    for (int i = 3; i < n; ++i) {
        y0[i] = max(max(y0[i - 1], y1[i - 1]), y23[i - 1]);
        y1[i] = y0[i - 1] + t[i];
        y23[i] = max(y1[i - 1] + t[i], n2[i - 1] + t[i]);

        n0[i] = max(max(n0[i - 1], n1[i - 1]), n2[i - 1]);
        n1[i] = n0[i - 1] + t[i];
        n2[i] = n1[i - 1] + t[i];
    }

    res = max(res, max(y0[n - 1], max(y1[n - 1], y23[n - 1])));
    res = max(res, max(n0[n - 1], max(n1[n - 1], n2[n - 1])));

    cout << res << '\n';

    return 0;
}


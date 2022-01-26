#include <iostream>
#include <vector>

// solv:
// na biezaco zliczamy odpowiednie podciagi (rodzajow podciagow jest stala ilosc - 1,2 / 1,3 / 2,3 / 1,2,3)

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    int v;
    int ones = 0, twos = 0;
    uint64_t seq_one = n, seq12 = 0, seq23 = 0, seq123 = 0, seq13 = 0;
    for (int i = 0; i < n; ++i) {
        cin >> v;
        if (v == 2) {
            seq12 += ones;
            ++twos;
        }
        else if (v == 3) {
            seq13 += ones;
            seq23 += twos;
            seq123 += seq12;
        }
        else {
            ++ones;
        }
    }

    uint64_t res = seq_one + seq12 + seq13 + seq23 + seq123;

    cout << res << '\n';
    return 0;
}


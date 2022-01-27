#include <iostream>
#include <vector>
#include <cassert>

// solv:
// musimy wykorzystac fakt ze a_i <= 10^5
// To bedzie dynamik, trzymamy globalnie ile dotychczas mozemy osiagnac ciagow, dodatkowo w tablicy trzymamy
// dla kazdej wartosci a_i ile ciagow konczy sie na te wartosc.
// Rozpatrujac teraz wartosc a_i, zwiekszamy ilosc ciagow o (wszystkie ciagi dotychczas - dotychczasowe ciagi konczace sie na a_i + 1)
// +1, bo ciag jednoelementowy. O te wartosc zwiekszamy ilosc wszystkich ciagow, jak i ciagow konczacych sie na a_i.

using namespace std;

int mod = 1000000000;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> seqs_ending_at(10001, 0);
    int seqs_all = 0;

    int val;
    cin >> val;
    ++seqs_all;
    seqs_ending_at[val] = 1;

    int cur;
    for (int i = 1; i < n; ++i) {
        cin >> val;
        cur = (mod + seqs_all - seqs_ending_at[val] + 1) % mod;
        seqs_all = (seqs_all + cur) % mod;
        seqs_ending_at[val] = (seqs_ending_at[val] + cur) % mod;
    }

    cout << seqs_all % mod << '\n';

    return 0;
}


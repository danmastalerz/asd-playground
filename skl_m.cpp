#include <iostream>
#include <vector>

// solv:
// zauwazamy ze skoro wartosci sa ograniczone przez 10^9, to kazda taka liczba jest zlozona z co najwyzej 30 bitow
// (bo floor(log(10^9)) = 29)
// Robimy sobie find union na tych 30 bitach (poczatkowo kazdy sam ze soba w skladowej, i in_res[bit] = false)
// Gdy dodajemy jakas liczbe do grafu, to przechodzimy po jej bitach ktore sa rowne 1,
// i laczymy je do jednej skladowej (korzystajac z FU), odpowiednio tez updatujemy in_res, która mowi czy dany bit wlicza sie do wyniku.
// Wyjatkiem jest liczba 0 (kazde zero jest w skladowej tylko samo ze sobą, bo dla kazdego v mamy p(0) & p(v) = 0.
// Wiec wynik to liczba zer + liczba bitów które maja in_res = true.

using namespace std;

int fu_find(vector<int> &a, int i) {
    int j = i;
    while (a[i] != i)
        i = a[i];

    int k;
    while (a[j] != i) {
        k = a[j];
        a[j] = i;
        j = k;
    }

    return i;
}

// zakladamy, ze i neq j.
// dodatkowo, trzeba tak naprawde zmniejszyc wynik o 1, czyli ustalic in_res[reprezentant mniejszego drzewa] na false
void fu_union(vector<int> &a, vector<int> &d, vector<bool> &in_res, int i, int j) {
    if (a[i] <= a[j]) {
        in_res[i] = false;
        d[i] += d[j];
        a[i] = j;
    }
    else {
        in_res[j] = false;
        a[j] = i;
        d[j] += d[i];
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    // tablica reprezentujaca FU
    vector<int> bits(30);
    for (int i = 0; i < 30; ++i) {
        bits[i] = i;
    }

    // wielkosci poddrzew
    vector<int> d(30, 1);
    // mowi czy dany bit wlicza sie do wyniku
    // (na true beda ustawieni reprezentanci skladowych, ktorzy sie pojawili w inpucie)
    vector<bool> in_res(30, false);
    int res = 0;

    int val;
    vector<int> met;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (val == 0) {
            ++res;
        }
        else {
            for (int b = 0; b < 30; ++b) {
                int v = 1 << b;
                if (v > val)
                    break;
                // sprawdzamy czy val zawiera bit rowny 1 na pozycji b-tej
                // jesli tak, dodajemy do vectora spotkanych
                if ((val & v) > 0) {
                    if (bits[b] == b)
                        in_res[b] = true;
                    met.push_back(b);
                }
            }

            // unionujemy wszystko co jest w vectorze
            for (int j = 1; j < met.size(); ++j) {
                int p1 = fu_find(bits, met[j]);
                int p2 = fu_find(bits, met[j - 1]);
                if (p1 != p2)
                    fu_union(bits, d, in_res, p1, p2);
            }

            met.clear();
        }
    }

    for (int i = 0; i < 30; ++i) {
        if (in_res[i])
            ++res;
    }

    cout << res << '\n';

    return 0;
}



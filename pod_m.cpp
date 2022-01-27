#include <iostream>
#include <set>
#include <vector>
#include <map>

// solv:
// Mamy: vector wartosci, set (zeby zliczac ile unikalnych elementow), mape (wartosc, ile razy wartosc wystepuje w aktualnym podciagu)
// Dodatkowo trzymamy 2 indeksy: i - poczatek aktualnego podciagu, j - koniec -||-
// Jesli wartosc na aktualnej pozycji (j-tej) wystepuje w ciagu albo w ciagu jest mniej niz k unikalnych wartosci to na luzie dodajemy
// Wpp. musimy przesuwac i-ty indeks i usuwac elementy dopoki ktoregos nie pozbedziemy sie na dobre (czyli gdy jego count w mapie bedzie 0).
// Wtedy mozemy dodac do ciagu to co jest na j-tym indeksie. Zwiekszamy wynik o (j - i + 1) - ilosc elementow w podciagu,
// bo tyle mozemy stworzyc podciagow z tym elementem (doczepiamy po jednym elemencie z przodu).
// Zauwazyc trzeba ze to usuwanie sie amortyzuje (kazdy element ktory jest juz w podciagu, moze zostac usuniety co najwyzej raz
// i wiecej sie w tym ciagu nie pojawi).

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    cin >> n >> k;

    uint64_t res = 0;
    map<int, int> values_count;
    set<int> unique;
    vector<int> values(n);

    int val;
    int i = 0;
    for (int j = 0; j < n; ++j) {
        cin >> val;
        values[j] = val;
        if (values_count[val] > 0 || unique.size() < k) {
            ++values_count[val];
            unique.insert(val);
        }
        else {
            // tu sie amortyzuje, nie mozemy usunac wiecej niz dodalismy
            while (true) {
                int &c = values_count[values[i]];
                --c;
                if (c == 0) {
                    unique.erase(values[i]);
                    ++i;
                    break;
                }
                ++i;
            }
            ++values_count[val];
            unique.insert(val);
        }

        res += (j - i + 1);
    }

    cout << res;

    return 0;
}


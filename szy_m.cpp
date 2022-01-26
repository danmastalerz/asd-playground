#include <iostream>
#include <set>

// solv:
// zachlan taki ze po prostu sprawdzamy czy secie jest aktualna wartosc, jak tak to zwiekszamy wynik o 1 i czyscimy set
// jak nie ma tej wartosci w secie, to ja dodajemy i tyle

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    cin >> n;

    set<int> s;

    int val;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        if (s.count(val) > 0) {
            ++res;
            s.clear();
        }
        else {
            s.insert(val);
        }
    }

    cout << res << '\n';

    return 0;
}


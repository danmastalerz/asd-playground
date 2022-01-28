#include <iostream>
#include <vector>

// najgorsze zadanie na playground, glownie przez ilosc kodu (ale moze po prostu nie umiem w drzewa przedzialowe)
// Pomysl podobny jak przy malowaniu autostrady, przy przesuwaniu wszystkich, zerujemy liczniki w najwiekszych podprzedzialach ktore sa cale pokryte
// Poprawiac bedziemy w dol (jak jestem wyzerowany, to wyzeruj dzieci bo moga byc zle wyliczone)
// Mamy na drzewie 3 operacje: query - daje w wyniku ile jest mrowek w danym punkcie
// leave - bierze przedzial [l, r] i symuluje wychodzenie mrowek, do tego w referencji zwraca ilosc mrowek na tym przedziale
// update - aktualizuje ilosc mrowek w danym punkcie
// NOTE: wszystkie te operacje musza isc z gory do dolu drzewa (zeby dobrze poprawiac na sciezce do liscia)

using namespace std;

int nextPowerOf2(int n) {
    unsigned count = 0;

    int x = n;
    while(x != 0)
    {
        if (n == 1 << count) return n;
        x >>= 1;
        count += 1;
    }

    return 1 << count;
}

class SegmentTree {
public:
    vector<pair<int, int>> t;
    int size;
    int my_n;

    SegmentTree(int n) {
        my_n = n;
        size = nextPowerOf2(n);
        t.resize(2 * nextPowerOf2(n));
    }

    void init() {
        t[1].second = my_n;
        for(int i = 1; i < size; i++) {
            t[i].first = 0;
            t[2 * i].first = 0;
            t[2 * i].second = (t[i].second + 1) / 2;
            t[2 * i + 1].first = 0;
            t[2 * i + 1].second = t[i].second / 2;
        }
    }

    int query(int v, int i, int begin) {
        int end = begin + t[i].second - 1;
        int s = (begin + end) / 2;

        if (t[i].second == 1) {
            return t[i].first;
        }

        if (t[i].first == 0) {
            t[2 * i].first = 0;
            t[2 * i + 1].first = 0;
        }

        int res;
        if (v <= s) {
            res = query(v, 2 * i, begin);
        }
        else {
            res = query(v, 2 * i + 1, s + 1);
        }

        t[i].first = t[2 * i].first + t[2 * i + 1].first;
        return res;
    }

    void leave (int l, int r, int i, int begin, int &count) {
        int end = begin + t[i].second - 1;
        int s = (begin + end) / 2;

        // pokrywamy caly przedzial
        if (r - l + 1 == t[i].second || t[i].second <= 1) {
            count += t[i].first;
            t[i].first = 0;
            return;
        }

        if (t[i].first == 0) {
            t[2 * i].first = 0;
            t[2 * i + 1].first = 0;
        }

        if (l <= s && r > s) {
            leave(l, s, 2 * i, begin, count);
            leave(s + 1, r, 2 * i + 1, s + 1, count);
        }
        else if (l <= s){
            leave(l, r, 2 * i, begin, count);
        }
            // l > s
        else {
            leave(l, r, 2 * i + 1, s + 1, count);
        }

        t[i].first = t[2 * i].first + t[2 * i + 1].first;
    }

    void update(int v, int i, int begin, int q) {

        int end = begin + t[i].second - 1;
        int s = (begin + end) / 2;

        if (t[i].second == 1) {
            t[i].first = q;
            return;
        }

        if (t[i].first == 0) {
            t[2 * i].first = 0;
            t[2 * i + 1].first = 0;
        }

        int res;
        if (v <= s) {
            update(v, 2 * i, begin, q);
        }
        else {
            update(v, 2 * i + 1, s + 1, q);
        }

        t[i].first = t[2 * i].first + t[2 * i + 1].first;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    SegmentTree t(n);
    t.init();

    vector<int> vec(n + 1, 0);
    int val;
    for (int i = 0; i < n; ++i) {
        cin >> val;
        ++vec[val];
        t.update(val, 1, 1, vec[val]);
    }

    int l, r;
    int c = 0;
    int res = 0;
    for(int i = 0; i < q; ++i) {
        cin >> l >> r >> val;
        c = t.query(val, 1, 1);
        res = 0;
        t.leave(l, r, 1, 1, res);
        cout << res - c << '\n';
        t.update(val, 1, 1, res);
    }

    return 0;
}


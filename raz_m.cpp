#include <iostream>
#include <set>
#include <vector>

// solv:
// mamy 3 sety, dla pozycji gdzie sa odpowiednio 1,2,3
// wyciagamy minimum z seta dla 1 (najwczesniejsza 1 z ciagu) - za pomoca begin
// wyciagamy maximum z seta dla 3 (najpozniejsza 3 z ciagu) 0 za pomoca rbegin
// wyciagamy dwojke (a wlasciwie pozycje) ktora jest po najwczesniejszej jedynce - za pomoca lower_bound
// sprawdzamy czy jedynka < dwojka < trojka

using namespace std;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    cin >> n;
    set<int> ones;
    set<int> twos;
    set<int> threes;
    vector<set<int>> s(4);
    vector<int> v(n + 1);

    int val;
    for (int i = 1; i <= n; ++i) {
        cin >> val;
        v[i] = val;
        s[val].insert(i);
    }

    int min_one, max_three, two;

    if (s[1].empty() || s[2].empty() || s[3].empty()) {
        cout << "NIE\n";
    }
    else {
        min_one = *(s[1].begin());
        max_three = *(s[3].rbegin());
        two = *(s[2].lower_bound(min_one));

        if (min_one < two && two < max_three)
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }

    cin >> m;
    int pos;
    for (int i = 0; i < m; ++i) {
        cin >> pos >> val;
        if (v[pos] != val) {
            s[v[pos]].erase(pos);
            v[pos] = val;
            s[val].insert(pos);
        }

        if (s[1].empty() || s[2].empty() || s[3].empty()) {
            cout << "NIE\n";
        }
        else {
            min_one = *(s[1].begin());
            max_three = *(s[3].rbegin());
            two = *(s[2].upper_bound(min_one));

            if (min_one < two && two < max_three) {
                cout << "TAK\n";
            }
            else {
                cout << "NIE\n";
            }
        }

    }

    return 0;
}


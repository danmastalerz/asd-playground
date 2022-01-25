/*
solv: sortujemy, potem w pętli sprawdzamy warunkek między t[i], t[i+1]
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> t(n, 0);
    for (int i = 0; i < n; i++) cin >> t[i];

    int curr_ans = 1;
    int max_ans = 1;
    int first_index = 0;
    int first_index_ans = 0;

    sort(t.begin(), t.end());

    for (int i = 0; i < n - 1; i++) {
        if (abs(t[i] - t[i + 1]) <= 1) {
            curr_ans++;
        }
        else {
            if (curr_ans > max_ans) {
                max_ans = curr_ans;
                curr_ans = 1;
                first_index_ans = first_index;
                first_index = i + 1;
                
            }
        }
    }

    if (curr_ans > max_ans) {
        max_ans = curr_ans;
        first_index_ans = first_index;     
    }

    cout << max_ans;

}
#include <iostream>
#include <vector>
using namespace std;
/*
    1 0 10 2 30 3 2 1 2 9
 0  1 1 2  1 1  1 0 1 0 0 <-- tablica prefiksowa modulo 3

i jak odejmuje prefiks z tym samym modulo to znaczy że będzie się dzieliło przez 3

czyli trzeba wiedzieć ile jest 0 1 i 2 w konkretnym przedziale

a potem zlicza ile takich samych modulo jest w przedziale
i odpowiednio wymnaża

 przyklad 2
    1 2 6 1 2 2 3
  0 1 0 0 1 0 2 2  
*/


int main() {
    long long n,m;
    cin>>n>>m;

    vector<vector<long long> > count_r;

    count_r.resize(n+1);
    long long a;
    count_r[0].resize(3);
    for (long long j = 0; j <3; j++) {
        count_r[0][j] = 0;
    }
    count_r[0][0] = 1;
    long long suma = 0;
    for (long long i = 1; i <= n; i++) {
        cin>>a;
        a%=3;
        suma +=a;
        suma%=3;
        count_r[i].resize(3);
        for (long long j = 0; j <3; j++) {
            count_r[i][j] = count_r[i-1][j];
        }
        count_r[i][suma]++;
    }
    long long r[3];
    long long left,right;
    for (long long i = 0; i < m; i++) {
        cin>>left>>right;
        if (left == 1) {
            for (long long j = 0; j <3; j++) {
                r[j] = count_r[right][j];
            }
        }
        else {
            for (long long j = 0; j <3; j++) {
                r[j] = count_r[right][j] - count_r[left-2][j];
            }
        }
        suma = 0;
        for (long long j = 0; j <3; j++) {
            long long a = r[j];
            if ( a > 1) {
                suma += a*(a-1)/2;
            }
            
        }
        cout<<suma<<endl;
    }
    return 0;
}
#include <iostream>
#include <set>
#include <map>
#include <queue>
#include <string.h>
using namespace std;

/*
    Solv analogicznie do rozwiazania CIA jest to praktycznie to samo tylko dla każdego paliwa trzeba osobno
    więc dlatego mapa struktur

    Tak zapomniałam że na tym przedmiocie można robić globalnie proszę nie oceniać XD
*/ 
struct rodzaj{
    vector<int> distances_count;
    set<int> s; //gdzie stacje
    priority_queue <int> queue; // do aktualizacji

};
void activate(map <string, struct rodzaj > *samochody , string s, int n){
    rodzaj nowy;
    nowy.distances_count.resize(n+1);
    for (int i = 0; i <= n; i++) {
        nowy.distances_count[i] = 0;
    }
    nowy.distances_count[n] = 1;
    nowy.s.insert(0);
    nowy.s.insert(n);
    nowy.queue.push(n);
    samochody->insert ({s,nowy} );

}
void safety_map(map <string, struct rodzaj > *samochody, string s, int n){
    if (samochody->find(s) == samochody->end()) {
        activate(samochody,s,n);
    }

}
void destroy(map <string, struct rodzaj > *samochody, int n) {
    int km;
    cin>> km;
    map<string, struct rodzaj>::iterator it;
    for (it = samochody->begin(); it != samochody->end(); it++)
    {
        if (it->second.s.find(km) != it->second.s.end()) {
            //trzeba usunąć
            auto it_pom = it->second.s.find(km);
            it_pom++;
            int next_value = *it_pom;
            it_pom--;
            it_pom--;
            int prev_value = *it_pom;
            it_pom++;
            //wrzucamy nowy element do stosu
            it->second.s.erase(it_pom);
            it->second.distances_count[next_value - prev_value]++;
            it->second.distances_count[next_value - km]--;
            it->second.distances_count[km-prev_value]--;
            it->second.queue.push(next_value - prev_value);
            while (it->second.distances_count[it->second.queue.top()] == 0) {
                it->second.queue.pop();
            }
        }
    }
}
void build(map <string, struct rodzaj > *samochody, int n){
    int km,ile;
    cin>>km>>ile;
    string s;
    for (int i = 0; i < ile; i++){
        cin>>s;
        safety_map(samochody,s,n);
        auto it = samochody->find(s);
        auto it_pom = it->second.s.lower_bound(km);
        int next_value = *it_pom;
        it_pom--;
        int prev_value = *it_pom;
        //wrzucamy nowy element do stosu
        it->second.s.insert(km);
        it->second.distances_count[next_value - prev_value]--;
        it->second.distances_count[next_value - km]++;
        it->second.distances_count[km-prev_value]++;
        it->second.queue.push(next_value - km);
        it->second.queue.push(km-prev_value);
        while (it->second.distances_count[it->second.queue.top()] == 0) {
            it->second.queue.pop();
        }

        
        
    }
    
}
int main() {
    int n;
    cin>>n;
    int a;
    int m;
    cin>>m;
    string s;
    int ile;
    map <string, struct rodzaj > samochody;
    for (int i = 0 ; i <m ; i++) {
        cin>>s;
        if (s.compare("query") == 0) {
            cin>>ile>>s;
            safety_map(&samochody,s,n);
            //ile zawiera jaki ma bak i ten bak musi być większy
            if (samochody[s].queue.top() <= ile) {
                cout<<"TAK"<<"\n";
            }
            else {
                cout<<"NIE"<<"\n";
            }
        }
        else if (s.compare("build") == 0) {
            build(&samochody,n);
        }
        else {
            //destroy
            destroy(&samochody, n);
        }
    
    }

    return 0;
}
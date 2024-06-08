#include <bits/stdc++.h>
using namespace std;

const int NMAX = 2e5; // Dimensiunea maximă pentru array-ul de frecvență
int freq[NMAX + 1]; // Vector pentru a ține evidența frecvenței fiecărui index

int main() {
    int n;
    cin >> n; // Citim numărul de elemente din array-urile A și B

    deque<pair<int, int>> dq; // Deque pentru a menține perechi de (valoare, index)
    vector<pair<int, int>> v; // Vector pentru a stoca valorile din array-urile A și B împreună cu indexurile lor

    // Citim valorile din array-urile A și B și le stocăm în vectorul v
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        v.push_back({x, i});
        v.push_back({y, i});
    }

    // Sortăm vectorul v pe baza valorilor
    sort(v.begin(), v.end());

    int cnt = 0; // Contor pentru a ține evidența câte elemente unice sunt în deque
    int sol = 1e9; // Inițializăm soluția cu o valoare mare

    // Parcurgem vectorul sortat v
    for (int i = 0; i < (int)v.size(); i++) {
        int value = v[i].first; // Extragem valoarea
        int idx = v[i].second; // Extragem indexul corespunzător valorii
        dq.push_back({value, idx}); // Adăugăm perechea (valoare, index) în deque
        freq[idx]++; // Incrementăm frecvența indexului

        if (freq[idx] == 1) {
            cnt++; // Dacă frecvența devine 1, înseamnă că am adăugat un index unic în deque
        }

        // Cât timp deque-ul conține toate indexurile de la 1 la n
        while (!dq.empty() && cnt == n) {
            sol = min(sol, dq.back().first - dq.front().first); // Calculăm diferența dintre valoarea maximă și minimă din deque
            idx = dq.front().second; // Extragem indexul elementului din fața deque-ului
            dq.pop_front(); // Eliminăm elementul din fața deque-ului
            freq[idx]--; // Decrementăm frecvența indexului

            if (freq[idx] == 0) {
                cnt--; // Dacă frecvența devine 0, înseamnă că am eliminat un index unic din deque
            }
        }
    }

    // Afișăm soluția
    cout << sol;
    return 0;
}

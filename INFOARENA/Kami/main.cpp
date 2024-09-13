#include <bits/stdc++.h>
using namespace std;

// Deschidem fișierele de intrare și ieșire
ifstream f("kami.in");
ofstream g("kami.out");

int n, m, x; // n - numărul de nivele, m - numărul de operații, x - valoarea maximă a zăpezii
int v[100002]; // Vector pentru stocarea cantităților de zăpadă pe nivele

int main() {
    // Citim numărul de nivele
    f >> n;
    // Citim cantitățile de zăpadă pentru fiecare nivel și determinăm valoarea maximă a zăpezii
    for (int i = 1; i <= n; ++i)
        f >> v[i], x = max(v[i], x);

    // Citim numărul de operații
    f >> m;

    // Procesăm fiecare operație
    for (int i = 1; i <= m; ++i) {
        int tip;
        f >> tip; // Citim tipul operației

        if (tip == 0) { // Dacă operația este de tipul 0 (Poseidon schimbă valoarea)
            int a, b;
            f >> a >> b; // Citim nivelul și noua valoare
            v[a] = b; // Actualizăm valoarea zăpezii la nivelul specificat
            x = max(v[a], x); // Actualizăm valoarea maximă a zăpezii dacă este necesar
        } else { // Dacă operația este de tipul 1 (Athena întreabă despre avalanșă)
            int nr;
            f >> nr; // Citim nivelul de start al avalanșei
            int pos = nr - 1; // Setăm poziția inițială de verificare cu un nivel mai jos
            int sum = v[nr]; // Inițializăm suma zăpezii cu valoarea de la nivelul de start
            int sol = 0; // Variabilă pentru poziția finală a avalanșei

            while (1) { // Buclă pentru determinarea poziției finale a avalanșei
                if (pos == 0) { // Dacă ajungem la poziția 0, avalanșa se oprește în afara muntelui
                    g << 0 << '\n';
                    break;
                }
                if (sum <= v[pos]) { // Dacă suma zăpezii este mai mică sau egală cu zăpada de la poziția curentă, avalanșa se oprește
                    g << pos << '\n';
                    break;
                } else { // Dacă nu, continuăm avalanșa
                    if (sum > x) { // Dacă suma depășește valoarea maximă, avalanșa se oprește în afara muntelui
                        g << 0 << '\n';
                        break;
                    }
                    sum += v[pos]; // Adunăm zăpada de la nivelul curent la sumă
                    --pos; // Decrementăm poziția pentru a verifica nivelul următor mai jos
                }
            }
        }
    }

    return 0;
}

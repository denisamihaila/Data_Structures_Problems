#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#define nmax 100001
using namespace std;

int n, a[nmax];
int rmin[18][nmax], rmax[18][nmax]; // Sparse Table pentru minimul și maximul intervalelor
int P[nmax]; // P[i] = j : secvența de la j la i are doar numere distincte
int fr[nmax]; // Vector de frecvență pentru șir
int lg[nmax]; // Vector pentru logaritmii în baza 2

void RMQ() {
    int i, j, k;

    // lg[i] = k - exponentul maxim cu proprietatea că 2^k <= i
    lg[1] = 0;
    for (i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    // rmin
    // Inițializare Sparse Table pentru minim
    for (i = 1; i <= n; i++)
        rmin[0][i] = a[i];

    // Calculare Sparse Table pentru minim
    for (i = 1; (1 << i) <= n; i++)
        for (j = (1 << i); j <= n; j++) {
            k = 1 << (i - 1);
            rmin[i][j] = min(rmin[i - 1][j], rmin[i - 1][j - k]);
        }

    // rmax
    // Inițializare Sparse Table pentru maxim
    for (i = 1; i <= n; i++)
        rmax[0][i] = a[i];

    // Calculare Sparse Table pentru maxim
    for (i = 1; (1 << i) <= n; i++)
        for (j = (1 << i); j <= n; j++) {
            k = 1 << (i - 1);
            rmax[i][j] = max(rmax[i - 1][j], rmax[i - 1][j - k]);
        }
}

int main() {
    cin >> n; //Dimensiune șir
    for (int i = 1; i <= n; i++)
        cin >> a[i]; // Șir

    // Construire P
    int i, j, q;
    j = 1;
    for (i = 1; i <= n; i++) {
        q = a[i];
        // Menținerea secvenței distincte
        while (fr[q] != 0) {
            fr[a[j]]--;
            j++;
        }
        fr[q]++;
        P[i] = j;
    }

    // Construirea Sparse Table
    RMQ();

    // Interogări
    int Q, x, y, k, m, M;
    cin >> Q; // Nr interogări

    stringstream output;

    while (Q--) {
        cin >> x >> y; // Intervalul de interogat
        if (P[y] <= x) { // Verificăm dacă secvența a[x..y] are doar numere distincte
            k = lg[y - x + 1];
            m = min(rmin[k][x + (1 << k) - 1], rmin[k][y]);
            M = max(rmax[k][x + (1 << k) - 1], rmax[k][y]);
            // Verificăm dacă diferența dintre maxim și minim este exact lungimea secvenței minus 1
            if (M - m == y - x) output << "1";
            else output << "0";
        } else {
            output << "0";
        }
    }

    cout << output.str();

    return 0;
}

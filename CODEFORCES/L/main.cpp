#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e5; // Dimensiunea maximă a secvenței
const long long MOD = 1e9 + 7; // Modulo pentru a evita overflow
long long v[NMAX + 5], lg[NMAX + 5]; // v - vectorul de valori, lg - vectorul pentru logaritmi
long long rmq[32][NMAX + 5]; // Sparse table pentru valorile maxime

// Funcție pentru a preprocesa Sparse Table-ul pentru RMQ (Range Maximum Query)
void solve_rmq(int n) {
    lg[1] = 0; // Logaritmul în baza 2 pentru 1 este 0

    // Preprocesăm logaritmii în baza 2 pentru toate valorile până la n
    for(long long i = 2; i <= n; i++)
        lg[i] = lg[i / 2] + 1;

    // Inițializăm Sparse Table-ul pentru nivelul 0 (valorile inițiale)
    for(long long i = 1; i <= n; ++i)
        rmq[0][i] = v[i];

    // Construim Sparse Table-ul pentru toate nivelele
    for(long long i = 1; (1 << i) <= n; i++)
        for (long long j = 1; j + (1 << i) - 1 <= n; j++)
            rmq[i][j] = max(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
}

// Funcție pentru exponentiere rapidă (modular exponentiation)
long long exponentiere(long long b, long long e) {
  long long r = 1;
  while(e) {
    if(e & 1)
      r = (b * r) % MOD;
    b = (b * b) % MOD;
    e >>= 1;
  }
  return r;
}

int main() {
    long long n, m, x, y;
    cin >> n; // Citim dimensiunea secvenței
    for(int i = 1; i <= n; ++i)
        cin >> v[i]; // Citim valorile din secvență

    solve_rmq(n); // Preprocesăm Sparse Table-ul pentru RMQ

    cin >> m; // Citim numărul de interogări
    for(int i = 1; i <= m; ++i) {
        cin >> x >> y; // Citim intervalul interogării
        long long a = y - x + 1; // Lungimea intervalului
        long long l = lg[a]; // Logaritmul lungimii intervalului
        long long s = a - (1 << l); // Diferența dintre lungimea intervalului și cea mai mare putere de 2 mai mică sau egală cu a

        // Calculăm valoarea maximă din interval folosind Sparse Table-ul
        long long maxim = max(rmq[l][x], rmq[l][x + s]);

        // Calculăm rezultatul final folosind exponentierea rapidă
        cout << maxim * exponentiere(2, y - x) % MOD << "\n";
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

ifstream f("pikachu.in");
ofstream g("pikachu.out");

int n, k;
int v[100002]; // Vector pentru stocarea înălțimilor munților

// Funcție pentru a verifica timpul minim necesar pentru a transforma `k` vârfuri la înălțimea `val`
long long check(int val) {
    long long mins = (1LL << 60); // Inițializăm mins cu o valoare foarte mare (aproximativ infinit)
    long long s = 0; // Variabilă pentru a stoca suma transformărilor

    // Calculăm suma transformărilor necesare pentru primele `k` vârfuri
    for (int i = 1; i <= k; ++i)
        s += abs(v[i] - val);

    // Verificăm și actualizăm suma minimă pentru toate subsecvențele de lungime `k`
    for (int i = k; i <= n; ++i) {
        if (i > k)
            s -= abs(v[i - k] - val); // Scoatem transformarea pentru elementul care iese din fereastră
        mins = min(mins, s); // Actualizăm mins dacă găsim o sumă mai mică
        if (i < n)
            s += abs(v[i + 1] - val); // Adăugăm transformarea pentru noul element care intră în fereastră
    }

    return mins; // Suma minimă a transformărilor
}

int main() {
    f >> n >> k;
    int b = 1; // Limita inferioară pentru înălțimi
    int e = 0; // Limita superioară pentru înălțimi

    // Citim înălțimile și determinăm limita superioară `e`
    for (int i = 1; i <= n; ++i)
        f >> v[i], e = max(e, v[i]);

    long long minsol = (1LL << 60); // Inițializăm soluția minimă cu o valoare foarte mare (aproximativ infinit)

    // Căutare binară pentru a găsi valoarea optimă a înălțimii
    while (b <= e) {
        int mid = b + (e - b) / 2; // Calculăm valoarea de mijloc
        // Verificăm dacă valoarea de mijloc este soluția optimă
        if (check(mid - 1) >= check(mid) && check(mid) <= check(mid + 1)) {
            minsol = check(mid); // Actualizăm soluția minimă
            break;
        }
        // Ajustăm limitele
        if (check(mid - 1) >= check(mid))
            b = mid + 1;
        else
            e = mid - 1;
    }

    g << minsol << '\n';

    return 0;
}

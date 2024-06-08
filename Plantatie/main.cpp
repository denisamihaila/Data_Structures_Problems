#include <fstream>  // pentru citirea și scrierea în fișiere
#define DIM 502     // Definim dimensiunea maximă pentru matrice
using namespace std;

// Declarația variabilelor globale
int n, m, i1, i2, j1, j2, lat, L, len, k;
int r[10][DIM][DIM]; // Sparse Table pentru maximi
int E[DIM]; // Vector pentru logaritmi în baza 2

// Funcție inline pentru a returna maximul dintre două valori
inline int maxim(int a, int b) {
    return (a > b ? a : b);
}

int main() {
    // Deschidem fișierele de intrare și ieșire
    ifstream fin("plantatie.in");
    ofstream fout("plantatie.out");

    // Citim dimensiunea plantatiei și numărul de întrebări
    fin >> n >> m;

    // Citim valorile productivității și le stocăm în r[0]
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            fin >> r[0][i][j];
        }
    }

    // Construim Sparse Table pentru a preprocesa maximi
    for (int p = 1, lat = 2; lat <= n; p++, lat *= 2) {
        for (int i1 = 1; i1 <= n - lat + 1; i1++) {
            for (int j1 = 1; j1 <= n - lat + 1; j1++) {
                i2 = i1 + (lat >> 1); // Determinăm punctele mijlocii
                j2 = j1 + (lat >> 1);
                // Calculăm maximul pentru subintervalele de dimensiune `lat x lat`
                r[p][i1][j1] = max(
                    max(r[p-1][i1][j1], r[p-1][i2][j1]),
                    max(r[p-1][i1][j2], r[p-1][i2][j2])
                );
            }
        }
    }

    // Preprocesăm vectorul E pentru logaritmi în baza 2
    E[1] = 0;
    for (int i = 2; i <= n; i++)
        E[i] = 1 + E[i / 2];

    // Procesăm fiecare întrebare
    for (; m; m--) {
        fin >> i1 >> j1 >> L; // Citim coordonatele colțului stânga-sus și latura patratului
        k = E[L]; // Determinăm cea mai mare putere de 2 <= L
        len = (1 << k); // Lungimea subintervalului
        // Determinăm coordonatele colțurilor subintervalului de dimensiune `L x L`
        i2 = i1 + L - len;
        j2 = j1 + L - len;
        // Calculăm maximul în subinterval folosind Sparse Table
        fout << max(
            max(r[k][i1][j1], r[k][i1][j2]),
            max(r[k][i2][j1], r[k][i2][j2])
        ) << "\n";
    }

    // Închidem fișierele
    return 0;
}

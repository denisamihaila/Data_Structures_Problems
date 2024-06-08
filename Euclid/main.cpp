#include <bits/stdc++.h>
using namespace std;

// Deschidem fișierele de intrare și ieșire
ifstream f("euclid.in");
ofstream g("euclid.out");

int T, n, m, h, w; // T - numărul de teste, n - numărul de linii, m - numărul de coloane, h - înălțimea minimă, w - lățimea minimă
int a[25][405][405]; // Sparse table pentru păstrarea valorilor CMMDC pentru dreptunghiuri verticale
int x[405][405]; // Matrice pentru stocarea valorilor inițiale (nu este folosită în codul dat)
int b[25][405][405]; // Sparse table pentru păstrarea valorilor CMMDC pentru dreptunghiuri orizontale
int de, d[405], r; // de - variabilă auxiliară, d - vector pentru logaritmi în baza 2, r - rezultat

// Funcție pentru calcularea CMMDC (Cel Mai Mare Divizor Comun)
int cmmdc(int a, int b) {
    if (b == 0)
        return a;
    return cmmdc(b, a % b);
}

int main() {
    // Citim numărul de teste
    f >> T;

    // Preprocesăm logaritmii în baza 2 pentru dimensiuni până la 400
    for (int i = 1; i <= 400; i++)
        for (int j = 0; j <= 10; j++)
            if ((1 << j) <= i)
                d[i] = j;

    // Procesăm fiecare test
    for (int t = 1; t <= T; t++) {
        f >> n >> m >> h >> w; // Citim dimensiunile matricei și dimensiunile minime ale dreptunghiului
        r = 0; // Inițializăm rezultatul pentru acest test

        // Citim valorile matricei
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                f >> b[0][i][j];

        // Construim Sparse Table-ul pentru dreptunghiurile orizontale
        for (int k = 1; k <= 10; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j + (1 << k) - 1 <= m; j++)
                    b[k][i][j] = cmmdc(b[k-1][i][j], b[k-1][i][j + (1 << (k-1))]);

        // Determinăm cea mai mare putere de 2 ≤ w
        for (int k = 0; k <= 10; k++)
            if ((1 << k) <= w)
                de = k;

        // Calculăm CMMDC pentru fiecare dreptunghi orizontal de lățime `w`
        for (int i = 1; i <= n; i++)
            for (int j = 1; j + w - 1 <= m; j++)
                a[0][i][j] = cmmdc(b[de][i][j], b[de][i][j + w - (1 << de)]);

        // Construim Sparse Table-ul pentru dreptunghiurile verticale
        for (int k = 1; k <= 10; k++)
            for (int i = 1; i + (1 << k) - 1 <= n; i++)
                for (int j = 1; j + w - 1 <= m; j++)
                    a[k][i][j] = cmmdc(a[k-1][i][j], a[k-1][i + (1 << (k-1))][j]);

        // Determinăm cea mai mare putere de 2 ≤ h
        for (int k = 0; k <= 10; k++)
            if ((1 << k) <= h)
                de = k;

        // Calculăm CMMDC pentru fiecare dreptunghi vertical de înălțime `h`
        for (int i = 1; i + h - 1 <= n; i++)
            for (int j = 1; j + w - 1 <= m; j++)
                r = max(r, cmmdc(a[de][i][j], a[de][i + h - (1 << de)][j]));

        // Scriem rezultatul pentru testul curent
        g << "Case #" << t << ": " << r << '\n';
    }

    return 0;
}

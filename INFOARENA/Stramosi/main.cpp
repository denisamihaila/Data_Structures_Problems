#include <bits/stdc++.h>
using namespace std;

// Deschidem fișierele de intrare și ieșire
ifstream f("stramosi.in");
ofstream g("stramosi.out");

int n, m, q, p;
int nr[250002]; // Vector pentru stocarea strămoșilor direcți
int ancestors[250002][20]; // Sparse table pentru păstrarea strămoșilor la diferite puteri de 2
vector<int> gul[250002]; // Lista de adiacență pentru construirea arborelui genealogic

// Funcție DFS pentru a construi sparse table-ul de strămoși
void dfs(int dad, int nod) {
    ancestors[nod][0] = dad; // Strămoșul direct (nivelul 0)
    int lvl = 0;
    int fth = dad;

    // Construim sparse table-ul pentru strămoși
    while (ancestors[fth][lvl]) {
        ancestors[nod][lvl + 1] = ancestors[fth][lvl];
        ++lvl;
        fth = ancestors[nod][lvl];
    }

    // Apelăm recursiv pentru toți copiii nodului curent
    for (int i = 0; i < gul[nod].size(); ++i)
        dfs(nod, gul[nod][i]);
}

int main() {
    // Citim numărul de membri și numărul de întrebări
    f >> n >> m;

    // Citim strămoșii direcți și construim lista de adiacență
    for (int i = 1; i <= n; ++i) {
        f >> nr[i];
        if (nr[i] != 0)
            gul[nr[i]].push_back(i);
    }

    // Pentru fiecare membru fără strămoș cunoscut, apelăm DFS pentru a construi sparse table-ul
    for (int i = 1; i <= n; ++i)
        if (!nr[i])
            dfs(0, i);

    // Procesăm fiecare întrebare
    for (int i = 1; i <= m; ++i) {
        f >> q >> p; // Citim membrul și strămoșul P
        int p2 = 1, lvl = 0;

        // Determinăm cea mai mare putere de 2 ≤ p
        while (p2 * 2 <= p)
            p2 *= 2, lvl++;

        int father = q; // Inițial, strămoșul căutat este membrul însuși

        // Căutăm al P-lea strămoș folosind sparse table-ul
        while (p && father != 0) {
            p -= p2; // Scădem puterea de 2 din p
            father = ancestors[father][lvl]; // Avansăm la strămoșul corespunzător
            while (p < p2) // Ajustăm puterea de 2 și nivelul dacă este necesar
                p2 /= 2, --lvl;
        }

        // Scriem rezultatul în fișierul de ieșire
        g << father << '\n';
    }

    return 0;
}

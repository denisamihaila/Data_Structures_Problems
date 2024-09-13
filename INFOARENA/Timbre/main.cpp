#include <fstream>
#include <algorithm>
#include <set>
using namespace std;

ifstream fin("timbre.in");
ofstream fout("timbre.out");

const int NMAX = 10005; // Limita maximă pentru numărul de intervale

int n, m, k, lim, cost;
multiset<int> mul; // Multiset pentru stocarea costurilor
pair<int, int> v[NMAX]; // Vector de perechi pentru a stoca limitele și costurile intervalelor

int main() {
    // Numărul de pagini, numărul de intervale și lungimea maximă a unei subsecvențe
    fin >> n >> m >> k;

    // Citim limitele și costurile fiecărui interval
    for (int i = 1; i <= m; i++) {
        fin >> lim >> cost;
        v[i] = {lim, cost};
    }

    // Sortăm intervalele după limitele superioare
    sort(v + 1, v + m + 1);

    int i = m; // Pornim de la ultimul interval
    int ans = 0; // Variabilă pentru a păstra suma minimă a costurilor

    // Continuăm până când numerotăm toate paginile
    while (n > 0) {
        // Adăugăm în multiset toate intervalele care acoperă pagina curentă `n`
        while (i >= 1 && v[i].first >= n)
            mul.insert(v[i--].second);

        // Adăugăm costul minim pentru a acoperi următoarele `k` pagini
        ans += *mul.begin();
        // Eliminăm acest cost din multiset, deoarece l-am folosit
        mul.erase(mul.begin());

        // Reducem numărul de pagini rămase de acoperit cu `k`
        n -= k;
    }

    fout << ans << '\n';

    return 0;
}

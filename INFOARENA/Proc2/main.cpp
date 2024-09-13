#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int main() {

    ifstream f("proc2.in");
    ofstream g("proc2.out");

    int n, m;
    f >> n >> m;

    // Coada de prioritate pentru procesoare, ordonate după index
    priority_queue<int, vector<int>, greater<int>> p; //Min heap
    // Coada de prioritate pentru timp, ordonată după timpul de finalizare al sarcinilor
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> timp; //Min heap

    int t1, t2, urmP;

    // Inițializăm coada de prioritate cu procesoarele disponibile
    for (int i = 1; i <= n; i++)
        p.push(i);

    // Procesăm fiecare sarcină
    for (int i = 0; i < m; i++)
    {
        f >> t1 >> t2;// t1 - timpul de începere ; t2 - durata sarcinii

        // Eliberăm procesoarele care au terminat sarcinile înainte de timpul curent t1
        while (!timp.empty() && t1 >= timp.top().first)
        {
            p.push(timp.top().second); // Adăugăm procesorul eliberat înapoi în coada de disponibilitate
            timp.pop(); // Scoatem elementul din coada de timp
        }

        // Selectăm cel mai mic index de procesor disponibil
        urmP = p.top();
        timp.push({ t1 + t2, urmP }); // Îl programăm pe acesta pentru noua sarcină, marcăm timpul de finalizare
        p.pop(); // Îl scoatem din coada de procesoare disponibile
        g << urmP << endl; // Procesorul asignat

    }
    f.close();
    g.close();

    return 0;
}

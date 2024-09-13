#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ifstream fin("bleach.in");
    ofstream fout("bleach.out");

    int N, K;
    fin >> N >> K; // Numărul de inamici și valoarea K

    // Min-heap pentru a stoca puterile inamicilor
    priority_queue<int, vector<int>, greater<int>> enemies;

    // Puterile inamicilor
    for (int i = 0; i < N; ++i) {
        int power;
        fin >> power;
        enemies.push(power);
    }

    long long neededPower = 0; // Puterea minimă inițială necesară pentru Ichigo
    long long ichigoPower = 0; // Puterea curentă a lui Ichigo

    // Procesăm toți inamicii din heap
    while (!enemies.empty()) {
        int enemyPower = enemies.top(); // Luăm puterea inamicului cel mai slab
        enemies.pop();

        // Verificăm dacă Ichigo are suficientă putere pentru a învinge inamicul
        if (ichigoPower >= enemyPower) {
            ichigoPower += enemyPower; // Ichigo absoarbe puterea inamicului
        } else {
            // Dacă Ichigo nu are suficientă putere, calculăm puterea necesară suplimentară
            neededPower += enemyPower - ichigoPower;
            ichigoPower = enemyPower * 2; // Ichigo absoarbe puterea inamicului și o dublează
        }
    }

    fout << neededPower << '\n';

    fin.close();
    fout.close();

    return 0;
}

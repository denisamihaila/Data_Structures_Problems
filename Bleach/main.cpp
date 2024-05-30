#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

int main() {

    ifstream fin("bleach.in");
    ofstream fout("bleach.out");

    int N, K;
    fin >> N >> K;

    priority_queue<int, vector<int>, greater<int>> enemies; //min heap cu puterile inamicilor

    for (int i = 0; i < N; ++i) {
        int power;
        fin >> power;
        enemies.push(power);
    }

    long long neededPower = 0;
    long long ichigoPower = 0;
    while (!enemies.empty())
        {
        int enemyPower = enemies.top(); //inamicul cel mai slab
        enemies.pop();

        if (ichigoPower >= enemyPower) {
            ichigoPower += enemyPower;
        } else {
            neededPower += enemyPower - ichigoPower;
            ichigoPower = enemyPower * 2;
        }
    }

    fout << neededPower << '\n';

    fin.close();
    fout.close();

    return 0;
}

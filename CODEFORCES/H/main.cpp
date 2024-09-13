#include <iostream>
#include <algorithm>
using namespace std;

// Structura pentru un nod din trie
struct Trienode {
    Trienode *bit1, *bit0;
    long long value;

    Trienode() {
        bit1 = bit0 = nullptr; // Inițializăm pointerii la null
    }
};

// Structura pentru trie
struct Trie {
    Trienode *root;

    Trie() {
        root = new Trienode;
        root->value = (1LL << 30); // Inițializăm valoarea nodului rădăcină cu 2^30
    }

    // Funcție pentru a insera un cuvânt (reprezentare binară a unui număr) în trie
    void insert(string word, Trienode *crt) {
        if (word == "")
            return;

        if (word[0] == '0' && crt->bit0 == nullptr)
            crt->bit0 = new Trienode, crt->bit0->value = crt->value / 2;
        if (word[0] == '1' && crt->bit1 == nullptr)
            crt->bit1 = new Trienode, crt->bit1->value = crt->value / 2;

        if (word[0] == '1') {
            word.erase(word.begin());
            insert(word, crt->bit1);
        } else {
            word.erase(word.begin());
            insert(word, crt->bit0);
        }
    }

    // Funcție pentru a căuta un cuvânt (reprezentare binară a unui număr) în trie
    long long search(string word, Trienode *crt) {
        if (word[0] == '0' && crt->bit1 != nullptr) {
            word.erase(word.begin());
            return crt->bit1->value + search(word, crt->bit1);
        }

        if (word[0] == '1' && crt->bit0 != nullptr) {
            word.erase(word.begin());
            return crt->bit0->value + search(word, crt->bit0);
        }

        if (word[0] == '0' && crt->bit0 != nullptr) {
            word.erase(word.begin());
            return search(word, crt->bit0);
        }

        if (word[0] == '1' && crt->bit1 != nullptr) {
            word.erase(word.begin());
            return search(word, crt->bit1);
        }
        return 0;
    }
} trie;

int v[200005]; // Vector pentru a stoca valorile din array
pair<int, int> maxi[200005]; // Vector pentru a stoca perechi de valori maxime și secunde maxime

// Funcție pentru a converti un număr într-un cuvânt binar de 30 de biți
string word(int val) {
    string ret;
    for (int i = 0; i <= 29; i++)
        if (val & (1 << i))
            ret.push_back('1');
        else ret.push_back('0');

    for (int i = 0; ret.size() != 30; i++)
        ret.push_back('0');

    reverse(ret.begin(), ret.end());
    return ret;
}

int main() {
    int N;
    cin >> N; // Citim dimensiunea array-ului
    for (int i = 1; i <= N; i++)
        cin >> v[i]; // Citim valorile array-ului

    // Calculăm valorile maxime și secunde maxime pentru fiecare poziție din array începând de la sfârșit
    for (int i = N; i >= 1; i--) {
        maxi[i] = maxi[i + 1];
        if (v[i] > maxi[i + 1].first)
            maxi[i].first = v[i], maxi[i].second = maxi[i + 1].first;
        else if (v[i] > maxi[i + 1].second)
            maxi[i].second = v[i];
    }

    long long ans = 0;
    trie.insert(word(v[1]), trie.root); // Inserăm prima valoare în trie
    for (int i = 2; i <= N - 2; i++) { // Iterăm prin array începând de la al doilea element până la N-2
        long long val = trie.search(word(v[i]), trie.root); // Căutăm valoarea în trie
        ans = max(ans, val * ((long long)maxi[i + 1].first + (long long)maxi[i + 1].second)); // Calculăm valoarea maximă
        trie.insert(word(v[i]), trie.root); // Inserăm valoarea curentă în trie
    }

    cout << ans; // Afișăm rezultatul final
}

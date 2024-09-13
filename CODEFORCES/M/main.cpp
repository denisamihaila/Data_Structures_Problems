#include <iostream>
#include <vector>

using namespace std;

int main() {
    unsigned long long cnt = 0; // Variabilă pentru a număra substrings interesante
    int N; // Numărul de elemente din vector
    cin >> N; // Citim numărul de elemente
    vector<int> nr(N); // Vector pentru stocarea elementelor
    vector<int> min_left(N); // Vector pentru stocarea indexului minimului din stânga pentru fiecare poziție

    // Citim elementele și calculăm minimul pentru fiecare poziție
    for (int i = 0; i < N; i++) {
        cin >> nr[i];
        if (i == 0)
            min_left[i] = i; // Primul element este minimul pentru el însuși
        else if (nr[i - 1] < nr[i])
            min_left[i] = i - 1; // Elementul precedent este minim pentru această poziție
        else {
            int index = min_left[i - 1]; // Indexul minimului precedent
            // Căutăm minimul în stânga până când găsim un element mai mic sau ajungem la începutul vectorului
            while (index > 0 && nr[index] >= nr[i]) {
                if (nr[index] >= nr[i])
                    index = min_left[index] - 1;
                else
                    break;
            }
            if (nr[index] < nr[i])
                index++;
            if (index < 0)
                index = 0;
            min_left[i] = index;
        }
    }

    int l = 0;
    // Calculăm numărul de substrings interesante
    while (l < N) {
        cnt += l - min_left[l]; // Adăugăm substrings care se termină la poziția `l`
        for (int i = 1; i < l - min_left[l]; i++) {
            if (l + i < N && min_left[l + i] > l) {
                cnt += l - min_left[l] - i; // Adăugăm substrings care continuă după poziția `l`
            } else {
                break;
            }
        }
        l++;
    }
    cout << cnt; // Afișăm numărul de substrings interesante
}

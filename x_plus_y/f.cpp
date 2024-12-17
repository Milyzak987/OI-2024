#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

// Funkcja odtwarzająca względne wartości ciągu na podstawie różnic |a[i+1] - a[i]|
vector<int> reconstructSequence(const vector<int>& diffs) {
    vector<int> sequence(diffs.size() + 1, 0);
    for (int i = 1; i < sequence.size(); ++i) {
        sequence[i] = sequence[i - 1] + diffs[i - 1];
    }
    return sequence;
}

// Funkcja znajdująca indeks najmniejszej liczby na podstawie różnic w trójelementowych oknach
int findMinIndex(const vector<int>& sequence, const vector<int>& maxMinDiffs) {
    int minIndex = -1;
    int minValue = INT_MAX;

    for (int i = 0; i + 2 < sequence.size(); ++i) {
        int maxVal = max({sequence[i], sequence[i + 1], sequence[i + 2]});
        int minVal = min({sequence[i], sequence[i + 1], sequence[i + 2]});
        if (maxVal - minVal == maxMinDiffs[i]) {
            // Jeśli różnica pasuje, sprawdzamy najmniejszy element
            if (minVal < minValue) {
                minValue = minVal;
                minIndex = i + (sequence[i] == minVal ? 0 : (sequence[i + 1] == minVal ? 1 : 2));
            }
        }
    }
    return minIndex;
}

int main() {
    // Przykładowe dane wejściowe
    vector<int> diffs = {4, 5, 6, 3}; // |a[i+1] - a[i]|
    vector<int> maxMinDiffs = {5, 6, 6}; // różnice max - min w oknach 3-elementowych

    // Odtwórz względne wartości ciągu
    vector<int> sequence = reconstructSequence(diffs);

    // Znajdź indeks najmniejszej liczby
    int minIndex = findMinIndex(sequence, maxMinDiffs);

    // Wynik
    if (minIndex != -1) {
        cout << "Indeks najmniejszej liczby: " << minIndex << endl;
    } else {
        cout << "Nie można jednoznacznie określić najmniejszej liczby." << endl;
    }

    return 0;
}
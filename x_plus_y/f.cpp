#include <iostream>
#include <vector>
#include <numeric> // dla std::partial_sum

int findIndexOfMinimum(const std::vector<int>& differences) {
    int n = differences.size() + 1; // liczba elementów ciągu
    std::vector<int> values(n, 0); // ciąg wartości względnych

    // Odtwarzamy wartości względne
    for (int i = 1; i < n; ++i) {
        values[i] = values[i - 1] + differences[i - 1];
    }

    // Znajdujemy indeks najmniejszej wartości
    int minIndex = 0;
    int minValue = values[0];

    for (int i = 1; i < n; ++i) {
        if (values[i] < minValue) {
            minValue = values[i];
            minIndex = i;
        }
    }

    return minIndex; // indeks najmniejszej liczby
}

int main() {
    // Przykład danych wejściowych
    std::vector<int> differences = {2, -3, 1, -4, 3}; // różnice między kolejnymi elementami ciągu

    // Wyznaczenie indeksu najmniejszego elementu
    int minIndex = findIndexOfMinimum(differences);

    std::cout << "Indeks najmniejszej liczby w ciagu: " << minIndex << std::endl;

    return 0;
}
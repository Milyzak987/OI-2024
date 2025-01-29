#include "szylib.h"
#include <vector>
#include <string>

using namespace std;

// Funkcja kodowania wiadomości
void Zaszyfruj(int X, int Y, int N, string S) {
    vector<vector<int>> T(8, vector<int>(8, 0)); // Tablica do przechowywania bitów
    int row = 0, col = 0;

    // Pomocnicza funkcja do znalezienia następnego wolnego pola (omija X i Y)
    auto next_valid = [&]() {
        do {
            if (++col == 8) {
                col = 0;
                ++row;
            }
        } while (row == X || col == Y);
    };

    // Zakodowanie wiadomości
    for (int i = 0; i < N; ++i) {
        T[row][col] = (S[i] == 'B' ? 1 : 0);
        next_valid();
    }

    // Obliczenie sum kontrolnych
    vector<int> row_parity(8, 0), col_parity(8, 0);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            row_parity[i] ^= T[i][j];
            col_parity[j] ^= T[i][j];
        }
    }

    // Wpisanie bitów parzystości do uszkodzonych miejsc
    T[X][Y] = 0; // Możemy wpisać cokolwiek, bo to i tak się zepsuje
    for (int i = 0; i < 8; ++i) {
        if (i != X) T[i][Y] = row_parity[i]; // Parzystość wiersza
        if (i != Y) T[X][i] = col_parity[i]; // Parzystość kolumny
    }

    // Ustawienie kryształów
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i != X && j != Y) {
                Oznacz(i, j, T[i][j]);
            }
        }
    }
}

// Funkcja dekodowania wiadomości
string Odszyfruj(int N, vector<vector<int>> T) {
    int X = -1, Y = -1;

    // Znalezienie X i Y przez analizę sum kontrolnych
    vector<int> row_parity(8, 0), col_parity(8, 0);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            row_parity[i] ^= T[i][j];
            col_parity[j] ^= T[i][j];
        }
    }

    // Uszkodzony wiersz X → jedyny, gdzie suma parzystości się nie zgadza
    for (int i = 0; i < 8; ++i) {
        if (row_parity[i] != 0) {
            X = i;
            break;
        }
    }

    // Uszkodzona kolumna Y → jedyna, gdzie suma parzystości się nie zgadza
    for (int j = 0; j < 8; ++j) {
        if (col_parity[j] != 0) {
            Y = j;
            break;
        }
    }

    // Odczytanie wiadomości
    string result;
    int row = 0, col = 0;
    auto next_valid = [&]() {
        do {
            if (++col == 8) {
                col = 0;
                ++row;
            }
        } while (row == X || col == Y);
    };

    for (int i = 0; i < N; ++i) {
        result += (T[row][col] == 1 ? 'B' : 'A');
        next_valid();
    }

    return result;
}
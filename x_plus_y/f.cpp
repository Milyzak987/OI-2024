#include <iostream>

// Funkcja obliczająca wartość kombinacji C(n, k)
long long combination(int n, int k) {
    if (k > n) return 0;
    long long result = 1;
    for (int i = 1; i <= k; ++i) {
        result = result * (n - i + 1) / i;
    }
    return result;
}

int main() {
    int n;
    std::cout << "Podaj wartość n: ";
    std::cin >> n;

    if (n < 2) {
        std::cout << "Nie można wybrać 3 liczb z przedziału [0, n] dla n < 2." << std::endl;
    } else {
        long long ways = combination(n + 1, 3);
        std::cout << "Liczba sposobów wyboru 3 liczb z przedziału [0, " << n << "] wynosi: " << ways << std::endl;
    }

    return 0;
}
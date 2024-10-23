#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <filesystem>

int main() {
    // Zasięg dla liczb: od 10^999999 do 10^1000000 - 1
    const int num_tests = 10000;  // Liczba plików z testami
    const std::string folder = "testy4"; // Folder docelowy

    // Sprawdzenie, czy folder istnieje, jeśli nie - utworzenie
    std::filesystem::create_directory(folder);

    // Generowanie liczb losowych i zapis do plików
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);   // Liczby losowe w zakresie 0-9 dla pozostałych cyfr
    std::uniform_int_distribution<> first_digit_dis(1, 9);  // Pierwsza cyfra w zakresie 1-9

    for (int i = 1; i <= num_tests; ++i) {
        std::ofstream file(folder + "/test" + std::to_string(i) + ".in");
        if (!file.is_open()) {
            std::cerr << "Nie udało się otworzyć pliku test" << i << ".in" << std::endl;
            return 1;
        }

        // Pierwsza cyfra musi być różna od zera, czyli w zakresie 1-9
        file << first_digit_dis(gen);

        // Generowanie pozostałych 999999 cyfr
        for (int j = 2; j < 1000000; ++j) {
            file << dis(gen);
        }

        file.close();
    }

    std::cout << "Wygenerowano 10 000 liczb losowych i zapisano do folderu " << folder << std::endl;
    return 0;
}

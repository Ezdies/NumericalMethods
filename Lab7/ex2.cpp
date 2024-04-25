#include <cmath>
#include <iostream>
#include <chrono>
#include <iomanip>

double maclaurin_sin(double x, double eps) {
    double result = 0;
    int i = 0;
    double term = x;

    while (true) {
        result += term;
        if (std::abs(term) < eps) {
            break;
        }
        i++;
        term *= -x * x / ((2 * i + 1) * (2 * i)); 
    }
    return result;
}

int main() {
    std::cout << "Moja implementacja szeregu Maclaurina dla funkcji sin:\n";
    auto start1 = std::chrono::high_resolution_clock::now();
    std::cout << maclaurin_sin(5, 0.0001) << "\n";
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration<double>(stop1 - start1);
    std::cout << "Czas to: " << std::fixed << std::setprecision(9) << time1.count() << "s.\n";
    
    std::cout << "Wartość funkcji sin z użyciem funkcji bibliotecznej:\n";
    auto start2 = std::chrono::high_resolution_clock::now();
    std::cout << std::sin(5) << "\n";
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration<double>(stop2 - start2);
    std::cout << "Czas to: " << std::fixed << std::setprecision(9) << time2.count() << "s.\n";
    return 0;
}

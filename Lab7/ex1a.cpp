#include <cmath>
#include <iostream>
#include <chrono>
#include <iomanip>

double factorial(int n) {
    if (n == 0) return 1.0;
    double result = 1.0;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

double maclaurin_exp(double x, double eps) {
    double result = 0;
    int i = 0;
    double term = 0.0;

    while (true) {
        term = std::pow(x, i) / factorial(i);
        result += term;
        if (std::abs(term) < eps) {
            break;
        }
        i++;
    }
    return result;
}


int main() {
    std::cout << "Moja implementacja szeregu Maclaurina dla funkcji eksponencjalnej:\n";
    auto start1 = std::chrono::high_resolution_clock::now();
    std::cout << maclaurin_exp(5, 0.0001) << "\n";
    auto stop1 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration<double>(stop1 - start1);
    std::cout << "Czas to: " << std::fixed << std::setprecision(9) << time1.count() << "s.\n";
    
    std::cout << "Wartość funkcji eksponencjalnej z użyciem funkcji bibliotecznej:\n";
    auto start2 = std::chrono::high_resolution_clock::now();
    std::cout << std::exp(5) << "\n";
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto time2 = std::chrono::duration<double>(stop2 - start2);
    std::cout << "Czas to: " << std::fixed << std::setprecision(9) << time2.count() << "s.\n";
    return 0;
}
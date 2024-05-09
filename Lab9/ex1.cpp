#include <iostream>
#include <cmath>
#include <functional>

double f_a(double x) {
    return 2 * pow(x, 2) + 2;
}

double df_a(double x) {
    return 4 * x;
}

double f_b(double x) {
    return 2 * pow(x, 4) - pow(x, 2) + 3 * x - 7;
}

double df_b(double x) {
    return 8 * pow(x, 3) - 2 * x + 3;
}

double f_c(double x) {
    return pow(x, 2) * exp(x);
}

double df_c(double x) {
    return (2 * x + pow(x, 2)) * exp(x);
}

//f'(x) = (f(x) - f(x - h)) / h
double backwards_estimation(std::function<double(double)> f, double x, double h) {
    return (f(x) - f(x - h)) / h;
}

double newton_estimation(std::function<double(double)> f, double x, double h) {
    return (f(x+h) - f(x)) / h;
}

double central_estimation(std::function<double(double)> f, double x, double h) {
    return (f(x+h) - f(x-h)) / (2 * h);
}

double relative_error(double estimated, double exact) {
    return std::abs((estimated - exact) / std::abs(exact));
}





int main() {
    double x = 3;
    double h = 0.01;

    // Funkcja f_a(x)
    double exact_a = df_a(x);
    double backward_estimate_a = backwards_estimation(f_a, x, h);
    double newton_estimate_a = newton_estimation(f_a, x, h);
    double central_estimate_a = central_estimation(f_a, x, h);
    double error_backwards_a = relative_error(backward_estimate_a, exact_a);
    double error_newton_a = relative_error(newton_estimate_a, exact_a);
    double error_central_a = relative_error(central_estimate_a, exact_a);
    std::cout << "Dokładna dla f_a: " << exact_a << "\n";
    std::cout << "Wsteczna dla f_a: " << backward_estimate_a << "\n";
    std::cout << "Błąd dla estymacji wstecznej dla f_a: " << error_backwards_a << "\n";
    std::cout << "Newtona dla f_a: " << newton_estimate_a << "\n";
    std::cout << "Błąd dla estymacji Newtona dla f_a: " << error_newton_a << "\n";
    std::cout << "Centralna dla f_a: " << central_estimate_a << "\n";
    std::cout << "Błąd dla estymacji centralnej dla f_a: " << error_central_a << "\n\n";

    // Funkcja f_b(x)
    double exact_b = df_b(x);
    double backward_estimate_b = backwards_estimation(f_b, x, h);
    double newton_estimate_b = newton_estimation(f_b, x, h);
    double central_estimate_b = central_estimation(f_b, x, h);
    double error_backwards_b = relative_error(backward_estimate_b, exact_b);
    double error_newton_b = relative_error(newton_estimate_b, exact_b);
    double error_central_b = relative_error(central_estimate_b, exact_b);
    std::cout << "Dokładna dla f_b: " << exact_b << "\n";
    std::cout << "Wsteczna dla f_b: " << backward_estimate_b << "\n";
    std::cout << "Błąd dla estymacji wstecznej dla f_b: " << error_backwards_b << "\n";
    std::cout << "Newtona dla f_b: " << newton_estimate_b << "\n";
    std::cout << "Błąd dla estymacji Newtona dla f_b: " << error_newton_b << "\n";
    std::cout << "Centralna dla f_b: " << central_estimate_b << "\n";
    std::cout << "Błąd dla estymacji centralnej dla f_b: " << error_central_b << "\n\n";

    // Funkcja f_c(x)
    double exact_c = df_c(x);
    double backward_estimate_c = backwards_estimation(f_c, x, h);
    double newton_estimate_c = newton_estimation(f_c, x, h);
    double central_estimate_c = central_estimation(f_c, x, h);
    double error_backwards_c = relative_error(backward_estimate_c, exact_c);
    double error_newton_c = relative_error(newton_estimate_c, exact_c);
    double error_central_c = relative_error(central_estimate_c, exact_c);
    std::cout << "Dokładna dla f_c: " << exact_c << "\n";
    std::cout << "Wsteczna dla f_c: " << backward_estimate_c << "\n";
    std::cout << "Błąd dla estymacji wstecznej dla f_c: " << error_backwards_c << "\n";
    std::cout << "Newtona dla f_c: " << newton_estimate_c << "\n";
    std::cout << "Błąd dla estymacji Newtona dla f_c: " << error_newton_c << "\n";
    std::cout << "Centralna dla f_c: " << central_estimate_c << "\n";
    std::cout << "Błąd dla estymacji centralnej dla f_c: " << error_central_c << "\n";

    return 0;
}


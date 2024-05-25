#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

const double TOLERANCE = 1e-12;
const int MAX_ITERATIONS = 1000;

using Complex = std::complex<double>;

Complex horner(const std::vector<Complex>& coefficients, Complex z) {
    Complex p = coefficients[0]; 

    for (int i = 1; i < coefficients.size(); ++i) {
        p = p * z + coefficients[i];
    }

    return p;
}

Complex first_derivative(const std::vector<Complex>& coefficients, Complex z) {
    if (coefficients.size() == 1) return 0.0;

    Complex p = Complex(coefficients[0]) * Complex((coefficients.size() - 1)); 

    for (int i = 1; i < coefficients.size() - 1; ++i) {
        p = p * z + Complex(coefficients[i]) * Complex((coefficients.size() - 1 - i));
    }

    return p;
}

Complex second_derivative(const std::vector<Complex>& coefficients, Complex z) {
    if (coefficients.size() <= 2) return 0.0;

    Complex p = Complex(coefficients[0]) * Complex((coefficients.size() - 1)) * Complex((coefficients.size() - 2)); 

    for (int i = 1; i < coefficients.size() - 2; ++i) {
        p = p * z + Complex(coefficients[i]) * Complex((coefficients.size() - 1 - i)) * Complex((coefficients.size() - 2 - i));
    }

    return p;
}

Complex laguerre(const std::vector<Complex>& coefficients, Complex z0) {
    int n = coefficients.size() - 1;
    Complex z = z0;

    for (int iter = 0; iter < MAX_ITERATIONS; ++iter) {
        Complex P = horner(coefficients, z);
        if (std::abs(P) < TOLERANCE) {
            return z;
        }
        
        Complex G = first_derivative(coefficients, z) / P;
        Complex H = G * G - second_derivative(coefficients, z) / P;
        Complex denom1 = G + std::sqrt(Complex(n - 1) * (H * Complex(n) - G * G));
        Complex denom2 = G - std::sqrt(Complex(n - 1) * (H * Complex(n) - G * G));
        
        Complex a = (std::abs(denom1) > std::abs(denom2)) ? denom1 : denom2;
        z -= Complex(n) / a;
    }

    return z;
}

std::vector<Complex> find_all_roots(const std::vector<Complex>& coefficients) {
    std::vector<Complex> roots;
    std::vector<Complex> reduced_coefficients = coefficients;
    int n = coefficients.size() - 1;

    for (int i = 0; i < n; ++i) {
        Complex root = laguerre(reduced_coefficients, Complex(0.0, 0.0));
        roots.push_back(root);

        // Synthetic division to deflate the polynomial
        std::vector<Complex> new_coefficients(n - i);
        new_coefficients[0] = reduced_coefficients[0];
        for (int j = 1; j < n - i; ++j) {
            new_coefficients[j] = reduced_coefficients[j] + root * new_coefficients[j - 1];
        }
        reduced_coefficients = new_coefficients;
    }

    return roots;
}

int main() {
    std::vector<Complex> coefficients1 = {1, -6, 11, -6};
    double z = 1.0;

    auto result1 = horner(coefficients1, z);
    auto first = first_derivative(coefficients1, z);
    auto second = second_derivative(coefficients1, z);

    std::cout << "Wartość wielomianu dla w(x) = x3 −6x2 +11x−6, x = " << z << " wynosi " << result1 << std::endl;
    std::cout << "First derivative: " << first << '\n';
    std::cout << "Second derivative: " << second << '\n';

    std::vector<Complex> roots = find_all_roots(coefficients1);

    
    std::cout << "Pierwiastki wielomianu:\n";
    for (const Complex& root : roots) {
        std::cout << root << std::endl;
    }


    std::vector<Complex> coefficients2 = {1, -6, 11, -1}; 

    auto result2 = horner(coefficients2, z);
    auto first2 = first_derivative(coefficients2, z);
    auto second2 = second_derivative(coefficients2, z);
    std::vector<Complex> roots2 = find_all_roots(coefficients1);

    std::cout << "w(x) = x3 − 6x2 +11x − 1, x = " << z << " wynosi " << result2 << std::endl;
    std::cout << "First derivative: " << first2 << '\n';
    std::cout << "Second derivative: " << second2 << '\n';

     std::cout << "Pierwiastki wielomianu:\n";
    for (const Complex& root : roots) {
        std::cout << root << std::endl;
    }


    return 0;
}

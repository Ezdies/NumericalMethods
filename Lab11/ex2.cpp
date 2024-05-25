#include <iostream>
#include <vector>

// Mnoży dwa wielomiany i zwraca wynikowy wielomian
std::vector<double> multiplyPolynomials(const std::vector<double>& poly1, const std::vector<double>& poly2) {
    std::vector<double> result(poly1.size() + poly2.size() - 1, 0.0);

    for (size_t i = 0; i < poly1.size(); ++i) {
        for (size_t j = 0; j < poly2.size(); ++j) {
            result[i + j] += poly1[i] * poly2[j];
        }
    }

    return result;
}

// Wyznacza współczynniki wielomianu mając dane jego miejsca zerowe
std::vector<double> findCoefficients(const std::vector<double>& roots) {
    // Rozpoczynamy od wielomianu (z - roots[0])
    std::vector<double> coefficients = {-roots[0], 1};

    // Mnożymy kolejne (z - roots[i])
    for (size_t i = 1; i < roots.size(); ++i) {
        std::vector<double> nextPoly = {-roots[i], 1};
        coefficients = multiplyPolynomials(coefficients, nextPoly);
    }

    return coefficients;
}

// Funkcja Hornera do obliczania wartości wielomianu
double horner(const std::vector<double>& coefficients, double z) {
    double p = coefficients[0];
    
    for (size_t i = 1; i < coefficients.size(); ++i) {
        p = p * z + coefficients[i];
    }
    
    return p;
}

int main() {
    // Przykładowe miejsca zerowe wielomianu
    std::vector<double> roots = {0};

    // Wyznaczanie współczynników wielomianu
    std::vector<double> coefficients = findCoefficients(roots);

    // Wyświetlenie wyznaczonych współczynników
    std::cout << "Współczynniki wielomianu: ";
    for (double coeff : coefficients) {
        std::cout << coeff << " ";
    }
    std::cout << std::endl;

    // Obliczanie wartości wielomianu dla z = 1.0
    double z = 1.0;
    double result = horner(coefficients, z);

    std::cout << "Wartość wielomianu dla z = " << z << " wynosi " << result << std::endl;

    return 0;
}

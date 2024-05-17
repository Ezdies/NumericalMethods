#include <iostream>
#include <functional>
#include <cmath>
#include <iomanip>


double dx_a(double x) {
    return x * x;
}

double error(double estimated, double exact) {
    return std::abs((estimated - exact) / std::abs(exact));
}

double rectangleIntegral(double a, double b, int n, std::function<double(double)> f){
    double h = (b - a) / (n * 1.0);
    double sumResult = 0.0;
    double result = 0;

    for(int i = 0; i < n; i++){
        sumResult += f(a + (h) * (i + 0.5));

    } 
    return h * sumResult;
}

double trapezoidIntegral(double a, double b, int n, std::function<double(double)> f) {
    double h = (b - a) / (n * 1.0);
    double sumResult = 0.0;

    sumResult += 0.5 * f(a);
    sumResult += 0.5 * f(b);

    for (int i = 1; i < n; i++) {
        double x = a + h * i;
        sumResult += f(x);
    }
    return h * sumResult;
}

double dx_b(double x){
    return cos(x);

}

double dx_c(double x){
    return 1/x;
}

int main(){
    double a1 = 0;
    double b1 = 1;
    int n = 100;

    std::cout << std::fixed << std::setprecision(10);

    double result_a_rect = rectangleIntegral(a1, b1, n, dx_a);
    std::cout << "Wartość całki x^2 metodą prostokątów to: " << result_a_rect << std::endl;
    std::cout << "Błąd względny: " << error(1.0/3.0, result_a_rect) << std::endl;

    double result_a_trap = trapezoidIntegral(a1, b1, n, dx_a);
    std::cout << "Wartość całki x^2 metodą trapezów to: " << result_a_trap << std::endl;
    std::cout << "Błąd względny: " << error(1.0/3.0, result_a_trap) << std::endl;

    double a2 = 0;
    double b2 = M_PI / 2;

    double result_b_rect = rectangleIntegral(a2, b2, n, dx_b);
    std::cout << "Wartość całki cos(x) metodą prostokątów to: " << result_b_rect << std::endl;
    std::cout << "Błąd względny: " << error(1, result_b_rect) << std::endl;

    double result_b_trap = trapezoidIntegral(a2, b2, n, dx_b);
    std::cout << "Wartość całki cos(x) metodą trapezów to: " << result_b_trap << std::endl;
    std::cout << "Błąd względny: " << error(1, result_b_trap) << std::endl;
    
    double a3 = M_E;
    double b3 = M_E * M_E;

    double result_c_rect = rectangleIntegral(a3, b3, n, dx_c);
    std::cout << "Wartość całki 1/x metodą prostokątów to: " << result_c_rect << std::endl;
    std::cout << "Błąd względny: " << error(1, result_c_rect) << std::endl;

    double result_c_trap = trapezoidIntegral(a3, b3, n, dx_c);
    std::cout << "Wartość całki 1/x metodą trapezów to: " << result_c_trap << std::endl;
    std::cout << "Błąd względny: " << error(1, result_c_trap) << std::endl;

    return 0;
}
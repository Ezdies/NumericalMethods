#include <iostream>
#include <vector>

double calculateA(const std::vector<double> &x, const std::vector<double> &y) {
    double result = 0.0;
    int n = x.size();

    for(int i = 0; i < n; i++){
        result += x[i] * y[i];
    }
    return result;
}

double calculateB(const std::vector<double> &x) {
    double result = 0.0;
    int n = x.size();

    for(int i = 0; i < n; i++){
        result += x[i];
    }
    return result;
}

double calculateC(const std::vector<double> &y) {
    double result = 0.0;
    int n = y.size();

    for(int i = 0; i < n; i++){
        result += y[i];
    }
    return result;
}

double calculateD(const std::vector<double> &x) {
    double result = 0.0;
    int n = x.size();

    for(int i = 0; i < n; i++){
        result += x[i] * x[i];
    }
    return result;
}

int main() {
    std::vector<double> x = {1.1, 1.4, 1.8, 2.5, 2.8, 3.0};
    std::vector<double> y = {2.1, 2.3, 2.9, 3.2, 3.6, 4.2};

    double A = calculateA(x, y);
    double B = calculateB(x);
    double C = calculateC(y);
    double D = calculateD(x);

    int n = x.size();

    double a = (n * A - B * C) / (n * D - B * B);
    double b = (C * D - A * B) / (n * D - B * B);

    std::cout << "a = " << a << " b = " << b << std::endl;

    return 0;
}

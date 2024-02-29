#include <iostream>
#include <vector>
#include <cmath>

void gill_moller(const std::vector<float> &numbers, int i, float &ss, float &pp, float &s_old) {
    float s = ss, p = pp; 
    s = s_old + numbers[i];
    p = p + (numbers[i] - (s - s_old));
    s_old = s;
    ss = s;
    pp = p;
}

// Funkcja realizująca algorytm Kahana
float kahan_sum(const std::vector<float> &arr) {
    float s = 0, e = 0;
    for (int i = 0; i < arr.size(); i++) {
        float tmp = s;
        float tmp2 = arr[i] + e;
        s = tmp + tmp2;
        e = (tmp - s) + tmp2;
    }
    return s;
}

int main() {
    std::vector<float> numbers;

    int m = pow(2, 5);
    int n = pow(2, 20);

    float sum = 0;
    float number = 0;
    float ss = 0;
    float pp = 0;
    float s_old = 0; // Initialize s_old

    for(int i = 0; i < n; i++) {
        number = 1.0/((i % m + 1) * (i % m + 2));
        sum += number;
        numbers.push_back(number);
        gill_moller(numbers, i, ss, pp, s_old);
    }

    float gm = ss + pp;

    for(const auto &number : numbers) {
        std::cout << number << " ";
    }

    float precise = n / (m + 1);
    std::cout << "\n";
    std::cout << "Suma: " << sum << "\n";
    std::cout << "Dokladny: " << precise << "\n"; 
    std::cout << "Blad wzgledny normalny: " << fabs(sum - precise)/precise << '\n';
    std::cout << "gm: " << gm << "\n";
    std::cout << "Blad wzgledny gm: " << fabs(precise - gm)/gm << '\n';
    std::cout << "Kahan sum: " << kahan_sum(numbers) << '\n';
    std::cout << "Blad wzgledny kahan sum: " << fabs(precise - gm)/gm << '\n';

    return 0;
}

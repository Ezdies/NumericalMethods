#include <iostream>
#include <vector>
#include <cmath>

float default_sum(std::vector<float> &numbers)
{
    const int m = pow(2, 5);
    const int n = pow(2, 20);

    float sum = 0;
    float number = 0;

    for (int i = 0; i < n; i++)
    {
        number = 1.0 / ((i % m + 1) * (i % m + 2));
        sum += number;
        numbers.push_back(number);
    }

    return sum;
}

float precise_sum(){

    const int m = pow(2, 5);
    const int n = pow(2, 20);

    return n / (m + 1);
}

float gill_moller(const std::vector<float> &numbers)
{
    float s = 0;
    float p = 0;
    float s_old = 0;
    int n = numbers.size();

    for (int i = 0; i < n; i++)
    {
        s = s_old + numbers[i];
        p = p + (numbers[i] - (s - s_old));
        s_old = s;
    }

    return s + p;
}

float kahan_sum(const std::vector<float> &arr)
{
    float s = 0, e = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        float tmp = s;
        float tmp2 = arr[i] + e;
        s = tmp + tmp2;
        e = (tmp - s) + tmp2;
    }
    return s;
}

int main()
{
    std::vector<float> numbers;
    
    float precise = precise_sum();
    float normal = default_sum(numbers);
    float gm = gill_moller(numbers);
    float kahan = kahan_sum(numbers);

    std::cout << "\n";
    std::cout << "Suma: " << normal << "\n";
    std::cout << "Dokladny: " << precise << "\n";
    std::cout << "Blad wzgledny normalny: " << fabs(normal - precise) / precise << '\n';
    std::cout << "gm: " << gm << "\n";
    std::cout << "Blad wzgledny gm: " << fabs(precise - gm) / gm << '\n';
    std::cout << "Kahan sum: " << kahan_sum(numbers) << '\n';
    std::cout << "Blad wzgledny kahan sum: " << fabs(precise - kahan) / kahan << '\n';

    return 0;
}

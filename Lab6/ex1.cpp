#include <iostream>
#include <vector>

float lagrange_interpolation(const std::vector<float>& x_values, const std::vector<float>& y_values, float x) {
    float result = 0;
    int n = x_values.size();

    for (int i = 0; i < n; i++) {
        float tmp = y_values[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                tmp *= (x - x_values[j]) / (x_values[i] - x_values[j]);
            }
        }
        result += tmp;
    }
    return result;
}

//ilorazy różnicowe Difference quotient
//f[xi]=f(xi)= yi
//f[xi,x+1]= ((yi+1)-yi)/xi+1-xi


//float newton_interpolation

#include <vector>

float difference_quotient(int k, const std::vector<float>& x_values, const std::vector<float>& y_values){
    int n = x_values.size();
    float result = 0;
    std::vector<float> new_values = y_values; 

    for(int j = 1; j <= k; j++){ 
        for(int i = n - 1; i >= j; i--) {
            new_values[i] = (new_values[i] - new_values[i-1]) / (x_values[i] - x_values[i-j]);
        }
    }
    result = new_values[k];
    return result;
}

float newton_interpolation(float x, const std::vector<float>& x_values, const std::vector<float>& y_values){
    int n = x_values.size();
    float result = y_values[0];

    for(int i = 1; i < n; i++){
        float tmp = difference_quotient(i, x_values, y_values);
        for(int j = 0; j < i; j++){
            tmp *= (x - x_values[j]);
        }
        result += tmp;
    }

    return result;
}

float spline_interpolation(float x, const std::vector<float>& x_values, const std::vector<float>& y_values){
    int n = x_values.size();
    float res = 0;
    for(int i = 0; i < n - 1; i++){
        if (x >= x_values[i] && x <= x_values[i + 1]) {
            res = y_values[i] + (y_values[i + 1] - y_values[i]) / (x_values[i + 1] - x_values[i]) * (x - x_values[i]);
            break;
        }
    }
    return res;
}



int main() {
   
    std::vector<float> x_values = {-1.4,-1, 0,1, 2, 2.2, 2.5, 2.7, 3, 3.2};
    std::vector<float> y_values = {11.95,1.85,1,0.54,0.17,0.31,0.57,0.76,0.97,0.99};

    float x = 1.5;
    float interpolated_value = lagrange_interpolation(x_values, y_values, x);
    float newton_value = newton_interpolation(x, x_values, y_values);
    float linear_spline_value = spline_interpolation(x, x_values, y_values);

    std::cout << interpolated_value << std::endl;
    std::cout << newton_value << std::endl;
    std::cout << linear_spline_value << std::endl;

    return 0;
}

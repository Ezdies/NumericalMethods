//jacobi
//xi^(k)=(bi-sum(aij*xj^(k-1)))/aii

#include <iostream>
#include <vector>

void print(std::vector<float> vec){
    for (const float &val : vec) {
        std::cout << val << "\n";
    }
}

std::vector<float> jacobi(std::vector<std::vector<float>>& A, std::vector<float>& b, std::vector<float>& x) {
    int n = A.size();
    int k = 100;
    std::vector<float> temp_x(n, 0);

    for (int iter = 0; iter < k; iter++) {
        for (int i = 0; i < n; i++) {
            float sum = 0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            temp_x[i] = (b[i] - sum) / A[i][i];
        }
        x = temp_x;
    }
    return x;
}

int main() {
    
    std::vector<std::vector<float>> A = {{4, -2, 0, 0}, {-2, 5, -1, 0}, {0, -1, 4, 2}, {0, 0, 2, 3}};
    std::vector<float> b = {0, 2, 3, -2};
    std::vector<float> x = {0, 0, 0, 0};

    std::vector<float> solution = jacobi(A, b, x);

    std::cout << "Jacobi:\n";
    print(solution);

    return 0;
}

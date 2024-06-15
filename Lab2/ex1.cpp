#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

//przestrzeń unormowana

float euklides(const std::vector<int> &numbers){
    float sum = 0;

    for (const int number : numbers){
        sum += number * number;
    }
    return sqrt(sum);
}

int manhattan(const std::vector<int> &numbers){
    int sum = 0;

    for(const int number : numbers){
        sum += abs(number);
    }
    return sum;
}

int maximum(const std::vector<int> &numbers){

    int maxi = INT_MIN;

    for(const int number : numbers){
        maxi = abs(std::max(maxi, number));
    }

    return maxi;
}

struct Point{
    int x;
    int y;
};

float d_euclidean(const Point &p, const Point &q){
    float dx = p.x - q.x;
    float dy = p.y - q.y;
    return std::sqrt(dx * dx + dy * dy);
}

float d_manhattan(const Point &p, const Point &q){
    return abs((p.x - q.x)) + abs((p.y - q.y));
}

float d_max(const Point &p, const Point &q){
    return std::max(abs(p.x - q.x), abs(p.y - q.y));
}

float d_river(Point &p, Point &q){
    float result = 0;
    if(p.x == q.x){
        result = d_euclidean(p, q);
    }
    else{
        Point c1 = {p.x, 0};
        Point c2 = {q.x, 0};
        result = d_euclidean(p, c1) + d_euclidean(c1, c2) + d_euclidean(c2, q);
    }
    return result;
}

float d_railway (Point &p, Point &q){
    if(abs(p.x + q.y - p.y + q.x) < 0.00001){
        return d_euclidean(p, q);
    }
    Point o{0, 0};
    return d_euclidean(p, o)+ d_euclidean(q, o);
}

std::vector<std::vector<int>> multiplyMatrix(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB) {
    if (matrixA[0].size() != matrixB.size()) {
        return {{0}};
    }
    //matixA size - szerokość
    //matrixB[0] size - wysokość
    std::vector<std::vector<int>> result(matrixA.size(), std::vector<int>(matrixB[0].size(), 0));

    for (int i = 0; i < matrixA.size(); ++i) {
        for (int j = 0; j < matrixB[0].size(); ++j) {
            for (int k = 0; k < matrixB.size(); ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    return result;
}  

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }
}

//przestrzeń metryczna
//p = (x0, x1, ... xn-1)
//q = (y0, y0, ... yn-1)
//d(p,q) = sqrt(sum(xi - yi))

int main(){

    std::vector<int> numbers{1, 1};
    std::vector<std::vector<int>> matrixA = {{1, 2, 3}, {4, 5, 6}};
    std::vector<std::vector<int>> matrixB = {{7, 8}, {9, 10}, {11, 12}};
    auto myMatrix = multiplyMatrix(matrixA, matrixB);

    Point p{1,1};
    Point q{3,2};
    std::cout << "Euklides: " << euklides(numbers) << std::endl;
    std::cout << "Manhattan: " << manhattan(numbers) << std::endl;
    std::cout << "Maksimum: " << maximum(numbers) << std::endl;
    std::cout << "D euklides: " << d_euclidean(p, q) << std::endl;
    std::cout << "D_manhattan: " << d_manhattan(p, q) << std::endl;
    std::cout << "D_max: " << d_max(p, q) << std::endl;
    std::cout << "D rzeczna: " << d_river(p, q) << std::endl;
    std::cout << "D kolejowa: " << d_railway(p, q) << std::endl;
    std::cout << "Mnozenie: "; 
    printMatrix(myMatrix);
}
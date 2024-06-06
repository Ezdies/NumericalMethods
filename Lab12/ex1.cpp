#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

struct Point{
    int x;
    int y;
};

void LCG(int a, int c, int M, int X0, int n) {
    if (n <= 0) {
        return;
    }

    int res = (a * X0 + c) % M;
    std::cout << res << std::endl;

    LCG(a, c, M, res, n - 1);
}

std::vector<Point> LCGiter(u_int32_t a, u_int32_t c, u_int32_t M, u_int32_t X0, u_int32_t n) {
    std::vector<Point> points;
    int X = X0;
    
    for (int i = 0; i < n; ++i) {
        int next = (a * X + c) % M;
        points.push_back({X, next});
        X = next;
    }
    
    return points;
}

std::vector<u_int32_t> LCGiterNum(u_int32_t a, u_int32_t c, u_int32_t M, u_int32_t X0, u_int32_t n) {
    std::vector<u_int32_t> numbers;
    u_int32_t X = X0;
    
    for (int i = 0; i < n; ++i) {
        u_int32_t next = (a * X + c) % M;
        numbers.push_back(next);
        X = next;
    }
    
    return numbers;
}


void printSVG(const std::vector<Point>& points) {
    std::cout << "<svg height=\"500\" width=\"500\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;

    for (const auto& point : points) {
        std::cout << "<circle cx=\"" << point.x % 500 << "\" cy=\"" << point.y % 500 << "\" r=\"1\" />" << std::endl;
    }

    std::cout << "</svg>" << std::endl;
}

bool count(const std::vector<u_int32_t>& numbers) {
    const int n = 20000;
    std::bitset<n> bits;
    int bitIndex = 0;

    for (u_int32_t number : numbers) {
        for (int j = 0; j < 32 && bitIndex < n; ++j) {
            bits.set(bitIndex, number & (1 << j));
            bitIndex++;
        }
        if (bitIndex >= n) {
            break;
        }
    }

    int res = bits.count();
    std::cout << res << std::endl;

    if (res > 9725 && res < 10275) {
        return true;
    } 
    return false;
}

int main(){
    u_int32_t a = 1103515245;
    u_int32_t c = 12345;
    u_int32_t M = pow(2, 31);
    u_int32_t X0 = 123;
    u_int32_t n = 1000;
   // LCG(a, c, M, X0, n);

    std::vector<Point> points = LCGiter(a, c, M, X0, n);
    std::vector<u_int32_t> numbers = LCGiterNum(a, c, M, X0, n);
    int res = count(numbers);

    std::cout << res << "\n";

    

  //  printSVG(points);

}
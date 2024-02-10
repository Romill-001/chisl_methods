#include <iostream>
#include <cmath>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include <algorithm>

std::mutex resultMutex;
double totalResult = 0.0;

double func(double t) {
    return (std::cos(t) - 1.0) / t;
}

double trapezoidalRule(double (*func)(double), double a, double b, int numSteps) {
    double h = (b - a) / numSteps;
    double result = 0.5 * (func(a) + func(b));
    for (int i = 1; i < numSteps; ++i) {
        result += func(a + i * h);
    }
    return result * h;
}

void integrateInRange(double (*func)(double), double a, double b, int numSteps) {
    double result = trapezoidalRule(func, a, b, numSteps);
    std::lock_guard<std::mutex> lock(resultMutex);
    totalResult += result;
}

int main() {
    double upperBound;
    int numSteps;
    
    std::cout << "Введите верхнюю границу интеграла x и количество шагов N: ";
    std::cin >> upperBound >> numSteps;

    std::vector<std::thread> threads;

    auto start = std::chrono::steady_clock::now();
    integrateInRange(func, 0, upperBound, numSteps);
    auto end = std::chrono::steady_clock::now();
    
    std::cout << "Интеграл рассчитан на 1 потоке. Время: " 
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
              << " мс" << std::endl;

    totalResult = 0.0;
    
    for (int numThreads = 2; numThreads <= 32; numThreads *= 2) {
        totalResult = 0.0;
        start = std::chrono::steady_clock::now();
        for (int i = 0; i < numThreads; ++i) {
            threads.push_back(std::thread(integrateInRange, func, i * upperBound / numThreads, (i + 1) * upperBound / numThreads, numSteps / numThreads));
        }
        for (std::thread& t : threads) {
            t.join();
        }
        end = std::chrono::steady_clock::now();

        std::cout << "Интеграл рассчитан на " << numThreads << " потоках. Время: " 
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() 
                  << " мс" << std::endl;

        threads.clear();
    }

    return 0;
}
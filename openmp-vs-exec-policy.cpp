#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <chrono>
#include <execution>
#include <functional>
#include <locale>

#include "utils/benchmark.h"

template <class ExecutionPolicy>
void test_stl(const std::vector<double>& X, ExecutionPolicy policy) {
    std::vector<double> Y(X.size());
    std::transform(policy, X.cbegin(), X.cend(), Y.begin(), [](double x){
        volatile double y = std::sin(x);
        return y;
    });
}

void test_openmp(const std::vector<double>& X) {
    std::vector<double> Y(X.size());
#pragma omp parallel for
    for (int i = 0; i < X.size(); ++i) {
        volatile double y = std::sin(X[i]);
        Y[i] = y;
    }
}

int main() {
    const size_t N = 10000000;
    std::vector<double> data(N);
    std::iota(data.begin(), data.end(), 1);
    std::vector< std::pair< std::string, std::function<void()> > > tests {
        { "OpenMP", [&data](){ test_openmp(data); } },
        { "STL seq", [&data](){ test_stl(data, std::execution::seq); } },
        { "STL par", [&data](){ test_stl(data, std::execution::par); } },
        { "STL par_unseq", [&data](){ test_stl(data, std::execution::par_unseq); } },
        { "STL unseq", [&data](){ test_stl(data, std::execution::unseq); } }
    };
    std::locale::global(std::locale(""));
    // std::cout.imbue(std::locale(""));
    for (auto& test : tests) {
        // std::cout << std::setw(14) << std::left << test.first << ": " << std::right << std::setw(13) << benchmark(test.second) << std::endl;
        std::cout << std::format("{0:<14}: {1: >14L%Q %q}", test.first, benchmark(test.second)) << std::endl;
    }
    return 0;
}

#include <chrono>
#include <functional>

auto benchmark(std::function<void()> f) {
    auto start = std::chrono::high_resolution_clock::now();
    f();
    auto stop = std::chrono::high_resolution_clock::now();
    return (stop - start);
}
#include <iostream>
#include <functional>

class defer {
    public:
        defer(std::function<void()> f) : f(f) {}
        ~defer() { f(); }
    private:
        std::function<void()> f;
};

int main() {
    defer d([&]() { std::cout << "defer\n"; });
    std::cout << "main\n";
    return EXIT_SUCCESS;
}
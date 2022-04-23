#include <functional>

class CDefer {
public:
    CDefer(std::function<void()> f) : f_(f) {}
    ~CDefer() { f_(); }
private:
    std::function<void()> f_;
};

#define defer CDefer __defer__##__LINE__
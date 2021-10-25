#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    unsigned long long x = 0x357620655410L;
    while(x)
        cout << char(0x726F6C6564574820L >> ((( x >>= 4) & 0377) << 3));
    return 0;
}

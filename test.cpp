#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    char msg[] = "Hello World!";
    for(int i = 0; i < sizeof(msg) / sizeof(msg[0]); i++) {
        cout << hex << static_cast<int>(msg[i]) << " ";
    }
    cout << endl;
}
#include <iostream>

int main() {
    const int w = 512;
    const int h = 512;

    using namespace std;

    cout << "P3\n" << w << " " << h << "\n255\n";

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {

            int ir = static_cast<std::uint8_t>(double(i) / (h / 2.0) * 255.0);
            int ig = static_cast<std::uint8_t>(double(j) / (w / 2.0) * 255.0);
            int ib = static_cast<std::uint8_t>(double(i + j) / double(h + w) * 255.0);

            cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}

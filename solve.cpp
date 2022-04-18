#include <iostream>
#include <vector>

std::vector<int> algarismos{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
std::vector<int> algNZ{1, 2, 3, 4, 5, 6, 7, 8, 9};

int C, R, O, S, A, D, N, G, E;

auto CROSS = [&]() -> int { return (C * 10000) + (R * 1000) + (O * 100) + (S * 10) + S; };
auto ROADS = [&]() -> int { return (R * 10000) + (O * 1000) + (A * 100) + (D * 10) + S; };
auto DANGER = [&]() -> int { return (D * 100000) + (A * 10000) + (N * 1000) + (G * 100) + (E * 10) + R; };

auto print_solution = [&]() -> void {
    std::cout << "   CROSS  :   " << C << R << O << S << S << std::endl;
    std::cout << "+  ROADS  :+  " << R << O << A << D << S << std::endl;
    std::cout << " -------  : -------" << std::endl;
    std::cout << "  DANGER  :  " << D << A << N << G << E << R << std::endl << std::endl;
};

auto solve = [&]() ->void {
    for(auto sC: algNZ) {
        C=sC;
        for(auto sR: algNZ) {
            R=sR;
            if(R == C) continue;
            for(auto sD: algNZ) {
                D=sD;
                if(D == C || D == R) continue;
                for(auto sO: algarismos) {
                    O=sO;
                    if(O == C || O == R || O == D) continue;
                    for(auto sS: algarismos) {
                        S=sS;
                        if(S == C || S == R || S == D || S == O) continue;
                        for(auto sA: algarismos) {
                            A=sA;
                            if(A == C || A == R || A == D || A == O || A == S) continue;
                            for(auto sN: algarismos) {
                                N=sN;
                                if(N == C || N == R || N == D || N == O || N == S || N == A) continue;
                                for(auto sG: algarismos) {
                                    G=sG;
                                    if(G == C || G == R || G == D || G == O || G == S || G == A || G == N) continue;
                                    for(auto sE: algarismos) {
                                        E=sE;
                                        if(E == C || E == R || E == D || E == O || E == S || E == A || E == N || E == G) continue;
                                        if(CROSS() + ROADS() == DANGER()) {
                                            print_solution();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
};

int main() {
    solve();
    return 0;
}
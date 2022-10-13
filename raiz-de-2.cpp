#include <iostream>
#include <locale>
#include <vector>

#ifdef _WIN32
#include <limits>

void resolve_double() {
    std::vector<int> digit_count(10, 0);
    long double val = 2;
    long double resto = val;
    unsigned long long digito = 0;
    long double impar_corrente = 1;
    long double maximo = std::numeric_limits<long double>::max() / 2.0;
    bool imprimiu_a_virgula = false;
    unsigned long long contas;
    while (resto > 0 && resto < maximo) {
        contas = 0;
        while (impar_corrente <= resto) {
            resto -= impar_corrente;
            impar_corrente += 2;
            contas++;
        }
        std::wcout << contas;
        digit_count[contas]++;
        if (!imprimiu_a_virgula) {
            std::wcout << L",";
            imprimiu_a_virgula = true;
        }
        digito++;
        if (resto > 0) {
            resto *= 100.0;
            impar_corrente = ((impar_corrente - 1) * 10.0) + 1;
        }
    }
    std::wcout << std::endl;
    if (resto > 0) {
        std::wcout << L"Paramos no dígito " << digito
                   << L" pois acabou os números do long double..." << std::endl;
    }
    std::wcout << L"Número de ocorrência dos dígitos: " << std::endl;
    std::wcout.imbue(std::locale(""));
    for (int i = 0; i < 10; ++i) {
        std::wcout << i << ": " << digit_count[i] << std::endl;
    }
}

void resolve_int() {
    std::vector<int> digit_count(10, 0);
    unsigned long long resto = 2;
    unsigned long long digito = 0;
    unsigned long long impar_corrente = 1;
    unsigned long long maximo =
        std::numeric_limits<unsigned long long>::max() / 2.0;
    bool imprimiu_a_virgula = false;
    unsigned long long contas;
    while (resto > 0 && resto < maximo) {
        contas = 0;
        while (impar_corrente <= resto) {
            resto -= impar_corrente;
            impar_corrente += 2;
            contas++;
        }
        std::wcout << contas;
        digit_count[contas]++;
        if (!imprimiu_a_virgula) {
            std::wcout << L",";
            imprimiu_a_virgula = true;
        }
        digito++;
        if (resto > 0) {
            resto *= 100.0;
            impar_corrente = ((impar_corrente - 1) * 10.0) + 1;
        }
    }
    std::wcout << std::endl;
    if (resto > 0) {
        std::wcout << L"Paramos no dígito " << digito
                   << L" pois acabou os números do unsigned long long..."
                   << std::endl;
    }
    std::wcout << L"Número de ocorrência dos dígitos: " << std::endl;
    std::wcout.imbue(std::locale(""));
    for (int i = 0; i < 10; ++i) {
        std::wcout << i << L": " << digit_count[i] << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    // resolve_double();
    resolve_int();
    return 0;
}

#else

#include <gmp.h>
#include <gmpxx.h>

// Compilar: g++ raiz-de-2.cpp -lgmpxx -lgmp -o raiz-de-2
// precisa ter instalada a biblioteca libgmp-dev

void resolve_int() {
    std::vector<int> digit_count(10, 0);
    mpz_class resto("2"), impar_corrente("1");
    unsigned long long digito = 0;
    bool imprimiu_a_virgula = false;
    unsigned contas;
    while (resto > 0 && digito < 400'000) {
        contas = 0;
        while (impar_corrente <= resto) {
            resto -= impar_corrente;
            impar_corrente += 2;
            contas++;
        }
        std::cout << contas;
        digit_count[contas]++;
        if (!imprimiu_a_virgula) {
            std::wcout << ",";
            imprimiu_a_virgula = true;
        }
        digito++;
        if (resto > 0) {
            resto *= 100.0;
            impar_corrente = ((impar_corrente - 1) * 10.0) + 1;
        }
    }
    std::cout << std::endl;
    //std::cout.imbue(std::locale(""));
    if (resto > 0) {
        std::cout << "Paramos no dígito " << digito
                   << " pois chegamos no limite de precisão "
                      "determinado..."
                   << std::endl << std::endl;
        //std::cout << "Resto: " << resto << std::endl << std::endl;
        //std::cout << "Ímpar corrente: " << impar_corrente << std::endl << std::endl;
    }
    std::cout << "Número de ocorrência dos dígitos: " << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << i << ": " << digit_count[i] << std::endl;
    }
}

int main() {
    resolve_int();
    return 0;
}

#endif
#include <iostream>

#ifdef _WIN32
#include <limits>

void resolve_double(){
    long double val = 2;
    long double resto = val;
    unsigned long long digito=0;
    long double impar_corrente = 1;
    long double maximo = std::numeric_limits<long double>::max() / 2.0;
    bool imprimiu_a_virgula = false;
    while(resto > 0 && resto < maximo) {
        unsigned long long contas = 0;
        while(impar_corrente <= resto) {
            resto -= impar_corrente;
            impar_corrente += 2;
            contas++;
        }
        std::cout << contas;
        if(!imprimiu_a_virgula) {
            std::cout << ",";
            imprimiu_a_virgula = true;
        } else {
            digito++;
        }
        if(resto > 0) {
            resto *= 100.0;
            impar_corrente = ((impar_corrente - 1) * 10.0) + 1;
        }
    }
    std::cout << std::endl;
    if(resto > 0) {
        std::cout << "Paramos no dígito " << digito << " depois da vírgula pois acabou os números do long double...";
    }
}

int main() {
    resolve_double();
    return 0;
}

#else

#include <string>
#include <gmp.h>
#include <gmpxx.h>

// Compilar: g++ raiz-de-2.cpp -lgmpxx -lgmp -o raiz-de-2
// precisa ter instalada a biblioteca libgmp-dev

void resolve_int() {
    std::string max_str(1000000, '9');
    mpz_class val("2"), resto("2"), impar_corrente("1"), maximo(max_str);
    unsigned int digito=0;
    bool imprimiu_a_virgula = false;
    while(resto > 0 && resto < maximo) {
        unsigned contas = 0;
        while(impar_corrente <= resto) {
            resto -= impar_corrente;
            impar_corrente += 2;
            contas++;
        }
        std::cout << contas;
        if(!imprimiu_a_virgula) {
            std::cout << ",";
            imprimiu_a_virgula = true;
        } else {
            digito++;
        }
        if(resto > 0) {
            resto *= 100.0;
            impar_corrente = ((impar_corrente - 1) * 10.0) + 1;
        }
    }
    std::cout << std::endl;
    if(resto > 0) {
        std::cout << "Paramos no dígito " << digito << " depois da vírgula pois chegamos no limite de precisão determinado...";
    }
}


int main() {
    resolve_int();
    // mpz_class val("2");
    // std::cout << val.sqrt(1000000);
    return 0;
}

#endif
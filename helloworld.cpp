#include <algorithm>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Um programa de exemplo. Este programa demonstra o simples
 * armazenamento e iteração em elementos de um vetor. Uma mensagem de boas
 * vindas é exibida ao usuário.
 *
 * @return Retorna 0 quando finaliza a execução.
 */
int main() {
  // replace the C++ global locale as well as the C locale with the
  // user-preferred locale
  std::locale::global(std::locale(""));
  // use the new global locale for future wide character output
  std::wcout.imbue(std::locale());
  // output the same number again
  std::wcout << L"Valor em reais: " << 1000.01
             << L" Acentos: á é í ó ú ã õ à ç Ç" << endl;

  vector<wstring> msg{L"Olá", L"Mundo",   L"C++",
                      L"do",  L"VS Code", L"e sua extensão C++"};

  for_each(msg.begin(), msg.end(), [](auto &a){wcout << a << L" ";});

  // for (auto palavra : msg) {
  //   wcout << palavra << L" ";
  // }
  wcout << endl;

  return 0;
}
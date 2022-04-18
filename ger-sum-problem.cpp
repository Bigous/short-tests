#include <algorithm>
#include <execution>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Função que carrega as palavras de um arquivo em um vetor
 *
 * @param file_name Arquivo a ser carregado
 * @return std::vector<std::string> Vetor de palavras do arquivo
 */
bool load_words_from_file(const std::string &file_name,
                          std::vector<std::string> &words) {
    std::ifstream file(file_name, std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo " << file_name << std::endl;
        return false;
    };
    std::string word;
    while (file >> word) {
        // Não permite palavras com menos de 3 letras
        if (word.size() >= 3) {
            // Já transforma tudo pra uppercase para que não haja diferença
            // entre maiúsculas e minúsculas nos algarismos numéricos. Assim,
            // tratamos 'a' e 'A' como iguais.
            for (auto &c : word) {
                c = std::toupper(c);
            }
            words.push_back(word);
        }
    }
    return true;
}

/**
 * @brief Função que retorna todas as letras diferentes em uma palavra
 *
 * @param word Palavra a ser analisada
 * @return std::vector<char> Vetor de letras diferentes
 */
std::vector<char> how_many_different_characters(const std::string &word) {
    std::vector<char> characters;
    for (char c : word) {
        if (std::find(characters.begin(), characters.end(), c) ==
            characters.end()) {
            characters.push_back(c);
        }
    }
    return characters;
}

/**
 * @brief Retorna o valor numérico para uma letra.
 *
 * @param c Letra a ser analisada.
 * @param characters Indice de cada letra.
 * @param values Valor numérico para cada letra.
 * @return int Valor numérico da letra -> algarismo.
 */
inline int get_value_for_character(const char &c,
                                   const std::vector<char> &characters,
                                   const std::vector<int> &values) {
    return values[std::find(characters.begin(), characters.end(), c) -
                  characters.begin()];
}

/**
 * @brief Função que retorna um valor numérico para uma palavra dando-se o valor
 * de cada letra
 *
 * @param word Palavra a ser convertida
 * @param characters Indice de cada letra
 * @param values Valor numérico para cada letra
 * @return std::uint64_t Valor numérico da palavra
 */
inline std::uint64_t get_value_for_word(const std::string &word,
                                        const std::vector<char> &characters,
                                        const std::vector<int> &values) {
    std::uint64_t value = 0;
    int digits = 0;
    for (int i = word.size() - 1; i >= 0; i--) {
        value += get_value_for_character(word[i], characters, values) *
                 std::pow(10, digits);
        digits++;
    }
    return value;
}

/**
 * @brief Valida se é possível montar uma combinação de substituição de letras
 * por algarismos em que a espressão `word + word2 = result` seja verdadeira.
 * Condições:
 * - Cada letra é um algarismo numérico difernte.
 * - Nenhum número formado pelas palavras contém zero a esquerda.
 *
 * @param word Palavra 1 que terá a substituição de letras por algarismos.
 *
 * @param word2 Palavra 2 que terá a substituição de letras por algarismos.
 *
 * @param result Palavra 3 que terá a substituição de letras por algarismos e
 * cujo valor final deve bater com a soma das palavras 1 e 2.
 *
 * @param val1 Valor numérico da palavra 1, quando o resultado for verdadeiro.
 *
 * @param val2 Valor numérico da palavra 2, quando o resultado for verdadeiro.
 *
 * @param val3 Valor numérico da palavra 3, quando o resultado for verdadeiro.
 *
 * @return `true` se for possível montar uma combinação de substituição de
 * letras por algarismos em que a espressão `word + word2 = result` seja
 * verdadeira.
 *
 * @remarks Esta rotina será executada diversas vezes, por isso é necessário
 * sair da rotina o mais rápido possível.
 */
bool check_for_possible_combination(const std::string &word,
                                    const std::string &word2,
                                    const std::string &result,
                                    std::uint64_t &val1, std::uint64_t &val2,
                                    std::uint64_t &result_val) {
    // O tamanho máximo de um uint64 é 18.446.744.073.709.551.615. Portanto
    // podemos ter no máximo 19 algarismos na resposta.
    if (result.size() > 18)
        return false;

    // A quantidade de algarismos do resultado deve ser igual ao tamanho da
    // maior palavra ou 1 dígito a mais
    int max_size = std::max(word.size(), word2.size());
    if (result.size() != max_size && result.size() != max_size + 1) {
        return false;
    }

    auto all_chars = how_many_different_characters(word + word2 + result);
    std::vector<int> values(all_chars.size(), 0);

    // Verifica se o número de letras diferentes das 3 palavras juntas tem no
    // máximo 10 (numero máximo de algarismos na base 10)
    if (all_chars.size() > 10) {
        return false;
    }

    std::vector<bool> used_chars(10, false);
    std::fill(used_chars.end() - all_chars.size(), used_chars.end(), true);

    do {
        // Seleciona os algarismos a serem usados
        int o = 0;
        for (int i = 0; i < 10; i++) {
            if (used_chars[i]) {
                values[o++] = i;
            }
        }

        do {
            // Aqui temos os valores para cada caracter...

            // Faz todas as permutações de algarismos com os algarismos
            // selecionados.

            // Verifica se foi atribuido 0 a primeira letra de cada palavra.
            // Se não for, a permutação é válida.
            if (get_value_for_character(word[0], all_chars, values) != 0 &&
                get_value_for_character(word2[0], all_chars, values) != 0 &&
                get_value_for_character(result[0], all_chars, values) != 0) {

                val1 = get_value_for_word(word, all_chars, values);
                val2 = get_value_for_word(word2, all_chars, values);
                result_val = get_value_for_word(result, all_chars, values);

                if (val1 + val2 == result_val) {
                    return true;
                }
            }
        } while (std::next_permutation(values.begin(), values.end()));
    } while (std::next_permutation(used_chars.begin(), used_chars.end()));

    return false;
}

int main(int argc, char *argv[]) {
    std::vector<std::string> words;

    // Se apenas 1 argumento foi passado, tratamos como o nome do arquivo de
    // entrada
    if (argc == 2) {
        if (load_words_from_file(argv[1], words)) {
            std::clog << words.size() << " palavras carregadas do arquivo ["
                      << argv[1] << "]." << std::endl;
        }
    } else if (argc > 2) {
        // Se mais de 1 argumento foi passado, tratamos como lista de palavras
        for (int i = 1; i < argc; i++) {
            words.push_back(argv[i]);
        }
        std::clog << words.size() << " palavras carregadas da linha de comando."
                  << std::endl;
    }

    // Se não temos nenhuma palavra, ou não foi conseguimos ler o arquivo ou não
    // foi passado argumento algum. Então vamos mostrar o menu de ajuda.
    if (words.size() == 0) {
        std::clog << "Uso 1: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
        std::clog << "Uso 2: " << argv[0] << " <PALAVRA1> <PALAVRA2> [PALAVRA...]" << std::endl;
        return 1;
    }
    // Lista de palavras em pt-BR extraída de:
    // https://www.ime.usp.br/~pf/dicios/index.html
    try {
        std::for_each(
            std::execution::par_unseq, words.begin(), words.end(),
            [&words](const std::string &word) {
                int idx = &word - &words[0];
                std::uint64_t val1, val2, res;
                for (int i = idx; i < words.size(); i++) {
                    const std::string &word2 = words[i];
                    for (const std::string &result : words) {
                        if (check_for_possible_combination(word, word2, result,
                                                           val1, val2, res)) {
                            std::stringstream ss;
                            ss << word << " + " << word2 << " = " << result
                               << "  <--->  " << val1 << " + " << val2 << " = "
                               << res << std::endl;
                            std::cout << ss.str();
                        }
                    }
                }
            });
    } catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 2;
    }
    return 0;
}
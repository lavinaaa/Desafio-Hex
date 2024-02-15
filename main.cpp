#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

struct Dados {
    std::string timestamp;
    double eixo_x;
    double eixo_y;
    double eixo_z;
};

int main() {
    std::ifstream arquivo("attitude_exam.log");
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    std::ofstream arquivo_saida("output.txt");
    if (!arquivo_saida.is_open()) {
        std::cerr << "Erro ao criar o arquivo de saída." << std::endl;
        return 1;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string valor;

        Dados dados;

        // Extrai os valores usando o delimitador ';'
        std::getline(ss, dados.timestamp, ';');
        std::getline(ss, valor, ';');
        dados.eixo_x = std::stod(valor); // Converte para double
        std::getline(ss, valor, ';');
        dados.eixo_y = std::stod(valor); // Converte para double
        std::getline(ss, valor, ';');
        dados.eixo_z = std::stod(valor); // Converte para double

        double pitch = atan2(-dados.eixo_x, sqrt(dados.eixo_y * dados.eixo_y + dados.eixo_z * dados.eixo_z));
        double roll = atan2(dados.eixo_y, dados.eixo_z);

        std::streambuf *salvo_cout = std::cout.rdbuf(); // Salva o buffer de saída atual
        std::cout.rdbuf(arquivo_saida.rdbuf()); // Redireciona a saída padrão para o arquivo de saída

        std::cout << "Pitch: " << pitch << std::endl;
        std::cout << "Roll: " << roll << std::endl;

        std::cout.rdbuf(salvo_cout);

        // Exibe os valores lidos
        //std::cout << "Timestamp: " << dados.timestamp << std::endl;
        //std::cout << "Eixo X: " << dados.eixo_x << std::endl;
        //std::cout << "Eixo Y: " << dados.eixo_y << std::endl;
        //std::cout << "Eixo Z: " << dados.eixo_z << std::endl;
    }

    arquivo.close();
    arquivo_saida.close();

    return 0;
}

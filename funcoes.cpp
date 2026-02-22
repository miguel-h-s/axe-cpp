#include <iostream>
#include <fstream>
#include "rano.hpp"

void apresentacao() {
    std::cout << AMARELO 
              << "      \n  _ __  \n | '__| \n | |    \n |_|    \n" 
              << " v1.0 Alpha - O poder do C++ no seu terminal Linux\n"
              << "------------------------------------------\n"
              << RESET;
}

void menu() {
    std::cout << "1 - criar e escrever em um arquivo\n";
    std::cout << "2 - mais sobre Rano\n";
    std::cout << "0 - sair\n";
}

void creditos() {
    std::cout << "\nCriado por: Miguel\nInspirado no Nano e escrito 100% em C++!\n";    
}

void criar_escrever(std::string nome_fornecido) {
    std::string nome_arquivo = nome_fornecido;
    int opcao_arquivo;
    
    if (nome_arquivo == "") {
        std::cout << "\ndigite o nome do arquivo: ";
        std::cin >> nome_arquivo;
    }

    std::cout << "\n--- CONFIGURAÇÃO DO ARQUIVO ---\n";
    std::cout << "opções de escrita:\n 1 - sobrescrever arquivo\n 2 - não sobrescrever arquivo(adiciona ao final)\n";
    std::cin >> opcao_arquivo;
    
    std::ios_base::openmode modo = (opcao_arquivo == 2) ? std::ios::app : std::ios::out;

    if (opcao_arquivo == 2) {
        std::ifstream leitura_previa(nome_arquivo);
        if (leitura_previa.is_open()) {
            std::string linha_antiga;
            std::cout << "\n--- CONTEÚDO ATUAL DO ARQUIVO ---\n";
            while (std::getline(leitura_previa, linha_antiga)) {
                std::cout << linha_antiga << "\n";
            }
            leitura_previa.close();
            std::cout << "---------------------------------\n";
        } else {
            std::cout << AMARELO << "[AVISO] Arquivo novo, começando do zero.\n" << RESET;
        }
    }

    std::vector<std::string> buffer;
    std::string linha;
    std::cout << "\n --- EDITANDO " << nome_arquivo << " ---\n";
    std::cout << "digite ':s' em uma linha vazia para salvar e sair\n\n";

    std::cin.ignore();
    while(true) {
        std::getline(std::cin, linha);
        if(linha == ":s") break;
        buffer.push_back(linha);
    }

    std::ofstream Arquivo(nome_arquivo, modo);
    if(Arquivo.is_open()) {
        for (const std::string& l : buffer) Arquivo << l << "\n";
        Arquivo.close();
        std::cout << VERDE << "\n[OK] " << buffer.size() << " linhas salvas em " << nome_arquivo << "\n" << RESET;
    } else {
        std::cerr << VERMELHO << "\n[ERROR] não foi possivel gravar o arquivo!\n" << RESET;
    }
}

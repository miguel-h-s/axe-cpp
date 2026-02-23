#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <vector>
#include "axe.hpp"

void apresentacao() {
    std::cout << VERMELHO << R"(
  ,  /\  .  
 //`-||-'\\ 
(| -=||=- |)
 \\,-||-.// 
  `  ||  '  
     ||     
     ||     
     ()     )" << RESET << "\n";
    std::cout << VERMELHO << " Axe Editor v1.1.0 Alpha | Performance edition\n" << RESET;
    std::cout << "--------------------------------------------------\n";
}

void menu() {
    std::cout << "1 - criar e escrever em um arquivo\n";
    std::cout << "2 - mais sobre o Axe\n";
    std::cout << "3 - registro de atualização\n";
    std::cout << VERMELHO << "0 - sair\n" << RESET;
}

void registro_atualizacao() {
    std::cout << VERDE << "\n--- REGISTRO DE ATUALIZAÇÃO v1.1.0 ---\n" << RESET;
    std::cout << "- Adicionado: Cronômetro de precisão e Flags -O3.\n";
    std::cout << "- Adicionado: Otimização de I/O e referências constantes.\n";
    std::cout << "- Alteração: Nome alterado de Rano para Axe.\n";
    std::cout << "- Alteração: Logo em ASCII Vermelho.\n";
}

void creditos() {
    std::cout << "\nCriado por: Miguel\nInspirado no Nano e escrito 100% em C++!\n";    
}

void criar_escrever(const std::string& nome_fornecido) {
    std::string nome_arquivo = nome_fornecido;
    int opcao_arquivo;
    std::vector<std::string> buffer; // buffer de RAM
    
    if (nome_arquivo == "") {
        std::cout << "\ndigite o nome do arquivo: ";
        std::cin >> nome_arquivo;
    }

    std::cout << "\n--- CONFIGURAÇÃO DO ARQUIVO ---\n";
    std::cout << "opções de escrita:\n 1 - sobrescrever arquivo\n 2 - não sobrescrever (carregar existente)\n";
    std::cout << std::flush;
    std::cin >> opcao_arquivo;
    
    // Se a opção for carregar o arquivo existente
    if (opcao_arquivo == 2) {
        std::ifstream arquivo_leitura(nome_arquivo);
        if (arquivo_leitura.is_open()) {
            std::cout << "\n[Axe] Lendo arquivo, aguarde..." << std::endl;
            auto inicio = std::chrono::high_resolution_clock::now();
            std::string linha_antiga;

            // reservando espaço de até 500 mil linhas
            buffer.reserve(500000);

            // LEITURA ULTRA RÁPIDA PARA A RAM
            while (std::getline(arquivo_leitura, linha_antiga)) {
                buffer.push_back(linha_antiga);
            }

            auto fim = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> tempo = fim - inicio;
            arquivo_leitura.close();

            // EXIBIÇÃO INTELIGENTE (PAGINAÇÃO)
            int total = buffer.size();
            std::cout << "\n--- CONTEÚDO ATUAL (" << total << " linhas) ---" << std::endl;
            std::cout << std::flush;
            if (total > 30) {
                for (int i = 0; i < 10; ++i) std::cout << CINZA << std::setw(4) << i+1 << " | " << RESET << buffer[i] << "\n";
                std::cout << AMARELO << "... [ " << total - 20 << " linhas ocultas para manter a velocidade ] ...\n" << RESET;
                for (int i = total - 10; i < total; ++i) std::cout << CINZA << std::setw(4) << i+1 << " | " << RESET << buffer[i] << "\n";
            } else {
                for (int i = 0; i < total; ++i) std::cout << CINZA << i+1 << " | " << RESET << buffer[i] << "\n";
            }

            std::cout << std::flush;

            std::cout << AMARELO << "\n[Axe Performance] Carregado em " << std::fixed 
                      << std::setprecision(4) << tempo.count() << "s\n" << RESET;
            std::cout << std::flush;
        } else {
            std::cout << AMARELO << "[AVISO] Arquivo novo ou não encontrado.\n" << RESET;
        }
    }

    // MODO DE EDIÇÃO
    std::string linha;
    std::cout << "\n --- EDITANDO: " << nome_arquivo << " ---\n";
    std::cout << "digite ':s' para salvar e sair\n\n";

    std::cin.ignore(); 
    while(true) {
        std::getline(std::cin, linha);
        if(linha == ":s") break;
        buffer.push_back(linha); // Adiciona ao que já estava na RAM
    }

    // SALVAMENTO FINAL
    std::ios_base::openmode modo = (opcao_arquivo == 2) ? std::ios::out : std::ios::out; 
    // Dica: Como carregamos TUDO na RAM, sempre salvamos como 'out' (sobrescrevendo o arquivo com o buffer completo)
    
    std::ofstream Arquivo(nome_arquivo, modo);
    if(Arquivo.is_open()) {
        for (const std::string& l : buffer) Arquivo << l << "\n";
        Arquivo.close();
        std::cout << VERDE << "\n[OK] Salvo com sucesso!\n" << RESET;
    } else {
        std::cerr << VERMELHO << "\n[ERRO] Falha ao gravar no disco!\n" << RESET;
    }
}
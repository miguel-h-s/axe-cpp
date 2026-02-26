#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <filesystem>
#include "axe.hpp"
namespace fs =  std::filesystem;

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
    std::cout << VERMELHO << " Axe Editor v1.2.0 Alpha | Productiviy edition\n" << RESET;
    std::cout << "--------------------------------------------------\n";
}

void menu() {
    std::cout << "1 - criar e escrever em um arquivo\n";
    std::cout << "2 - mais sobre o Axe\n";
    std::cout << "3 - registro de atualização\n";
    std::cout << VERMELHO << "0 - sair\n" << RESET;
}

void registro_atualizacao() {
    std::cout << VERDE << "\n--- REGISTRO DE ATUALIZAÇÃO v1.2.0 ---\n" << RESET;
    std::cout << "- Adicionado: comandos de produtividade(editar, remover linha etc\n";
    std::cout << VERDE << "\n-- REGISTRO DE ATUALIZAÇÃO v1.1.0(passada) ---\n" << RESET;
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
            auto tamanho_bytes = fs::file_size(nome_arquivo);
            size_t estimativa_linhas = tamanho_bytes / 10; 
            buffer.reserve(estimativa_linhas + 100);

            std::cout << "\n[Axe] Lendo arquivo, aguarde..." << std::endl;
            auto inicio = std::chrono::high_resolution_clock::now();
            std::string linha_antiga;



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
                std::cout << AMARELO << "... [ " << total - 20 << " linhas ocultas para não poluir o terminal ] ...\n" << RESET;
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
    std::cout << "digite ':help' para comandos e ':s' para salvar e sair\n\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer do teclado

    while(true) {
        std::getline(std::cin, linha);
        if(linha == ":s") break;

        // COMANDO HELP
        if(linha == ":help"){
            std::cout<<AMARELO << "\n--- Axe PRODUCTIVITY ---\n";
            std::cout<<":v (visualizar, limites 50 linhas)\n";
            std::cout<<":e <linha> (editar linha especifica)\n";
            std::cout<<":d <linha> (deletar linha especifica)\n";
            std::cout<<":s (salvar e sair)\n";
            std::cout<<RESET;
        }

        // COMANDO VISUALIZAR
        if(linha == ":v"){
            int total = buffer.size();
            std::cout<<"\n--- VISUALIZAção (Total: "<<total<<" linhas) ---\n";
            int limite = (total > 50) ? 50 : total;
            for (int i = 0; i < limite; ++i) {
                std::cout << CINZA << std::setw(6) << i+1 << " | " << RESET << buffer[i] << "\n";
            }
            if(total > 50) std::cout << AMARELO << "... (mais " << total-50 << " linhas ocultas) ...\n" << RESET;
            continue;
        }
        

        // COMANDO: EDITAR OU DELETAR
        if(linha.size() > 3 && (linha.substr(0, 3) == ":e " || linha.substr(0, 3) == ":d ")) {
            try {
                int num = std::stoi(linha.substr(3)) - 1;
                if (num >= 0 && (size_t)num < buffer.size()) {
                    if (linha[1] == 'e') {
                        std::cout << "Linha " << num+1 << " atual: " << buffer[num] << "\nNova: ";
                        std::string nova;
                        std::getline(std::cin, nova);
                        buffer[num] = nova;
                        std::cout << VERDE << "[OK] Editado!\n" << RESET;
                    } else {
                        buffer.erase(buffer.begin() + num);
                        std::cout << VERMELHO << "[OK] Deletado!\n" << RESET;
                    }
                } else {
                    std::cout << AMARELO << "[!] Linha fora do limite.\n" << RESET;
                }
            } catch (...) {
                std::cout << AMARELO << "[!] Use :e <num> ou :d <num>\n" << RESET;
            }
            continue;
        }

        // TEXTO PADRAO
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

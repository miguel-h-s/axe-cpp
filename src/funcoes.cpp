#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <vector>
#include <filesystem>
#include "axe.hpp"

namespace fs =  std::filesystem;

void menu() {
    std::cout << "1 - criar e escrever em um arquivo\n";
    std::cout << VERMELHO << "0 - sair\n" << RESET;
}

void criar_escrever(const std::string& nome_fornecido) {
    std::string nome_arquivo = nome_fornecido;
    int opcao_arquivo;
    std::vector<std::string> buffer; // buffer de RAM
    bool modificado = false; // sistema dirty buffer
    
    if (nome_arquivo == "") {
        std::cout << "\nFile: ";
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

            
            std::string linha_antiga;



            // LEITURA ULTRA RÁPIDA PARA A RAM
            while (std::getline(arquivo_leitura, linha_antiga)) {
                buffer.push_back(linha_antiga);
            }

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

            std::cout << std::flush;
        } else {
            std::cout << AMARELO << "[AVISO] Arquivo novo ou não encontrado.\n" << RESET;
        }
    }

    // MODO DE EDIÇÃO
    std::string linha;
    std::cout << CINZA << "[Axe: " << nome_arquivo << "]" << RESET << std::endl;
    std::cout << "digite ':help' para a lista de comandos\n";

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
            std::cout<<":w <nome> (mudar nome do arquivo para salvamento)\n";
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
                        modificado = true;
                        std::cout << VERDE << "[OK] Editado!\n" << RESET;
                    } else {
                        buffer.erase(buffer.begin() + num);
                        modificado = true;
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

        // COMANDO: SALVAR COM NOME ESPECÍFICO (:w nome.txt)
        if(linha.size() > 3 && linha.substr(0, 3) == ":w ") {
            std::string novo_nome = linha.substr(3);
            if (!novo_nome.empty()) {
                nome_arquivo = novo_nome; // Atualiza o nome que será usado no final
                modificado = true;        // Força o salvamento já que o nome mudou
                std::cout << VERDE << "[Axe] Nome do arquivo alterado para: " << nome_arquivo << RESET << std::endl;
            } else {
                std::cout << AMARELO << "[!] Digite um nome após o :w\n" << RESET;
            }
            continue;
        }

        // checa se o usuario digitou um comando invalido
        if (!linha.empty() && linha[0] == ':') {
            std::cout << AMARELO << "[!] Comando desconhecido. Use :help para ver a lista de comandos\n" << RESET;
            continue; // Ignora e volta para o início do loop sem salvar no buffer
        }

        // TEXTO PADRAO
        buffer.push_back(linha); // Adiciona ao que já estava na RAM
        modificado = true;
    }

    // Antes de salvar, se por algum motivo o nome_arquivo ainda estiver vazio
    while (nome_arquivo.empty()) {
        std::cout << AMARELO << "\n[!] O arquivo ainda não tem nome. Salvar como: " << RESET;
        std::cin >> nome_arquivo;
    }

    
    // SALVAMENTO FINAL INTELIGENTE
    if (modificado) {
        // Abrimos para escrita (sobrescrevendo o antigo com o que está no buffer da RAM)
        std::ofstream Arquivo(nome_arquivo, std::ios::out); 
        
        if (Arquivo.is_open()) {
            for (const std::string& l : buffer) {
                Arquivo << l << "\n";
            }
            Arquivo.close();
            std::cout << VERDE << "[OK] Alterações salvas em: " << nome_arquivo << RESET << std::endl;
        } else {
            std::cerr << VERMELHO << "[ERRO] Falha crítica ao gravar no disco!" << RESET << std::endl;
        }
    } else {
        // Se o usuário não mudou nada, o programa apenas avisa e fecha o arquivo virtualmente
        std::cout << CINZA << "[Axe] Nenhuma alteração detectada. Arquivo mantido intacto." << RESET << std::endl;
    }
}

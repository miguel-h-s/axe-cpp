#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <filesystem>
#include <limits>

#include "axe.hpp"
#include "assets.hpp"
#include "messages.hpp"

namespace fs =  std::filesystem;

void menu() {
    std::cout << "1 - criar e escrever em um arquivo\n";
    std::cout << VERMELHO << "0 - sair\n" << RESET;
}

void apresentacao() {
    std::cout << VERMELHO << AXE_LOGO << RESET << "\n";
    std::cout << DOURADO << "Axe Editor v1.3.0 |  The Derusting" << RESET << "\n";
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

    std::cout << std::flush;
    std::cin >> opcao_arquivo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
            std::cout << Msg::aviso_novo << "\n";
        }
    }

    // MODO DE EDIÇÃO
    std::string linha;
    std::cout << CINZA << "[Axe: " << nome_arquivo << "]" << RESET << std::endl;
    std::cout << Msg::aviso_help << "\n";

    
    while(true) {
        std::cout << CINZA << std::setw(4) << buffer.size() + 1 << " | " << RESET;
        std::getline(std::cin, linha);
        if(linha == ":s") break;

        // COMANDO HELP
        if(linha == ":help"){
            std::cout << Msg::help_menu << "\n";
            continue;
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
                        std::cout << Msg::editado << "\n";
                    } else {
                        buffer.erase(buffer.begin() + num);
                        modificado = true;
                        std::cout << Msg::deletado << "\n";
                    }
                } else {
                    std::cout << Msg::erro_limite << "\n";
                }
            } catch (...) {
                std::cout << Msg::erro_sintaxe << "\n";
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
            std::cout << Msg::erro_comando << "\n";
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

    
    if (modificado) {
        int escolha;
        std::cout << "\n" << Msg::config_header << "\n";
        std::cout << " 1 - Sobrescrever (Apaga o antigo e grava o novo)\n";
        std::cout << " 2 - Anexar (Adiciona ao final do arquivo existente)\n";
        std::cout << " 3 - Descartar alterações e sair\n";
        std::cout << " Escolha: ";
        std::cin >> escolha;

        if (escolha == 1 || escolha == 2) {
            // Se escolha for 2, usamos ios::app (Append), senão usamos ios::out (Overwrite)
            std::ios_base::openmode modo = (escolha == 2) ? std::ios::app : std::ios::out;
            
            std::ofstream Arquivo(nome_arquivo, modo); 
            
            if (Arquivo.is_open()) {
                for (const std::string& l : buffer) {
                    Arquivo << l << "\n";
                }
                Arquivo.close();
                std::cout << Msg::salvo_em(nome_arquivo) << "\n";
            } else {
                std::cerr << Msg::erro_critico << "\n";
            }
        } else {
            std::cout << AMARELO << "[Aviso] Alterações descartadas!\n" << RESET;
        }
    }
}

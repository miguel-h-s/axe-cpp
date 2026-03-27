#include <cstdlib>

#include "engine.hpp"
#include "assets.hpp"
#include "messages.hpp"
#include "axe.hpp"

void carregar_para_ram(const std::string& nome, std::vector<std::string>& buffer) {
    if (!fs::exists(nome)) {
        std::cout << Msg::arquivo_novo << "\n";
        return;
    }

    std::ifstream arquivo(nome);
    if (arquivo.is_open()) {
        std::cout << Msg::loading << "\n";
        auto tamanho_bytes = fs::file_size(nome);
        buffer.reserve(tamanho_bytes / 30); 

        std::string linha;
        while (std::getline(arquivo, linha)) {
            buffer.push_back(linha);
        }
        arquivo.close();
    }
}

void exibir_paginado(const std::vector<std::string>& buffer) {
    int total = buffer.size();
    if (total == 0) return;

    std::cout << Msg::view_header << " (" << total << " linhas) ---\n";
    
    if (total > 30) {
        for (int i = 0; i < 10; ++i) 
            std::cout << CINZA << std::setw(4) << i+1 << " | " << RESET << buffer[i] << "\n";
        
        std::cout << Msg::linhas_ocultas << "\n";
        
        for (int i = total - 10; i < total; ++i) 
            std::cout << CINZA << std::setw(4) << i+1 << " | " << RESET << buffer[i] << "\n";
    } else {
        for (int i = 0; i < total; ++i) 
            std::cout << CINZA << std::setw(4) << i+1 << " | " << RESET << buffer[i] << "\n";
    }
}

void processar_edicao(std::vector<std::string>& buffer, std::string& nome_arquivo, bool& modificado) {
    std::string linha;
    std::cout << Msg::editando_file << nome_arquivo << "]" << RESET << "\n";
    std::cout << Msg::aviso_help << "\n";

    while(true) {
        // Mostra o número da próxima linha que será escrita
        std::cout << CINZA << std::setw(4) << buffer.size() + 1 << " | " << RESET;
        if (!std::getline(std::cin, linha)) break;

        // --- COMANDOS TIPO 1: SIMPLES ---
        if (linha == ":q!") { std::cout << Msg::abortar << "\n"; modificado = false; return; }
        if (linha == ":s") break;
        if (linha == ":v") { exibir_paginado(buffer); continue; }
        if (linha == ":help") { std::cout << Msg::help_menu; continue; }

        if (linha == ":path") {
            try {
                // fs::absolute transforma o nome do arquivo no caminho completo do Linux
                std::cout << AMARELO << "[Caminho]: " << RESET << fs::absolute(nome_arquivo).string() << "\n";
            } catch (...) {
                std::cout << VERMELHO << "[Erro] Não foi possível resolver o caminho.\n" << RESET;
            }
            continue; // Essencial para não tratar o comando como texto!
        } 

        if (linha == ":!") {
            // Limpa a tela ou avisa que está saindo temporariamente
            std::cout << "\033[1;33m\n[ Axe: Abrindo Shell Temporário ]\033[0m" << std::endl;
            std::cout << "Dica: Digite 'exit' para retornar ao Axe.\n" << std::endl;

        
            // O Axe fica "congelado" aqui até você sair do bash
            system("bash"); 

            // Quando você digita 'exit' no terminal, o código volta para cá
            std::cout << "\033[1;32m\n[ Bem-vindo de volta ao Axe! ]\033[0m" << std::endl;
        }

        // --- COMANDOS TIPO 2: COM ARGUMENTOS (:e, :d, :w) ---
        
        // Comando :e (Editar)
        if (linha.substr(0, 3) == ":e ") {
            try {
                int num = std::stoi(linha.substr(3)) - 1;
                if (num >= 0 && num < (int)buffer.size()) {
                    std::cout << "Nova linha " << num + 1 << ": ";
                    std::string nova;
                    std::getline(std::cin, nova);
                    buffer[num] = nova;
                    modificado = true;
                    std::cout << Msg::editado << "\n";
                } else { std::cout << Msg::erro_limite << "\n"; }
            } catch (...) { std::cout << Msg::erro_sintaxe << "\n"; }
            continue;
        }

        


        // Comando :d (Deletar)
        if (linha.substr(0, 3) == ":d ") {
            try {
                int num = std::stoi(linha.substr(3)) - 1;
                if (num >= 0 && num < (int)buffer.size()) {
                    buffer.erase(buffer.begin() + num);
                    modificado = true;
                    std::cout << Msg::deletado << "\n";
                } else { std::cout << Msg::erro_limite << "\n"; }
            } catch (...) { std::cout << Msg::erro_sintaxe << "\n"; }
            continue;
        }

        // Comando :w (Mudar nome do arquivo - O que você sentiu falta!)
        if (linha.substr(0, 3) == ":w ") {
            std::string novo_nome = linha.substr(3);
            if (novo_nome.empty() || novo_nome.find_first_not_of(' ') == std::string::npos) {
                std::cout << Msg::erro_nome_vazio << "\n";
            } else {
                nome_arquivo = novo_nome;
                std::cout << Msg::nome_alterado << nome_arquivo << "\n";
            }
            
            continue;
        }

        // --- TRATAMENTO DE ERRO DE COMANDO ---
        if (!linha.empty() && linha[0] == ':') {
            std::cout << Msg::erro_comando << "\n";
            continue;
        }

        


        // --- SE NÃO FOR COMANDO, É TEXTO ---
        buffer.push_back(linha);
        modificado = true;
    }
}

void salvar_final(std::vector<std::string>& buffer, std::string& nome_arquivo, bool modificado) {
    if (!modificado) {
        std::cout << Msg::intacto << "\n";
        return;
    }

    int escolha;
    std::cout << Msg::config_header << "\n";
    std::cout << Msg::config_opcoes;
    
    if (!(std::cin >> escolha)) return;
    std::cin.ignore(); // Limpa o buffer após o cin >> escolha

    if (escolha == 3) {
        std::cout << Msg::descartado << "\n";
        return;
    }

    // garante que o caminho exista
    fs::path p(nome_arquivo);
    if (p.has_parent_path() && !fs::exists(p.parent_path())) {
        std::cout << Msg::criando_diretorios << "\n";
        fs::create_directories(p.parent_path());
    }

    std::ios_base::openmode modo = (escolha == 2) ? std::ios::app : std::ios::out;
    std::ofstream arquivo(nome_arquivo, modo);

    if (arquivo.is_open()) {
        for (const auto& l : buffer) arquivo << l << "\n";
        arquivo.close();
        std::cout << Msg::salvo_em(nome_arquivo) << "\n";
    } else {
        std::cerr << Msg::erro_critico << "\n";
    }
}
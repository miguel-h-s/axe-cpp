#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <string>
#include "axe.hpp"

namespace Msg {
    // --- CABEÇALHOS E INTERFACE ---
    const std::string versao = DOURADO + "Axe Editor v1.3.1 Alpha| The Derusting" + RESET;
    const std::string menu_opcoes = "1 - criar e escrever em um arquivo\n" + VERMELHO + "0 - sair" + RESET;
    const std::string prompt_opcao = "opção: ";
    
    // --- CONFIGURAÇÃO DE ARQUIVO ---
    const std::string config_header = "\n--- CONFIGURAÇÃO DO ARQUIVO ---";
    const std::string config_opcoes = "opções de escrita:\n 1 - sobrescrever arquivo\n 2 - não sobrescrever (carregar existente)";
    
    // --- MODO EDIÇÃO / HELP ---
    const std::string help_menu = AMARELO + "\n--- Axe PRODUCTIVITY ---\n" +
                                ":v (visualizar, limites 50 linhas)\n" +
                                ":e <linha> (editar linha especifica)\n" +
                                ":d <linha> (deletar linha especifica)\n" +
                                ":s (salvar e sair)\n" +
                                ":w <nome> (mudar nome do arquivo para salvamento)\n" + RESET;
    
    const std::string aviso_help = "digite ':help' para a lista de comandos";

    // --- ALERTAS E ERROS ---
    const std::string erro_comando = AMARELO + "[!] Comando desconhecido. Use :help para ver a lista de comandos" + RESET;
    const std::string erro_limite = AMARELO + "[!] Linha fora do limite." + RESET;
    const std::string erro_sintaxe = AMARELO + "[!] Use :e <num> ou :d <num>" + RESET;
    const std::string aviso_novo = AMARELO + "[AVISO] Arquivo novo ou não encontrado." + RESET;
    const std::string erro_critico = VERMELHO + "[ERRO] Falha crítica ao gravar no disco!" + RESET;
    
    // --- SUCESSO E STATUS ---
    const std::string editado = VERDE + "[OK] Editado!" + RESET;
    const std::string deletado = VERMELHO + "[OK] Deletado!" + RESET;
    const std::string intacto = CINZA + "[Axe] Nenhuma alteração detectada. Arquivo mantido intacto." + RESET;
    
    // Função utilitária para mensagens dinâmicas
    inline std::string salvo_em(std::string nome) {
        return VERDE + "[OK] Alterações salvas em: " + nome + RESET;
    }
}

#endif
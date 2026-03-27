#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <string>
#include "axe.hpp" // Para as cores

namespace Msg {
    // --- CABEÇALHOS E INTERFACE ---
    const std::string menu_opcoes = "1 - criar e escrever em um arquivo\n" + VERMELHO + "0 - sair" + RESET;
    
    // --- ENGINE E CARREGAMENTO ---
    const std::string loading = VERDE + "[Axe] Carregando arquivo para a RAM..." + RESET;
    const std::string arquivo_novo = AMARELO + "[Axe] Arquivo novo detectado." + RESET;
    const std::string view_header = "\n--- AXE VIEW ---";
    const std::string linhas_ocultas = AMARELO + "... [ linhas ocultas para não poluir o terminal ] ..." + RESET;

    // --- CONFIGURAÇÃO DE SALVAMENTO ---
    const std::string config_header = "\n" + DOURADO + "--- CONFIGURAÇÃO DO ARQUIVO ---" + RESET;
    const std::string config_opcoes = " 1 - Sobrescrever | 2 - Anexar | 3 - Descartar\n Escolha: ";
    
    // --- MODO EDIÇÃO / HELP ---
    const std::string editando_file = CINZA + "[Editando: " + RESET;
    const std::string help_menu = AMARELO + "\n--- Axe PRODUCTIVITY ---\n" +
                                ":v (visualizar buffer)\n" +
                                ":e <linha> (editar linha)\n" +
                                ":d <linha> (deletar linha)\n" +
                                ":s (salvar e sair)\n" +
                                ":q! (sair sem salvar)\n" 
                                ":path (vê o caminho em que você esta tentando salvar/escrever)\n"
                                ":! (abre um shell temporario)\n" + RESET;

    
    const std::string aviso_help = "digite ':help' para a lista de comandos";


    

    // --- ALERTAS E ERROS ---
    const std::string editado = VERDE + "[OK] Editado!" + RESET;
    const std::string deletado = VERMELHO + "[OK] Deletado!" + RESET;
    const std::string erro_limite = AMARELO + "[!] Linha fora do limite." + RESET;
    const std::string erro_sintaxe = AMARELO + "[!] Use :e <num> ou :d <num>" + RESET;
    const std::string erro_comando = AMARELO + "[!] Comando desconhecido. Use :help" + RESET;
    const std::string abortar = AMARELO + "\n[Axe] Abortando tudo! Voltando ao terminal..." + RESET;
    const std::string erro_critico = VERMELHO + "[ERRO] Falha crítica ao gravar no disco!" + RESET;
    const std::string descartado = AMARELO + "[AVISO] Alterações descartadas!" + RESET;
    const std::string intacto = CINZA + "[Axe] Nenhuma alteração detectada." + RESET;
    

    // Erros de Validação
    const std::string erro_nome_vazio = VERMELHO + "[!] Nome de arquivo invalido!" + RESET;
    const std::string erro_input_menu = VERMELHO + "\n[!] Use apenas numeros no menu!" + RESET;
    const std::string erro_path = VERMELHO + "[Erro] Nao foi possivel resolver o caminho." + RESET;

    // Feedbacks de Ação
    const std::string criando_diretorios = AMARELO + "[Axe] Criando diretorios inexistentes..." + RESET;
    const std::string nome_alterado = VERDE + "[Axe] Nome do arquivo alterado para: " + RESET;
    const std::string voltando_menu = CINZA + "[Axe] Retornando ao menu principal..." + RESET;

    // Status de Sistema
    const std::string prompt_opcao = "opção: ";
    const std::string prompt_filename = AMARELO + "File name: " + RESET;

    // Funções dinâmicas
    inline std::string salvo_em(std::string nome) {
        return VERDE + "[OK] Alterações salvas em: " + nome + RESET;
    }
}

#endif
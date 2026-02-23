#ifndef RANO_H
#define RANO_H

#include <string>
#include <vector>

// Cores e Estilos
const std::string AMARELO   = "\033[33m";
const std::string RESET     = "\033[0m";
const std::string VERMELHO  = "\033[31m";
const std::string VERDE     = "\033[32m";
const std::string CINZA = "\033[38;5;237m";

// Protótipos das funções
// Note que o "= """ (valor padrão) só fica aqui no .h
void apresentacao();
void menu();
void creditos();
void criar_escrever(const std::string& nome_fornecido = "");
void registro_atualizacao();

#endif
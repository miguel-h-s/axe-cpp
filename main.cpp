#include <iostream>
#include <string>
#include "axe.hpp"

int main(int argc, char* argv[]) {

    // Caso o usuário abra via terminal direto
    if (argc == 2) {
        (void)std::system("clear"); // Limpa primeiro
        apresentacao();             // Carrega o texto na memória
        std::cout << std::flush;    // DESPEJA o texto no monitor AGORA
        criar_escrever(argv[1]);    // Entra na função
        return 0; 
    }
    
    int opcao;
    while(true) {
        apresentacao();
        menu();
        std::cout << "opção: " << std::flush;
        if (!(std::cin >> opcao)) break; // Evita loop infinito se digitar letra

        if (opcao == 0) break;
        
        std::cout << "\n";
        switch (opcao) {
            case 1: criar_escrever(); break;
            case 2: creditos(); break;
            case 3: registro_atualizacao(); break;
            default: std::cout << "Opcao invalida!\n";
        }
        std::cout << "\n";
    }

    return 0;
}
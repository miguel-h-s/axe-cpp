#include <iostream>
#include <string>
#include "axe.hpp"
#include "assets.hpp"

int main(int argc, char* argv[]) {

    // Caso o usuário abra via terminal direto
    if (argc == 2) {
        (void)std::system("clear"); // Limpa primeiro
        std::cout << std::flush;    // DESPEJA o texto no monitor AGORA
        criar_escrever(argv[1]);    // Entra na função
        return 0; 
    }
    
         

    int opcao;
    
    while(true) {
        std::system("clear");
        apresentacao();
        menu();
        std::cout << "opção: " << std::flush;
        if (!(std::cin >> opcao)) break; // Evita loop infinito se digitar letra

        if (opcao == 0) break;
        
        std::cout << "\n";
        switch (opcao) {
            case 1: criar_escrever(); break;
            default: std::cout << "Opcao invalida!\n";
        }
        std::system("clear");
    }

    return 0;
}
#include <iostream>
#include <string>
#include "rano.h"

int main(int argc, char* argv[]) {
    // Caso o usuário abra via terminal direto
    if (argc == 2) {
        std::system("clear");
        apresentacao();
        criar_escrever(argv[1]); 
        return 0; 
    }
    
    int opcao;
    while(true) {
        apresentacao();
        menu();
        std::cout << "opção: ";
        if (!(std::cin >> opcao)) break; // Evita loop infinito se digitar letra

        if (opcao == 0) break;
        
        std::cout << "\n";
        switch (opcao) {
            case 1: criar_escrever(); break;
            case 2: creditos(); break;
            default: std::cout << "Opcao invalida!\n";
        }
        std::cout << "\n";
    }

    return 0;
}
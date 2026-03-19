# Axe v1.3.0 Alpha | "The Derusting"

## O que é o Axe?
Axe é um editor de texto, escrito **100%** em **C++**, de código aberto e **fortemente** inspirado na ferramenta ``nano`` e ``vim``!

## Feito **100%** pra funcionar em linux
<img src="https://github.com/user-attachments/assets/9ebb2674-febd-4c61-9a90-2963f2f5dbe2" width="100">


## Especificações do Axe
- **Edição In-Memory:** As alterações são feitas na RAM e só gravadas no disco ao salvar.
- **Modo Append:** Visualize o conteúdo atual antes de adicionar novas linhas.
- **Interface Colorida:** Feedback visual com cores ANSI (Verde para sucesso, Vermelho para erros).
- **Modularizado:** Estrutura organizada em Header e Source files.
- **Desempenho:** revelou que o Axe processa arquivos de 10 milhões de linhas em menos de 10 segundos!!
- **Dirty Buffer System:** salvamento inteligente que detecta se você mexeu ou não no seu arquivo, assim não sobscrevendo se não digitou nada nele.

## Segurança e Privacidade
O Axe é um projeto de código aberto e focado em privacidade:
- **Sem conexões externas:** O código não possui bibliotecas de rede; tudo é processado localmente no seu terminal.
- **Transparência:** Sinta-se à vontade para mudar o código fonte na sua maquina antes de compilar.
- **Offline:** O editor funciona 100% sem internet.

## Tabela de comandos(introduzida na versão 1.2.0 Alpha)

Dentro do modo de edição, o Axe aceita comandos rápidos para facilitar o seu workflow:

| Comando | Descrição |
| :--- | :--- |
| `:help` | Mostra o guia de comandos rápido |
| `:v` | Visualiza as linhas do arquivo (limite de 50 para performance) |
| `:e <linha>` | Edita uma linha específica (ex: `:e 10`) |
| `:d <linha>` | Deleta uma linha específica (ex: `:d 5`) |
| `:s` | Salva as alterações e sai do editor |

## Requisitos
- **Compilador:** g++ (suporte a C++17 ou superior)
- **Sistema:** Linux (testado em Debian/Arch)
- **Ferramentas:** `make` para automação do build

## Estrutura do Projeto
O Axe segue uma organização modular para facilitar a manutenção:
- `/src`: Lógica principal (`main.cpp`, `funcoes.cpp`, `assets.cpp`).
- `/include`: Headers e definições globais (`axe.hpp`).
- `/obj`: Objetos de compilação (gerados via Makefile).

## screenshots do projeto
<img width="1366" height="768" alt="Captura de tela_2026-03-18_20-59-49" src="https://github.com/user-attachments/assets/63ec4d95-4977-4459-a84c-316ecb3ce6e5" />


## Como instalar e usar

Para rodar o Axe no seu terminal Linux:

1. **Clone o repositório:**
   ```bash
   git clone https://github.com/miguel-h-s/axe-cpp.git
   ```

2. **Entre na pasta:**
  ```bash
  cd axe-cpp
  ```
3. **Compile:**
  ```bash
  make
  ```

4. **Execute:**
   ```bash
   ./axe #abre o Axe no menu
   ```
   ou execute com o nome do arquivo em que quer escrever/abrir:
   ```bash
   ./axe nomedoarquivo.txt
   ```

Desenvolvido com amor e C++ por [Miguel](https://github.com/miguel-h-s)

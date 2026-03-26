# Axe v1.5.1 Alpha | "The Diamond Axe Update"

> "estou trabalhando na TUI, juro!"

## O que é o Axe?
Axe é um editor de texto, escrito **100%** em **C++**, de código aberto e **fortemente** inspirado nas ferramentas ``nano``(inspiração principal), ``vim``(inpiração dos comandos) e ``ed``(inspiração de mecanica)!

## Feito **100%** pra funcionar em linux
<img src="https://github.com/user-attachments/assets/9ebb2674-febd-4c61-9a90-2963f2f5dbe2" width="100">


## Especificações do Axe
- **Edição In-Memory:** As alterações são feitas na RAM e só gravadas no disco ao salvar.
- **Modo Append:** Visualize o conteúdo atual antes de adicionar novas linhas.
- **Interface Colorida:** Feedback visual com cores ANSI (Verde para sucesso, Vermelho para erros).
- **Modularizado:** Estrutura organizada em Header e Source files.
- **Desempenho:** revelou que o Axe processa arquivos de 10 milhões de linhas em menos de 10 segundos!!
- **Dirty Buffer System:** salvamento inteligente que detecta se você mexeu ou não no seu arquivo, assim não sobscrevendo se não digitou nada nele.
- **Language Agnostic(independente de idioma):** use Axe independente de sua lingua editando apenas o arquivo [messages.hpp](include/messages.hpp)!

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
| `:w <nome do arquivo>` | Renomeia o arquivo em que esta editando |
nota: a lista de comandos no README:md não pode estar atualizada como o comando `:help` do Axe!


## Requisitos
- **Compilador:** g++ (suporte a C++17 ou superior)
- **Sistema:** Linux (testado em Debian/Arch)
- **Ferramentas:** `make` para automação do build

## Estrutura do Projeto
O Axe segue uma organização modular para facilitar a manutenção:
- `/src`: Lógica principal (`main.cpp`, `funcoes.cpp`, `assets.cpp`).
- `/include`: Headers e definições globais (`axe.hpp`).
- `/obj`: Objetos de compilação (gerados via Makefile).

## You don't speak Portuguese?
Make sure to edit the [messages.hpp](include/messages.hpp) file for error commands in your language!

## screenshots da ultima versão(1.4.1) com a nova engine
<img width="1366" height="768" alt="Captura de tela_2026-03-20_15-13-18" src="https://github.com/user-attachments/assets/bb212ccb-3dd8-4d1b-9fda-c99c4c3e5d37" />

<img width="1366" height="768" alt="Captura de tela_2026-03-20_15-20-55" src="https://github.com/user-attachments/assets/68487ad2-4e4e-49cf-9341-43524eac12f5" />

## Como instalar e usar!

### instalando

1. clone o repositório
``git clone https://github.com/miguel-h-s/axe-cpp.git``

2. entre na pasta
``cd axe-cpp``

3. prepare e compile o binario
```bash
cmake -B build   # Cria a receita de compilação na pasta build
cmake --build build  # Cozinha o código e gera o executável
```

**4. instalando em sua distribuição(opcional)**
Este passo coloca o Axe em /usr/local/bin, permitindo que você use o seu "machado" em qualquer diretório.
``sudo cmake --install build``

### usando

existem DUAS formas de invocar seu machado!

**1. uso global(se você instalou)**
abre o editor de qualquer pasta na sua distro
```bash
axe                       # Abre no menu principal
axe caminho/do/arquivo    # Abre/Cria um arquivo específico
```

**2. uso local(sem instalação)**
Roda o binário diretamente de onde ele foi construído:

```Bash
./build/axe
./build/axe meu_arquivo.txt
```

### desinstalando
Caso queira remover o Axe do sistema:

```Bash
sudo rm /usr/local/bin/axe
```
**dica:** Para limpar os arquivos de compilação e começar do zero, basta apagar a pasta build: rm -rf build.
Desenvolvido com amor e C++ por [Miguel](https://github.com/miguel-h-s)

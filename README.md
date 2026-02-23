# Axe v1.1.0 Alpha | Power Edition - antigo Rano
**> sinta o poder do C++ em seu terminal Linux!**

## O que é o Axe?
Axe é um editor de texto, escrito **100%** em **C++**, de código aberto e **fortemente** inspirado na ferramenta ``nano`` e ``vim``!

## Especificações do Rano
- **Edição In-Memory:** As alterações são feitas na RAM e só gravadas no disco ao salvar.
- **Modo Append:** Visualize o conteúdo atual antes de adicionar novas linhas.
- **Interface Colorida:** Feedback visual com cores ANSI (Verde para sucesso, Vermelho para erros).
- **Modularizado:** Estrutura organizada em Header e Source files.
- **Desempenho:** um teste com **500 mil** linhas de arquivo revelou que o Axe abre isto em **0.600** milisegundos!

## Segurança e Privacidade
O Axe é um projeto de código aberto e focado em privacidade:
- **Sem conexões externas:** O código não possui bibliotecas de rede; tudo é processado localmente no seu terminal.
- **Transparência:** Sinta-se à vontade para mudar o código fonte na sua maquina antes de compilar.
- **Offline:** O editor funciona 100% sem internet.

## Como instalar e usar

Para rodar o Axe no seu terminal Linux:

1. **Clone o repositório:**
   ```bash
   # desatualizado!
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

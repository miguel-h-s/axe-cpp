# Rano v1.0 Alpha
**> sinta o poder do C++ em seu terminal Linux!**

## O que é o Rano?
Rano é escrito **100%** em **C++**, de código aberto e **fortemente** inspirado na ferramenta ``nano``!

## Especificações do Rano
- **Edição In-Memory:** As alterações são feitas na RAM e só gravadas no disco ao salvar.
- **Modo Append:** Visualize o conteúdo atual antes de adicionar novas linhas.
- **Interface Colorida:** Feedback visual com cores ANSI (Verde para sucesso, Vermelho para erros).
- **Modularizado:** Estrutura organizada em Header e Source files.

## Como instalar e usar

Para rodar o Rano no seu terminal Linux:

1. **Clone o repositório:**
   ```bash
   git clone [https://github.com/miguel-h-s/rano-cpp.git](https://github.com/miguel-h-s/rano-cpp.git)
   ```

2. **Entre na pasta:**
  ```bash
  cd rano-cpp
```
3. **Compile:**
  ```bash
  make
  ```

4. **Execute:**
   ```bash
   ./rano #abre o Rano no menu
   ```
   ou execute com o nome do arquivo em que quer escrever/abrir:
   ```bash
   ./rano nomedoarquivo.txt
   ```

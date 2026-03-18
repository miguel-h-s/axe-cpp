# Variáveis de Compilação
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN = axe

# Lista de arquivos fonte e objetos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Regra padrão: Compila tudo
all: $(BIN)

# Linkagem final do executável
$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $(BIN)
	@echo "--- Axe Editor compilado com sucesso! ---"

# Compilação dos arquivos .cpp em .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria a pasta de objetos se ela não existir
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpa os arquivos temporários
clean:
	rm -rf $(OBJ_DIR) $(BIN)
	@echo "--- Limpeza concluída ---"

.PHONY: all clean
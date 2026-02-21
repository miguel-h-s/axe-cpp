# Nome do executável
TARGET = rano

# Arquivos fonte
SRCS = main.cpp funcoes.cpp

# Comando do compilador
CC = g++

# Flags (avisos e padrão C++17)
CFLAGS = -Wall -std=c++17

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
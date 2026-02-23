# Nome do executável
TARGET = axe

# Arquivos fonte
SRCS = main.cpp funcoes.cpp

# Comando do compilador
CC = g++

CFLAGS = -Wall -std=c++17 -O3 -march=native

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
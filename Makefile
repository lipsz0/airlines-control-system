CC = gcc
CFLAGS = -Wall -I./include
SRC = ./src
OBJS = ./temp
TARGET = airlines_system

# Lista de objetos necessários (baseado no seu código original)
# Note: main.o é tratado separadamente pois o main.c está na raiz
OBJECTS_LIST = $(OBJS)/archives.o \
							$(OBJS)/menu.o \
							$(OBJS)/register.o \
							$(OBJS)/reports.o \
							$(OBJS)/utils.o \
							$(OBJS)/validation.o \
							$(OBJS)/search.o \
							$(OBJS)/export.o \
							$(OBJS)/main.o

# .PHONY avisa ao make que 'all' e 'clean' não são arquivos reais
.PHONY: all clean setup

# A primeira regra é a padrão (executada ao digitar apenas 'make')
all: setup $(TARGET)

# Regra para linkar o executável final
$(TARGET): $(OBJECTS_LIST)
	$(CC) $(OBJECTS_LIST) -o $(TARGET)

# Regra genérica para compilar arquivos .c da pasta src para .o na pasta temp
# $< significa o arquivo de entrada (.c)
# $@ significa o arquivo de saída (.o)
$(OBJS)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra específica para o main.c (se estiver na raiz do projeto)
$(OBJS)/main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o $(OBJS)/main.o

# Garante que o diretório de objetos exista antes de compilar
setup:
	mkdir -p $(OBJS)

# Regra clean para limpar os arquivos temporários e o executável
clean:
	rm -rf $(OBJS)/*.o $(TARGET)
	@echo "Limpeza concluída."
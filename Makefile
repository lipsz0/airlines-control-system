CC = gcc
SRC = ./src
OBJS = ./temp
TARGET = airlines_system

all: objetos
	$(CC) $(OBJS)/*.o -o $(TARGET)

objetos:
	$(CC) -c $(SRC)/archives.c -o $(OBJS)/archives.o
	$(CC) -c $(SRC)/menu.c -o $(OBJS)/menu.o
	$(CC) -c $(SRC)/register.c -o $(OBJS)/register.o
	$(CC) -c $(SRC)/utils.c -o $(OBJS)/utils.o
	$(CC) -c $(SRC)/validation.c -o $(OBJS)/validation.o
	$(CC) -c main.c -o $(OBJS)/main.o

clean:
	rm -rf $(OBJS)/*.o $(TARGET)
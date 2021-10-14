TARGET=permission-converter
SRC=$(wildcard *.c)

CC=gcc
CFLAGS=

.PHONY: all clean

all: $(TARGET)

clean: 
	rm -r $(TARGET)

$(TARGET) : $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

CC      = gcc
CFLAGS  = -Wall -Wextra -g
TARGET  = mysh
OBJS    = main.o parser.o execute.o builtins.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c mysh.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
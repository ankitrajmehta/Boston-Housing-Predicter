CC = gcc
CFLAGS = -Wall -Wextra -pedantic
LDFLAGS = -lm

# Specify the name of your C program and the object files
TARGET = main
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to compile the C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
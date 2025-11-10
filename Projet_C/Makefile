CC = gcc
CFLAGS = -Wall -g
TARGET = pathfinding
SRCS = pathfinding.c library.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET) -lm

clean:
	rm -f $(OBJS) $(TARGET)

re: clean all
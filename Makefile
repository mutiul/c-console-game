CC := cc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic
TARGET := guessing-game
SOURCE := src/main.c

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

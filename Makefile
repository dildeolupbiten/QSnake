CC = g++

CFLAGS = -Iinclude

SRC_DIR = src
INC_DIR = include

SRC = $(wildcard $(SRC_DIR)/*.cpp)

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

TARGET = QSnake

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET) agent.dat

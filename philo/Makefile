NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -Iincludes

# Source files
SRC_DIR = srcs
SRCS = $(SRC_DIR)/actions.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/monitor.c \
	$(SRC_DIR)/threads.c \
	$(SRC_DIR)/utils.c

# Object files
OBJ_DIR = obj
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Criterion test sources
TEST_DIR = tests
TEST_SRCS = $(TEST_DIR)/test_parsing.c
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_BIN = unit_tests

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile tests
$(TEST_BIN): $(OBJ_DIR) $(OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJS) -o $@ -lcriterion

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

tests: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BIN)

re: fclean all

.PHONY: all clean fclean re tests
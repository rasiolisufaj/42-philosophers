NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes

SRC_DIR = srcs

SRCS = $(SRC_DIR)/actions.c \
	   $(SRC_DIR)/init.c \
	   $(SRC_DIR)/main.c \
	   $(SRC_DIR)/monitor.c \
	   $(SRC_DIR)/threads.c \
	   $(SRC_DIR)/utils.c

OBJS = $(SRCS:.c=.o)

# Criterion test sources
TEST_DIR = tests
TEST_SRCS = $(TEST_DIR)/test_parsing.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_BIN = unit_tests

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compile tests | MAKE SURE TO EXCLUDE MAIN.C FROM TESTS
$(TEST_BIN): $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(OBJS) -o $(TEST_BIN) -lcriterion

tests: $(TEST_BIN)
	./$(TEST_BIN)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
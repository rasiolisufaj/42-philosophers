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
	   $(SRC_DIR)/utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@make -C clean

fclean: clean
	@rm -f $(NAME)
	@make -C fclean

re: fclean all

.PHONY: all clean fclean re
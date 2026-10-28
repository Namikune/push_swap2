NAME    = push_swap
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I include -I libft
LIBFT   = libft/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS    = main.c
OBJS    = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/push_swap.h
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re

NAME    = push_swap
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -I include -I libft
LIBFT   = libft/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS    = main.c \
          John/handle_errors.c \
          John/simple_sort.c \
          John/sort_three.c \
          John/stack_init.c \
          sort/rank_numbers.c \
          stack/emit.c \
          stack/ops_push.c \
          stack/ops_rotate.c \
          stack/ops_rrorate.c \
          stack/ops_swap.c \
          stack/stack_utils.c \
          stack/stack.c \
          input/flags.c \
          bench/disorder
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

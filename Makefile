CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I/usr/include -Imlx_linux -O3
LDFLAGS =-Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -ljpeg

NAME = so_long

SRCS = \
$(addsuffix .c, \
	$(addprefix $(SRCS_DIR)/, \
		error \
		key_event \
		main \
		parse_map \
		render_map \
		utils \
		valid_path \
	) \
) \

OBJS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.o))
DEPS = $(addprefix $(OUT_DIR)/, $(SRCS:.c=.d))


SRCS = ./srcs/parse_map.c ./srcs/error.c ./srcs/key_event.c ./srcs/render_map.c \
		./srcs/main.c ./srcs/utils.c ./srcs/valid_path.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
		./libft/ft_split.c ./libft/ft_strdup.c ./libft/ft_strnstr.c ./libft/ft_strlen.c \
		./ft_printf/ft_printf.c ./ft_printf/ft_printf_utils.c ./ft_printf/format_put_num.c \
		./ft_printf/format_put_letter.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

val:re
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) > analysis 2>&1 ; tail analysis

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

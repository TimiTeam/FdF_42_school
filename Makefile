NAME = fdf

DIR_SRC = ./src/

DIR_OBJ = ./obj/

FILES = action_func.c additional_func.c get_next_line.c hook_func.c main.c make_color_func.c objects_worker.c  print_functions.c validate_map.c zoom_in_zoom_out.c

FLAGS = -Wall -Wextra -Werror

LIB_FT = -I libft/includes -L libft -lft

MINI_LIB = -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft
	clang $(FLAGS) -c $(addprefix $(DIR_SRC), $(FILES))
	mkdir -p obj
	mv $(OBJ) $(DIR_OBJ)
	clang $(FLAGS) $(addprefix $(DIR_OBJ), $(OBJ)) $(LIB_FT) $(MINI_LIB) -o $(NAME)

clean:
	make -C libft/ fclean
	/bin/rm -rf $(DIR_OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all


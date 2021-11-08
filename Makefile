NAME = cub3d
HEAD_PATH = includes/
SRCS_PATH = source/
OBJ_PATH = objects/
SRCS_LST = posiiiiiing.c main.c ft_split.c get_next_line.c utils.c rendering.c raycasting.c spriting.c \
			screenshooting.c input.c texturing.c forsaj.c map_parsing.c utils_part_two.c utils_part_three.c
OBJS_LST = $(patsubst %.c, %.o, $(SRCS_LST))
SRCS = $(addprefix $(SRCS_PATH),$(SRCS_LST))
OBJS = $(addprefix $(OBJ_PATH),$(OBJS_LST))
RM = rm -rf
CC = gcc
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror -I $(HEAD_PATH)
OFLAGS = -Wall -Wextra -Werror -I $(HEAD_PATH)
#OFLAGS = -Wall -Wextra -Werror -c -I $(HEAD_PATH)
DFLAGS = -g -fsanitize=address -I $(HEAD_PATH)

all: $(NAME)

$(NAME): $(OBJ_PATH) $(SRCS) 
	$(CC) $(OFLAGS) $(SRCS) $(MLXFLAGS) -o $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEAD_PATH)%.h
	$(CC)  $(MLXFLAGS)$(OFLAGS) $< -o $@ 

debug:
	$(CC) $(DFLAGS) $(SRCS) $(MLXFLAGS)  -o $(NAME)

re:	fclean all

clean:
	$(RM) $(OBJ_PATH)

fclean:
	$(RM) $(NAME)




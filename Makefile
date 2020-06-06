# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Malou <Malou@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/01 13:24:04 by Malou          #+#    #+#                 #
#    Updated: 2020/06/06 17:18:15 by rsteigen      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = doom

FLAGS = -Wall -Wextra -Werror -o

LIBFT = ./libft/

SDL = ./sdl/

SDL_FLAGS = `sdl2-config --cflags --libs`

SRCS = ./srcs/

SRCS_FILES = main doom_init game_loop doom_render sidedef_render \
	plane_projections slope_projections draw_sidedef draw_floor_ceiling \
	doom_input line_calculations move_position exit load_textures \
	sprite_init sprite_check

C_FILES = $(SRCS_FILES:%=$(SRCS)%.c)

O_FILES = $(C_FILES:%.c=%.o)

HEADERS = includes/doom.h

ADD_FILES = Makefile textures/

all: $(NAME)

%.o: %.c
	@gcc -g -c $(FLAGS) $@ $<

$(NAME) : $(O_FILES)
	@make re -C $(LIBFT)
	@gcc -I $(LIBFT) -L $(LIBFT) -lft $(C_FILES) $(FLAGS) $(NAME) $(SDL_FLAGS)
	@rm -f $(O_FILES)

clean :
	@make clean -C $(LIBFT)
	@rm -f $(O_FILES)
	@rm -f *#
	@rm -f *.o
	@rm -f *~
	@rm -f *.DS_Store
	@rm -Rf .vscode

fclean : clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)

re : fclean all

add : fclean
	@git add $(LIBFT) $(C_FILES) $(HEADERS) $(ADD_FILES) $(SDL)
	@git status

push :
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif
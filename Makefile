# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Malou <Malou@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/01 13:24:04 by Malou         #+#    #+#                  #
#    Updated: 2020/06/16 17:45:50 by jessicasmit   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = doom

FLAGS = -Wall -Wextra -Werror -o

LIBFT = ./libft2/libft

BMP = ./bmp/

SDL = ./sdl/

SDL_FLAGS = `sdl2-config --cflags --libs`

CORE = ./srcs/core/
EVENTS = ./srcs/events/
RENDER = ./srcs/render/
READ = ./srcs/read_file/

CORE_FILES = main doom_init sdl_init  game_loop line_calculations doom_update \
				exit
EVENTS_FILES = key_events mouse_events move_position move_position2
RENDER_FILES = doom_render sidedef_render plane_projections draw_sidedef \
				draw_floor load_textures
READ_FILES = add_info_to_lib error read_file main2

C_FILES = $(CORE_FILES:%=$(CORE)%.c) $(EVENTS_FILES:%=$(EVENTS)%.c) \
	$(RENDER_FILES:%=$(RENDER)%.c) $(READ_FILES:%=$(READ)%.c)

O_FILES = $(C_FILES:%.c=%.o)

HEADERS = includes/doom.h

ADD_FILES = Makefile textures

all: $(NAME)

%.o: %.c
	@gcc -g -c $(FLAGS) $@ $<

$(NAME) : $(O_FILES)
	@make re -C $(LIBFT)
	@make re -C $(BMP)
	@gcc -I $(LIBFT) -L $(LIBFT) bmp/lib_bmp.a -lft $(C_FILES) $(FLAGS) $(NAME) $(SDL_FLAGS)
	@rm -f $(O_FILES)

clean :
	@make clean -C $(LIBFT)
	@rm -f $(O_FILES)
	@rm -f *#
	@rm -f *~
	@rm -f *.DS_Store
	@rm -Rf .vscode

fclean : clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)

re : fclean all

add : fclean
	@git add $(LIBFT) $(C_FILES) $(HEADERS) $(ADD_FILES) $(SDL) $(BMP)
	@git status

push :
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif
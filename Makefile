# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Malou <Malou@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/01 13:24:04 by Malou         #+#    #+#                  #
#    Updated: 2020/07/03 14:21:34 by jessicasmit   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
RED = $(shell printf "\033[0;31m")

NAME = doom

FLAGS = -Wall -Wextra -Werror

LIBFT = libft/
BMP = bmp/
SDL = sdl/
SDL_FLAGS = `sdl2-config --cflags --libs`

CORE = srcs/core/
EVENTS = srcs/events/
RENDER = srcs/render/
READ = srcs/read_file/

CORE_FILES = main doom_init sdl_init  game_loop line_calculations doom_update \
				exit
EVENTS_FILES = key_events mouse_events move_position move_position2
RENDER_FILES = doom_render sidedef_render plane_projections draw_sidedef \
				draw_floor slope_projections horizontal_texture
READ_FILES = add_info_to_lib error read_file main2

C_FILES = $(CORE_FILES:%=$(CORE)%.c) $(EVENTS_FILES:%=$(EVENTS)%.c) \
	$(RENDER_FILES:%=$(RENDER)%.c) $(READ_FILES:%=$(READ)%.c)
O_FILES = $(C_FILES:srcs/%/%.c=.objects/%.o)

HEADERS = includes/doom.h
ADD_FILES = Makefile textures

all: $(NAME)

$(NAME): libft/libft.a bmp/lib_bmp.a .objects $(O_FILES)
	@gcc -o $@ -I $(LIBFT) -L $(LIBFT) bmp/lib_bmp.a bmp/libft/libft.a -lft $(C_FILES) $(FLAGS) $(SDL_FLAGS)
	@echo "$(GREEN)[√]$(WHITE) compiling done!"

.objects/%.o: srcs/%.c $(HEADERS)
	@$(CC) -c -o $@ $<
	@echo "$(GREEN)[+]$(WHITE) compiling $@"

.objects:
	@mkdir .objects

libft/libft.a:
	@make -C libft

bmp/lib_bmp.a:
	@make -C bmp

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(BMP)
	@rm -rf .objects
	@rm -f *#
	@rm -f *~
	@rm -f *.DS_Store
	@rm -rf .vscode
	@echo "cleaned $(OBJ_FILES)"

fclean: clean
	@make fclean -C $(LIBFT)
	@make fclean -C $(BMP)
	@rm -f $(NAME)
	@echo "cleaned $(NAME)"

re: fclean all

add: fclean
	@git add $(LIBFT) $(C_FILES) $(HEADERS) $(ADD_FILES) $(SDL) $(BMP)
	@git status

push:
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif
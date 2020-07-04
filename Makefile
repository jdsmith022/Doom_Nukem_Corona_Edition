# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Malou <Malou@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/01 13:24:04 by Malou         #+#    #+#                  #
#    Updated: 2020/06/20 13:27:10 by nde-wild      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
RED = $(shell printf "\033[0;31m")

NAME = doom
FLAGS = -Wall -Wextra -Werror

LIBFT = libft
BMP = bmp
SDL = sdl
SDL_FLAGS = `sdl2-config --cflags --libs`
LIB = $(LIBFT) $(BMP) $(SDL)

CORE = srcs/core/
EVENTS = srcs/events/
RENDER = srcs/render/
READ = srcs/read_file/
GAME_EDITOR = srcs/game_editor/

CORE_FILES = main doom_init sdl_init  game_loop line_calculations doom_update \
				exit
EVENTS_FILES = key_events mouse_events move_position move_position2
RENDER_FILES = doom_render sidedef_render plane_projections draw_sidedef \
				draw_floor slope_projections horizontal_texture put_texture
READ_FILES = add_info_to_lib error read_file main2
GAME_EDITOR_FILES = game_editor draw_bar sector sidedefs portal add_to_game mouse_events_game_editor

C_FILES = $(CORE_FILES:%=$(CORE)%.c) $(EVENTS_FILES:%=$(EVENTS)%.c) \
		$(RENDER_FILES:%=$(RENDER)%.c) $(READ_FILES:%=$(READ)%.c) \
		$(GAME_EDITOR:%=$(GAME_EDITOR_FILES)%.c)
O_FILES = $(C_FILES:%.c=%.o)

HEADERS = includes/doom.h
ADD_FILES = Makefile textures

all: $(NAME)

$(NAME): libft/libft.a bmp/lib_bmp.a $(O_FILES)
	@gcc -o $@ $(O_FILES) -L $(LIBFT) bmp/lib_bmp.a bmp/libft/libft.a -lft $(FLAGS) $(SDL_FLAGS)
	@echo "$(GREEN)[√]$(WHITE) compiling done!"

%.o: %.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) compiling $@"

libft/libft.a:
	@make -C libft

bmp/lib_bmp.a:
	@make -C bmp

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(BMP)
	@rm -f $(O_FILES)
	@echo "cleaned $(NAME) object files"

fclean: clean
	@make fclean -C $(LIBFT)
	@make fclean -C $(BMP)
	@rm -f $(NAME)
	@echo "cleaned $(NAME) binary"

re: fclean all

add: fclean
	@git add $(LIBFT) $(C_FILES) $(HEADERS) $(ADD_FILES) $(SDL) $(BMP)
	@git status

push:
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif

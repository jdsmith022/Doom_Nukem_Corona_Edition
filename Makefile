# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Malou <Malou@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/01 13:24:04 by Malou         #+#    #+#                  #
#    Updated: 2020/07/04 14:59:43 by elkanfrank    ########   odam.nl          #
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

CORE_FILES = main doom_init sdl_init  game_loop line_calculations doom_update \
				exit
EVENTS_FILES = key_events mouse_events move_position move_position2
RENDER_FILES = doom_render sidedef_render plane_projections draw_sidedef \
				draw_floor slope_projections horizontal_texture put_texture
READ_FILES = add_info_to_lib error read_file main2

C_FILES_CORE = $(CORE_FILES:%=%.c)
C_FILES_EVENTS = $(EVENTS_FILES:%=%.c)
C_FILES_RENDER = $(RENDER_FILES:%=%.c)
C_FILES_READ = $(READ_FILES:%=%.c)

O_FILES_CORE = $(CORE_FILES:%=$(CORE).objects/%.o)
O_FILES_EVENTS = $(EVENTS_FILES:%=$(EVENTS).objects/%.o)
O_FILES_RENDER = $(RENDER_FILES:%=$(RENDER).objects/%.o)
O_FILES_READ = $(READ_FILES:%=$(READ).objects/%.o)

O_FILES_DIRS = $(CORE).objects $(EVENTS).objects $(RENDER).objects $(READ).objects
O_FILES = $(O_FILES_CORE) $(O_FILES_EVENTS) $(O_FILES_RENDER) $(O_FILES_READ)

HEADERS = includes/doom.h
ADD_FILES = Makefile textures

all: $(NAME)

$(NAME): libft/libft.a bmp/lib_bmp.a $(O_FILES_DIRS) $(O_FILES)
	@gcc -o $@ $(O_FILES) -L $(LIBFT) bmp/lib_bmp.a bmp/libft/libft.a -lft $(FLAGS) $(SDL_FLAGS)
	@echo "$(GREEN)[√]$(WHITE) compiling done!"

$(CORE).objects/%.o: $(CORE)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(EVENTS).objects/%.o: $(EVENTS)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(RENDER).objects/%.o: $(RENDER)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(READ).objects/%.o: $(READ)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

%/.objects:
	@mkdir $@

libft/libft.a:
	@make -C libft

bmp/lib_bmp.a:
	@make -C bmp

clean:
	@make clean -C $(LIBFT)
	@make clean -C $(BMP)
	@rm -rf $(O_FILES_DIRS)
	@echo "cleaned $(NAME) object files"

fclean: clean
	@make fclean -C $(LIBFT)
	@make fclean -C $(BMP)
	@rm -f $(NAME)
	@echo "removed $(NAME) binary"

re: fclean all

add: fclean
	@git add $(LIBFT) $(C_FILES) $(HEADERS) $(ADD_FILES) $(SDL) $(BMP)
	@git status

push:
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif

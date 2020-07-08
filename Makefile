# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Malou <Malou@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/04/01 13:24:04 by Malou         #+#    #+#                  #
#    Updated: 2020/07/08 13:34:23 by jessicasmit   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
RED = $(shell printf "\033[0;31m")

NAME = doom
FLAGS = -Wall -Wextra -Werror

LIBFT = libft
SDL = sdl
BMP = bmp
SDL_FLAGS = `sdl2-config --cflags --libs`
LIBS = -L $(LIBFT) bmp/lib_bmp.a bmp/libft/libft.a -lSDL2_mixer -lft

CORE = srcs/core/
EVENTS = srcs/events/
RENDER = srcs/render/
READ = srcs/read_file/
EDITOR = srcs/editor/
AUDIO = srcs/audio/

CORE_FILES = main doom_init sdl_init  game_loop line_calculations doom_update \
				exit
EVENTS_FILES = key_events mouse_events move_position move_position2
RENDER_FILES = doom_render sidedef_render plane_projections draw_sidedef \
				draw_floor_and_ceiling slope_projections put_texture\
				skybox_top_bottom draw_skybox set_texture_properties
READ_FILES = add_info_to_lib error read_file main2 save_sdl malloc_lib
EDITOR_FILES = game_editor draw_bar sector sidedefs portal add_to_game \
					mouse_events_game_editor
AUDIO_FILES = audio helpers

C_FILES_CORE = $(CORE_FILES:%=%.c)
C_FILES_EVENTS = $(EVENTS_FILES:%=%.c)
C_FILES_RENDER = $(RENDER_FILES:%=%.c)
C_FILES_READ = $(READ_FILES:%=%.c)
C_FILES_EDITOR = $(EDITOR_FILES:%=%.c)
C_FILES_AUDIO = $(AUDIO_FILES:%=%.c)

O_FILES_CORE = $(CORE_FILES:%=$(CORE).objects/%.o)
O_FILES_EVENTS = $(EVENTS_FILES:%=$(EVENTS).objects/%.o)
O_FILES_RENDER = $(RENDER_FILES:%=$(RENDER).objects/%.o)
O_FILES_READ = $(READ_FILES:%=$(READ).objects/%.o)
O_FILES_EDITOR = $(EDITOR_FILES:%=$(EDITOR).objects/%.o)
O_FILES_AUDIO = $(AUDIO_FILES:%=$(AUDIO).objects/%.o)

SRCS_DIRS = $(CORE) $(EVENTS) $(RENDER) $(READ) $(EDITOR) $(AUDIO)
O_FILES_DIRS = $(SRCS_DIRS:%=%.objects)
O_FILES = $(O_FILES_CORE) $(O_FILES_EVENTS) $(O_FILES_EDITOR) \
		$(O_FILES_RENDER) $(O_FILES_READ) $(O_FILES_AUDIO)

HEADERS = includes/doom.h includes/audio.h
ADD_FILES = Makefile textures

all: $(NAME)

$(NAME): libft/libft.a bmp/lib_bmp.a $(O_FILES_DIRS) $(O_FILES)
	@gcc -o $@ $(O_FILES) $(LIBS) $(FLAGS) $(SDL_FLAGS)
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

$(EDITOR).objects/%.o: $(EDITOR)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(AUDIO).objects/%.o: $(AUDIO)%.c $(HEADERS)
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
	@git add $(LIBFT) $(HEADERS) $(ADD_FILES) $(SDL) $(BMP) \
	$(C_FILES_CORE) $(C_FILES_EVENTS) $(C_FILES_RENDER) $(C_FILES_READ) \
	$(C_FILES_EDITOR) $(C_FILES_AUDIO)
	@git status

push:
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif

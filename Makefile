GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
RED = $(shell printf "\033[0;31m")

NAME = doom
FLAGS = -Wall -Wextra -Werror

LIBFT = libft
SDL = sdl
BMP = bmp
SDL_FLAGS = `sdl2-config --cflags --libs`
LIBS = -L $(LIBFT) bmp/lib_bmp.a bmp/libft/libft.a -lSDL2_mixer -lSDL2_ttf -lft

CORE = srcs/core/
EVENTS = srcs/events/
RENDER = srcs/render/
READ = srcs/read_file/
EDITOR = srcs/editor/
AUDIO = srcs/audio/
GAMEPLAY = srcs/gameplay/
SPRITE = srcs/sprite/
DRAW = srcs/draw/
FONT = srcs/font/
HUD = srcs/hud/
MENU = srcs/menu/

CORE_FILES = main doom_init sdl_init  game_loop line_calculations doom_update \
				exit moving_sidedef free_library libs_init
EVENTS_FILES = key_events move_position move_position2 mouse_movement mouse_press 
RENDER_FILES = doom_render sidedef_render plane_projections draw_sidedef \
				draw_row slope_projections put_texture\
				draw_skybox_top_bottom draw_skybox set_texture_properties\
				render_sky_box set_offsets draw_poster action light_floor_ceiling \
				draw_floor draw_ceiling set_floor_limit get_slope \
				find_infection set_ceiling_limit set_properties_plane
READ_FILES = add_info_to_lib error read_file save_libraries save_sdl malloc_lib \
			sector_inf sidedef_inf obj_inf save_bmp_to_sdl save_sky \
			 set_texture_type
EDITOR_FILES = game_editor draw_bar sector sidedefs portal add_to_game \
				mouse_events_game_editor box_in_sector draw_edit_console \
				printing_map
AUDIO_FILES = audio playback helpers
SPRITE_FILES = sprite_check sprite_draw sprite_scale sprite_render \
				sprite_sort sprite_reset
GAMEPLAY_FILES = groceries basket node search shopping_list collect_groceries \
				init_groceries grocery_ui add_infection
DRAW_FILES = img vector
FONT_FILES = draw_font set_font_colors font_to_sdl game_editor_font \
				save_font_libraries hud_font basket_font shopping_font \
				start_menu_font setting_window_font
HUD_FILES = update_hud
MENU_FILES = start_menu mouse_settings

C_FILES_CORE = $(CORE_FILES:%=%.c)
C_FILES_EVENTS = $(EVENTS_FILES:%=%.c)
C_FILES_RENDER = $(RENDER_FILES:%=%.c)
C_FILES_READ = $(READ_FILES:%=%.c)
C_FILES_EDITOR = $(EDITOR_FILES:%=%.c)
C_FILES_AUDIO = $(AUDIO_FILES:%=%.c)
C_FILES_GAMEPLAY = $(GAMEPLAY_FILES:%=%.c)
C_FILES_SPRITE = $(SPRITE_FILES:%=%.c)
C_FILES_DRAW = $(DRAW_FILES:%=%.c)
C_FILES_FONT = $(FONT_FILES:%=%.c)
C_FILES_HUD = $(HUD_FILES:%=%.c)
C_FILES_MENU = $(MENU_FILES:%=%.c)

O_FILES_CORE = $(CORE_FILES:%=$(CORE).objects/%.o)
O_FILES_EVENTS = $(EVENTS_FILES:%=$(EVENTS).objects/%.o)
O_FILES_RENDER = $(RENDER_FILES:%=$(RENDER).objects/%.o)
O_FILES_READ = $(READ_FILES:%=$(READ).objects/%.o)
O_FILES_EDITOR = $(EDITOR_FILES:%=$(EDITOR).objects/%.o)
O_FILES_AUDIO = $(AUDIO_FILES:%=$(AUDIO).objects/%.o)
O_FILES_SPRITE = $(SPRITE_FILES:%=$(SPRITE).objects/%.o)
O_FILES_FONT = $(FONT_FILES:%=$(FONT).objects/%.o)
O_FILES_GAMEPLAY = $(GAMEPLAY_FILES:%=$(GAMEPLAY).objects/%.o)
O_FILES_DRAW = $(DRAW_FILES:%=$(DRAW).objects/%.o)
O_FILES_HUD = $(HUD_FILES:%=$(HUD).objects/%.o)
O_FILES_MENU = $(MENU_FILES:%=$(MENU).objects/%.o)

SRCS_DIRS = $(CORE) $(EVENTS) $(RENDER) $(READ) $(EDITOR) $(AUDIO) \
			$(SPRITE) $(FONT) $(GAMEPLAY) $(DRAW) $(HUD) $(MENU)
O_FILES_DIRS = $(SRCS_DIRS:%=%.objects)
O_FILES = $(O_FILES_CORE) $(O_FILES_EVENTS) $(O_FILES_EDITOR) $(O_FILES_GAMEPLAY) \
		$(O_FILES_DRAW) $(O_FILES_RENDER) $(O_FILES_READ) $(O_FILES_AUDIO) \
		$(O_FILES_SPRITE) $(O_FILES_FONT) $(O_FILES_HUD) $(O_FILES_MENU)

HEADERS = includes/doom.h includes/audio.h includes/gameplay.h includes/font.h includes/textures.h \
			includes/menu.h includes/hud.h
ADD_FILES = Makefile textures

all: $(NAME)

$(NAME): libft/libft.a bmp/lib_bmp.a $(O_FILES_DIRS) $(O_FILES)
	@make re -C $(LIBFT)
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

$(SPRITE).objects/%.o: $(SPRITE)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(FONT).objects/%.o: $(FONT)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(GAMEPLAY).objects/%.o: $(GAMEPLAY)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(DRAW).objects/%.o: $(DRAW)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(HUD).objects/%.o: $(HUD)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"
$(MENU).objects/%.o: $(MENU)%.c $(HEADERS)
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
	$(C_FILES_EDITOR) $(C_FILES_AUDIO) $(C_FILES_SPRITE) $(C_FILES_FONT) \
	$(HUD) $(MENU)
	@git status

push:
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif

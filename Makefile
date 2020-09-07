GREEN = $(shell printf "\e[38;5;10m")
WHITE = $(shell printf "\e[39m")
RED = $(shell printf "\033[0;31m")

NAME = doom-nukem
FLAGS = -g -Wall -Wextra -Werror -O3 -Wpedantic -fsanitize=address
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
ACTION = srcs/action/

CORE_FILES = main doom_init sdl_init  game_loop calculations_line calculations_point \
			doom_update exit free_library_struct free_library_sdl update_screen \
			doom_init_events doom_init_ui doom_init_window free_lists free_clip_lists
EVENTS_FILES = key_events move_position mouse_movement mouse_press \
				check_diff key_select_and_shoot
RENDER_FILES = doom_render sidedef_render plane_projections draw_sidedef \
				draw_row slope_projections put_texture put_portal_pixel \
				draw_skybox_sky draw_skybox_sidedefs \
				render_sky_box set_offsets draw_poster add_light_to_pixel \
				draw_floor draw_ceiling set_floor_limit \
				set_ceiling_limit set_properties_plane draw_window img
READ_FILES = add_info_to_lib error read_file save_libraries save_sdl malloc_lib \
			sector_inf sidedef_inf obj_inf save_bmp_to_sdl save_sky \
			 set_texture_type create_sidedef bmp_safe_exit save_player_settings_sprites
EDITOR_FILES = 	game_editor init_game_editor draw_bar draw_edit_console \
				draw_map_sidedef draw_map_sprite mouse_event_sidedef \
				mouse_events_game_editor create_sector delete_sector\
				delete_sprite create_sidedef create_sprites put_textures \
				set_sprite_values put_textures2 check_sector_in_sector \
				set_utilities check_sidedef_connection set_sprite_values_2\
				add_lists_to_lib add_lists_to_lib_sidedef add_lists_to_lib_sector\
				add_lists_to_lib_sprite add_lists_to_lib_groceries
AUDIO_FILES = audio audio_init playback helpers stop_sounds
SPRITE_FILES = sprite_check sprite_draw sprite_scale sprite_render \
				sprite_sort sprite_reset sprite_hud_draw \
				sprite_hud_scale find_prev_sectors sprite_set_player_sprites\
				sprite_light sprite_clipping sprite_collision sprite_distance\
				list_clipping set_nodes_clipping sprite_check_y_side_line
GAMEPLAY_FILES = groceries checkout basket node search shopping_list \
				 find_shelf init_groceries grocery_ui \
				 position gameplay game_over timer sprite_hit \
				 check_select_spray_sprite \
				 remove_red_virus set_sprite
FONT_FILES = draw_font set_font_colors font_to_sdl game_editor_font \
				save_font_libraries hud_font set_vanishing_box_coordinates \
				start_menu_font setting_window_font game_over_font \
				font_timer pause_font vanishing_text_box set_font_style \
				instruction_font instruction_font_2 time_difference \
				shopper_hit_font font_timer_boxes
HUD_FILES = update_hud calculate_hud_levels update_levels \
			update_list_and_basket update_timer
MENU_FILES = start_menu event_settings print_background menu_selection \
			menu_click_events finished_text print_menu print_player_sprite \
			game_over_menu
ACTION_FILES = light_switch moving_sidedef sprite_interaction \
				player_action action_handler sanitizer_refill

C_FILES_CORE = $(CORE_FILES:%=%.c)
C_FILES_EVENTS = $(EVENTS_FILES:%=%.c)
C_FILES_RENDER = $(RENDER_FILES:%=%.c)
C_FILES_READ = $(READ_FILES:%=%.c)
C_FILES_EDITOR = $(EDITOR_FILES:%=%.c)
C_FILES_AUDIO = $(AUDIO_FILES:%=%.c)
C_FILES_GAMEPLAY = $(GAMEPLAY_FILES:%=%.c)
C_FILES_SPRITE = $(SPRITE_FILES:%=%.c)
C_FILES_FONT = $(FONT_FILES:%=%.c)
C_FILES_HUD = $(HUD_FILES:%=%.c)
C_FILES_MENU = $(MENU_FILES:%=%.c)
C_FILES_ACTION = $(ACTION_FILES:%=%.c)

O_FILES_CORE = $(CORE_FILES:%=$(CORE).objects/%.o)
O_FILES_EVENTS = $(EVENTS_FILES:%=$(EVENTS).objects/%.o)
O_FILES_RENDER = $(RENDER_FILES:%=$(RENDER).objects/%.o)
O_FILES_READ = $(READ_FILES:%=$(READ).objects/%.o)
O_FILES_EDITOR = $(EDITOR_FILES:%=$(EDITOR).objects/%.o)
O_FILES_AUDIO = $(AUDIO_FILES:%=$(AUDIO).objects/%.o)
O_FILES_SPRITE = $(SPRITE_FILES:%=$(SPRITE).objects/%.o)
O_FILES_FONT = $(FONT_FILES:%=$(FONT).objects/%.o)
O_FILES_GAMEPLAY = $(GAMEPLAY_FILES:%=$(GAMEPLAY).objects/%.o)
O_FILES_HUD = $(HUD_FILES:%=$(HUD).objects/%.o)
O_FILES_MENU = $(MENU_FILES:%=$(MENU).objects/%.o)
O_FILES_ACTION = $(ACTION_FILES:%=$(ACTION).objects/%.o)

SRCS_DIRS = $(CORE) $(EVENTS) $(RENDER) $(READ) $(EDITOR) $(AUDIO) \
			$(SPRITE) $(FONT) $(GAMEPLAY) $(HUD) $(MENU) $(ACTION)
O_FILES_DIRS = $(SRCS_DIRS:%=%.objects)
O_FILES = $(O_FILES_CORE) $(O_FILES_EVENTS) $(O_FILES_EDITOR) \
		$(O_FILES_GAMEPLAY) $(O_FILES_RENDER) $(O_FILES_READ) \
		$(O_FILES_AUDIO) $(O_FILES_SPRITE) $(O_FILES_FONT) \
		$(O_FILES_HUD) $(O_FILES_MENU) $(O_FILES_ACTION)

HEADERS = includes/doom.h includes/audio.h includes/gameplay.h \
		includes/font.h  includes/textures.h includes/menu.h includes/hud.h \
		includes/action.h includes/sprites.h includes/read.h
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

$(HUD).objects/%.o: $(HUD)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(MENU).objects/%.o: $(MENU)%.c $(HEADERS)
	@$(CC) -o $@ -c $<
	@echo "$(GREEN)[+]$(WHITE) $@"

$(ACTION).objects/%.o: $(ACTION)%.c $(HEADERS)
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
	$(C_FILES_HUD) $(C_FILES_MENU) $(C_FILES_ACTION)
	@git status

push:
ifdef MSG
	@git commit -m "$(MSG)"
	@git push
endif

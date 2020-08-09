#ifndef MENU_H
# define MENU_H

typedef	struct s_doom	t_doom;

typedef struct			s_menu {
	bool				menu;
	bool				start;
	bool				game_over;
	bool				game_editor;
	bool				settings;
	bool				retry;
}						t_menu;

void					doom_start(t_doom *doom);
void					mouse_settings(t_doom *doom);
void					instruction_window(t_doom *doom);
void					print_background(t_doom *doom, Uint32 color);
void					check_levels_and_time(t_doom *doom);

#endif
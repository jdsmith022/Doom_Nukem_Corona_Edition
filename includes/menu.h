#ifndef MENU_H
# define MENU_H

# include "../libft/libft.h"

typedef	struct s_doom	t_doom;

typedef struct	s_menu {
	int			menu;
	int			start;
	int			game_editor;
	int			settings;
}				t_menu;

void				doom_start(t_doom *doom);
void				mouse_settings(t_doom *doom, double dt);

#endif
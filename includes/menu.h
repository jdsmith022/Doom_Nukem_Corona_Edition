#ifndef MENU_H
# define MENU_H

# include "../libft/libft.h"

typedef	struct s_doom	t_doom;

typedef struct	s_menu {
	int			menu;
	int			start;
	int			game_editor;
	int			game_play;
}				t_menu;

void				doom_start(t_doom *doom);
// void				set_up_menu(t_doom *doom);

#endif
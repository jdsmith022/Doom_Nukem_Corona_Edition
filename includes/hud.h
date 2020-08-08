#ifndef HUD_H
# define HUD_H

typedef	struct s_doom	t_doom;

typedef struct	s_hud
{
	int			sanitizer;
	int			corona;
}				t_hud;

void		update_hud(t_doom *doom);

#endif
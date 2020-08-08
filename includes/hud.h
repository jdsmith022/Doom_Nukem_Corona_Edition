#ifndef HUD_H
# define HUD_H

typedef	struct s_doom	t_doom;

typedef struct	s_hud
{
	int			sanitizer;
	int			facemask;
	int			health_pack;
	int			health_pack_plus;
	int			shopper;
	int			corona;
	int			time;
	bool		start;
}				t_hud;

void		update_hud(t_doom *doom);

#endif
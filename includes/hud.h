#ifndef HUD_H
# define HUD_H

typedef	struct s_doom	t_doom;

typedef struct	s_hud
{
	bool		sanitizer;
	bool		facemask;
	bool		health_pack;
	bool		health_pack_plus;
	bool		shopper;
	bool		corona;
	bool		start;
	int			time;
}				t_hud;

void		update_hud(t_doom *doom);

#endif
#ifndef HUD_H
# define HUD_H

typedef	struct s_doom	t_doom;

typedef struct	s_hud
{
	bool		sanitizer;
	bool		sanitizer_shooting;
	bool		facemask;
	bool		health_pack;
	bool		health_pack_plus;
	bool		shopper;
	bool		corona;
	bool		start;
	int			time;
	Uint32		corona_level;
	Uint32		sanitizer_level;
}				t_hud;

void			update_hud(t_doom *doom);
void			update_hud_levels(t_doom *doom, t_font *lib);
void			calculate_hud_levels(t_doom *doom);

#endif
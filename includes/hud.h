#ifndef HUD_H
# define HUD_H

# define SCISSOR 28
# define SPRAY_HAND 29
# define SPRAYING_HAND 30
# define TROLLEY 33

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
	bool		boxes;
	bool		start;
	int			hold_time;
	int			curr_time;
	Uint32		corona_level;
	Uint32		sanitizer_level;
}				t_hud;

void			update_hud(t_doom *doom);
void			update_hud_levels(t_doom *doom, t_font *lib);
int				calculate_hud_levels(t_doom *doom);
void			update_timer(t_doom *doom, t_font *lib);
void			update_list_and_basket(t_doom *doom);

#endif